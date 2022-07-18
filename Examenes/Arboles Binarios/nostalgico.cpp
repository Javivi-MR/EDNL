/*

    Cuenta nodos nostálgicos (tienen más ancestros que sucesores)

*/

#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

int nostalgicos(Abin<tElto> A);
int nostalgicosRec(Abin<tElto> A,Abin<tElto>::nodo n);
int Ascentros(Abin<tElto> A,Abin<tElto>::nodo n);
int Sucesores(Abin<tElto> A,Abin<tElto>::nodo n);

int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    imprimirAbin(fs, A, fin); // En fichero.

    int numNodos = nostalgicos(A);

    cout << "Numero de nodos nostajicos es de: " << numNodos << endl; 

    return 0;
}

int nostalgicos(Abin<tElto> A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return nostalgicosRec(A,A.raiz());
    }
}

int nostalgicosRec(Abin<tElto> A,Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(Ascentros(A,n) > Sucesores(A,n))
        {
            return 1 + nostalgicosRec(A,A.hijoIzqdo(n)) + nostalgicosRec(A,A.hijoDrcho(n));
        }
        else
        {
            return nostalgicosRec(A,A.hijoIzqdo(n)) + nostalgicosRec(A,A.hijoDrcho(n));
        }
    }
}

int Ascentros(Abin<tElto> A,Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + Ascentros(A,A.padre(n));
    }
}

int Sucesores(Abin<tElto> A,Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + Ascentros(A,A.hijoIzqdo(n)) + Ascentros(A,A.hijoDrcho(n));
    }
}