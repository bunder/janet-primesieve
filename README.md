# [primesieve](https://github.com/kimwalisch/primesieve) bindings for Janet

## Install

Make sure _primesieve_ library is installed in your system.

```
jpm install https://github.com/bunder/janet-primesieve.git
```

## Source

You can get the source on [GitHub](https://github.com/bunder/janet-primesieve).

## Example

```
(import primesieve)

(print (sum (primesieve/primes 2000000)))
```
