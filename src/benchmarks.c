#include "include/student_t.h"
#include "include/benchmarks.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global status
bench_status_et bench_status = BENCH_NOT_STARTED;

bench_t* init_bench(int k, double pval, int maxiter){
    
    bench_t* ret = calloc(1, sizeof(bench_t));
    ret->k = k;
    ret->put = 0;
    ret->maxiter = maxiter;
    ret->times = calloc(k, sizeof(double));
    ret->pval = pval;
    ret->avg = 0.0;
    ret->var = 0.0;
    ret->t = t_k_gamma(pval, k);
    ret->c = calloc(1, sizeof(chrono_t));
    ret->ci = 0.0;

    return ret;
}

void destroy_bench(bench_t* restrict bench){
    free(bench->times);
    free(bench->c);
    free(bench);
}

void bench_start_measure(bench_t* b){
    timespec_get(&(b->c->t0), TIME_UTC);
}


bench_status_et bench_stop_measure(bench_t* b){
    timespec_get(&(b->c->t1), TIME_UTC);

    const double old_sample = b->times[b->put % b->k];
    const double sample = (b->c->t1.tv_sec - b->c->t0.tv_sec) + (b->c->t1.tv_nsec - b->c->t0.tv_nsec)*1e-9;

    double old_avg = b->avg; // Current avg
    double add_avg = (b->k * b->avg + sample ) / (b->k+1); // Average as if we added the sample
    double upd_avg = b->avg + (sample - old_sample)/b->k; // Updated average
    
    // Online computation of variance
    b->var += (sample + old_sample - 2.0*add_avg)*(sample - old_sample)/(b->k-1)
            + b->k*(old_avg + upd_avg - 2.0*add_avg)*(old_avg - upd_avg)/(b->k-1);

    // Update time in the circular buffer
    b->times[b->put++ % b->k] = sample;
    b->avg = upd_avg;
    b->ci = sqrt(b->var / b->k) * b->t;
    b->peff = b->ci / b->avg;

    if (b->put < b->k) return BENCH_CONTINUE; // Not enough samples
    printf("Avg: %f, std: %f, p_eff = %f, ci = %f\n", b->avg, sqrt(b->var), b->peff, b->ci);
    if (b->peff <= b->pval) return BENCH_FINISHED; // P-value reached
    if (b->put >= b->maxiter) return BENCH_MAX_ITER; // Maxiter reached

    // Stopping conditions not reached, continue
    return BENCH_CONTINUE;
}
