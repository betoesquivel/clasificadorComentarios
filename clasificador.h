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
bool debug = true;
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
		clasificador(string nComentarios, string nPalabrasClave, string nPalabrasIgnoradas, string nSalida);

		void convertirAMinusculas(string &s);
		void quitarSignosDePuntuacion(string &s);
		void resetearContadorCategorias(NodoArbol<string,int>* inicial);

		void clasificarPalabra(string palabra);
		void clasificarComentario(string comentario);
		void clasificarArchivoDeComentarios();

		void llenarArbolPalabrasClave();
		void llenarArbolPalabrasIgnoradas();

		void escribirComentarioEnArchivo(string comentario, string categoria);

		void desplegarPalabrasClave(){palabrasClave.desplegarArbol(palabrasClave.getRaiz());}
		void desplegarCategorias(){categorias.desplegarArbol(categorias.getRaiz());}
		void desplegarPalabrasIgnoradas(){palabrasIgnoradas.desplegarArbol(palabrasIgnoradas.getRaiz());}
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

clasificador::clasificador(string nComentarios, string nPalabrasClave, string nPalabrasIgnoradas, string nSalida)
{
	//Al inicializar con este constructor el clasificador, el arbol de categorias se creara conforme se leen las palabras clave.
	nom_ArchivoComentarios = nComentarios;
	nom_ArchivoPalabrasClave = nPalabrasClave;
	nom_ArchivoPalabrasIgnoradas = nPalabrasIgnoradas;
	nom_ArchivoSalida = nSalida;

	palabrasClave.setDebug(false);
	palabrasIgnoradas.setDebug(false);
	categorias.setDebug(debug);
}

void clasificador::llenarArbolPalabrasClave()
{
	ifstream archivoPalabrasClave;
	archivoPalabrasClave.open(nom_ArchivoPalabrasClave.c_str());
	string palabra, categoria;
	while(archivoPalabrasClave>>palabra>>categoria)
	{
		palabrasClave.insertar(palabra,categoria);
		if(!categorias.existe(categoria)){
			categorias.insertar(categoria,0);
		}
	}
	archivoPalabrasClave.close();	
}

void clasificador::llenarArbolPalabrasIgnoradas()
{
	ifstream archivoPalabrasIgnoradas;
	archivoPalabrasIgnoradas.open(nom_ArchivoPalabrasIgnoradas.c_str());
	string palabra;
	int dato2 = 0;//Solamente es el segundo dato en el arbol. Por ahora es inutil. Puede usarse para futuras optimizaciones.
	while(archivoPalabrasIgnoradas>>palabra)
	{
		palabrasIgnoradas.insertar(palabra,dato2);
	}
	archivoPalabrasIgnoradas.close();	
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
			NodoArbol<string, int> *categoriaEncontrada = categorias.encontrar(palabraEncontrada->info2);		
			categoriaEncontrada->info2 += 1; 

			if(categoriaMayor!=NULL){
				categoriaMayor = (categoriaMayor->info2 < categoriaEncontrada->info2) ? categoriaEncontrada:categoriaMayor;	
			}else{
				categoriaMayor = categoriaEncontrada;
			}
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
	inicial->info2 = 0;	
	resetearContadorCategorias(inicial->izq);	
	resetearContadorCategorias(inicial->der);
}

void clasificador::clasificarComentario(string comentario)
{	
	string temp = comentario;
	trim(temp);
	quitarSignosDePuntuacion(temp);
	convertirAMinusculas(temp);

	istringstream iss(temp);
	string palabra = ""; 
	while(iss>>palabra){
		clasificarPalabra(palabra);
		cout<<"Termine de clsificar la palabra.."<<endl;
		cout<<palabra<<'.'<<endl;
	}
	// unsigned int i = 0;
	// while (i < temp.length()) {
	// 	if (temp[i]==' ') {
	// 		trim(palabra);
	// 		// clasificarPalabra(palabra);
	// 		cout<<palabra<<endl;
	// 		palabra = "";
	// 	}else{
	// 		palabra+=temp[i];
	// 	}
	// 	
	// 	i++;		
	// }
	cout<<"salgo del while"<<endl;

	if(categoriaMayor == NULL){
		cout<<"No pude clasificar ese comentario."<<endl;
	}else{
		// escribirComentarioEnArchivo(comentario,categoriaMayor->info);
	}

	// if (debug) {
	// 	cout<<"DEBUG::Categoria del comentario: "<<categoriaMayor->info<<endl;
	// 	cout<<"---------DEBUG-----------"<<endl;
	// 	cout<<comentario<<endl;
	// 	cout<<"DEBUG::Comentario contaba con "<<categoriaMayor->info2<<" coincidencias"<<endl;
	// }

	//bug 2
	// resetearContadorCategorias(categorias.getRaiz());
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
		if(debug) {
			cout<<"Linea: "<<linea<<endl;
		}
		if(linea == ""){
			if (debug) {
				cout<<"DEBUG::Salto de linea en el archivo."<<endl;
			}
			clasificarComentario(comentario);
			comentario = "";
		}else{
			trim(linea);
			comentario += "\n ";
			comentario += linea;
		}
	}
	if (debug) {
		cout<<"DEBUG::Ultimo comentario."<<endl;
	}
	clasificarComentario(comentario);
	comentario = "";
	archivoComentarios.close();
}

//bug 1
void clasificador::escribirComentarioEnArchivo(string comentario, string categoria)
{
	if(debug)
		cout<<"escribiendo el comentario"<<endl;
	ofstream archivoSalida;
	if(debug)
		cout<<"abro el archivo"<<endl;
	archivoSalida.open(nom_ArchivoSalida.c_str());
	if(debug)
		cout<<"imprimo la categoria en el archivo rodeada de llaves"<<endl;
	archivoSalida<<"<"<<categoria<<">"<<endl;
	archivoSalida<<comentario<<endl;
	archivoSalida<<endl;

	archivoSalida.close();
}


