#include <iostream>
#include <fstream>
#include "agen.hpp"
#include "agen_E-S.h"

typedef int tElto;

const tElto fin = -1;

using namespace std;

void BuscarNodo(Agen<tElto>& A,int a);
void BuscarNodoRec(Agen<tElto>& A,int a,Agen<tElto>::nodo n);
void PodarArbolito(Agen<tElto>& A,int a,Agen<tElto>::nodo n);

int main()
{
    Agen<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAgen(A,fin);
        
    ofstream fs("agen.dat"); // Abrir fichero de salida

    BuscarNodo(A,7);

    imprimirAgen(fs, A, fin); // En fichero.

    cout << "El arbol ha sido podado correctamente, reviselo en agen.dat :)" << endl;

    return 0;
}

void BuscarNodo(Agen<tElto>& A,int a)
{
    BuscarNodoRec(A,a,A.raiz());
}

void BuscarNodoRec(Agen<tElto>& A,int a,Agen<tElto>::nodo n)
{
    if(n != Agen<tElto>::NODO_NULO)
    {
        if(A.elemento(n) == a)
        {
            PodarArbolito(A,a,n);
        }
        else
        {
            Agen<tElto>::nodo p = A.hijoIzqdo(n);
            while(p != Agen<tElto>::NODO_NULO)
            {
                BuscarNodoRec(A,a,p);
                p = A.hermDrcho(p);
            }
        }
    }
}

void PodarArbolito(Agen<tElto>& A,int a,Agen<tElto>::nodo n)
{
    Agen<tElto>::nodo p1 = A.hijoIzqdo(n);
    Agen<tElto>::nodo p2 = A.hermDrcho(p1);

    if(p1 != Agen<tElto>::NODO_NULO && p2 != Agen<tElto>::NODO_NULO)
    {
        if(A.hijoIzqdo(p1) != Agen<tElto>::NODO_NULO)
        {
            PodarArbolito(A,a,p1);  //podamos el/los hijos(del hijo izquierdo)
            PodarArbolito(A,a,n);   //llamada para podar hijo izquierdo
        }
        else
        {
            A.eliminarHijoIzqdo(n); //podamos hijo izquierdo 
            PodarArbolito(A,a,n);   //lamada para podar a su hermano derecho (nuevo hijo izquierdo)
        }
    }

    if(p1 != Agen<tElto>::NODO_NULO && p2 == Agen<tElto>::NODO_NULO)
    {
        A.eliminarHijoIzqdo(n); //podamos el hijo izquierdo unico y no llamamos mas por que solo queda este :)
    }
}