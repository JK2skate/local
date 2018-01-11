#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>




int main(int argc, char **argv){
      pid_t hijo;

      int status;

      int p[2];

      if(pipe(p)<0){
            perror("Llmada a pipe.\n");
            exit(1);
      }
      
	

      hijo = fork();

      if(hijo<0){
            perror("Llamada a fork.\n");
            exit(1);
      }

      if(hijo==0){
		dup2(p[0], STDOUT_FILENO);
            execl("usr/bin/awk", "awk", "-F:", "'{print $1 "  " $2}'",NULL);
		exit(1);
      }else{
            
            execl("/bin/cat", "cat", "/etc/passwd", NULL);
		wait(&status);
		exit(1);
            
            



      }

     
}
