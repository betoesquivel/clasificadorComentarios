/*
 * =====================================================================================
 *
 *       Filename:  ejemplo.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  27/11/13 22:55:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Alberto Esquivel Patino (), 
 *   Organization:  ITESM Campus Monterrey
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
using namespace std; 
int main(int argc, const char *argv[])
{
	ifstream entrada;
	entrada.open("ejemplo.txt");
	string s;
	entrada>>s;
	cout<<s<<endl;
	ofstream salida;

	salida.open("sal.txt");	
	salida<<"What up, gayum!?"<<endl;

	entrada.close();
	salida.close();
	return 0;
}
