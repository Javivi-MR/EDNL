#include <iostream>
#include <fstream>
#include "agen.hpp"
#include "agen_E-S.h"

typedef char tElto;

const tElto fin = '#';

using namespace std;

int profundidad(Agen<tElto> A , Agen<tElto>::nodo n);
int profundidadRec(Agen<tElto> A , Agen<tElto>::nodo n);

int main()
{
    Agen<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAgen(A,fin);
        
    ofstream fs("agen.dat"); // Abrir fichero de salida.

    imprimirAgen(fs, A, fin); // En fichero.

    Agen<tElto>::nodo n = A.hijoIzqdo(A.hijoIzqdo(A.raiz()));

    int p = profundidad(A,n);

    cout << "la profundidad del nodo es: " << p << endl;

    return 0;
}

int profundidad(Agen<tElto> A , Agen<tElto>::nodo n)
{
    return profundidadRec(A,n);
}

int profundidadRec(Agen<tElto> A , Agen<tElto>::nodo n)
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + profundidadRec(A,A.padre(n));
    }
}