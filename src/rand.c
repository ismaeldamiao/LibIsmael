#include <stdlib.h>

double system_rand(int *y){
   static int start = 1;
   if(((*y) < 0) || start){
      srand((unsigned)(*y));
      start = 0;
   }
   *y = rand();
   return ((double)(*y) / (double)RAND_MAX);
}
