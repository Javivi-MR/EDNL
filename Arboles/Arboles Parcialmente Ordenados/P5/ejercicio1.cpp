#include <iostream>
#include "abin.hpp"
#include "abin_E-S.h"

typedef int tElto;
const tElto fin = -1;

using namespace std;

void eliminarnodo(Abin<int>& A, int a);
void eliminacionRec(Abin<int>& A, Abin<int>::nodo n);
void localizarNodoRec(Abin<int>& A, int a, Abin<int>::nodo n);
void quitarNodo(Abin<int>& A,Abin<int>::nodo n);

int main()
{
    Abin<int> A;
    rellenarAbin(A,fin);
    
    eliminarnodo(A,9);

    ofstream fs("abin.dat"); // Abrir fichero de salida. 

    imprimirAbin(fs,A,fin);
    fs.close();

    return 0;
}


void eliminarnodo(Abin<int>& A, int a)
{
    if(!A.arbolVacio())
    {
        localizarNodoRec(A,a,A.raiz());
    }
}

void localizarNodoRec(Abin<int>& A, int a, Abin<int>::nodo n)
{
    if(n != Abin<int>::NODO_NULO)
    {
        if(n->elto == a)
        {
            eliminacionRec(A,n);
        }
        else
        {
            localizarNodoRec(A,a,A.hijoIzqdo(n));
            localizarNodoRec(A,a,A.hijoIzqdo(n));
        }
    }
}

void eliminacionRec(Abin<int>& A, Abin<int>::nodo n)
{
    if(n != Abin<int>::NODO_NULO)
    {
        int aux;
        if(A.hijoIzqdo(n) != Abin<int>::NODO_NULO && A.hijoDrcho(n) != Abin<int>::NODO_NULO)
        {
            if(A.elemento(A.hijoIzqdo(n)) < A.elemento(A.hijoDrcho(n)))
            {
                aux = A.elemento(n);
                A.elemento(n) = A.elemento(A.hijoIzqdo(n));
                A.elemento(A.hijoIzqdo(n)) = aux;
                eliminacionRec(A,A.hijoIzqdo(n));
            }
            else
            {
                aux = A.elemento(n);
                A.elemento(n) = A.elemento(A.hijoDrcho(n));
                A.elemento(A.hijoDrcho(n)) = aux;
                eliminacionRec(A,A.hijoDrcho(n));      
            }
        }
        if(A.hijoIzqdo(n) == Abin<int>::NODO_NULO && A.hijoDrcho(n) == Abin<int>::NODO_NULO)
        {
            quitarNodo(A,n);
        }
        if(A.hijoIzqdo(n) != Abin<int>::NODO_NULO && A.hijoDrcho(n) == Abin<int>::NODO_NULO)
        {
            aux = A.elemento(n);
            A.elemento(n) = A.elemento(A.hijoIzqdo(n));
            A.elemento(A.hijoIzqdo(n)) = aux;
            eliminacionRec(A,A.hijoIzqdo(n));
        }
        if(A.hijoIzqdo(n) == Abin<int>::NODO_NULO && A.hijoDrcho(n) != Abin<int>::NODO_NULO)
        {
            aux = A.elemento(n);
            A.elemento(n) = A.elemento(A.hijoDrcho(n));
            A.elemento(A.hijoDrcho(n)) = aux;
            eliminacionRec(A,A.hijoDrcho(n));        
        }
    }

}

void quitarNodo(Abin<int>& A,Abin<int>::nodo n)
{
    if(A.hijoIzqdo(A.padre(n)) == n)
    {
        A.eliminarHijoIzqdo(A.padre(n));
    }
    else
    {
        A.eliminarHijoDrcho(A.padre(n));
    }
}