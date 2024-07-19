# MicroBenchmarks

## Who is this for ?

This small library is for people like me who ...

- Are often timing parts of C code
- Always rewrite the same functions to time their code

## Dependencies 

- Autotools (Autoconf, Automake, ...)
- M4
- CUnit
- A `C` compiler

## Quickstart

Benchmarking functions/snippets is as simple as :

```c 
int k = number_of_samples;
int maxiter = max_iterations;
double pval = target_p_value;
bench_t* b = bench_init(k, maxiter, pval);

do {
    // Benchmark setup here, not timed 
    // ...
    bench_start_measure(b);
    // Benchmark what is here
    // ...
} while (bench_stop_measure(b) == BENCH_CONTINUE);

if (b->status == BENCH_MAX_ITER){
    // The benchmark was not statistically consistent
    // you can retrieve the effective p-value in b->peff
}
else {
    // Get the info you need
}

bench_destroy(b);
```

Afterwards, you can access the following properties for your benchmark :

- Average time: `avg`
- Variance: `var`
- Effective p-value: `peff`
- Confidence interval: `ci`. Note that this is *technically* not the confidence interval but rather the half-amplitude of the CI.

The real CI can be computed as `[avg - ci; avg + ci]`. There is a probability `1 - peff` that a measure will belong to this interval. 

In mathematical terms, if $T$ is the random variable representing the time taken by a single run of your function/snippet, with mean $\bar{T}$ then :

$$ \mathbb{P}[\bar{T} - ci < \bar{T} + ci] <= 1 - p_{eff} $$

## How to compile

### From source 

```bash 
git clone https://github.com/MonkD3/MicroBenchmarks && cd MicroBenchmarks
autoreconf --install
./configure
make
make install
```

## References 

The benchmarking method is adapted from the following source(s).

> Andy Georges, Dries Buytaert, and Lieven Eeckhout. 2007. Statistically rigorous java performance evaluation. SIGPLAN Not. 42, 10 (October 2007), 57–76. https://doi.org/10.1145/1297105.1297033
