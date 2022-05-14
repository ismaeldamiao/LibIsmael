#include <stdio.h>
#include <stdlib.h>
void error(int errnum, const char *msg){
   fprintf(stderr, "%s", msg);
   exit(errnum);
}
