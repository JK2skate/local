#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


pid_t hijo;
pid_t termina;

int status;

int pregunta(char *fichero1, char *fichero2){
      char *cadena = NULL;
      ssize_t leidos = 0;
      size_t pedidos = 0;


      if((access(fichero1, F_OK)!=0)&&(access(fichero1, R_OK)!=0)){
            return 1;

      }

      if((access(fichero2, F_OK)==0)&&(access(fichero1, W_OK)==0)){
            printf("Quiere sobreescribir el segundo archivo?:\n");

            leidos = getline(&cadena, &pedidos, stdin);
            if(leidos!=-1){

                  if(strcmp(cadena, "S\n")==0){
                        if(cadena){
                              free(cadena);
                        }
                        return 0;
                  }else if(strcmp(cadena, "N\n")==0){
                        if(cadena){
                              free(cadena);
                        }

                        return 1;

                  }else{
                        if(cadena){
                              free(cadena);
                        }
                        perror("Respuesta no valida");
                        return 1;

                  }

            }else{
                  if(cadena){
                        free(cadena);
                  }
                  perror("unknown error");
                  return 1;
            }

      }
}

void terminar(int signal){
      pritnf("Soy el proceso hijo y muero.\n");
      exit(0);
}

int main(int argc, char **argv){

      if(argc!=3){
            perror("Numero parametros incorrectos");
            exit(1);
      }

      if(pregunta(argv[1],argv[2])!= 0){
            exit(1);
      }

      int ph[2];
      int hp[2];

      if(pipe(ph)<0){
            perror("llamada pipe");
            exit(1);
      }

      if(pipe(hp)<0){
            perror("llamada pipe");
            exit(1);
      }
      char *cadena2 = NULL;
      ssize_t leidos2 = 0;
      ssize_t nbytes = 0;
      size_t pedidos2 = 0;

      FILE *file1;
      FILE *file2;

      file1 = fopen(argv[1], "r");
      file2 = fopen(argv[2], "a");

      hijo = fork();

      if(hijo<0){
            perror("llamada fork");
            exit(1);
      }

      if(hijo == 0){

            dup2(ph[0], STDIN_FILENO);
            dup2(hp[1], STDOUT_FILENO);

            execlp("./calculadora", "./calculadora", 0);
            perror("No se pudo ejecutar el comando calculadora\n");



      }else{
            while(getline(&cadena2,&pedidos2, file1)!=-1){
                  write(ph[1], cadena2, strlen(cadena2));
                  nbytes = read(hp[0], cadena2, strlen(cadena2)+1);
                  cadena2[nbytes] = 0;
                  fprintf(file2, "%s", cadena2);

            }

            fclose(file1);
            fclose(file2);
            kill(hijo, SIGALARM);
            wait(&status);
            if(cadena2){
                  free(cadena2);
            }





      }
      return 0;


}
