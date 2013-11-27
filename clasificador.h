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
//ocupo <fstream> y <iostream>
bool debug = false;
class clasificador{
	private: 
		ArbolAVL<string> palabrasClave;
		ArbolAVL<string> palabrasIgnoradas;
		string nom_ArchivoComentarios;
		string nom_ArchivoPalabrasClave;
		string nom_ArchivoPalabrasIgnoradas;
		string nom_ArchivoSalida; 

	public:
		clasificador(string nombreArchivoComentarios, string nombreArchivoSalida, string nombreArchivoPalabrasClave, string nombreArchivoPalabrasIgnoradas);
		string clasificar(string comentario);
		void llenarArbolPalabrasClave();
		void llenarArbolPalabrasIgnoradas();
		void escribirComentarioEnArchivo(string comentario, string categoria);
};

clasificador::clasificador(string nombreArchivoComentarios, string nombreArchivoSalida, string nombreArchivoPalabrasClave, string nombreArchivoPalabrasIgnoradas)
{
	nom_ArchivoComentarios = nombreArchivoComentarios;
	nom_ArchivoSalida = nombreArchivoSalida;
	nom_ArchivoPalabrasClave = nombreArchivoPalabrasClave;
	nom_ArchivoPalabrasIgnoradas = nombreArchivoPalabrasIgnoradas;
}

void clasificador::llenarArbolPalabrasClave()
{
	ifstream archivoPalabrasClave;
	archivoPalabrasClave.open(nom_ArchivoPalabrasClave.c_str());
	string palabra, categoria;
	while(archivoPalabrasClave>>palabra>>categoria)
	{
		palabrasClave.insertar(palabra,categoria);
	}
	archivoPalabrasClave.close();	
}

void clasificador::llenarArbolPalabrasIgnoradas()
{
	ifstream archivoPalabrasIgnoradas;
	archivoPalabrasIgnoradas.open(nom_ArchivoPalabrasIgnoradas.c_str());
	string palabra, categoria = "ignorada";
	while(archivoPalabrasIgnoradas>>palabra)
	{
		palabrasIgnoradas.insertar(palabra,categoria);
	}
	archivoPalabrasIgnoradas.close();	
}

void clasificador::escribirComentarioEnArchivo(string comentario, string categoria)
{
	ofstream archivoSalida;
	archivoSalida.open(nom_ArchivoSalida.c_str());
	archivoSalida<<"<"<<categoria<<">"<<endl;
	archivoSalida<<comentario<<endl;
	archivoSalida<<endl;

	archivoSalida.close();
}


