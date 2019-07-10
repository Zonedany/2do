#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct _arbol{
	int dato;
	struct _arbol *hizq;
	struct _arbol *hder;
}arbol;

arbol *CrearNodo(char valor);
char *CrearArbolEnArreglo(arbol *unArbol, int tam);
void CopiaArbolEnArreglo(arbol *unArbol, char *DestinoArreglo, int pos);
int IniciarArreglo(int tam,char Arreglo[0]);
int Altura(arbol *unArbol);
int MuestraArbolEnTerminal(arbol *unArbol, int tam, int h);

char *CrearArbolEnArreglo(arbol *unArbol,int tam){
//	printf(" %d ",tam);
		
	char *Arreglo = (char*)malloc(sizeof(char)*tam); //sin (char*) mi compilador da un error

	IniciarArreglo(tam, Arreglo); 
	
	CopiaArbolEnArreglo(unArbol, Arreglo,0);
	
	return Arreglo;
}

void CopiaArbolEnArreglo(arbol *unArbol, char *Arreglo, int pos){

	if(unArbol == NULL){
		Arreglo[pos] = 'N';
		return ;
	}
	Arreglo[pos] = unArbol->dato /*+ '0'*/;
	CopiaArbolEnArreglo(unArbol->hizq, Arreglo, (2*pos)+1);
	CopiaArbolEnArreglo(unArbol->hder, Arreglo, (2*pos)+2);
	
	return;
}


int IniciarArreglo(int tam,char Arreglo[0]){
	int i = 0;
	
	while(i < tam){
		Arreglo[i] = '\0';
		i++;
	}
/*	i=0;
	while(i < tam){
		printf("%c"	,Arreglo[i]); // %c me da caracter random
		i++;
	}
	printf("tam: %d",i);
*/	
}

int MuestraArbolEnTerminal(arbol *unArbol, int tam, int h){
	char *auxArreglo = CrearArbolEnArreglo(unArbol,tam);
//	int cont=0;

/*	int i=0;
	while(i < tam){
		printf("\t %c ",auxArreglo[i]);
		i++;
		
		if(i==pow(2,cont)){
			printf("\n\n");
			cont++;
		}	
	}
*/
	int contador=0,piso=0,arregloenpiso = 0,i=0;

	while(piso < h+2){
			arregloenpiso = pow(2,piso);
			contador=0;
			printf("\n");
			
			while(contador < arregloenpiso){
				if(auxArreglo[i] != 'N'){
					printf("\t\t %c", auxArreglo[i]);
				}
				else{
					printf("\t\t %c", auxArreglo[i]);
				}
				contador++;
				i++;
			}
			
			printf("\n\n");
			piso++;
	}
}
/*
void imprimirArreglo(int tam,char arreglo[0]){
	int i = 0,cont = 0;
	
	while(i < tam){
		printf("\n arreglo[%i]=%c",i,arreglo[i]);
		i++;
		
		if(i == pow(2,cont)){
			printf("\n\n");
			cont++;
		}
		
	}
}
*/
arbol *CrearArbol(FILE *fd,char c){
	
	if(fd == NULL){
		return 0;
	}
	while((c = fgetc(fd)) != EOF){
		putchar(c);
		c = c -'\0'; 

		if(c == 'N'){
			return(NULL);
		}
		else{
			arbol *NuevoNodo = CrearNodo(c);			
			NuevoNodo->hizq = CrearArbol(fd,c);
			NuevoNodo->hder = CrearArbol(fd,c);			

			return(NuevoNodo); //Retorna el arbol creado
		}
	}
}

arbol *CrearNodo(char valor){
	
	arbol *unArbol =(arbol*) malloc(sizeof(arbol));
	unArbol->dato = valor;
	unArbol->hizq = NULL;
	unArbol->hder = NULL;
	
//	printf("%s",unArbol);
	return(unArbol);
}

/* Altura del árbol */

int Altura(arbol *unArbol){
	int h, max;

	if(unArbol == NULL){
		return -1;
	}
	else{
		h = Altura( unArbol->hder );
		max = Altura( unArbol->hizq );
	}
	
	if(h > max){
		return(h + 1);
	}
	else{
		return(max + 1);
	}
}
