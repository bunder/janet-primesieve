/*
 * Janet bindings for primesieve library.
 *
 * SPDX-License-Identifier: MIT
 */

#include <primesieve.h>
#include <janet.h>

static inline void check_double(const double x, const char *name) {
    if (x < 0 || x > JANET_INTMAX_DOUBLE)
        janet_panicf("%s (%f) is out of range [0; int-max]", name, x);
}

static Janet primes(int32_t argc, Janet *argv) {
    janet_arity(argc, 1, 2);

    double start = argc == 1 ? 0 : janet_getnumber(argv, 0);
    double stop = janet_getnumber(argv, argc - 1);

    check_double(start, "start");
    check_double(stop, "stop");

    size_t size;
    uint64_t *primes = primesieve_generate_primes((uint64_t)start, (uint64_t)stop,
                                                  &size, UINT64_PRIMES);

    if (size > INT32_MAX)
        janet_panic("number of primes is higher than maximum array length");

    JanetArray *a = janet_array(size);
    for (size_t i = 0; i < size; i++)
        janet_array_push(a, janet_wrap_number(primes[i]));

    primesieve_free(primes);

    return janet_wrap_array(a);
}

static Janet nprimes(int32_t argc, Janet *argv) {
    janet_arity(argc, 1, 2);

    double n = janet_getnumber(argv, 0);
    double start = argc == 1 ? 0 : janet_getnumber(argv, 1);

    if (n < 0 || !janet_checkintrange(n))
        janet_panicf("n (%f) is not integer or out of range [0; int32-max]", n);

    check_double(start, "start");

    uint64_t *primes = primesieve_generate_n_primes(n, start, UINT64_PRIMES);

    if (primes[(uint32_t)n - 1] > JANET_INTMAX_INT64)
        janet_panic("at least one prime is bigger than int-max");

    JanetArray *a = janet_array(n);
    for (size_t i = 0; i < n; i++)
        janet_array_push(a, janet_wrap_number(primes[i]));

    primesieve_free(primes);

    return janet_wrap_array(a);
}

static Janet nth_prime(int32_t argc, Janet *argv) {
    janet_arity(argc, 1, 2);

    double n = janet_getnumber(argv, 0);
    double start = argc == 1 ? 0 : janet_getnumber(argv, 1);

    if (n < 0 || !janet_checkint64range(n))
        janet_panicf("n (%f) is not integer or out of range [0; int-max]", n);

    check_double(start, "start");

    uint64_t prime = primesieve_nth_prime(n, start);
    if (prime == PRIMESIEVE_ERROR)
        janet_panic("primesieve error");

    if (prime > JANET_INTMAX_INT64)
        janet_panic("prime is bigger than int-max");

    return janet_wrap_number(prime);
}

#define DEFINE_COUNT_FUNCTION(suffix) \
static Janet count_##suffix(int32_t argc, Janet *argv) { \
    janet_arity(argc, 1, 2); \
    double start = argc == 1 ? 0 : (uint64_t)janet_getnumber(argv, 0); \
    double stop = (uint64_t)janet_getnumber(argv, argc - 1); \
    check_double(start, "start"); check_double(stop, "stop"); \
    uint64_t count = primesieve_count_##suffix(start, stop); \
    return janet_wrap_number(count); \
}

DEFINE_COUNT_FUNCTION(primes);
DEFINE_COUNT_FUNCTION(twins);
DEFINE_COUNT_FUNCTION(triplets);
DEFINE_COUNT_FUNCTION(quadruplets);
DEFINE_COUNT_FUNCTION(quintuplets);
DEFINE_COUNT_FUNCTION(sextuplets);

static Janet version(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);

    return janet_cstringv(primesieve_version());
}

static const JanetReg cfuns[] = {
    { "primes", primes,
      "(primesieve/primes [start] stop)\n\n"
      "Get an array with the primes inside the interval [start, stop].\n"
      "start=0 if not specified." },
    { "nprimes", nprimes,
      "(primesieve/nprimes n [start])\n\n"
      "Get an array with the first n primes >= start.\n"
      "start=0 if not specified." },
    { "nth-prime", nth_prime,
      "(primesieve/nth-prime n [start])\n\n"
      "Find the n-th prime" },
    { "count-primes", count_primes,
      "(primesieve/count-primes [start] stop)\n\n"
      "Count the primes within the interval [start, stop].\n"
      "start=0 if not specified." },
    { "count-twins", count_twins,
      "(primesieve/count-twins [start] stop)\n\n"
      "Count the twin primes within the interval [start, stop].\n"
      "start=0 if not specified." },
    { "count-triplets", count_triplets,
      "(primesieve/count-triplets [start] stop)\n\n"
      "Count the prime triplets within the interval [start, stop].\n"
      "start=0 if not specified." },
    { "count-quadruplets", count_quadruplets,
      "(primesieve/count-quadruplets [start] stop)\n\n"
      "Count the prime quadruplets within the interval [start, stop].\n"
      "start=0 if not specified." },
    { "count-quintuplets", count_quintuplets,
      "(primesieve/count-quintuplets [start] stop)\n\n"
      "Count the prime quintuplets within the interval [start, stop].\n"
      "start=0 if not specified." },
    { "count-sextuplets", count_sextuplets,
      "(primesieve/count-sextuplets [start] stop)\n\n"
      "Count the prime sextuplets within the interval [start, stop].\n"
      "start=0 if not specified." },
    { "version", version,
      "(primesieve/version)\n\n"
      "Get primesieve library version number as a string" },
    { /* sentinel */}
};

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "primesieve", cfuns);
}
