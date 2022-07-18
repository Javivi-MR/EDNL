#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

int AlturaArbol(Abin<tElto> A);
int AlturaArbolRec(Abin<tElto>::nodo n, Abin<tElto> A);


int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    imprimirAbin(fs, A, fin); // En fichero.

    int Altura = AlturaArbol(A);

    cout << "La altura del arbol es: " << Altura << endl; 

    return 0;
}

int AlturaArbol(Abin<tElto> A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return AlturaArbolRec(A.raiz(),A);
    }
}

int AlturaArbolRec(Abin<tElto>::nodo n, Abin<tElto> A)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + max(AlturaArbolRec(A.hijoDrcho(n),A),AlturaArbolRec(A.hijoIzqdo(n),A));
    }
}
