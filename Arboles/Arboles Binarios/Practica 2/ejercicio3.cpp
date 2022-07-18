#include "abin.hpp"
#include <iostream>

using namespace std;

struct mathExpr 
{
    mathExpr(char c): operador{c}, operando{0} 
    {}
     mathExpr(double n): operando{n}, operador{}
    {}

    char operador;
    double operando;
};

double operacion(Abin<mathExpr> A);
double operacionRec(Abin<mathExpr> A,Abin<mathExpr>::nodo n);

int main()
{
    Abin<mathExpr> A;

    A.insertarRaiz(mathExpr{'*'});

    Abin<mathExpr>::nodo n = A.raiz();

    A.insertarHijoIzqdo(n, mathExpr{7.0});

    A.insertarHijoDrcho(n, mathExpr{'/'});

    n = A.hijoDrcho(n);

    A.insertarHijoDrcho(n, mathExpr{2.0});

    A.insertarHijoIzqdo(n, mathExpr{'-'});

    n = A.hijoIzqdo(n);

    A.insertarHijoIzqdo(n, mathExpr{15.0});

    A.insertarHijoDrcho(n, mathExpr{3.2});

    double resultado = operacion(A);

    cout << "El resultado de la operacion es de:" << resultado << endl;

    return 0;
}

double operacion(Abin<mathExpr> A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return operacionRec(A,A.raiz());
    }
}

double operacionRec(Abin<mathExpr> A,Abin<mathExpr>::nodo n)
{
    if (A.hijoIzqdo(n) == Abin<mathExpr>::NODO_NULO)
    {
        return A.elemento(n).operando;
    }
    else
    {
        switch (A.elemento(n).operador)
        {
            case '+': 
                return operacionRec(A,A.hijoIzqdo(n)) + operacionRec(A,A.hijoDrcho(n));
                break;
            case '-': 
                return operacionRec(A,A.hijoIzqdo(n)) - operacionRec(A,A.hijoDrcho(n));
                break;
            case '*':
                return operacionRec(A,A.hijoIzqdo(n)) * operacionRec(A,A.hijoDrcho(n));
                break;
            case '/':
                return operacionRec(A,A.hijoIzqdo(n)) / operacionRec(A,A.hijoDrcho(n));
                break;
        }
    }
}