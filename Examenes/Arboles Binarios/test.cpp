#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

void eliminarHijos(Abin<tElto> A);

int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    eliminarHijos(A);

    ofstream fs("abin.dat"); // Abrir fichero de salida.
    imprimirAbin(fs, A, fin); // En fichero.

    cout << "Arbol cortado con exito (Para consultarlo, mirar el fichero Abin.dat)" << endl; 

    return 0;
}

void eliminarHijos(Abin<tElto> A)
{
    A.eliminarHijoIzqdo(A.hijoIzqdo(A.raiz()));
}