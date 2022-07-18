/*
    Contar cuantos nodos del árbol A tienen exactamente 3 nietos.
*/

#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

int Nietos(Abin<tElto> A);
int NietosRec(Abin<tElto> A,Abin<tElto>::nodo n);


int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    imprimirAbin(fs, A, fin); // En fichero.

    int numNodos = Nietos(A);

    cout << "Numero de nodos con 3 nietos del arbol es: " << numNodos << endl; 

    return 0;
}

int Nietos(Abin<tElto> A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return NietosRec(A,A.raiz());
    }
}

int NietosRec(Abin<tElto> A,Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        Abin<tElto>::nodo ni = A.hijoIzqdo(n);
        Abin<tElto>::nodo nd = A.hijoDrcho(n);
        if(ni != Abin<tElto>::NODO_NULO && nd != Abin<tElto>::NODO_NULO)
        {
            if((A.hijoIzqdo(ni) != Abin<tElto>::NODO_NULO && A.hijoDrcho(ni) != Abin<tElto>::NODO_NULO && (A.hijoIzqdo(nd) == Abin<tElto>::NODO_NULO || A.hijoDrcho(nd) == Abin<tElto>::NODO_NULO)) || (A.hijoIzqdo(nd) != Abin<tElto>::NODO_NULO && A.hijoDrcho(nd) != Abin<tElto>::NODO_NULO && (A.hijoIzqdo(ni) == Abin<tElto>::NODO_NULO || A.hijoDrcho(ni) == Abin<tElto>::NODO_NULO)))
            {
                return 1 + NietosRec(A,ni) + NietosRec(A,nd);
            }
            else
            {
                return NietosRec(A,ni) + NietosRec(A,nd);
            }
        }
        else
        {
            return NietosRec(A,ni) + NietosRec(A,nd); // Da igual que cualquiera sea nulo ( contaran como 0 :) )
        }
    }
}