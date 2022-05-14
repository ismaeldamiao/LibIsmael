/* *****************************************************************************
   Function to compute a set of N correlated numbers using a Fourier transform
   obtained by the trace of a fractional Brownian motion defined as

   V_i = \sum_{j=0}^{N/2-1} (j+1)^{-0.5\alpha}
   \cos\left(  \frac{2\pi (i+1) j}{N} + \Phi_j  \right)

   Where i = 0, ..., N-1 and \Phi_j is a set of pseudo-random nunbers in
   the interval [0, 2 pi) and \alpha is a parameter that controls correlations.
   *****************************************************************************
   E-mail: ismaellxd@gmail.com
   Site: https://ismaeldamiao.github.io/
   *****************************************************************************
   Copyright (c) 2021 I.F.F. dos SANTOS (Ismael Damiao)

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
#include "../ismael.h"

#if defined(UINT64_MAX)
#define unsigned uint64_t
#define random(x) ismael.random.mt64(x)
#elif defined(UINT32_MAX)
#define unsigned uint32_t
#define random(x) ismael.random.mt32(x)
#else
#define unsigned int
#define random(x) ismael.random.system(x)
#endif

double *correlated_w_fourier(double alpha, int N, int seed){
#if !defined(M_PI)
   const double M_PI = 3.14159265358979323846;
#endif
#if defined(UINT64_MAX)
   uint64_t idum;
#elif defined(UINT32_MAX)
   uint32_t idum;
#else
   unsigned int idum;
#endif
   int N2, i, j;
   double _2pi, alpha_2, k;
   double *phi, *V, aux1, aux2, deviation;
   double menor = DBL_MAX;
   double maior = -DBL_MAX;

   _2pi = 2.0 * M_PI;
   alpha_2 = 0.5 * alpha;
   aux1 = aux2 = 0.0;
   N2 = N / 2;
   idum = seed;

   V = (double*)malloc((size_t)((N) * sizeof(double)));
   phi = (double*)malloc((size_t)((N2) * sizeof(double)));

   /* Fist draw the values of phi[i] */
   for(i = 0; i < N2; ++i) phi[i] = _2pi * random(&idum);

   menor = DBL_MAX;
   maior = -DBL_MAX;
   for(i = 0; i < N; ++i){
      /* Compute correlated values */
      V[i] = 0.0;
      k = _2pi * (double)(i+1) / ((double)N);
      for(j = 0; j < N2; ++j)
      V[i] += cos( k * (j+1) + phi[j]) /
      pow((double)(j+1), alpha_2);

      aux1 += V[i];
      aux2 += V[i]*V[i];
      menor = ((menor) < (V[i]) ? (menor) : (V[i]));
      maior = ((maior) > (V[i]) ? (maior) : (V[i]));
   }

   /* Normalize the sequence */
   aux1 /= ((double)N);
   aux2 /= ((double)N);
   deviation = sqrt(aux2 - aux1*aux1);
   menor = (aux1 - menor) / deviation;
   maior = (maior - aux1) / deviation + menor;
   menor /= maior;
   for(i = 0; i < N; ++i) V[i] = menor + (V[i] - aux1) / (deviation * maior);

   free(phi);

   return V;
}
