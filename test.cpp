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
	cout<<"Compila."<<endl;	
	ArbolAVL<string, string> lista(true);
	
	string entrada = "";	
	string categoria = "prueba";
	while(entrada!="0")
	{
		cin>>entrada;
		if(entrada!="0"){
			lista.insertar(entrada, categoria);
		}
	}
	lista.desplegarArbol(lista.getRaiz());
	return 0;
}

