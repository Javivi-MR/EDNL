/*
    Contar cuantos nodos del árbol booleano A son rebeldes, un nodo es rebelde si es diferente que la mayoría de sus ancestros 
    (si es distinto de lo que sea la mayoría de sus ancestros)

*/

#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

int ContarNodos(Abin<bool> A);
int ContarNodosRec(Abin<bool> A,Abin<bool>::nodo n);
int contarAntecesoresRec(Abin<bool> A,Abin<bool>::nodo n);
int AntecesoresIguales(Abin<bool> A,Abin<bool>::nodo n,bool aux);

int main()
{
    Abin<bool> A;

    A.insertarRaiz(true);

    Abin<bool>::nodo n = A.raiz();

    A.insertarHijoIzqdo(n,false);

    A.insertarHijoDrcho(n,true);

    n = A.hijoDrcho(n);

    A.insertarHijoDrcho(n,false);

    A.insertarHijoIzqdo(n,true);

    n = A.hijoIzqdo(n);

    A.insertarHijoIzqdo(n,false);

    A.insertarHijoDrcho(n,true);

    int NumNodosReb = ContarNodos(A);

    cout << "El numero de nodos rebeldes es: " << NumNodosReb << endl;

    return 0;
}

int ContarNodos(Abin<bool> A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return ContarNodosRec(A,A.raiz());
    }
}

int ContarNodosRec(Abin<bool> A,Abin<bool>::nodo n)
{
    if(n == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        bool aux = A.elemento(n);
        if(AntecesoresIguales(A,n,aux) < (contarAntecesoresRec(A,n)/2))
        {
            return 1 + ContarNodosRec(A,A.hijoIzqdo(n)) + ContarNodosRec(A,A.hijoDrcho(n));
        }
        else
        {
            return ContarNodosRec(A,A.hijoIzqdo(n)) + ContarNodosRec(A,A.hijoDrcho(n));
        }
    }
}



int contarAntecesoresRec(Abin<bool> A,Abin<bool>::nodo n)
{
    if(A.padre(n) == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + contarAntecesoresRec(A,A.padre(n));
    }
}

int AntecesoresIguales(Abin<bool> A,Abin<bool>::nodo n,bool aux)
{
    if(A.padre(n) == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(A.elemento(A.padre(n)) == aux)
        {
            return 1 + AntecesoresIguales(A,A.padre(n),aux);
        }
        else
        {
            return AntecesoresIguales(A,A.padre(n),aux);
        }
    }
}