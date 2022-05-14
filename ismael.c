/*
gcc -std=c99 -g -c ismael.c -o libismael.o
*/
#include "./ismael.h"


#include "./src/atoc.c"
#include "./src/FDP.c"
#include "./src/correlated_w_bernoulli.c"
#include "./src/correlated_w_distance.c"
#include "./src/correlated_w_fourier.c"
#include "./src/rand.c"
#if defined(UINT64_MAX)
# include "./src/MT19937_64.c"
#endif
#if defined(UINT32_MAX)
# include "./src/MT19937_32.c"
#endif
#include "./src/erro.c"

const __ismael_namespace ismael = {
#include "./src/rk14.c"
#include "./src/rk8.c"
   .random.mt64 = mt19937_64,
   .random.mt32 = mt19937_32,
   .random.system = system_rand,
   .random.bernoulli = correlated_w_bernoulli,
   .random.distance = correlated_w_distance,
   .random.fourier = correlated_w_fourier,
   .atoc = atoc,
   .FDP = FDP,
   .error = error
};
