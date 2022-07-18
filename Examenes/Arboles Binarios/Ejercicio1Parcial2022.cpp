/*
    PRIMER PARCIAL 2022
    Dado un arbol binario de un tipo generico T calcular el numero de nodos que siendo hermanos entre si, 
    tienen la misma raiz y sus subarboles son reflejados (respecto a sus elementos)

    Ejemplo :                             a
                                    b          b
                                c       d   d     c

    Hay 2 nodos reflejados.

    Otro ejemplo :                        a
                                    b          b
                                  c   c      c   c
    
    Hay 6 nodos reflejados.
*/

#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

int ContarNodos(Abin<tElto> A);
int ContarNodosRec(Abin<tElto> A,Abin<tElto>::nodo ni,Abin<tElto>::nodo nd);

int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    imprimirAbin(fs, A, fin); // En fichero.

    int NumNodos = ContarNodos(A);

    cout << "El numero de nodos reflejados es: " << NumNodos << endl;

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
        return ContarNodosRec(A,A.hijoIzqdo(A.raiz()),A.hijoDrcho(A.raiz()));
    }
}

int ContarNodosRec(Abin<tElto> A,Abin<tElto>::nodo ni,Abin<tElto>::nodo nd)
{
    if(ni == Abin<tElto>::NODO_NULO && nd == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(ni != Abin<tElto>::NODO_NULO && nd != Abin<tElto>::NODO_NULO)
        {
            if (A.elemento(ni) == A.elemento(nd))
            {
                return 2 + ContarNodosRec(A,A.hijoIzqdo(ni),A.hijoDrcho(ni)) + ContarNodosRec(A,A.hijoIzqdo(nd),A.hijoDrcho(nd));
            }
        }

        if(ni != Abin<tElto>::NODO_NULO && nd == Abin<tElto>::NODO_NULO)
        {
            return ContarNodosRec(A,A.hijoIzqdo(ni),A.hijoDrcho(ni));
        }

        if(ni == Abin<tElto>::NODO_NULO && nd != Abin<tElto>::NODO_NULO)
        {
            return ContarNodosRec(A,A.hijoIzqdo(nd),A.hijoDrcho(nd));
        }
    }
}