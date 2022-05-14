/* *****************************************************************************
   A C99 implementation of

   *** Mersenne Twister -- pseudorandom number generator ***

   This program generate pseudorandom numbers (deterministically) based on
   Makoto Matsumoto and Takuji Nishimura algorithm developed in 1997. This
   work based in the Mersenne prime (2^19937 - 1).

   The funcion mt19937_32 return a pseudorandom double number
   uniformly distributed on [0, 1) interval, for each call.
   The only one parameter is a pointer to 32 bit integer, at the first call the
   integer need to be the (nonzero) seed that initialize the generator and,
   for each call, this get the value of a pseudorandom 32 bit integer.

   References:
   * M. Matsumoto and T. Nishimura,
     "Mersenne Twister: A 623-Dimensionally Equidistributed Uniform
     Pseudo-Random Number Generator", ACM Transactions on Modeling and
     Computer Simulation, Vol. 8, No. 1, January 1998, pp 3--30.
   *****************************************************************************
   E-mail: ismaellxd@gmail.com
   Site: https://ismaeldamiao.github.io/
   *****************************************************************************
   Copyright (c) 2021 I.F.F. dos SANTOS

   Permission is hereby granted, free of charge, to any person obtaining a copy 
   of this software and associated documentation files (the “Software”), to 
   deal in the Software without restriction, including without limitation the 
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
   sell copies of the Software, and to permit persons to whom the Software is 
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in 
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
   IN THE SOFTWARE.
***************************************************************************** */
#include <stdint.h> /* Use C99 or latter */

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A UINT32_C(0x9908b0df) /* constant vector a */
#define UPPER_MASK UINT32_C(0x80000000) /* most significant w-r bits */
#define LOWER_MASK UINT32_C(0x7fffffff) /* least significant r bits */
/* Tempering parameters */
#define TEMPERING_MASK_B UINT32_C(0x9d2c5680)
#define TEMPERING_MASK_C UINT32_C(0xefc60000)
#define TEMPERING_U 11
#define TEMPERING_S 7
#define TEMPERING_T 15
#define TEMPERING_L 18

/* This function combines the top bit of x with the bottom 63 bits of y. */
#define COMBINE_BITS(x, y) (((x) & UPPER_MASK) | ((y) & LOWER_MASK))
/* This one does the magic scrambling function. */
#define MATRIX_MULTIPLY(original, new) \
((original) ^ ((new) >> 1) ^ mag01[(int)((new) & UINT64_C(0x1))])

double mt19937_32(uint32_t *y){
   int i;
   const int N1 = N-1, NM = N-M, MN = M-N;
   static uint32_t mt[N]; /* the array for the state vector */
   static int mti = N+1; /* mti==N+1 means mt[N] is not initialized */
   static uint32_t mag01[2] = {0x0, MATRIX_A};

   /* The following routine generate N words at one time */
   if(mti >= N){

      /* If mti == N+1 then the function is called by the first time and the
         array mt[] need to be initialized.
         The value pointed by 'y' in the firt call
         is the seed of generator, if this value is 0 then set it to 1999. */
      if(mti == N+1){ /* initializing the array with NONZERO seed */

         if((*y) == UINT32_C(0)) *y = UINT32_C(1999);
         mt[0] = (*y) & UINT32_C(0xffffffff);
         for(mti = 1; mti < N; ++mti)
            mt[mti] = (69069 * mt[mti-1]) & UINT32_C(0xffffffff);
      }

      /* With the array mt[] already initialized, generate the words. */
      for(i = 0; i < NM; ++i){
         *y = COMBINE_BITS(mt[i], mt[i+1]);
         mt[i] = MATRIX_MULTIPLY(mt[i+M], *y);
      }
      for(; i < N1; ++i){
         *y = COMBINE_BITS(mt[i], mt[i+1]);
         mt[i] = MATRIX_MULTIPLY(mt[i + (MN)], *y);
      }
      *y = COMBINE_BITS(mt[i], mt[0]);
      mt[N-1] = MATRIX_MULTIPLY(mt[M-1], *y);
      mti = 0;
   }

   /* Extract tempered value of mt[mti]. */
   *y = mt[mti];
   *y ^= ((*y) >> TEMPERING_U);
   *y ^= ((*y) << TEMPERING_S) & TEMPERING_MASK_B;
   *y ^= ((*y) << TEMPERING_T) & TEMPERING_MASK_C;
   *y ^= ((*y) >> TEMPERING_L);
   ++mti;

   return ((double)(*y) / (double)UINT32_MAX);
}
#undef N
#undef M
#undef MATRIX_A
#undef UPPER_MASK
#undef LOWER_MASK
#undef TEMPERING_MASK_B
#undef TEMPERING_MASK_C
#undef TEMPERING_U
#undef TEMPERING_S
#undef TEMPERING_T
#undef TEMPERING_L
#undef COMBINE_BITS
#undef MATRIX_MULTIPLY
