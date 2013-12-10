/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  aqui hago las pruebas unitarias de mis clases.
 *
 *        Version:  1.0
 *        Created:  24/11/13 14:26:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Alberto Esquivel Patino (), 
 *   Organization:  ITESM Campus Monterrey
 *
 * =====================================================================================
 */

#include <iostream>
#include <queue>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>

using namespace std;

#include "ArbolAVL.h"
#include "clasificador.h"

int main(int argc, const char *argv[])
{
	cout<<"Bienvenido al programa de clasificacion de comentarios."<<endl;	
	string nArchComentarios, nArchPalabrasClave, nArchPalabrasIgnoradas, nArchSalida;  	

	nArchComentarios = "prueba.txt";
	nArchPalabrasClave = "palabrasClave.txt";
	nArchPalabrasIgnoradas = "palabrasIgnoradas.txt";
 
	cout<<"Introduzca el nombre del archivo salida: "<<endl;
	cin>>nArchSalida;
	if (nArchSalida == "default") {
		nArchSalida = "salidaEjemplo.txt";
	}
	
	clasificador bob(nArchComentarios, nArchPalabrasClave, nArchPalabrasIgnoradas, nArchSalida);
	bob.llenarArbolPalabrasClave();
	bob.llenarArbolPalabrasIgnoradas();	
 	
	cout<<"Estas son las palabras clave: "<<endl;
	bob.desplegarPalabrasClave();
	
	cout<<"Estas son las categorias: "<<endl;
	bob.desplegarCategorias();
	
	cout<<"Estas son las palabras ignoradas: "<<endl;
	bob.desplegarPalabrasIgnoradas();
	
	bob.clasificarArchivoDeComentarios();
	cout<<endl;
	cout<<"========================================================================"<<endl;
	// cout<<"Gracias por utilizar la aplicación. Se ha generado el archivo de salida: "<<nArchSalida<<endl;
	cout<<"Gracias por utilizar la aplicación. Se ha generado el archivo de salida para cada categoria."<<endl;

	return 0;
}

