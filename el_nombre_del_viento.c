#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct relacion{
      int id;
      char * n_comun;
      char * n_real;
};

int borro_duplicados(struct relacion array, int size){

      if(size == 0 || array == NULL){
            perror("No hay elementos en el array\n");
            return -1;
      }
      struct relacion *aux;
      struct relacion elemento;

      int i;
      int j;
      int encontrado;
      int count = 0;

      for(i = 0; i < size ; i++){
            encontrado  = 0;

            for(j= i +1; j < size && encontrado == 0; j++){
                  if(strcmp(&array[i]->n_comun, &array[j]->n_comun)==0){
                        encontrado++;
                  }
            }

            if(!encontrado) {
                  count++;

                  aux = (struct relacion *)realloc(aux, sizeof(struct relacion)*count);

                  aux[count-1].id = array[i].id;
                  aux[count-1].n_comun = strdup(array[i].n_comun);
                  aux[count-1].n_real = strdup(array[i].n_real);
            }
      }

      for(i = 0; i<size ; i++){
            free(array[i].n_comun);
            free(array[i].n_real);
            free(array[i]);
      }

      if(array) {
            free(array);

      }
      array = NULL;

      array = (struct relacion *) malloc(sizeof(aux));

      array = aux;
      return count;
}
