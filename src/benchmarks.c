#include "include/student_t.h"
#include "include/benchmarks.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bench_t* bench_init(int const k, int const maxiter, double const pval){
    bench_t * const ret = calloc(1, sizeof(bench_t));

    ret->k = k;
    ret->put = 0;
    ret->maxiter = maxiter;
    ret->status = BENCH_NOT_STARTED;
    ret->times = calloc(k, sizeof(double));
    ret->pval = pval;
    ret->peff = 1.0;
    ret->avg = 0.0;
    ret->var = 0.0;
    ret->t = t_k_gamma(pval, k-1.0);
    ret->c = calloc(1, sizeof(chrono_t));
    ret->ci = 0.0;

    return ret;
}

void bench_destroy(bench_t* restrict b){
    free(b->times);
    free(b->c);
    free(b);
}

void bench_reset(bench_t* const b){
    b->put = 0;
    b->status = BENCH_NOT_STARTED;
    // Reset times to 0
    memset(b->times, 0, b->k * sizeof(b->times[0]));
    b->peff = 1.0;
    b->avg = 0.0;
    b->var = 0.0;
    b->ci = 0.0;
}

void bench_start_measure(bench_t* const b){
    timespec_get(&(b->c->t0), TIME_UTC);
}


bench_status_et bench_stop_measure(bench_t* const b){
    timespec_get(&(b->c->t1), TIME_UTC);

    double const old_sample = b->times[b->put % b->k];
    double const sample = (b->c->t1.tv_sec - b->c->t0.tv_sec) + (b->c->t1.tv_nsec - b->c->t0.tv_nsec)*1e-9;

    double const old_avg = b->avg; // Current avg
    double const add_avg = (b->k * b->avg + sample ) / (b->k+1); // Average as if we added the sample
    double const upd_avg = b->avg + (sample - old_sample)/b->k; // Updated average
    
    // Online computation of variance
    b->var += (sample + old_sample - 2.0*add_avg)*(sample - old_sample)/(b->k-1)
            + b->k*(old_avg + upd_avg - 2.0*add_avg)*(old_avg - upd_avg)/(b->k-1);

    // Update time in the circular buffer
    b->times[b->put++ % b->k] = sample;
    b->avg = upd_avg;
    b->ci = sqrt(b->var / b->k) * b->t;
    b->peff = b->ci / b->avg;

    if (b->put < b->k) return (b->status = BENCH_CONTINUE); // Not enough samples
    if (b->peff <= b->pval) return (b->status = BENCH_FINISHED); // P-value reached
    if (b->put >= b->maxiter) return (b->status = BENCH_MAX_ITER); // Maxiter reached

    // Stopping conditions not reached, continue
    return (b->status = BENCH_CONTINUE);
}
