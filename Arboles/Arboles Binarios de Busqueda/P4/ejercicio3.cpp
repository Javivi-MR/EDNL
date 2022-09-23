#include <vector>
#include <algorithm>
#include <iostream>
#include "abb.hpp"

using namespace std;

//FUNCIONES EJERCICIO3
Abb<int> Union(Abb<int> A, Abb<int> B);
void UnionRec1(const Abb<int> A,Abb<int>& Resultado);
void UnionRec2(const Abb<int> B,Abb<int>& Resultado);

//FUNCIONES EJERCICIO2 (Equilibrar arbol)
void distribuir(Abb<int>& A);
void llenar_v(vector<int>& v,const Abb<int>& A);
void equilibrarRec(vector<int>& v,Abb<int>& B);

int main()
{
    Abb<int> A,B;

    A.insertar(7);
    A.insertar(3);
    A.insertar(2);
    A.insertar(5);
    A.insertar(4);
    A.insertar(6);
    A.insertar(10);
    A.insertar(9);    

    B.insertar(8);
    B.insertar(5);
    B.insertar(11);
    B.insertar(12);
    B.insertar(6);

    //La union deberia contener 2,3,4,5,6,7,8,10,11,12

    Abb<int> AUB = Union(A,B);
    distribuir(AUB);

    //Si se realiza los dos, se realizo la union correctamente
    if(!(AUB.buscar(7)).vacio())
    {
        cout << "El 7 esta contenido en A U B" << endl;
    }
    if(!(AUB.buscar(11)).vacio())
    {
        cout << "El 11 esta contenido en A U B" << endl;
    }

    return 0;
}

Abb<int> Union(Abb<int> A, Abb<int> B)
{
    Abb<int> Resultado;
    UnionRec1(A,Resultado);
    UnionRec2(B,Resultado);

    return Resultado;
}

void UnionRec1(const Abb<int> A,Abb<int>& Resultado)//Rellena el arbol resultado con A
{
    if(!A.vacio())
    {
        Resultado.insertar(A.elemento());
        UnionRec1(A.izqdo(),Resultado);
        UnionRec1(A.drcho(),Resultado);
    }
}

void UnionRec2(const Abb<int> B,Abb<int>& Resultado)
{
    if(!B.vacio())
    {
        if((Resultado.buscar(B.elemento())).vacio())
        {
            Resultado.insertar(B.elemento());
            UnionRec2(B.izqdo(),Resultado);
            UnionRec2(B.drcho(),Resultado);
        }
        else
        {
            UnionRec2(B.izqdo(),Resultado);
            UnionRec2(B.drcho(),Resultado);            
        }
    }

}

//------------------------------------------------------------------------------------------------

void distribuir(Abb<int>& A)
{
    vector<int> v;
    Abb<int> B;

    llenar_v(v,A);  // El vector se rellena del arbol
    sort(v.begin(),v.end());    // El vector se ordena
    unsigned t = v.size();

    for(unsigned it=0; it < v.size(); it++)
        cout<< v[it] << endl;
    cout << "Vector terminado" << endl;
    equilibrarRec(v,B);
    A = B;
}

void llenar_v(vector<int>& v,const Abb<int>& A)
{
    if(!A.vacio())
    {
        llenar_v(v,A.izqdo());
        v.push_back(A.elemento());
        llenar_v(v,A.drcho());
    }
}

void equilibrarRec(vector<int>& v,Abb<int>& B)
{
    if(v.size() == 1)   //Si sólo queda un elemento en el vector lo insertamos directamente en el árbol.
        B.insertar(v.front());
    else{
        if(v.size() != 0){

            vector<int> vIzq, vDer;
            int mediana = v.size()/2;
            B.insertar(v[mediana]);

            for(int i=0; i < mediana; i++)
                vIzq.push_back(v[i]);

            for(int i=mediana+1; i < v.size(); i++)
                vDer.push_back(v[i]);

            equilibrarRec(vIzq,B);
            equilibrarRec(vDer,B);
        }
    }
}