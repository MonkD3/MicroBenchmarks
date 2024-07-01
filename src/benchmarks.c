#include "include/student_t.h"
#include <stdlib.h>

typedef struct {
    int k;      // Number of sample
    double *times; // Recorded times for each sample
    int put;    // Current index in times
    double pval;   // Target P-value
    double mean;   // Current mean
    double t;      // Student-T parameter
} bench_t;

bench_t* init_bench(int k, double pval){
    
    bench_t* ret = (bench_t*) calloc(1, sizeof(bench_t));
    ret->k = k;
    ret->times = (double*) calloc(k, sizeof(double));
    ret->put = 0;
    ret->pval = pval;
    ret->mean = 0.0;
    ret->t = t_k_gamma(pval, k);

    return ret;
}

void destroy_bench(bench_t* restrict bench){
    free(bench->times);
    free(bench);
}
