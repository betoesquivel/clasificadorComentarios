
// #include <iostream>
// #include <queue>
// 
// using namespace std;

template <class T>
class NodoArbol
{ public:
	T info;
	string categoria;

	int FB;
	//Factor de Balance del nodo en un árbol AVL = Altura del subarbol derecho - altura del subarbol izquierdo;
	//Vale 0 si las alturas son iguales, 1 si el subárbol derecho es más alto y -1 si el izquierdo es más alto

	NodoArbol<T> *izq, *der, *padre;
	NodoArbol() { izq = der = padre = NULL; }
	NodoArbol(T dato, string categoria) { info = dato; this->categoria = categoria; FB = 0; izq = der = padre = NULL; }
};

template <class T>
class ArbolAVL
{
private:
		NodoArbol<T> *raiz;
public:
		ArbolAVL() { raiz = NULL; }
		NodoArbol<T>* getRaiz(){return raiz;}

		//Balanceo AVL
		void balancear(NodoArbol<T> *pivote);
		
		NodoArbol<T>* rotacionSimpleIzquierda(NodoArbol<T> *pivote);
		NodoArbol<T>* rotacionSimpleDerecha(NodoArbol<T> *pivote);

		NodoArbol<T>* rotacionDobleIzquierda(NodoArbol<T> *pivote);
		NodoArbol<T>* rotacionDobleDerecha(NodoArbol<T> *pivote);

		int calcularFB(NodoArbol<T> *inicial);
		bool balanceado(NodoArbol<T> *inicial);
		//Fin del BalanceoAVL

		void insertar (T dato);
		bool existe (T dato);
		int obtenerAltura(NodoArbol<T> *inicial);
		int contarComparaciones(NodoArbol<T> *inicial);
		void desplegarArbol(NodoArbol<T> *inicial);
		void desplegarArbolNivelPorNivel();

		~ArbolAVL() { libera(raiz); }
};


template <class T>
void ArbolAVL<T>::balancear(NodoArbol<T> *pivote)
{
	if (pivote->FB>0) {
		if (pivote->der->FB > 0) {
			pivote = rotacionSimpleIzquierda(pivote);
		}else{
			pivote = rotacionDobleIzquierda(pivote);
		}
	}else{
		if (pivote->izq->FB > 0) {
			pivote = rotacionSimpleDerecha(pivote);
		}else{
			pivote = rotacionDobleDerecha(pivote);
		}
	}

	while(pivote!=raiz)
	{
		pivote = pivote->padre;
		if (pivote->FB>1 || pivote->FB<-1) {
			balancear(pivote);
		}
	}
}

template <class T>
NodoArbol<T>* ArbolAVL<T>::rotacionSimpleIzquierda(NodoArbol<T> *pivote)
{
	NodoArbol<T> *A, *B;
	A = pivote->der;
	B = pivote;

	B->der = A->izq;
	A->izq = B; 

	(B->der)->padre = B; 
	A->padre = B->padre;
	B->padre = A; 

	if (A->info < (A->padre)->info) {
		(A->padre)->izq = A;
	}else{
		(A->padre)->der = A; 
	}

	A->FB = B->FB = 0;
	return A;
}

template <class T>
NodoArbol<T>* ArbolAVL<T>::rotacionSimpleDerecha(NodoArbol<T> *pivote)
{
	NodoArbol<T> *A, *B;
	A = pivote->izq;
	B = pivote;

	B->izq = A->der;
	A->der = B; 

	(B->izq)->padre = B; 
	A->padre = B->padre;
	B->padre = A; 

	if (A->info < (A->padre)->info) {
		(A->padre)->izq = A;
	}else{
		(A->padre)->der = A; 
	}

	A->FB = B->FB = 0;
	return A;
}

template <class T>
NodoArbol<T>* ArbolAVL<T>::rotacionDobleIzquierda(NodoArbol<T> *pivote)
{
	NodoArbol<T> *A, *B, *C, *aux;
	A = pivote->der;
	B = pivote;
	C = (pivote->der)->izq;

	aux = C->der;
	C->der = A;
	A->izq = aux;

	aux = C->izq;
	C->izq = B;
	B->der = aux;

	(B->der)->padre = B; 
	(A->izq)->padre = A; 

	A->padre = C; 
	C->padre = B->padre;
	B->padre = C;
	if (C->info < C->padre) {
		(C->padre)->izq = C;
	}else{
		(C->padre)->der = C;
	}

	C->FB = 0;
	A->FB = calcularFB(A);
	B->FB = calcularFB(B);
	return C;
}

template <class T>
NodoArbol<T>* ArbolAVL<T>::rotacionDobleDerecha(NodoArbol<T> *pivote)
{
	NodoArbol<T> *A, *B, *C, *aux;
	A = pivote;
	B = pivote->izq;
	C = (pivote->izq)->der;

	aux = C->der;
	C->der = A;
	A->izq = aux;

	aux = C->izq;
	C->izq = B;
	B->der = aux;

	(B->der)->padre = B; 
	(A->izq)->padre = A; 

	B->padre = C; 
	C->padre = A->padre;
	A->padre = C;
	if (C->info < C->padre) {
		(C->padre)->izq = C;
	}else{
		(C->padre)->der = C;
	}

	C->FB = 0;
	A->FB = calcularFB(A);
	B->FB = calcularFB(B);
	return C;
}

template <class T>
int ArbolAVL<T>:calcularFB(NodoArbol<T> *inicial)
{
	return ( obtenerAltura(inicial->der) - obtenerAltura(inicial->izq) );
}
	
template <class T>
bool ArbolAVL<T>::balanceado(NodoArbol<T> *inicial)
{
	if(inicial==NULL){
		return true;
	}else{
		int FB = calcularFB(NodoArbol<T> *inicial);
		if (FB>=-1 || FB<=1) {
			return (balanceado(inicial->izq) && balanceado(inicial->der));
		}else{
			return false;
		}
	}
}

template <class T>
void libera (NodoArbol<T>* raiz) 
{ //Observar que al ser recursive, es una función libre llamada por el método
	if (raiz != NULL)
	{ 	libera(raiz->izq);
		libera(raiz->der);
	delete(raiz);
	}
}

template <class T>
void ArbolAVL<T>::insertar (T valor)
{ //Precondición: el valor no existe en el árbol.
	NodoArbol<T> *NuevoNodo = new NodoArbol<T>(valor);
	NodoArbol<T> *actual = raiz, *anterior = NULL, *pivote = NULL;
	while (actual != NULL)
	{
		anterior=actual;

		if (valor < actual->info) {
			actual->FB -= 1; 
			if (actual->FB<-1) {
				pivote = actual;
			}
				
			actual = actual->izq;
		}else{
			actual->FB += 1; 
			if (actual->FB>1) {
				pivote = actual;
			}

			actual = actual->der;
		}
	}

	if (anterior==NULL)	
	{
		raiz = NuevoNodo;
	}
	else
	{
		if (valor < anterior->info) 
		{
			anterior->izq = NuevoNodo;
		}
		else 
		{
			anterior->der = NuevoNodo;
		}
	}
	if(pivote!=NULL){
		balancear(pivote);
	}
}

template <class T>
bool ArbolAVL<T>::existe(T dato)
{
	NodoArbol<T> *aux = raiz;
	while (aux != NULL && aux->info != dato)
		aux = (dato < aux->info? aux->izq : aux->der);
	return !(aux == NULL);
}

template <class T>
int ArbolAVL<T>::obtenerAltura(NodoArbol<T> *inicial)
{
	int altura_izquierdo, altura_derecho;
	if(inicial!=NULL)
	{
		altura_izquierdo = obtenerAltura(inicial->izq);
		altura_derecho = obtenerAltura(inicial->der);
		return (altura_izquierdo > altura_derecho) ? (altura_izquierdo+1):(altura_derecho+1);
	}
	else
	{
		return 0;
	}
}

template <class T>
int ArbolAVL<T>::contarComparaciones (NodoArbol<T>* raiz, int comparaciones)
{
	if (raiz != NULL) {
		return (
			 comparaciones 
			 + contarComparaciones(raiz->izq, comparaciones+1)
			 + contarComparaciones(raiz->der, comparaciones+1)
		);
	}else{
		return 0;
	}
}

template <class T>
void ArbolAVL<T>::desplegarArbol(NodoArbol<T> *inicial)
{
	if(inicial!=NULL)
	{
		if(inicial->izq != NULL || inicial->der != NULL)
			cout<<"Padre: "<<inicial->info<<endl;
		else
			cout<<"Hoja: "<<inicial->info<<endl;
		desplegarArbol(inicial->izq);
		desplegarArbol(inicial->der);
	}
}

template <class T>
void ArbolAVL<T>::desplegarArbolNivelPorNivel()
{
	queue< NodoArbol<T>* > fila;
	fila.push(raiz);
	while(!fila.empty())
	{
		NodoArbol<T> *temporal = fila.front();
		fila.pop();
		cout<<temporal->info<<endl;
		if(temporal->izq!=NULL)
			fila.push(temporal->izq);
		if(temporal->der!=NULL)
			fila.push(temporal->der);
	}
}
