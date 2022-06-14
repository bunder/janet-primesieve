(import primesieve)

(print "Testing (primesieve/version)...")
(def ver (primesieve/version))
(assert (string? ver) "(primesieve/version) returns string")
(assert (not (empty? ver)) "(primesieve/version) returns non-empty string")

(print "Testing (primesieve/primes)...")
(assert (deep= @[2 3 5 7] (primesieve/primes 10)))
(assert (deep= @[53 59 61 67] (primesieve/primes 50 70)))
(assert (deep= @[53 59 61 67] (primesieve/primes 53 67)))

(print "Testing (primesieve/nprimes)...")
(assert (deep= @[2 3 5 7 11] (primesieve/nprimes 5)))
(assert (deep= @[53 59 61 67] (primesieve/nprimes 4 50)))
(assert (deep= @[53 59 61 67] (primesieve/nprimes 4 53)))

(print "Testing (primesieve/nth-prime)...")
(assert (= 11 (primesieve/nth-prime 5)))
(assert (= 67 (primesieve/nth-prime 4 50)))
(assert (= 67 (primesieve/nth-prime 3 53)))

(print "Testing (primesieve/count-primes) and friends...")
(assert (= 1229 (primesieve/count-primes 10001)))
(assert (= 8363 (primesieve/count-primes 10001 100001)))

(assert (= 205 (primesieve/count-twins 10001)))
(assert (= 112 (primesieve/count-triplets 10001)))
(assert (= 12 (primesieve/count-quadruplets 10001)))
(assert (= 9 (primesieve/count-quintuplets 10001)))
(assert (= 2 (primesieve/count-sextuplets 10001)))
