#include<stdio.h> // -lm
#include<stdlib.h>
#include "arbolEstruct.h"

int main(){
	
	FILE *fd = fopen("C:\\Users\\iki\\Desktop\\ABB.txt","r");
	
	if(fd == NULL){	return 1; }
	
	char c = 0;	
	arbol *unArbol = CrearArbol(fd,c);
	
	int altura = Altura(unArbol);
	printf("\nAltura arbol: %i",altura);
	
	int tam = pow(2,altura+2)-1;

	char *Arreglo = CrearArbolEnArreglo(unArbol,tam);
//imprimirArreglo(tam,Arreglo);
	MuestraArbolEnTerminal(unArbol,tam,altura);
	return 0;
}
