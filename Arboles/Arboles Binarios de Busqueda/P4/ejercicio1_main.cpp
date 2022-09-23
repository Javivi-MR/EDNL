#include <iostream>

#include "ejercicio1.hpp"

using namespace std;
/*
                7
            3       10
          2   5    9
            4   6
*/

int main()
{
    Abb<int> A;

    A.insertar(7);
    A.insertar(3);
    A.insertar(2);
    A.insertar(5);
    A.insertar(4);
    A.insertar(6);
    A.insertar(10);
    A.insertar(9);

    A.borrardescendencia(3);

    Abb<int> A1 = A.buscar(3);
    if(A1.vacio())
    {
        cout << "El 3 ya no existe" << endl;
    }

    A1 = A.buscar(7);
    if(!A1.vacio())
    {
        cout << "El 7 existe" << endl;
    }

    A1 = A.buscar(5);
    if(A1.vacio())
    {
        cout << "El 5 ya no existe" << endl;
    }

    A1 = A.buscar(4);
    if(A1.vacio())
    {
        cout << "El 4 ya no existe" << endl;
    }

    return 0;
}