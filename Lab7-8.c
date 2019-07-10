#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab78.h"

int main(){
	NodoB *unNodo = CrearNodo(1);
//	MostrarNodo(unNodo);
	
	Guardar(unNodo);
	
	NodoB *actualNodo = Leer(1);
//	MostrarNodo(actualNodo);

	actualNodo = imitacionmain();
//	MostrarNodo(actualNodo);
	
	return 0;
}
