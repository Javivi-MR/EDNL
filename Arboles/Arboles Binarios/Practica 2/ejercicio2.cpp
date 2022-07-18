/*
    IMPORTANTE: PARA COMPROBAR VER EL FICHERO Abin.dat Y AHI ESTARA EL ARBOL Breflejado
*/
#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

Abin<tElto> reflejarArbol(Abin<tElto> B);
void reflejarArbolRec(Abin<tElto> B,Abin<tElto> A,Abin<tElto>::nodo na,Abin<tElto>::nodo nd,Abin<tElto>::nodo ni);

int main()
{
    Abin<tElto> B;

    cout << "*** Lectura del arbol binario B ***\n";

    rellenarAbin(B, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    Abin<tElto> Breflejado = reflejarArbol(B);

    imprimirAbin(fs, Breflejado, fin); // En fichero.

    cout << "Arbol reflejado con exito" << endl; 

    return 0;
}

Abin<tElto> reflejarArbol(Abin<tElto> B)
{
    Abin<tElto> A;
    A.insertarRaiz(B.elemento(B.raiz()));
    reflejarArbolRec(B,A,A.raiz(),B.hijoDrcho(B.raiz()),B.hijoIzqdo(B.raiz()));
    return A;
}

void reflejarArbolRec(Abin<tElto> B,Abin<tElto> A,Abin<tElto>::nodo na,Abin<tElto>::nodo nd,Abin<tElto>::nodo ni)
{
    if(nd != Abin<tElto>::NODO_NULO && ni != Abin<tElto>::NODO_NULO)
    {
        A.insertarHijoDrcho(na,B.elemento(ni));
        A.insertarHijoIzqdo(na,B.elemento(nd));
        reflejarArbolRec(B,A,A.hijoDrcho(na),B.hijoDrcho(ni),B.hijoIzqdo(ni));
        reflejarArbolRec(B,A,A.hijoIzqdo(na),B.hijoDrcho(nd),B.hijoIzqdo(nd));
    }
    if(nd == Abin<tElto>::NODO_NULO && ni != Abin<tElto>::NODO_NULO)
    {
        A.insertarHijoDrcho(na,B.elemento(ni));
        reflejarArbolRec(B,A,A.hijoDrcho(na),B.hijoDrcho(ni),B.hijoIzqdo(ni));
    }
    if(nd != Abin<tElto>::NODO_NULO && ni == Abin<tElto>::NODO_NULO)
    {
        A.insertarHijoIzqdo(na,B.elemento(nd));
        reflejarArbolRec(B,A,A.hijoIzqdo(na),B.hijoDrcho(nd),B.hijoIzqdo(nd));
    }
}