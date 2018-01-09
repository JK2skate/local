#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t pid_A = 0;
pid_t pid_B = 0;
pid_t pid_C = 0;
pid_t pid_D = 0;

pid_t termina = 0;

int cambio_sentido = 0;
int status;
int sentido = 0; //ida = 0, vuelta = 1;


void signal_alarm(int senhal){
  printf( "Cambio de sentido. Fin alarma.\n");
  cambio_sentido = 1;
}

void signal_PB(int senhal){
  kill(pid_C, SIGINT);
  termina = wait(&status);
  printf( "Proceso B: %i, con status: %i.\n", termina, WEXITSTATUS(status));
  exit(0);
}

void signal_PC(int senhal){
  kill(pid_D, SIGINT);
  termina = wait(&status);
  printf("Proceso C: %i, con status: %i.\n", termina, WEXITSTATUS(status));
  exit(0);
}

void signal_PD(int senhal){

  printf( "Proceso D: %i, con status: %i.\n", termina, WEXITSTATUS(status));
  exit(0);
}

int main(int argc, char **argv){
	int A_B[2];
	int B_A[2];

	int B_C[2];
	int C_B[2];

	int C_D[2];
	int D_C[2];

	int D_A[2];
	int A_D[2];

	char envio1 = 1;
	char envio2 = 255;
	char recibo;

	char *ptr;

	long segundos;

	int count = 0;

	segundos = strtol(argv[1], &ptr, 10);

	if(segundos<=0){
		return 0;
	}
	
	

	if(pipe(A_B)<0){
		perror("Lllamada a pipe con A_B");
		return 0;
	}

	if(pipe(B_A)<0){
		perror("Lllamada a pipe con B_A");
		return 0;
	}

	if(pipe(B_C)<0){
		perror("Lllamada a pipe con B_C");
		return 0;
	}

	if(pipe(C_B)<0){
		perror("Lllamada a pipe con C_B");
		return 0;
	}

	if(pipe(C_D)<0){
		perror("Lllamada a pipe con C_D");
		return 0;
	}

	if(pipe(D_C)<0){
		perror("Lllamada a pipe con D_C");
		return 0;
	}

	if(pipe(D_A)<0){
		perror("Lllamada a pipe con D_A");
		return 0;
	}

	if(pipe(A_D)<0){
		perror("Lllamada a pipe con A_D");
		return 0;
	}

	pid_B = fork();

	if(pid_B < 0){
		perror("Llamada a fork");
		return 1;
	}
	
	if(pid_B ==0) {
		
		printf("traza\n");
		
		// Hijo
		signal(SIGINT, signal_PB);
		pid_C = fork();

		if(pid_C < 0){
			perror("Llamada a fork");
			return 1;
		}

		if(pid_C == 0) {
			// Nieto
			signal(SIGINT, signal_PC);
			pid_D = fork();

			if(pid_D < 0) {
				perror("Llamada a fork");
				return 1;
			}

			if(pid_D == 0){
				signal(SIGINT, signal_PD);
				// Visnieto
				while(1){
					
					if(sentido == 0){

						read(C_D[0], &recibo, sizeof(char));

						if(recibo == envio1){
							write(D_A[1],&envio1, sizeof(char));
						}else{
							write(D_A[1],&envio2, sizeof(char));
							sentido = 1;
						}

					}else{

						read(A_D[0], &recibo, sizeof(char));

						if(recibo == envio1){
							write(D_C[1],&envio1, sizeof(char));
						}else{
							write(D_C[1],&envio2, sizeof(char));
							sentido = 0;
						}

					}
				}

			}else{
			
				while(1) {
					if(sentido == 0){

						read(B_C[0], &recibo, sizeof(char));

						if(recibo == envio1){
							write(C_D[1],&envio1, sizeof(char));
						}else{
							write(C_D[1],&envio2, sizeof(char));
							sentido = 1;
						}

					}else{

						read(D_C[0], &recibo, sizeof(char));

						if(recibo == envio1){
							write(C_B[1],&envio1, sizeof(char));
						}else{
							write(C_B[1],&envio2, sizeof(char));
							sentido = 0;
						}

					}

				}
			}

		} else {

			while(1){
				if(sentido == 0){
					
					read(A_B[0], &recibo, sizeof(char));

					if(recibo == envio1){
						write(B_C[1],&envio1, sizeof(char));
					}else{
						write(B_C[1],&envio2, sizeof(char));
						sentido = 1;
					}

				}else{

					read(C_B[0], &recibo, sizeof(char));

					if(recibo == envio1){
						write(B_A[1],&envio1, sizeof(char));
					}else{
						write(B_A[1],&envio2, sizeof(char));
						sentido = 0;
					}

				}

			}

		}

	}else {
		signal(SIGALRM, signal_alarm);

		for(count = 0; count < 5; count++){
			cambio_sentido = 0;
			alarm(segundos);
			
			
			while(!cambio_sentido) {
				if(sentido == 0){
					write(A_B[1],&envio1, sizeof(char));
					read(D_A[0],&recibo, sizeof(char));
				}else{
					write(A_D[1], &envio1, sizeof(char));
					read(B_A[0],&recibo, sizeof(char));        
					
				}
			}


			if(sentido ==0){
				write(A_B[1],&envio2, sizeof(char));
				read(D_A[0],&recibo, sizeof(char));
				sentido = 1;
			}else{
				write(A_D[1],&envio2, sizeof(char));
				read(B_A[0],&recibo, sizeof(char));
				sentido = 0;
			}
			alarm(0);
		}

		kill(pid_B, SIGINT);
		termina = wait(&status);
		printf("Proceso A: %i, con status: %i.\n", termina, WEXITSTATUS(status));
		return 0;
	}

}
