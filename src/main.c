#include <stdio.h>
#include <stdlib.h>
#include "include/benchmarks.h"


int main(void){

    srand(time(NULL));

    bench_t* b = init_bench(100, 0.05, 1000);

    float* v1 = malloc(1000000*sizeof(float));
    float* v2 = malloc(1000000*sizeof(float));
    float* v3 = malloc(1000000*sizeof(float));

    do {
        bench_start_measure(b);

        for (int i = 0; i < 1000000; ++i) v3[i] = v1[i] + v2[i];

        bench_status = bench_stop_measure(b);
    } while (bench_status == BENCH_CONTINUE);

    free(v1);
    free(v2);
    free(v3);

    return EXIT_SUCCESS;
}
