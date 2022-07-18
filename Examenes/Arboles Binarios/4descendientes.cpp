/*
    Contar descendientes: 'Dado un árbol binario, contar el número 
    de nodos de dicho árbol que tienen 4 descendientes.'
*/

#include <iostream>
#include <fstream>
#include "abin.hpp"
#include "abin_E-S.h"

using namespace std;

typedef char tElto;

const tElto fin = '#';

int descendientes(Abin<tElto> A);
int descendientesRec(Abin<tElto> A,Abin<tElto>::nodo n);
int contarDescendientesRec(Abin<tElto> A,Abin<tElto>::nodo n);

int main()
{
    Abin<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAbin(A, fin); // Desde std::cin

    ofstream fs("abin.dat"); // Abrir fichero de salida.

    imprimirAbin(fs, A, fin); // En fichero.

    int numNodos = descendientes(A);

    cout << "Numero de nodos con 4 descendientes del arbol es: " << numNodos << endl; 

    return 0;
}

int descendientes(Abin<tElto> A)
{
    if(A.arbolVacio())
    {
        return 0; 
    }
    else
    {
        return descendientesRec(A,A.raiz());
    }
}

int descendientesRec(Abin<tElto> A,Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(contarDescendientesRec(A,n) == 4)
        {
            return 1 + descendientesRec(A,A.hijoIzqdo(n)) + descendientesRec(A,A.hijoDrcho(n));
        }
        else
        {
            return descendientesRec(A,A.hijoIzqdo(n)) + descendientesRec(A,A.hijoDrcho(n));
        }
    }
}

int contarDescendientesRec(Abin<tElto> A,Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + contarDescendientesRec(A,A.hijoIzqdo(n)) + contarDescendientesRec(A,A.hijoDrcho(n));
    }
}