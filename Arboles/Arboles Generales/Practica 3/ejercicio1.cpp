#include <iostream>
#include <fstream>
#include "agen.hpp"
#include "agen_E-S.h"

typedef char tElto;

const tElto fin = '#';

using namespace std;

int CalculateGrade(Agen<tElto> A);
int CalculateGradeRec(Agen<tElto> A, Agen<tElto>::nodo n);
int NumHijos(Agen<tElto> A, Agen<tElto>::nodo n);


int main()
{
    Agen<tElto> A;

    cout << "*** Lectura del arbol binario A ***\n";

    rellenarAgen(A,fin);
        
    ofstream fs("agen.dat"); // Abrir fichero de salida.

    imprimirAgen(fs, A, fin); // En fichero.


    int grado = CalculateGrade(A);

    cout << "El grado maximo del Arbol es: " << grado << endl;

     return 0;
}

int CalculateGrade(Agen<tElto> A)
{
    return CalculateGradeRec(A,A.raiz());
}

int CalculateGradeRec(Agen<tElto> A, Agen<tElto>::nodo n) //No se porque no va >:(
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int maximo = NumHijos(A,n);
        Agen<tElto>::nodo p = A.hijoIzqdo(n);
        while(p != Agen<tElto>::NODO_NULO)
        {
            maximo = max(maximo,CalculateGradeRec(A,p));
            p = A.hermDrcho(p);
        }
        return maximo;
    }
}

int NumHijos(Agen<tElto> A, Agen<tElto>::nodo n)
{
    Agen<tElto>::nodo p = A.hijoIzqdo(n);
    
    int num_hijos = 0;
    
    while(p != Agen<tElto>::NODO_NULO)
    {
        num_hijos++;
        p = A.hermDrcho(p);
    }
    return num_hijos;
}