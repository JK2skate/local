//ENERO 2015 .PROBLEMA 1(El nombre del viento)---->ARRAY DINAMICO

/////////////////////////nombre.h//////////////////
struct relacion{
	int id;
	char *n_real;
	char *n_comun;
};
/////////////////////////nombre.c//////////////////
struct relacion *borro_duplicados(struct relacion *array_kvothe,int *tam){
	struct relacion *array = array_kvothe;
	struct relacion *tmp;
	int i,j;
	for(i=0;i<(*tam);i++){
		j=i+1;
		while(j < (*tam)){
			if(strcmp(array[i].n_comun,array[j].n_comun)==0){
				free(array[j].n_comun);
				free(array[j].n_real);
				array[j] = array[*tam-1];
				tmp = realloc(array,sizeof(struct relacion)*(*tam-1));
				if(tmp == NULL){
					return array;
				}
				array = tmp;
				*tam--;
			}else{
				j++;
			}
		}
	}
	return array;
}
