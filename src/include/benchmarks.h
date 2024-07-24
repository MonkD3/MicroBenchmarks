#ifndef BENCHMARKS_H
#define BENCHMARKS_H
#include <time.h>

typedef enum {
    BENCH_FINISHED    = 0,
    BENCH_MAX_ITER    = 1,
    BENCH_CONTINUE    = 2,
    BENCH_NOT_STARTED = 3,
} bench_status_et;

typedef struct {
    struct timespec t0;
    struct timespec t1;
} chrono_t;

typedef struct {
    int             k;        // Number of samples (dof)
    int             put;      // Current index in times
    int             maxiter;  // Maximum number of iterations
    bench_status_et status;   // Status of the benchmark
    double*         times;    // Recorded time for each sample
    double          pval;     // Target P-value
    double          peff;     // Effective P-value
    double          avg;      // Current mean
    double          var;      // Current variance
    double          t;        // Student-T parameter
    double          ci;       // Confidence interval
    chrono_t*       c;        // Chronometer
} bench_t;

__attribute__((nonnull(1))) void bench_destroy(bench_t* b);

__attribute__((malloc, malloc(bench_destroy, 1))) bench_t* bench_init(int const    k,
                                                                      int const    maxiter,
                                                                      double const pval);

__attribute__((nonnull(1))) void bench_reset(bench_t* const b);

__attribute__((nonnull(1))) void bench_start_measure(bench_t* const b);

__attribute__((nonnull(1))) bench_status_et bench_stop_measure(bench_t* const b);

#ifdef BENCHMARK
#define BENCH_START(b) \
    do {               \
        bench_start_measure(b);

#define BENCH_STOP(b)          \
        bench_stop_measure(b); \
    } while (BENCH_CONTINUE == b->status);
#else
#pragma message("The benchmarking macros BENCH_START() and BENCH_STOP() are disabled.\n \
          If you wish to enable them, use the compiler flag -DBENCHMARK")
#define BENCH_START(b)
#define BENCH_STOP(b)
#endif

#endif  // BENCHMARKS_H
