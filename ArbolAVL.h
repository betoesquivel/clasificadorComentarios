
// #include <iostream>
// #include <queue>
// 
// using namespace std;

template <class T, class V>
class NodoArbol
{ public:
	T info;
	V info2;

	int FB;
	//Factor de Balance del nodo en un árbol AVL = Altura del subarbol derecho - altura del subarbol izquierdo;
	//Vale 0 si las alturas son iguales, 1 si el subárbol derecho es más alto y -1 si el izquierdo es más alto
	NodoArbol<T,V> *izq, *der, *padre;
	NodoArbol() { izq = der = padre = NULL; }
	NodoArbol(T dato, V dato2) { info = dato; info2 = dato2; FB = 0; izq = der = padre = NULL; }
};

template <class T, class V>
class ArbolAVL
{
private:
		NodoArbol<T,V> *raiz;
		bool debug;
public:
		ArbolAVL() { raiz = NULL; this->debug = false;}
		ArbolAVL(bool debug) { raiz = NULL; this->debug = debug;}
		NodoArbol<T,V>* getRaiz(){return raiz;}
		
		void setDebug(bool d) { debug = d; } 

		//Balanceo AVL
		void balancear(NodoArbol<T,V> *pivote);
		
		NodoArbol<T,V>* rotacionSimpleIzquierda(NodoArbol<T,V> *pivote);
		NodoArbol<T,V>* rotacionSimpleDerecha(NodoArbol<T,V> *pivote);

		NodoArbol<T,V>* rotacionDobleIzquierda(NodoArbol<T,V> *pivote);
		NodoArbol<T,V>* rotacionDobleDerecha(NodoArbol<T,V> *pivote);

		int calcularFB(NodoArbol<T,V> *inicial);
		bool balanceado(NodoArbol<T,V> *inicial);
		//Fin del BalanceoAVL

		void insertar (T dato, V categoria);
		bool existe (T dato);
		NodoArbol<T,V>* encontrar (T dato);
		int obtenerAltura(NodoArbol<T,V> *inicial);
		int contarComparaciones(NodoArbol<T,V> *inicial, int comparaciones);
		void desplegarArbol(NodoArbol<T,V> *inicial);
		void desplegarArbolNivelPorNivel();

		~ArbolAVL() { libera(raiz); }
};


template <class T, class V>
void ArbolAVL<T,V>::balancear(NodoArbol<T,V> *pivote)
{
	if (debug) {
		cout<<"DEBUG::Entro al metodo balancear con pivote: "<<pivote->info<<endl;
	}
	if (pivote->FB>0) {
		if (pivote->der->FB > 0) {
			pivote = rotacionSimpleIzquierda(pivote);
		}else{
			pivote = rotacionDobleIzquierda(pivote);
		}
	}else{
		if (pivote->izq->FB < 0) {
			pivote = rotacionSimpleDerecha(pivote);
		}else{
			pivote = rotacionDobleDerecha(pivote);
		}
	}
	//calculo el FB de todos los padres
	NodoArbol<T,V> *aux = pivote; 
	while(aux!=raiz)
	{
		aux = aux->padre;
		aux->FB = calcularFB(aux);
	}	
	while(pivote!=raiz)
	{
		pivote = pivote->padre;
		if (pivote->FB>1 || pivote->FB<-1) {
			balancear(pivote);
		}
	}
}

template <class T, class V>
NodoArbol<T,V>* ArbolAVL<T,V>::rotacionSimpleIzquierda(NodoArbol<T,V> *pivote)
{
	if (debug) {
		cout<<"Hago rotacion simple a la izquierda."<<endl;
	}
	NodoArbol<T,V> *A, *B;
	A = pivote->der;
	B = pivote;

	B->der = A->izq;
	A->izq = B; 

	if(B->der != NULL){
		(B->der)->padre = B; 
	}
	A->padre = B->padre;
	B->padre = A; 

	if(A->padre != NULL)
	{
		if (A->info < (A->padre)->info) {
			(A->padre)->izq = A;
		}else{
			(A->padre)->der = A; 
		}
	}
	else
	{
		raiz = A; 
	}

	A->FB = B->FB = 0;
	if (debug) {
		desplegarArbol(raiz);
	}
	return A;
}

template <class T, class V>
NodoArbol<T,V>* ArbolAVL<T,V>::rotacionSimpleDerecha(NodoArbol<T,V> *pivote)
{
	if (debug) {
		cout<<"Hago rotacion simple a la derecha."<<endl;
	}
	NodoArbol<T,V> *A, *B;
	A = pivote->izq;
	B = pivote;

	B->izq = A->der;
	A->der = B; 

	if(B->izq != NULL){
		(B->izq)->padre = B; 
	}
	A->padre = B->padre;
	B->padre = A; 

	if(A->padre != NULL)
	{
		if (A->info < (A->padre)->info) {
			(A->padre)->izq = A;
		}else{
			(A->padre)->der = A; 
		}
	}
	else
	{
		raiz = A; 
	}

	A->FB = B->FB = 0;
	if (debug) {
		desplegarArbol(raiz);
	}
	return A;
}

template <class T, class V>
NodoArbol<T,V>* ArbolAVL<T,V>::rotacionDobleIzquierda(NodoArbol<T,V> *pivote)
{
	if (debug) {
		cout<<"Hago rotacion doble a la izquierda."<<endl;
	}
	NodoArbol<T,V> *A, *B, *C, *aux;
	A = pivote->der;
	B = pivote;
	C = (pivote->der)->izq;

	aux = C->der;
	C->der = A;
	A->izq = aux;

	aux = C->izq;
	C->izq = B;
	B->der = aux;

	if(B->der != NULL){
		(B->der)->padre = B; 
	}
	if(A->izq != NULL){
		(A->izq)->padre = A; 
	}

	A->padre = C; 
	C->padre = B->padre;
	B->padre = C;
	if(C->padre != NULL)
	{
		if(debug){cout<<"El padre de C es: "<<C->padre->info<<endl;}
		if (C->info < (C->padre)->info) {
			(C->padre)->izq = C;
		}else{
			(C->padre)->der = C; 
		}
	}
	else
	{
		if(debug){cout<<"C es la raiz: "<<endl;}
		raiz = C; 
	}

	C->FB = 0;
	A->FB = calcularFB(A);
	B->FB = calcularFB(B);
	if (debug) {
		desplegarArbol(raiz);
	}
	return C;
}

template <class T, class V>
NodoArbol<T,V>* ArbolAVL<T,V>::rotacionDobleDerecha(NodoArbol<T,V> *pivote)
{
	if (debug) {
		cout<<"Hago rotacion doble a la derecha."<<endl;
	}
	NodoArbol<T,V> *A, *B, *C, *aux;
	A = pivote;
	B = pivote->izq;
	C = (pivote->izq)->der;

	aux = C->der;
	C->der = A;
	A->izq = aux;

	aux = C->izq;
	C->izq = B;
	B->der = aux;

	if(B->der != NULL){
		(B->der)->padre = B; 
	}
	if(A->izq != NULL){
		(A->izq)->padre = A; 
	}

	B->padre = C; 
	C->padre = A->padre;
	A->padre = C;
	if(C->padre != NULL)
	{
		if (C->info < (C->padre)->info) {
			(C->padre)->izq = C;
		}else{
			(C->padre)->der = C; 
		}
	}
	else
	{
		raiz = C; 
	}

	C->FB = 0;
	A->FB = calcularFB(A);
	B->FB = calcularFB(B);
	if (debug) {
		desplegarArbol(raiz);
	}
	return C;
}

template <class T, class V>
int ArbolAVL<T,V>::calcularFB(NodoArbol<T,V> *inicial)
{
	int factorBalance = obtenerAltura(inicial->der) - obtenerAltura(inicial->izq);
	if (debug) {
		if(factorBalance>1 || factorBalance<-1){
			cout<<"DEBUG::Para "<<inicial->info<<"\nHubo un error con el factor balance: "<<factorBalance<<endl;
		}
	}
	return ( factorBalance  );
}
	
template <class T, class V>
bool ArbolAVL<T,V>::balanceado(NodoArbol<T,V> *inicial)
{
	if(inicial==NULL){
		return true;
	}else{
		int FB = calcularFB(inicial);
		if (FB>=-1 || FB<=1) {
			return (balanceado(inicial->izq) && balanceado(inicial->der));
		}else{
			return false;
		}
	}
}

template <class T, class V>
void libera (NodoArbol<T,V>* raiz) 
{ //Observar que al ser recursive, es una función libre llamada por el método
	if (raiz != NULL)
	{ 	libera(raiz->izq);
		libera(raiz->der);
	delete(raiz);
	}
}

template <class T, class V>
void ArbolAVL<T,V>::insertar (T valor, V categoria)
{ //Precondición: el valor no existe en el árbol.
	NodoArbol<T,V> *NuevoNodo = new NodoArbol<T,V>(valor, categoria);
	NodoArbol<T,V> *actual = raiz, *anterior = NULL, *pivote = NULL;
	while (actual != NULL)
	{
		// if (debug && anterior!=NULL) {
		// 	cout<<"DEBUG::El valor anterior es: "<<anterior->info<<endl;
		// 	cout<<"DEBUG::El valor anterior tiene un FB de: "<<anterior->FB<<endl;
		// }
		anterior=actual;
		
		if (valor < actual->info) {
			actual->FB -= 1; 
			if (actual->FB<-1) {
				pivote = actual;
			}else if (actual->FB==0 && actual->padre!=NULL) {
				if (debug) {
					cout<<"DEBUG::No ha aumentado un nivel."<<endl;
				}

				while(anterior!=raiz){
					anterior = anterior->padre;
					anterior->FB = calcularFB(anterior);
				}
				pivote = NULL;
				anterior = actual;
			}
				
			actual = actual->izq;
		}else{
			actual->FB += 1; 
			if (actual->FB>1) {
				pivote = actual;
			}else if (actual->FB==0 && actual->padre!=NULL) {
				if (debug) {
					cout<<"DEBUG::No ha aumentado un nivel."<<endl;
				}

				while(anterior!=raiz){
					anterior = anterior->padre;
					anterior->FB = calcularFB(anterior);
				}
				pivote = NULL;
				anterior = actual;
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
		NuevoNodo->padre = anterior;
	}
	if(pivote!=NULL){
		balancear(pivote);
	}
	// if(debug){
	// 	desplegarArbol(raiz);
	// }
}

template <class T, class V>
bool ArbolAVL<T,V>::existe(T dato)
{
	NodoArbol<T,V> *aux = raiz;
	while (aux != NULL && aux->info != dato)
		aux = (dato < aux->info? aux->izq : aux->der);
	return !(aux == NULL);
}

template <class T, class V>
NodoArbol<T,V>* ArbolAVL<T,V>::encontrar (T dato)
{
	NodoArbol<T,V> *aux = raiz;
	while (aux != NULL && aux->info != dato)
		aux = (dato < aux->info? aux->izq : aux->der);
	if (aux!=NULL) {
		return aux;
	}else{
		return aux;
	}
}

template <class T, class V>
int ArbolAVL<T,V>::obtenerAltura(NodoArbol<T,V> *inicial)
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

template <class T, class V>
int ArbolAVL<T,V>::contarComparaciones (NodoArbol<T,V>* raiz, int comparaciones)
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

template <class T, class V>
void ArbolAVL<T,V>::desplegarArbol(NodoArbol<T,V> *inicial)
{

	if(inicial!=NULL)
	{
		desplegarArbol(inicial->izq);
		cout<<inicial->info<<" "<<inicial->FB<<endl;
		desplegarArbol(inicial->der);
	}
}

template <class T, class V>
void ArbolAVL<T,V>::desplegarArbolNivelPorNivel()
{
	queue< NodoArbol<T,V>* > fila;
	fila.push(raiz);
	while(!fila.empty())
	{
		NodoArbol<T,V> *temporal = fila.front();
		fila.pop();
		cout<<temporal->info<<endl;
		if(temporal->izq!=NULL)
			fila.push(temporal->izq);
		if(temporal->der!=NULL)
			fila.push(temporal->der);
	}
}
