// Descripcion: Clasifica comentarios dentro de una de las distintas categorias
// basándose en las listas de palabras clave que identifican cada categoría. 
// Guardo las palabras en un árbol de búsqueda binario conforme van apareciendo, 
// dependiendo de la cantidad de veces que aparece la palabra, es la prioridad
// que tiene en el árbol. Tal vez pueda utilizar mejor una priorityqueue para
// las palabras.
// 
// Autor: José Alberto Esquivel Patino A01139626
// Carrera: BCT
// Clase: Estructura de Datos
// Profesor: Roman Martinez Martinez
//
#include <queue>
class clasificador{
	private: 
		priority_queue<string> clave_biblioteca;
		priority_queue<string> clave_informatica;
		priority_queue<string> clave_tesoreria;
	public:
		clasificador(string nombreArchivoBaseDeDatos); 
		string clasificar(string comentario);
};
