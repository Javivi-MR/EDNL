#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

bool similares(Abin<tElto> A,Abin<tElto> B);
bool similaresRec(Abin<tElto> A,Abin<tElto> B,Abin<tElto>::nodo na,Abin<tElto>::nodo nb);

int main()
{
    Abin<tElto> A,B;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fsa("abina.dat"); // Abrir fichero de salida.

    imprimirAbin(fsa, A, fin); // En fichero.

    cout << "*** Lectura del arbol binario B ***\n";

    rellenarAbin(B, fin); // Desde std::cin

    ofstream fsb("abinb.dat"); // Abrir fichero de salida.

    imprimirAbin(fsb, B, fin); // En fichero.

    bool flag = similares(A,B);

    if(flag)
    {
        cout << "Los arboles son similares" << endl; 
    }
    else
    {
        cout << "Los arboles NO son similares" << endl; 
    }

    return 0;
}

bool similares(Abin<tElto> A,Abin<tElto> B)
{
    return similaresRec(A,B,A.raiz(),B.raiz());
}

bool similaresRec(Abin<tElto> A,Abin<tElto> B,Abin<tElto>::nodo na,Abin<tElto>::nodo nb)
{
    if(na == Abin<tElto>::NODO_NULO && nb == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if((na == Abin<tElto>::NODO_NULO && nb != Abin<tElto>::NODO_NULO)||(na != Abin<tElto>::NODO_NULO && nb == Abin<tElto>::NODO_NULO))
        {
            return false;
        }
        if(na != Abin<tElto>::NODO_NULO && nb != Abin<tElto>::NODO_NULO)
        {
            return true && similaresRec(A,B,A.hijoDrcho(na),B.hijoDrcho(nb)) && similaresRec(A,B,A.hijoIzqdo(na),B.hijoIzqdo(nb));
        }
    }
}