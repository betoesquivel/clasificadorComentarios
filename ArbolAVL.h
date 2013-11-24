
#include <iostream>

using namespace std;

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

		void balancear(NodoArbol<T> *pivote);
		void rotacionSimpleDerecha(NodoArbol<T> *pivote);
		void rotacionSimpleIzquierda(NodoArbol<T> *pivote);
		void rotacionDobleDerecha(NodoArbol<T> *pivote);
		void rotacionDobleIzquierda(NodoArbol<T> *pivote);

		bool balanceado(NodoArbol<T> *inicial);

		void insertar (T dato);
		bool existe (T dato);
		int obtenerAltura(NodoArbol<T> *inicial);
		int contarComparaciones(NodoArbol<T> *inicial);
		void desplegarArbol(NodoArbol<T> *inicial);
		void desplegarArbolNivelPorNivel();

		~ArbolAVL() { libera(raiz); }
};

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
	NodoArbol<T> *actual = raiz, *anterior = NULL;
	while (actual != NULL)
	{
		anterior=actual;
		actual=(actual->info>valor? actual->izq: actual->der);
	}
	if (anterior==NULL)	raiz = NuevoNodo;
	else
		if (anterior->info > valor) anterior->izq = NuevoNodo;
		else anterior->der = NuevoNodo;
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
