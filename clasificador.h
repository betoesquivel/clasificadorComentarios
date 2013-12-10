// Descripcion: Clasifica comentarios dentro de una de las distintas categorias
// basándose en las listas de palabras clave que identifican cada categoría. 
// Guardo las palabras en un árbol de búsqueda binario conforme van apareciendo, 
// dependiendo de la cantidad de veces que aparece la palabra, es la prioridad
// que tiene en el árbol. Tal vez pueda utilizar mejor una priorityqueue para
// las palabras.
// 
// A partir de un archivo de entrada, genero un archivo de salida (especificado por el usuario)
// que tiene los comentarios clasificados.
//
//pendiente...
// Voy guardando los comentarios clasificados en dos listas 
// de strings paralelos. Uno contiene el comentario y otro contiene
// la categoria. 
//
// Autor: José Alberto Esquivel Patino A01139626
// Carrera: BCT
// Clase: Estructura de Datos
// Profesor: Roman Martinez Martinez
//
// #include <fstream>
// #include <iostream>
//
// I need these for the copied trim.
// #include <algorithm> tambien lo ocupo para convertir a minusculas
// #include <cctype>
// #include <locale>
//
// Para partir un string en palabras
// #include <stringstream>
bool debug = false;
class clasificador{
	private: 
		ArbolAVL<string, string> palabrasClave;
		ArbolAVL<string, int> palabrasIgnoradas;
		ArbolAVL<string, int> categorias;

		string nom_ArchivoComentarios;
		string nom_ArchivoPalabrasClave;
		string nom_ArchivoPalabrasIgnoradas;

		string nom_ArchivoSalida; 

		NodoArbol<string, int>* categoriaMayor;

	public:
		clasificador(string nComentarios, string nPalabrasClave, 
			     string nPalabrasIgnoradas, string nSalida);

		void convertirAMinusculas(string &s);
		void quitarSignosDePuntuacion(string &s);
		void resetearContadorCategorias(NodoArbol<string,int>* inicial);

		void modificarCategoriasEncontradasDePalabra(NodoArbol<string,string> *palabraEncontrada);
		void clasificarPalabra(string palabra);
		void clasificarComentario(string comentario);
		void clasificarArchivoDeComentarios();

		void llenarArbolPalabrasClave();
		void llenarArbolPalabrasIgnoradas();

		void escribirComentarioEnArchivo(string comentario, string categoria);

		void desplegarPalabrasClave(){
			palabrasClave.desplegarArbol(palabrasClave.getRaiz());
		}
		void desplegarCategorias(){
			categorias.desplegarArbol(categorias.getRaiz());
		}
		void desplegarPalabrasIgnoradas(){
			palabrasIgnoradas.desplegarArbol(palabrasIgnoradas.getRaiz());
		}
};

// ============= Obtenido de usuario Evan Teran, Stack Overflow =================================//

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// ============= Fin de reuso de codigo de Evan Teran ========================================//

clasificador::clasificador(string nComentarios, string nPalabrasClave, 
			   string nPalabrasIgnoradas, string nSalida)
{
	//Al inicializar con este constructor el clasificador,
	//el arbol de categorias se creara conforme se leen las palabras clave.
	nom_ArchivoComentarios = nComentarios;
	nom_ArchivoPalabrasClave = nPalabrasClave;
	nom_ArchivoPalabrasIgnoradas = nPalabrasIgnoradas;
	nom_ArchivoSalida = nSalida;
	categoriaMayor = NULL;

	palabrasClave.setDebug(false);
	palabrasIgnoradas.setDebug(false);
	categorias.setDebug(debug);
}

void clasificador::llenarArbolPalabrasClave()
{
	ifstream archivoPalabrasClave;
	archivoPalabrasClave.open(nom_ArchivoPalabrasClave.c_str());
	string palabra, categoria;
	string linea;
	while(getline(archivoPalabrasClave, linea))
	{
		istringstream iss(linea);
		iss>>palabra;
		while(iss>>categoria){
			palabrasClave.insertar(palabra,categoria);
			if(!categorias.existe(categoria)){
				categorias.insertar(categoria,0);
			}
		}
	}
	archivoPalabrasClave.close();	
}

void clasificador::llenarArbolPalabrasIgnoradas()
{
	ifstream archivoPalabrasIgnoradas;
	archivoPalabrasIgnoradas.open(nom_ArchivoPalabrasIgnoradas.c_str());
	string palabra;
	int dato2 = 0;//Solamente es el segundo dato en el arbol. 
	//Por ahora es inutil. Puede usarse para futuras optimizaciones.
	while(archivoPalabrasIgnoradas>>palabra)
	{
		palabrasIgnoradas.insertar(palabra,dato2);
	}
	archivoPalabrasIgnoradas.close();	
}

void clasificador::modificarCategoriasEncontradasDePalabra(NodoArbol<string,string> *palabraEncontrada)
{
	NodoArbol<string, int> *categoriaEncontrada = categorias.encontrar(palabraEncontrada->info2);		
	categoriaEncontrada->info2 += 1; 
	cout<<"categoria encontrada: "<<categoriaEncontrada->info<<endl;
	

	if(categoriaMayor!=NULL){
		if (categoriaMayor->info2 < categoriaEncontrada->info2) {
			categoriaMayor = categoriaEncontrada; 
		}
	}else{
		categoriaMayor = categoriaEncontrada;
	}

	if (palabraEncontrada->izq!=NULL) {
		if(palabraEncontrada->izq->info == palabraEncontrada->info){
			cout<<"La palabra se repite en el arbol."<<endl;
			modificarCategoriasEncontradasDePalabra(palabraEncontrada->izq);
		}	
	}
	if (palabraEncontrada->der!=NULL) {
		if(palabraEncontrada->der->info == palabraEncontrada->info){
			cout<<"La palabra se repite en el arbol."<<endl;
			modificarCategoriasEncontradasDePalabra(palabraEncontrada->der);
		}	
	}
}
void clasificador::clasificarPalabra(string palabra)
{
	if (debug) {
		cout<<"DEBUG::Buscando palabra en el arbol de palabras clave."<<endl;
		cout<<palabra<<endl;
	}
	if(!palabrasIgnoradas.existe(palabra)){
		NodoArbol<string, string> *palabraEncontrada = palabrasClave.encontrar(palabra);		
		if (palabraEncontrada!=NULL) {
			if (debug) {
				cout<<"Palabra encontrada en claves: "<<palabraEncontrada->info<<endl;
			}
			modificarCategoriasEncontradasDePalabra(palabraEncontrada);
			//tengo que hacer esto para todas las categorias de la palabra
			// NodoArbol<string, int> *categoriaEncontrada = categorias.encontrar(palabraEncontrada->info2);		
			// categoriaEncontrada->info2 += 1; 

			// if(categoriaMayor!=NULL){
			// 	if (categoriaMayor->info2 < categoriaEncontrada->info2) {
			// 		categoriaMayor = categoriaEncontrada; 
			// 	}
			// }else{
			// 	categoriaMayor = categoriaEncontrada;
			// }
			//esto iria dentro del while
		}		

	}else{
		if (debug) {
			cout<<"DEBUG::Esa palabra la ignoro: "<<palabra<<endl;
		}
	}
}

void clasificador::convertirAMinusculas(string &s)
{
	transform(s.begin(),s.end(),s.begin(), ::tolower);
}

void clasificador::quitarSignosDePuntuacion(string &s)
{	
	string c;
	for (unsigned int i = 0; i < s.length(); i++) {
		c = s[i];
		if (
			c=="."||c==","||c=="?"||c=="!"||c=="¿"||c=="¡"||c==";"||
		  	c=="-"||c=="+"||c=="_"||c=="*"||c=="&"||c=="'"
		   ) 
		{
			c = " ";
			s[i] = c.c_str()[0]; 
		}
	}
}

void clasificador::resetearContadorCategorias(NodoArbol<string,int>* inicial)
{
	if(inicial!=NULL){
		inicial->info2 = 0;	
		resetearContadorCategorias(inicial->izq);	
		resetearContadorCategorias(inicial->der);
	}
}

void clasificador::clasificarComentario(string comentario)
{	
	string temp = comentario;
	string categoria;
	trim(temp);
	quitarSignosDePuntuacion(temp);
	convertirAMinusculas(temp);

	istringstream iss(temp);
	string palabra = ""; 
	while(iss>>palabra){
		clasificarPalabra(palabra);
	}

	if(categoriaMayor == NULL){
		categoria = "NA";
	}else{
		categoria = categoriaMayor->info;
	}
	escribirComentarioEnArchivo(comentario,categoria);

	if (debug && categoriaMayor != NULL) {
		cout<<"DEBUG::Categoria del comentario: "<<categoriaMayor->info<<endl;
		cout<<"---------DEBUG-----------"<<endl;
		cout<<comentario<<endl;
		cout<<"DEBUG::Comentario contaba con "<<categoriaMayor->info2
		<<" coincidencias"<<endl;
	}

	resetearContadorCategorias(categorias.getRaiz());
	categoriaMayor=NULL;
}

void clasificador::clasificarArchivoDeComentarios()
{	
	ifstream archivoComentarios;
	archivoComentarios.open(nom_ArchivoComentarios.c_str());
	if (debug) {
		cout<<"DEBUG::Abro el archivo con los comentarios."<<endl;
		cout<<"DEBUG:: "<<nom_ArchivoComentarios<<endl;
	}
	string linea, comentario = "";
	while(!archivoComentarios.eof()){
		getline(archivoComentarios, linea);
		if(linea == "" && comentario != ""){
			if (debug) {
				cout<<"DEBUG::Salto de linea en el archivo."<<endl;
			}
			clasificarComentario(comentario);
			comentario = "";
		}else{
			trim(linea);
			comentario += linea;
			comentario += "\n";
		}
		if (debug) {
			cout<<"Fin de comentario del ciclo."<<endl;
		}
	}
	if (debug) {
		cout<<"DEBUG::Ultimo comentario."<<endl;
	}
	if (comentario != "") {
		clasificarComentario(comentario);
	}
	comentario = "";
	archivoComentarios.close();
}

void clasificador::escribirComentarioEnArchivo(string comentario, string categoria)
{
	if(debug) {
		cout<<"DEBUG::escribiendo el comentario"<<endl;
		cout<<"DEBUG::con categoria: "<<categoria<<endl;
	}
	categoria += ".txt";
	ofstream archivoSalida;
	archivoSalida.open(categoria.c_str(),ios::app);
	// archivoSalida<<"<"<<categoria<<">"<<endl;
	archivoSalida<<comentario;
	// archivoSalida<<"<"<<categoria<<">"<<endl;
	archivoSalida<<endl;

	archivoSalida.close();
}


