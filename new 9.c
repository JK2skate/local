//ENERO 2015 .PROBLEMA 2(El nombre del viento)---->LISTA ENLAZADA

/////////////////////////nombre.h//////////////////
struct node{
	int id;
	char *n_real;
	char *n_comun;
	struct node *next;
};

/////////////////////////nombre.c//////////////////
/////////////////////////APARTADO 2.1//////////////
struct node *creo(int id,char *n_real,char *n_comun,int *error){
	*error = 0;
	struct node *aux = (struct node *)malloc(sizeof(struct node));
	if(aux == NULL){
		*error = errno;
		return NULL;
	}
	
	if((aux->n_real=strdup(n_real))==NULL){
		*error = errno;
		free(aux);
		return NULL;
	}
	
	if((aux->n_comun=strdup(n_comun))==NULL){
		*error = errno;
		free(aux->real);
		free(aux);
		return NULL;
	}
	
	aux->id = id;
	aux->next = NULL;
	return aux;
}

struct node *copio(struct node *vieja,int *error){
	*error = 0;
	if(vieja == NULL){
		return NULL;
	}
	
	struct node *aux;
	aux = creo(vieja->id,vieja->n_real,vieja->n_comun,error);
	if(&error){
		return NULL;
	}
	aux->next = copio(vieja->next,error);
	return aux;
}

struct node *mezclo(struct node *listaPar,struct node *listaImpar,int *error){
	*error = 0;
	int id_nuevo=0;
	struct node *aux = NULL;
	struct node *nuevo = NULL;
	struct node *ultimo = NULL;
	struct node *sobra = NULL;
	if(listaImpar == NULL){
		return copio(listaPar,error);
	}
	if(listaPar == NULL){
		return copio(listaImpar,error);
	}
	
	while((listaPar)&&(listaImpar)){
		aux = creo(++id_nuevo,listaImpar->n_real,listaImpar->n_comun,error);
		aux->next = creo(++id_nuevo,listaPar->n_real,listaPar->n_comun,error);
		
		if(nuevo == NULL){
			nuevo = aux;
		}else{
			ultimo = aux->next;
		}
		ultimo = aux->next;
		listaImpar = listaImpar->next;
		listaPar = listaPar->next;
	}
	
	if(listaPar){
		sobra = listaPar;
	}
	if(listaImpar){
		sobra = listaImpar;
	}
	ultimo->next = copio(sobra);
	return nuevo;
}


