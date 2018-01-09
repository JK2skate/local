#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

char *cadena = NULL;

void fin(int signal){
      if(cadena){
            free(cadena);
      }

      exit(1);

}

int proceso_pregunta(char *cadena, int *error){

      int operacion;
      int resultado;
      int contador;
      long num;
      long numveces;

      char *token = NULL;
      char *ptr = NULL;
      char *sig;

      *error = 0;
      cadena[strlen(cadena)-1] = 0;

      token = strtok_r(&cadena, " ", &sig);

      if(token == NULL){
            *error = 1;
            return -1;
      }

      if(strcmp(token,"add")==0){
            operacion = 0;
            resultado = 0;
      }else if(strcmp(token, "mul")==0){
            operacion = 1;
            resultado = 1;

      }else{
            *error = 1;
            return -1;
      }

      token = strtok_r(NULL, " ", &sig);

      if(token == NULL){
            *error = 1;
            return -1;
      }




      numveces = strtol(token, &ptr, 10);

      if(*ptr!=0){
            *error = 1;
            return -1;
      }

      contador = 0;

      while(contador<numveces){
            token = strtok_r(NULL, " ", &sig);

            if(token == NULL){
                  *error = 1;
                  return -1;
            }

            num = strtol(token, &ptr,10);

            if(*ptr!=0){
                  *error = 1;
                  return -1;
            }
            if(operacion==0){

                  resultado += num;

            }else{

                  resultado *= num;
            }

            contador++;

      }

      if(token){
            token = strtok_r(NULL, " ", &sig);

            if(token == NULL){
                  *error = 1;
                  return -1;
            }

      }

      *error = 0;
      return resultado;

}

int main(int argc, char **argc){

      size_t pedidos = 0;
      ssize_t leidos = 0;

      int resultado = 0;

      int error = 0;

      signal(SIGALRM, fin);
      signal(SIGINT, fin);

      while(leidos != -1){

            alarm(10);
            leidos = getline(&cadena, &pedidos, stdin);
            alarm(0);

            if((leidos!=-1)&&(&cadena!='\n')){
                  resultado = proceso_pregunta(cadena, &error);

                  if(error!=-1){

                        printf("%i.\n", resultado);

                  }else{

                        printf("-1\n");
                  }
                  fflush(stdout);
            }
      }

      fin(0);
      return 0;
}
