#include <iostream>
#include "agen.hpp"
#include "agen_E-S.h"

typedef char tElto;
const tElto fin = '#';

bool ternario(Agen<char>& A);
bool ternarioRec(Agen<char>& A, Agen<char>::nodo n);
int contarnodosRec(Agen<char>& A, Agen<char>::nodo n);

int main()
{
    Agen<char> A;

    rellenarAgen(A,fin);

    bool  resultado = ternario(A);

    if(resultado)
    {
        cout << "si es ternario!" << endl;
    }
    else
    {
        cout << "no es ternario!" << endl;
    }

    return 0;
}

bool ternario(Agen<char>& A)
{
    if(!A.arbolVacio())
    {
        return ternarioRec(A,A.raiz());
    }
    else
    {
        return true;
    }
    
}

bool ternarioRec(Agen<char>& A, Agen<char>::nodo n)
{
    if(n != Agen<char>::NODO_NULO)
    {
        if(contarnodosRec(A,n) == 0 || contarnodosRec(A,n) == 3)
        {
            if(A.hijoIzqdo(n) == Agen<char>::NODO_NULO)
            {
                return true;
            }
            else
            {
                Agen<char>::nodo naux = A.hijoIzqdo(n);
                while(naux != Agen<char>::NODO_NULO)
                {
                    return ternarioRec(A,naux);
                    naux = A.hermDrcho(naux);
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
    return true; // NO NECESARIO PERO PARA EVITAR PROBLEMAS CON EL COMPILADOR LO PONGO :)
}

int contarnodosRec(Agen<char>& A, Agen<char>::nodo n)
{

    int contador = 0;
    Agen<char>::nodo naux = A.hijoIzqdo(n);
    while(naux != Agen<char>::NODO_NULO)
    {
        contador++;
        naux = A.hermDrcho(naux);
    }
    return contador;
    
}