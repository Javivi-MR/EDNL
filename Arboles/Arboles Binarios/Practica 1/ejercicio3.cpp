#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

int produndidadNodo(Abin<tElto> A,Abin<tElto>::nodo n);
int profundidadNodoRec(Abin<tElto> A,Abin<tElto>::nodo n);


int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    imprimirAbin(fs, A, fin); // En fichero.

    int profundidad = produndidadNodo(A,A.hijoDrcho(A.raiz()));

    cout << "La altura del arbol es: " << profundidad << endl; 

    return 0;
}

int produndidadNodo(Abin<tElto> A,Abin<tElto>::nodo n)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return profundidadNodoRec(A,n);
    }
}

int profundidadNodoRec(Abin<tElto> A,Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + profundidadNodoRec(A,A.padre(n));
    }
}