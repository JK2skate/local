#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdarg.h>


int count(int modo, int nargs, ...){
  va_list ap;
  int i;
  int num;

  int count = 0;

  for(i = 0; i<nargs; i++){
    if(mode==0){
      num = va_arg(ap, int);

      if(num%2==0){
        count++;
      }

    }else{

      num = va_arg(ap,int);

      if(num%2!=0){
        count++
      }

    }
  }

  return count;

}


int main(int argc, char **argv){
  int count1;
  int count2;
  int count3;

  count1 = count(0, 4, 2,5,3,6);
  count2 = count(1, 2, 2,5);
  count2 = count(0, 8, 2,5,3,6, 9, 7,0,10);

  pritnf("Prueba 1. Resultado =  %i. Debería ser: 2", count1);
  pritnf("Prueba 2. Resultado =  %i. Debería ser: 1", count2);
  pritnf("Prueba 3. Resultado =  %i. Debería ser: 4", count3);
}
