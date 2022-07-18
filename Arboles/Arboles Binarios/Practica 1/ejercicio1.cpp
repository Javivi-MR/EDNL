#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

int ContarNodos(Abin<tElto> A);
int ContarNodosRec(Abin<tElto>::nodo n, Abin<tElto> A);

int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    imprimirAbin(fs, A, fin); // En fichero.

    int NumNodos = ContarNodos(A);

    cout << "El numero de nodos es: " << NumNodos << endl;

    return 0;
}

int ContarNodos(Abin<tElto> A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return ContarNodosRec(A.raiz(),A);
    }
}

int ContarNodosRec(Abin<tElto>::nodo n, Abin<tElto> A)
{
    if(Abin<tElto>::NODO_NULO == n)
    {
        return 0;
    }
    return 1 + ContarNodosRec(A.hijoDrcho(n),A) + ContarNodosRec(A.hijoIzqdo(n),A);
}
