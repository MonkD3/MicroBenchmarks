#ifndef BENCHMARKS_H
#define BENCHMARKS_H
#include <time.h>

typedef enum {
    BENCH_FINISHED = 0,
    BENCH_MAX_ITER = 1,
    BENCH_CONTINUE = 2,
    BENCH_NOT_STARTED = 3,
} bench_status_et;

typedef struct {
    struct timespec t0;
    struct timespec t1;
} chrono_t;

typedef struct {
    int k;         // Number of samples (dof)
    int put;       // Current index in times
    int maxiter;   // Maximum number of iterations
    bench_status_et status; // Status of the benchmark
    double *times; // Recorded time for each sample
    double pval;   // Target P-value
    double peff;   // Effective P-value
    double avg;    // Current mean
    double var;    // Current variance
    double t;      // Student-T parameter
    double ci;     // Confidence interval
    chrono_t* c;   // Chronometer
} bench_t;

bench_t* bench_init(int k, int maxiter, double pval);
void bench_destroy(bench_t* b);

void bench_start_measure(bench_t* b);
bench_status_et bench_stop_measure(bench_t* b);

#endif // BENCHMARKS_H
