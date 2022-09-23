#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"

using namespace std;

GrafoP<int>::tCoste diametro (GrafoP<int>& G);
void pseudocentro(GrafoP<int>& G , GrafoP<int>::tCoste t);

int main()
{
    GrafoP<int> G ("ejercicio1.txt");

    cout << G << endl;

    GrafoP<int>::tCoste d = diametro(G);

    cout <<d;

    return 0;
}

GrafoP<int>::tCoste diametro (GrafoP<int>& G)
{
    typedef typename GrafoP<int>::vertice vertice;
    typedef typename GrafoP<int>::tCoste tCoste;
    tCoste diametro = 0, aux1, aux2;
    matriz<vertice> Mvertices(G.numVert());
    matriz<tCoste> Mcostes = Floyd(G,Mvertices);

    vertice pseudocentro;

    cout << Mcostes;

    for(vertice i = 0; i < G.numVert() ; i++)
    {
        aux1 = 0;
        aux2 = 0;
        for(vertice j = 0; j < G.numVert(); j++)
        {
            if(Mcostes[i][j] >= aux1 && Mcostes[i][j] != GrafoP<int>::INFINITO)
            {
                aux2 = aux1;
                aux1 = Mcostes[i][j];
            }
            else
            {
                if(Mcostes[i][j] >= aux2 && Mcostes[i][j] != GrafoP<int>::INFINITO)
                {
                    aux2 = Mcostes[i][j];
                }
            }
        }
        if(diametro < aux1 + aux2)
        {
            diametro = aux1 + aux2;
            pseudocentro = i;
        }
    }
    cout << "\n \n" << pseudocentro << " ";
    return diametro;
}

