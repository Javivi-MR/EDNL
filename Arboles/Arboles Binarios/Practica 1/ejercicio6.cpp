#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

int desequilibrioNodo(Abin<tElto> A);
int desequilibrioNodoRec(Abin<tElto> A,Abin<tElto>::nodo n);
int AlturaArbolRec(Abin<tElto>::nodo n, Abin<tElto> A);

int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    imprimirAbin(fs, A, fin); // En fichero.

    int desequilibrio = desequilibrioNodo(A);

    cout << "La desequilibrio del arbol es: " << desequilibrio << endl; 

    return 0;
}

int desequilibrioNodo(Abin<tElto> A)
{
    if(A.arbolVacio())
    {
        return 0; 
    }
    else
    {
        return desequilibrioNodoRec(A,A.raiz());
    }
}

int desequilibrioNodoRec(Abin<tElto> A,Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return max(abs(AlturaArbolRec(A.hijoDrcho(n),A) - AlturaArbolRec(A.hijoIzqdo(n),A)), max(desequilibrioNodoRec(A,A.hijoDrcho(n)),desequilibrioNodoRec(A,A.hijoIzqdo(n))));
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
