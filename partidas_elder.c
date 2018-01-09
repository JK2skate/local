

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



struct partida{
  float puntos;
  char *nombre;
};

struct puntuacion{
  float total;
  char *nombre;
  int num_partidas;
}


struct puntuacion *agrego_puntuacion(struct partida * partidas, int num_partidas, int *num_ninos, int *error){
  int i;
  int j;
  int z;

  int encontrado = 0;
  int partidas_ind = 1;
  float puntos_tot;

  *error = 0;

  struct puntuacion *puntuaciones = (strcuct puntuacion *)malloc(sizeof(struct puntuacion));

  if(num_partidas == 0){
    *error = 1;
    return NULL;
  }

  if(!partidas){
    *error = 1;
    return NULL;
  }

  //primer elemento sabemos con seguridad que no está en la tabla de puntuaciones

  puntos_tot = partidas[0].puntos;

  for(i = 1; i< num_partidas; i++){
      if(strcmp(partidas[0].nombre, partidas[i].nombre)==0){
        puntos_tot = puntos_tot + partidas[i].puntos;
        partidas_ind++;
      }

  }

  puntuaciones[0].nombre = strdup(partidas[0].nombre);
  puntuaciones[0].total = puntos_tot;
  puntuaciones[0].num_partidas = partidas_ind;

  *num_ninos++;

  for(i = 0; i<num_partidas ; i++){
    encontrado = 0;

      for(j = 0; j<&num_ninos; j++){

          if(strcmp(puntuaciones[j].nombre, partidas[i].nombre)==0){
            encontrado++
          }
      }

      if(encontrado == 0){
        partidas_ind = 1;
        puntos_tot = partidas[i].puntos;

          for(z = i+1;z<num_partidas; z++){
              if(strcmp(partidas[i].nombre, partidas[z].nombre)==0){
                  puntos_tot = puntos_tot +partidas[z].puntos;
                  partidas_ind++;
              }

          }

          puntuaciones = (struct puntuacion *)realloc(puntuaciones, sizeof(puntuaciones)+ sizeof(struct puntuacion));

          puntuaciones[&num_ninos].nombre = strdup(partidas[i].nombre);
          puntuaciones[&num_ninos].total = puntos_tot;
          puntuaciones[&num_ninos].num_partidas = partidas_ind;

          *num_ninos++
      }
  }

  return puntuaciones;
}

int main(int argc, char **argv){
  int num_partidas = 20;
  int num_ninos = 0;
  int error = 0;

  int i;


  struct partida *partidas;
  struct puntuacion *puntuaciones;

  partidas = (struct partida *)malloc(sizeof(struct partida)*num_partidas);

  // partida = algo;

  puntuaciones = agrego_puntuacion(partidas, num_partidas, &num_ninos, &error);

  for(i = 0; i< num_ninos; i++){
    prtintf( "Niño número %i: Nombre: %s.   Puntos: %f.   Número de partidas: %i. \n", i, puntuaciones[i].nombre, puntuaciones[i].total, puntuaciones[i].num_partidas);
  }

    for(i = 0; i< num_ninos; i++){

      free(puntuaciones[i].nombre);
      free(puntuaciones[i]);


    }

    if(puntuaciones){
      free(puntuaciones);

    }
  return 0;
}
