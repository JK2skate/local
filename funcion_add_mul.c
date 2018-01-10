#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdarg.h>


int operacion(int mode, int nargs, ...){
      int resultado;
      int i;
      int num;

      va_list ap;

      if(mode==1)
            resultado = 1;
      else if(mode == 0)
            resultado = 0;
      else
            return -1;

      va_start(ap, nargs);

      for(i=0; i<nargs; i++){
            num = va_arg(ap, int);
            if(mode){
                  reultado *= num;

            }else{
                  resultado +=num;
            }


      }

      va_end(ap);

      return resultado;

}

int main(int argc, char **argv){

      int e1;
      int e2;
      int e3;
      int e4;

      e1 = operacion(0, 4, 2, 2, 6, 5);
      e1 = operacion(1, 4, 2, 2, 2, 2);
      e1 = operacion(0, 2, 6, 5);
      e1 = operacion(1, 6, 0, 1, 1, 1, 1, 1);

      printf("Prueba 1. Resultado =  %d. Debería ser: 15\n", e1);
      printf("Prueba 2. Resultado =  %d. Debería ser: 16\n", e2);
      printf("Prueba 3. Resultado =  %d. Debería ser: 11\n", e3);
      printf("Prueba 4. Resultado =  %d. Debería ser: 0\n", e4);




}
