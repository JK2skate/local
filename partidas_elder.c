

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

void libero_puntuaciones(struct puntuacion * puntuaciones, int cont){
      int i;
      for(i = 0; i< cont; i++){
            if(puntuaciones[i].nombre){
                  free(puntuaciones[i].nombre);
            }
      }
      free(puntuaciones);
}
struct puntuacion *agrego_puntuacion(struct partida * partidas, int num_partidas, int *num_ninos, int *error){
  int i;
  int j;
  int z;

  int encontrado = 0;
  int partidas_ind = 1;
  float puntos_tot;

  *error = 0;

  errno = 0;
  struct puntuacion *aux = NULL;
  struct puntuacion *puntuaciones = NULL;

  if(num_partidas == 0){
    *error = 1;
    return NULL;
  }

  if(!partidas){
    *error = 1;
    return NULL;
  }

 aux = (struct puntuacion *)realloc(puntuaciones, sizeof(struct puntuacion));

 if(errno){
       *error = errno;
       libero_puntuaciones(puntuaciones, 0);
       *num_ninos = 0;
       return NULL;

 }
 puntuaciones = aux;

  //primer elemento sabemos con seguridad que no está en la tabla de puntuaciones

  puntos_tot = partidas[0].puntos;

  for(i = 1; i< num_partidas; i++){
      if(strcmp(partidas[0].nombre, partidas[i].nombre)==0){
        puntos_tot = puntos_tot + partidas[i].puntos;
        partidas_ind++;
      }

  }

  puntuaciones[0].nombre = strdup(partidas[0].nombre);

  if (errno){
          *error = errno;
          libero_puntuaciones(puntuaciones, 1);
          *numero = 0;
          return NULL;
        }
  puntuaciones[0].total = puntos_tot;
  puntuaciones[0].num_partidas = partidas_ind;

  *num_ninos++;

  for(i = 0; i<num_partidas ; i++){
    encontrado = 0;
    errno = 0;

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

          aux = (struct puntuacion *)realloc(puntuaciones, sizeof(struct puntuacion)*(&num_ninos+1));
          if(errno){
                *error = errno;
                libero_puntuaciones(puntuaciones, &num_ninos);
                *num_ninos = 0;
                return NULL;

          }
          puntuaciones = aux;

          puntuaciones[&num_ninos].nombre = strdup(partidas[i].nombre);
          if (errno){
                  *error = errno;
                  libero_puntuaciones(puntuaciones, &num_ninos+1);
                  *numero = 0;
                  return NULL;
                }
          puntuaciones[&num_ninos].total = puntos_tot;
          puntuaciones[&num_ninos].num_partidas = partidas_ind;

          *num_ninos++
      }
  }

  return puntuaciones;
}

int main(int argc, char **argv){
  int num_partidas = 5;
  int num_ninos = 0;
  int error = 0;

  int i;
  int j;


  struct partida *partidas;
  struct puntuacion *puntuaciones;

  partidas = (struct partida *)malloc(sizeof(struct partida)*num_partidas);
  for(j = 0; j< num_partidas;j++){
        swtch(j){
             case 0:
                  partidas[j].puntos = 10;
                  partidas[j].nombre = "oscar";
                  break;
            case 1:
                  partidas[j].puntos = 2;
                  partidas[j].nombre = "manuel";
                  break;
            case 2:
                  partidas[j].puntos = 2;
                  partidas[j].nombre = "oscar";
                  break;
            case 3:
                  partidas[j].puntos = 20;
                  partidas[j].nombre = "pedro";
                  break;
            case 4:
                  partidas[j].puntos = 5;
                  partidas[j].nombre = "manuel";
                  break;
            }
       }




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
