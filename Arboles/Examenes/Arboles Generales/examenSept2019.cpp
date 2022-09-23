/*
    Implementa un subprograma que devuelva el porcentaje de descendientes propios de un arbol general que sean multiplo de 3
*/
#include <iostream>
#include <fstream>
#include "agen.hpp"
#include "agen_E-S.h"

typedef char tElto;

const tElto fin = '#';

using namespace std;

float PorcentajeDescMul3(Agen<tElto>& A);
float PorcentajeDescMul3Rec(Agen<tElto>& A, Agen<tElto>::nodo n);
size_t TotalNodosArbol(Agen<tElto>& A);
size_t TotalNodosArbolRec(Agen<tElto>& A, Agen<tElto>::nodo n);
size_t descendientesPropiosRec(Agen<tElto>& A, Agen<tElto>::nodo n);

int main()
{
    Agen<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAgen(A,fin);
        
    ofstream fs("agen.dat"); // Abrir fichero de salida

    float porcentaje = PorcentajeDescMul3(A);

    cout << "El porcentaje de descendientes propios de un arbol general que sean multiplo de 3 es de un " << porcentaje << "%";

    return 0;
}

float PorcentajeDescMul3(Agen<tElto>& A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        size_t numNodos = TotalNodosArbol(A);
        return (PorcentajeDescMul3Rec(A,A.raiz()) / numNodos) * 100;
    }
}

float PorcentajeDescMul3Rec(Agen<tElto>& A, Agen<tElto>::nodo n)
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t sum = 0;
        size_t desPropios = descendientesPropiosRec(A,n);
        Agen<tElto>::nodo p = A.hijoIzqdo(n);
        if(desPropios % 3 == 0 && desPropios != 0)
        {
            sum++;
        }
        while(p != Agen<tElto>::NODO_NULO)
        {
            sum = sum + PorcentajeDescMul3Rec(A,p);
            p = A.hermDrcho(p);
        }
        return sum;
    }    
}

size_t TotalNodosArbol(Agen<tElto>& A)
{
    return TotalNodosArbolRec(A,A.raiz());
}

size_t TotalNodosArbolRec(Agen<tElto>& A, Agen<tElto>::nodo n)
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t sum = 1;
        Agen<tElto>::nodo p = A.hijoIzqdo(n);
        while(p != Agen<tElto>::NODO_NULO)
        {
            sum = sum + TotalNodosArbolRec(A,p);
            p = A.hermDrcho(p);
        }
        return sum;
    }
}

size_t descendientesPropiosRec(Agen<tElto>& A, Agen<tElto>::nodo n)
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t sum = 0;
        Agen<tElto>::nodo p = A.hijoIzqdo(n);
        while(p != Agen<tElto>::NODO_NULO)
        {
            sum = sum + 1;
            p = A.hermDrcho(p);
        }
        p = A.hijoIzqdo(n);
        while(p != Agen<tElto>::NODO_NULO)
        {
            sum = sum + descendientesPropiosRec(A,p);
            p = A.hermDrcho(p);
        }
        return sum;
    }
}