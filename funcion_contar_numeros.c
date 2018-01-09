#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdarg.h>

//gkhk

int count(int modo, int nargs, ...){
  va_list ap;
  int i;
  int num;

  int counting = 0;
  va_start(ap, nargs);
  for(i = 0; i<nargs; i++){
    if(modo==0){
      num = va_arg(ap, int);

      if(num%2==0){
        counting++;
      }

    }else{

      num = va_arg(ap,int);

      if(num%2!=0){
        counting++;
      }

    }
  }
  
  va_end(ap);

  return counting;

}


int main(int argc, char **argv){
  int count1;
  int count2;
  int count3;

  count1 = count(0, 4, 2,5,3,6);
  count2 = count(1, 2, 2,5);
  count3 = count(0, 8, 2,5,3,6, 9, 7,0,10);

  printf("Prueba 1. Resultado =  %d. Debería ser: 2", count1);
  printf("Prueba 2. Resultado =  %d. Debería ser: 1", count2);
  printf("Prueba 3. Resultado =  %d. Debería ser: 4", count3);
  return 0;
  
}
