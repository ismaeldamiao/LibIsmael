/*
cc test_random.c -lm -o test_random && time ./test_random
*/
#include "libismael/ismael.h"

#if (__STDC_VERSION__ >= 201112L) /* ISO C11 */
   #define alloc(size, type) \
   (type*)aligned_alloc(sizeof(type), (size_t)size * sizeof(type))
#else
   #define alloc(size, type) \
   (type*)malloc((size_t)size * sizeof(type))
#endif /* ISO C11 */

int main(void){
   int Q;
   uint64_t seed;
   double *rand, **pdf, correlation, partitions;
   FILE *fil;
   partitions = 400;

   /* Quantitie of random numbers to generate */
   Q = 1000000;
   rand = alloc(Q, double);

   /* Seed of random number generator */
   seed = 2;

   /* Generate random numbers */
   for(int i = 0; i < Q; ++i) rand[i] = ismael.random.mt64(&seed);

   /* Compute the Function Density Probability Function and save the values
      in a file. */
   pdf = ismael.FDP(rand, Q, partitions);
   fil = fopen("random.dat", "w");
   for(int i = 0; i < partitions; ++i)
   fprintf(fil, "%g %g\n", pdf[0][i], pdf[1][i]);
   fclose(fil);
   free(rand);

   /* Now generate correlated random numbers and repeat the other process */
   correlation = 1.0;
   rand = ismael.random.distance(correlation, Q, seed);
   pdf = ismael.FDP(rand, Q, partitions);
   fil = fopen("random1.dat", "w");
   for(int i = 0; i < partitions; ++i)
   fprintf(fil, "%g %g\n", pdf[0][i], pdf[1][i]);
   fclose(fil);
   free(rand);

   correlation = 0.1;
   rand = ismael.random.bernoulli(correlation, Q, seed);
   pdf = ismael.FDP(rand, Q, partitions);
   fil = fopen("random2.dat", "w");
   for(int i = 0; i < partitions; ++i)
   fprintf(fil, "%g %g\n", pdf[0][i], pdf[1][i]);
   fclose(fil);
   free(rand);

   correlation = 1.0;
   rand = ismael.random.fourier(correlation, Q, seed);
   pdf = ismael.FDP(rand, Q, partitions);
   fil = fopen("random3.dat", "w");
   for(int i = 0; i < partitions; ++i)
   fprintf(fil, "%g %g\n", pdf[0][i], pdf[1][i]);
   fclose(fil);
   free(rand);

   return 0;
}

#include "libismael/ismael.c"
