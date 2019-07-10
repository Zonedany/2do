#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 10
typedef struct _nodo {
	int n;
	int hoja; //1 si es hoja, 0 si es un nodo interno
	char Claves[2*T - 1];
	struct _nodo *Hijos[2*T];
	int CantidadClaves;
	int miNombre;
} NodoB;

//int cont =0;

NodoB *Disco(NodoB *raiz){
  NodoB *x = raiz;
  const char *str = "C:\\Users\\Iki\\Desktop\\Laboratorios Estructura de datos\\Lab 7 y 8\\Nodos\\nodo";
  char extension[] = ".txt";

  int i = strlen(str);
  char *direccion = (char *) malloc(i + 1 + 1);
  strcpy(direccion, str);
  direccion[i] = x->Claves[0];
  
  direccion[i + 1] = '\0';
  strcat(direccion,extension);

  FILE *fd = fopen("C:\\Users\\Iki\\Desktop\\Laboratorios Estructura de datos\\Lab 7 y 8\\Nodos\\nodo.txt","wb");

  if(fd == NULL){
    printf("Error al crear el archivo");
  }
  else{
    fprintf(fd,"%i\n",x->n);
    fprintf(fd,"%i\n",x->hoja);
    
	for(i = 0; i < x->n; i++){
      if(x->Claves[i] != '\0'){
        fprintf(fd,"%c ",x->Claves[i]);
      }
    }
  }

  return x;
}


NodoB *CrearNodo(int nombreNodo){ //Nombre Nodo numero 1 pasado desde el main

	NodoB *auxNodo = (NodoB*)malloc(sizeof(NodoB)); //Mi compilador pide esta forma
	int i;										//[ERROR] si lo declado dentro del for
	for(i = 0; i < (2*T) - 1; i++){
		auxNodo->Claves[i] = i;					//Ej: auxNodo->Claves[5]=5;
		auxNodo->Hijos[i] = 0;					//hasta la pos 18con t=10
	}
	auxNodo->Hijos[(2*T) - 1] = 0;				//pos con t=10 19
	
	auxNodo->CantidadClaves = (2*T) - 1;		//Numero total de claves con t=10 son 19
	
	auxNodo->hoja = 1;
	auxNodo->miNombre = nombreNodo;
	
	return auxNodo;								//retorna primer nodo
}

int Guardar(NodoB *unNodo){
	
	if(unNodo == NULL){
		return -1;
	}
	
	char direccion[] = "C:\\Users\\Iki\\Desktop\\ArB.txt";
	FILE *archivo = fopen(direccion,"wb");							/* Se crea el archivo y se prepara para insertar informacion */
	
	if(archivo == NULL){
		return 0;
	}
	else{
		sprintf(direccion, "%d", unNodo->Claves);		/* Archivo con simbolos ilegibles *///linux %s
		fwrite(unNodo, sizeof(NodoB), 1, archivo);				//fwrite(cadena,sizeof(char),sizeof(cadena),fp); char cadena[] cada pos. es de tam 'char'
	}
	
	fclose(archivo);
	return 1;
}

NodoB *Leer(int nombreNodo){
	
	NodoB *auxNodo = (NodoB*) malloc(sizeof(NodoB));
	
	char strNombreNodo[] = "C:\\Users\\Iki\\Desktop\\ArB.txt";
	FILE *fd = fopen(strNombreNodo,"rb");
	
	if(fd == NULL){
		return 0;
	}
	else{
		sprintf(strNombreNodo,"%d",nombreNodo);
		fread(auxNodo, sizeof(NodoB), 1, fd); //Esta función lee un bloque de una "stream" de datos
	}
	return auxNodo;
}

NodoB *AllocateNode(){
   NodoB *a = (NodoB *)malloc(sizeof(NodoB));
   a->n = 0;
   a->hoja = 1;
   return a;
}

void Buscar(NodoB *x, int k){
	int i = 1;

	while(i < x->n && k > x->Claves[i]){
    	i = i+1;
	}

	if(i <= x->n && k == x->Claves[i]){
    	printf("\n\nClave encontrada");
		return;
	}
	if(x->hoja == 1){
		printf("\n\nLa clave no se encuentra en el arbol");
		return;
	}
	else{
    	Buscar(x->Hijos[i],k);
	}
}

NodoB *BTreeSplitChild (NodoB *x, int i, NodoB *y){
    NodoB *z = AllocateNode();
    
    y = x->Hijos[i]; //
    z->hoja = y->hoja; //
    
	z->n = T - 1;

    int j;
    for(j = 0; j < T - 1; j++){
        z->Claves[j] = y->Claves[j+T];
    }

    if(y->hoja == 0){ //es falso
        for(j = 0; j < T; j++){
            z->Hijos[j] = y->Hijos[j+T];
        }
    }

    y->n = T - 1;
    for(j = x->n+1; j >= i+1; j--){
        x->Hijos[j+1] = x->Hijos[j];
    }

    x->Hijos[i+1] = z;
    for(j = x->n; j >= i; j--){
        x->Claves[j+1] = x->Claves[j];
    }

    x->Claves[i] = y->Claves[T-1];

    x->n = x->n+1;

	Disco(y);
	Disco(z);
	Disco(x);
	return x;
}

NodoB *BTreeInsertNonFull (NodoB *x, char k) {
    int i = x->n-1;

    if(x->hoja == 1){ //es verdadero
        while (i >= 0 && x->Claves[i] > k){
            x->Claves[i+1] = x->Claves[i];
            i = i-1;
        }
        x->Claves[i+1] = k;
        x->n = x->n+1;
        Disco(x);
    }
    else{
        while (i >= 0 && k < x->Claves[i]){
            i = i-1;
        }
        i = i+1;

        if(x->Hijos[i]->n == 2*T-1){
            x = BTreeSplitChild(x, i, x->Hijos[i]);
        
		    if(k > x->Claves[i]){
                i = i+1;
            }
        }
        BTreeInsertNonFull(x->Hijos[i], k);
    }
    return x;
}

NodoB *BTreeInsert (NodoB *raiz, char k) {
	NodoB *r = raiz;
	
	if(r->n == (2*T - 1)) {
    	NodoB *s = AllocateNode();
   
    	raiz = s; //
   
    	s->hoja = 0; //Falso
   
    	s->n = 0;//
   
    	s->Hijos[0] = r;
    	
		s = BTreeSplitChild (s, 0, r);//1
    	s = BTreeInsertNonFull (s, k);
    	return s;
	}
	else{
    	return BTreeInsertNonFull (r, k);
	}
}

void ImprimirArbolB (NodoB *a, int nivel) {
   int i;

	for(i = 0; i < nivel; i++){
		printf(" ");
	}

   printf(" ");

   for(i = 0; i < a->n; i++){
      printf("%c ", a->Claves[i]);
   }

   printf("\n");

   for(i = 0; i <= a->n; i++){
      if(a->hoja == 0) {
         ImprimirArbolB(a->Hijos[i], nivel+10);
      }
   }
}

void MostrarNodo(NodoB *unNodo){
	
	if(unNodo == NULL){
		return;
	}
	printf("\nHoja: %d, CantidadClaves: %d \n\n", unNodo->hoja, unNodo->n);
	
	int i;
	for(i = 0; i < ((2*T) - 1); i++){
		printf("  %d",unNodo->Claves[i]);
	}
	printf("\n");
	for(i = 0; i < (2*T); i++){
		printf("%i  ",unNodo->Hijos[i]);
	}
	printf("\n\n");
	
}

NodoB *imitacionmain(){
	NodoB *a = AllocateNode();
	
	a = BTreeInsert(a, 'a');
	a = BTreeInsert(a, 'b');
   a = BTreeInsert(a, 'c');
   a = BTreeInsert(a, 'd');
   a = BTreeInsert(a, 'e');
   a = BTreeInsert(a, 'f');
   a = BTreeInsert(a, 'g');
   a = BTreeInsert(a, '1');
   a = BTreeInsert(a, 'i');
/*   a = BTreeInsert(a, 'j');
   a = BTreeInsert(a, 'k');
   a = BTreeInsert(a, 'l');
  a = BTreeInsert(a, 'm');
   a = BTreeInsert(a, 'n');
   a = BTreeInsert(a, 'o');
   a = BTreeInsert(a, 'p');
   a = BTreeInsert(a, 'q');
   a = BTreeInsert(a, 'r');
   a = BTreeInsert(a, 's');
   a = BTreeInsert(a, 't');
	a = BTreeInsert(a, 'u');
	a = BTreeInsert(a, 'v');
	a = BTreeInsert(a, 'w');
	a = BTreeInsert(a, 'ñ');
	a = BTreeInsert(a, 'y');
	a = BTreeInsert(a, 'z');
*/


//printf("%d",cont);

   ImprimirArbolB(a,2);

   Buscar(a,'j');
   return a;
}
