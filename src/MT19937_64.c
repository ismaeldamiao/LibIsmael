/* *****************************************************************************
   A C99 implementation of

   *** Mersenne Twister -- pseudorandom number generator ***

   This program generate pseudorandom numbers (deterministically) based on
   Makoto Matsumoto and Takuji Nishimura algorithm developed in 1997. This
   work based in the Mersenne prime (2^19937 - 1).

   The funcion mt19937_64 return a pseudorandom double number
   uniformly distributed on [0, 1) interval, for each call.
   The only one parameter is a pointer to 64 bit integer, at the first call the
   integer need to be the (nonzero) seed that initialize the generator and,
   for each call, this get the value of a pseudorandom 64 bit integer.

   References:
   * M. Matsumoto and T. Nishimura,
     "Mersenne Twister: A 623-Dimensionally Equidistributed Uniform
     Pseudo-Random Number Generator", ACM Transactions on Modeling and
     Computer Simulation, Vol. 8, No. 1, January 1998, pp 3--30.
   * T. Nishimura,
     "Tables of 64-bit Mersenne Twisters", ACM Transactions on Modeling and
     Computer Simulation, Vol. 10, No 4, October 2000, Pages 348 –357.
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
#define N 312
#define M0 63
#define M1 151
#define M2 224
#define MATRIX_A UINT64_C(0xB3815B624FC82E2F) /* constant vector a */
#define UPPER_MASK (UINT64_C(0xffffffff80000000)) /* most significant w-r bits */
#define LOWER_MASK (UINT64_C(0x7fffffff)) /* least significant r bits */
/* Tempering parameters */
#define TEMPERING_MASK_B UINT64_C(0x599CFCBFCA660000)
#define TEMPERING_MASK_C UINT64_C(0xFFFAAFFE00000000)
#define TEMPERING_U 26
#define TEMPERING_S 17
#define TEMPERING_T 33
#define TEMPERING_L 39

/* This function combines the top bit of x with the bottom 63 bits of y. */
#define COMBINE_BITS(x, y) (((x) & UPPER_MASK) | ((y) & LOWER_MASK))

double mt19937_64(uint64_t *y){
   int i;
   const int N1 = N-1, NM2 = N-M2, NM1 = N-M1, NM0 = N-M0,
   M2N = M2-N, M1N = M1-N, M0N = M0-N;
   static uint64_t mt[N]; /* the array for the state vector */
   static int mti = N+1; /* mti==N+1 means mt[N] is not initialized */
   static uint64_t mag01[2] = {0x0, MATRIX_A};

   /* The following routine generate N words at one time */
   if(mti >= N){

      /* If mti == N+1 then the function is called by the first time and the
         array mt[] need to be initialized.
         The value pointed by 'y' in the firt call
         is the seed of generator, if this value is 0 then set it to 1999. */
      if(mti == N+1){ /* initializing the array with NONZERO seed */
         uint64_t ux, lx;
         if((*y) == UINT64_C(0)) *y = UINT64_C(1999);
         for(mti = 0; mti < N; ++mti){
            ux = (*y) & UINT64_C(0xFFFFFFFF00000000);
            *y = UINT64_C(2862933555777941757) * (*y) + UINT64_C(1);
            lx = (*y) >> 32;
            *y = UINT64_C(2862933555777941757) * (*y) + UINT64_C(1);
            mt[mti] = ux | lx;
         }
      }

      /* With the array mt[] already initialized, generate the words. */
      for(i = 0; i < NM2; ++i){
         *y = COMBINE_BITS(mt[i], mt[i+1]);
         mt[i] = ((*y) >> 1) ^ mag01[(int)((*y) & UINT64_C(1))];
         mt[i] ^= mt[i+M0] ^ mt[i+M1] ^ mt[i+M2];
      }
      for(; i < NM1; ++i){
         *y = COMBINE_BITS(mt[i], mt[i+1]);
         mt[i] = ((*y) >> 1) ^ mag01[(int)((*y) & UINT64_C(1))];
         mt[i] ^= mt[i+M0] ^ mt[i+M1] ^ mt[i+M2N];
      }
      for(; i < NM0; ++i){
         *y = COMBINE_BITS(mt[i], mt[i+1]);
         mt[i] = ((*y) >> 1) ^ mag01[(int)((*y) & UINT64_C(1))];
         mt[i] ^= mt[i+M0] ^ mt[i+M1N] ^ mt[i+M2N];
      }
      for(; i < N1; ++i){
         *y = COMBINE_BITS(mt[i], mt[i+1]);
         mt[i] = ((*y) >> 1) ^ mag01[(int)((*y) & UINT64_C(1))];
         mt[i] ^= mt[i+M0N] ^ mt[i+M1N] ^ mt[i+M2N];
      }
      *y = COMBINE_BITS(mt[i], mt[0]);
      mt[i] = ((*y) >> 1) ^ mag01[(int)((*y) & UINT64_C(1))];
      mt[i] ^= mt[M0-1] ^ mt[M1-1] ^ mt[M2-1];
      mti = 0;
   }

   /* Extract tempered value of mt[mti]. */
   *y = mt[mti];
   *y ^= ((*y) >> TEMPERING_U);
   *y ^= ((*y) << TEMPERING_S) & TEMPERING_MASK_B;
   *y ^= ((*y) << TEMPERING_T) & TEMPERING_MASK_C;
   *y ^= ((*y) >> TEMPERING_L);
   ++mti;

   return ((double)(*y) / (double)UINT64_MAX);
}
#undef N
#undef M0
#undef M1
#undef M2
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
