#include <iostream>

#include "abb.hpp"

using namespace std;
/*
                20
            15       30
         10    18    
       5      
          7
            9
    infimo de 8 -> 7
    supremo de 8 -> 9

*/

int infimo(Abb<int>& A, int x);
int supremo(Abb<int>& A, int x);
int contarhasta(int a, int x);
void infimoRec(const Abb<int> A, int x, int& aux);
void supremoRec(const Abb<int> A, int x, int& aux);


int main()
{
    Abb<int> A;

    A.insertar(20);
    A.insertar(30);
    A.insertar(15);
    A.insertar(10);
    A.insertar(18);
    A.insertar(5);
    A.insertar(7);
    A.insertar(9);

    int f = infimo(A,8);
    int s = supremo(A,8);

    cout << s;


    return 0;
}

int infimo(Abb<int>& A, int x)
{
    int aux = A.elemento();
    infimoRec(A,x,aux);
    return aux;
}

void infimoRec(const Abb<int> A, int x, int& aux)
{
    if(!A.vacio())
    {
        if(A.elemento() > x)
        {
            if(contarhasta(A.elemento(),x) <= contarhasta(aux,x))
            {
                aux = A.elemento();
            }
            infimoRec(A.izqdo(),x,aux);
        }
        else
        {
            if(contarhasta(A.elemento(),x) <= contarhasta(aux,x))
            {
                aux = A.elemento();
            }
            infimoRec(A.drcho(),x,aux);
        }
    }

}

int contarhasta(int a, int x)
{
    int i = 0;
    while(a != x)
    {
        i++;
        if(a < x)
        {
            a++;
        }
        else
        {
            a--;
        }
    }
    return i;
}

int supremo(Abb<int>& A, int x)
{
    int aux = A.elemento();
    //supremoRec(A,x,aux);
    return aux;
}

void supremoRec(const Abb<int> A, int x, int& aux)
{
    if(!A.vacio())
    {
        if(A.elemento() > x)
        {
            if(contarhasta(A.elemento(),x) < contarhasta(aux,x))
            {
                aux = A.elemento();
            }
            supremoRec(A.izqdo(),x,aux);
        }
        else
        {
            if(contarhasta(A.elemento(),x) < contarhasta(aux,x))
            {
                aux = A.elemento();
            }
            supremoRec(A.drcho(),x,aux);
        }
    }
}