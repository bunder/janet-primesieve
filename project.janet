(declare-project
  :name "primesieve"
  :description "Fast prime number generator"
  :author "Anton Leontiev <scileont@gmail.com>"
  :license "MIT"
  :url "https://github.com/bunder/janet-primesieve"
  :repo "https://github.com/bunder/janet-primesieve.git")

(declare-native
  :name "primesieve"
  :source ["primesieve.c"]
  :lflags ["-lprimesieve"])
