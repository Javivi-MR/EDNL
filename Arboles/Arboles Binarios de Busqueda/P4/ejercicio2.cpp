#include <vector>
#include <algorithm>
#include <iostream>
#include "abb.hpp"

using namespace std;

void distribuir(Abb<int>& A);
void llenar_v(vector<int>& v,const Abb<int>& A);
void equilibrarRec(vector<int>& v,Abb<int>& B);

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

    distribuir(A);
    
    return 0;
}


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