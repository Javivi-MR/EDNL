/*
Parcial 1 - 23/03/2017

Implemente una función que modifique un árbol binario de forma que si el árbol tiene nodos con un solo hijo, se elimine toda la descendencia de dichos nodos.



NOTA: MUY IMPORTANTE EL & EN LOS ARBOLES, PARA PASARLOS POR REFERENCIA Y EL ARBOL QUE ESTÉ EN EL MAIN SEA EL QUE SE CORTA :)


*/

#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

void eliminarHijos(Abin<tElto> &A);
void eliminarHijosRec(Abin<tElto>& A,Abin<tElto>::nodo n);
void eliminarDescendencia(Abin<tElto>& A,Abin<tElto>::nodo na,Abin<tElto>::nodo n,int p);
void eliminarDescendenciaRec(Abin<tElto>& A,Abin<tElto>::nodo na,Abin<tElto>::nodo n);

int AlturaArbol(Abin<tElto> A);
int AlturaArbolRec(Abin<tElto>::nodo n, Abin<tElto> A);
int profundidadNodoRec(Abin<tElto> A,Abin<tElto>::nodo n);


int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    eliminarHijos(A);

    ofstream fs("abin.dat"); // Abrir fichero de salida.
    imprimirAbin(fs, A, fin); // En fichero.

    cout << "Arbol cortado con exito (Comprueba que se han cortado en Abin.dat :) )" << endl;

    return 0;
}

void eliminarHijos(Abin<tElto>& A)
{
    if(!A.arbolVacio())
    {
        eliminarHijosRec(A,A.raiz());
    }
}

void eliminarHijosRec(Abin<tElto>& A,Abin<tElto>::nodo n)
{
    if(n != Abin<tElto>::NODO_NULO)
    {
        if(A.hijoIzqdo(n) != Abin<tElto>::NODO_NULO && A.hijoDrcho(n) == Abin<tElto>::NODO_NULO)
        {
            int profundidadmax = AlturaArbol(A);
            eliminarDescendencia(A,n,A.hijoIzqdo(n),profundidadmax);
        }
        if(A.hijoIzqdo(n) == Abin<tElto>::NODO_NULO && A.hijoDrcho(n) != Abin<tElto>::NODO_NULO)
        {
            int profundidadmax = AlturaArbol(A);
            eliminarDescendencia(A,n,A.hijoDrcho(n),profundidadmax);
        }
        if(A.hijoIzqdo(n) != Abin<tElto>::NODO_NULO && A.hijoDrcho(n) != Abin<tElto>::NODO_NULO)
        {
            eliminarHijosRec(A,A.hijoIzqdo(n));
            eliminarHijosRec(A,A.hijoDrcho(n));
        }
    }
}

void eliminarDescendencia(Abin<tElto>& A,Abin<tElto>::nodo na,Abin<tElto>::nodo n,int p)
{
    if(n != Abin<tElto>::NODO_NULO)
    {
        if(p == profundidadNodoRec(A,n))
        {
            eliminarDescendenciaRec(A,na,n);
        }
        else
        {
            eliminarDescendencia(A,na,A.hijoIzqdo(n),p);
            eliminarDescendencia(A,na,A.hijoDrcho(n),p);
        }
    }

}

void eliminarDescendenciaRec(Abin<tElto>& A,Abin<tElto>::nodo na,Abin<tElto>::nodo n)
{
    if(n != na)
    {   
        
        Abin<tElto>::nodo naux = A.padre(n);
        if(A.hijoIzqdo(naux) != Abin<tElto>::NODO_NULO && A.hijoDrcho(naux) != Abin<tElto>::NODO_NULO)
        {
            A.eliminarHijoDrcho(naux);
            A.eliminarHijoIzqdo(naux);
            eliminarDescendenciaRec(A,na,naux);
        }
        if(A.hijoIzqdo(naux) != Abin<tElto>::NODO_NULO && A.hijoDrcho(naux) == Abin<tElto>::NODO_NULO)
        {
            A.eliminarHijoIzqdo(naux);
            eliminarDescendenciaRec(A,na,naux);
        }
        if(A.hijoIzqdo(naux) == Abin<tElto>::NODO_NULO && A.hijoDrcho(naux) != Abin<tElto>::NODO_NULO)
        {
            A.eliminarHijoDrcho(naux);
            eliminarDescendenciaRec(A,na,naux);
        }
    }
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