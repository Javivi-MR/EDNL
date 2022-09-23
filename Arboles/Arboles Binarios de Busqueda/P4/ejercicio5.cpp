#include <vector>
#include <algorithm>
#include <iostream>
#include "abb.hpp"

using namespace std;

//------------------------------------INTERSECCION------------------------------------------
Abb<int> interseccion(Abb<int> A, Abb<int> B);
void interseccionRec1(const Abb<int> A,Abb<int>& Resultado);
void interseccionRec2(const Abb<int> B,Abb<int>& Resultado,const Abb<int> Resultadoa);
//-----------------------------------------------------------------------------------------------------------------------------

//------------------------------------UNION------------------------------------------------------------------------------------
Abb<int> Union(Abb<int> A, Abb<int> B);
void UnionRec1(const Abb<int> A,Abb<int>& Resultado);
void UnionRec2(const Abb<int> B,Abb<int>& Resultado);
//-----------------------------------------------------------------------------------------------------------------------------

//------------------------------------ROMBO------------------------------------------------------------------------------------
Abb<int> rombo(Abb<int> A,Abb<int>B);
Abb<int> resta(Abb<int> Union,Abb<int>Inter);
void restaRec(const Abb<int> Union,const Abb<int>Inter,Abb<int>& resultado);
//-----------------------------------------------------------------------------------------------------------------------------
void distribuir(Abb<int>& A);
void llenar_v(vector<int>& v,const Abb<int>& A);
void equilibrarRec(vector<int>& v,Abb<int>& B);
//-----------------------------------------------------------------------------------------------------------------------------


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
    B.insertar(10);
    B.insertar(12);
    B.insertar(6);

    Abb<int> AB = rombo(A,B); // 2,3,4,5,6,7,8,9,10,11,12 - 5,6,10 = 2,3,4,7,8,11,12

    distribuir(AB);

    if(!(AB.buscar(2)).vacio())
    {
        cout << "El 2 esta contenido en A rombo B" << endl;
    }

    if((AB.buscar(6)).vacio())
    {
        cout << "El 6 no esta contenido en A rombo B" << endl;
    }

    if((AB.buscar(10)).vacio())
    {
        cout << "El 10 no esta contenido en A rombo B" << endl;
    }

    if(!(AB.buscar(12)).vacio())
    {
        cout << "El 12 esta contenido en A rombo B" << endl;
    }

    return 0;
}

Abb<int> rombo(Abb<int> A,Abb<int>B)
{
    Abb<int> AUB = Union(A,B);
    Abb<int> AnB = interseccion(A,B);

    Abb<int> resultado = resta(AUB,AnB);

    return resultado;
}

Abb<int> resta(Abb<int> Union,Abb<int>Inter)
{
    Abb<int> resultado = Union;
    restaRec(Union,Inter,resultado);
    return resultado;
}

void restaRec(const Abb<int> Union,const Abb<int>Inter,Abb<int>& resultado)
{
    if(!Inter.vacio())
    {
        if(!Union.buscar(Inter.elemento()).vacio()) // se econtro un elemento de la interseccion en la union
        {
            resultado.eliminar(Inter.elemento());
            restaRec(Union,Inter.izqdo(),resultado);
            restaRec(Union,Inter.drcho(),resultado);
        }
        else
        {
            restaRec(Union,Inter.izqdo(),resultado);
            restaRec(Union,Inter.drcho(),resultado);            
        }
    }
}

//-------------------------------------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------------------------------------

Abb<int> interseccion(Abb<int> A, Abb<int> B)
{
    Abb<int> Resultadoa,Resultado;
    interseccionRec1(A,Resultado);
    Resultadoa = Resultado;
    interseccionRec2(B,Resultado,Resultadoa);

    return Resultado;
}

void interseccionRec1(const Abb<int> A,Abb<int>& Resultado)
{
    if(!A.vacio())
    {
        Resultado.insertar(A.elemento());
        interseccionRec1(A.izqdo(),Resultado);
        interseccionRec1(A.drcho(),Resultado);
    }
}

void interseccionRec2(const Abb<int> B,Abb<int>& Resultado,const Abb<int> Resultadoa)
{
    if(!Resultadoa.vacio())
    {
        if(B.buscar(Resultadoa.elemento()).vacio())//si no esta el elemento de b
        {
            Resultado.eliminar(Resultadoa.elemento());
            interseccionRec2(B,Resultado,Resultadoa.izqdo());
            interseccionRec2(B,Resultado,Resultadoa.drcho());
        }
        else
        {
            interseccionRec2(B,Resultado,Resultadoa.izqdo());
            interseccionRec2(B,Resultado,Resultadoa.drcho());            
        }
    }
}

//--------------------------------------------------------------------------------------------------------

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