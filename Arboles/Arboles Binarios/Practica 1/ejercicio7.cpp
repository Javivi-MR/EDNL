#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

bool pseudocompleto(Abin<tElto> A);
bool pseudocompletoRec(Abin<tElto> A,Abin<tElto>::nodo n,int altura);
int AlturaArbol(Abin<tElto> A);
int AlturaArbolRec(Abin<tElto>::nodo n, Abin<tElto> A);
int profundidadNodoRec(Abin<tElto> A,Abin<tElto>::nodo n);


int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    imprimirAbin(fs, A, fin); // En fichero.

    bool pseudo = pseudocompleto(A);

    if(pseudo)
    {
        cout << "El arbol es pseudo completo" << endl;
    }
    else
    {
        cout << "El arbol NO es pseudo completo" << endl;
    }
     

    return 0;
}

bool pseudocompleto(Abin<tElto> A)
{
    if(A.arbolVacio())
    {
        return true;
    }
    else
    {
        int altura = AlturaArbol(A);
        return pseudocompletoRec(A,A.raiz(),altura);
    }
}

bool pseudocompletoRec(Abin<tElto> A,Abin<tElto>::nodo n,int altura)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(altura - 1 != profundidadNodoRec(A,n))
        {
            return pseudocompletoRec(A,A.hijoDrcho(n),altura) && pseudocompletoRec(A,A.hijoIzqdo(n),altura);
        }
        else
        {
            if((A.hijoDrcho(n) == Abin<tElto>::NODO_NULO && A.hijoIzqdo(n) == Abin<tElto>::NODO_NULO) || (A.hijoDrcho(n) != Abin<tElto>::NODO_NULO && A.hijoIzqdo(n) != Abin<tElto>::NODO_NULO))
            {
                return true;
            }
            else
            {
                return false;
            }
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