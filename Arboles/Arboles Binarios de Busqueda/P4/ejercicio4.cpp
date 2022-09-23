#include <vector>
#include <algorithm>
#include <iostream>
#include "abb.hpp"

using namespace std;

Abb<int> interseccion(Abb<int> A, Abb<int> B);
void interseccionRec1(const Abb<int> A,Abb<int>& Resultado);
void interseccionRec2(const Abb<int> B,Abb<int>& Resultado,const Abb<int> Resultadoa);

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
    B.insertar(10);
    B.insertar(12);
    B.insertar(6);

    //   2,3,4,5,6,7,9,10  n 5,6,8,10,11,12           la interseccion deberia ser 5 6 10

    Abb<int> AnB = interseccion(A,B);

    distribuir(AnB);

    if((AnB.buscar(2)).vacio())
    {
        cout << "El 2 no esta contenido en A n B" << endl;
    }

    if((AnB.buscar(8)).vacio())
    {
        cout << "El 8 no esta contenido en A n B" << endl;
    }

    if(!(AnB.buscar(10)).vacio())
    {
        cout << "El 10 esta contenido en A n B" << endl;
    }

    return 0;
}

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

//-------------------------------------------------------------------------------------------------------------

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