#include "include/benchmarks.h"
#include <math.h>

void bench_output(const bench_t *const b, FILE* out){
    fprintf(out, 
            "========================== Benchmarks ========================\n"
            "Sample size k    = %-12d\n"
            "Max iterations   = %-12d ----> Performed : %-12d\n"
            "Required P-value = %.10f ----> Obtained  : %.10f\n"
            "Confidence interval : %.10f +- %.10f sec\n"
            "Standard deviation  : %.10f\n"
            "==============================================================\n",
            b->k, b->maxiter, b->put, b->pval, b->peff, b->avg, b->ci, sqrt(b->var)
    );
}
