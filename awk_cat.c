#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


void fin(int signal){
      printf("Soy el proceso hijo y muero.\n");
      exit(0);
}

int main(int argc, char **argv){
      pid_t hijo;

      int status;

      int pipe[2];

      if(pipe(pipe)<0){
            perror("Llmada a pipe.\n");
            exit(1);
      }

      hijo = fork();

      if(hijo<0){
            perror("Llamada a fork.\n");
            exit(1);
      }

      if(hijo==0){
            signal(SIGINT, fin);
            dup2(pipe[0], 0);
            execl("usr/bin/awk", "./awk", "-F:", "'{print $1 " "$2}'", pipe[0]);
            fprintf(stderr, "Error exec %s\n", strerror(errno));
            exit(1);
      }else{
            dup2(pipe[1], 1);
            execl("/bin/cat", "./cat", "etc/passwd");
            fprintf(stderr, "Error exec %s\n", strerror(errno));
            exit(1);
      }
}
