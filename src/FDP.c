#include <stdlib.h>

#if (__STDC_VERSION__ >= 201112L) /* ISO C11 */
   #define alloc(size, type) \
   (type*)aligned_alloc(sizeof(type), (size_t)size * sizeof(type))
#else
   #define alloc(size, type) \
   (type*)malloc((size_t)size * sizeof(type))
#endif /* ISO C11 */

double **FDP(double *valor, int N, int particoes){
   double acrescimo;
   double janela;
   double **_fdp;
   double menor, maior;

   {  /* Routine to get the bigger and the smaller values in the sample */
      menor = DBL_MAX;
      maior = -DBL_MAX;
      for(int i = 0; i < N; ++i){
         menor = ((menor) < (valor[i]) ? (menor) : (valor[i]));
         maior = ((maior) > (valor[i]) ? (maior) : (valor[i]));
      }
      //particoes = ceil((maior - menor) / janela);
      janela = (maior - menor) / (double)(particoes);
   }

   _fdp = alloc(2, double*);
   _fdp[0] = alloc(particoes, double);
   _fdp[1] = alloc(particoes, double);
   
   /* Escrever os tipos de energia que ha nesse intervalo */
   for(int i = 0; i < particoes; ++i){
      _fdp[0][i] = menor + (i+1) * janela;
      _fdp[1][i] = 0.0;
   }
   /* ***
      Rotina para contar a ocorrencia de cada tipo de energia
   *** */
   acrescimo = 1.0 / (janela * (double)N);
   for(int j = 0; j < N; ++j){
      for(int i = 0; i < particoes; ++i){
         if(valor[j] <= _fdp[0][i]){
            _fdp[1][i] += acrescimo;
            break;
         }
      }
   }
   return _fdp;
}
