
#include <iostream>
#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"
#include "matriz.h"
#include <vector>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

matriz<tCoste> zuelandia(GrafoP<int>& G, vector<bool>& V, matriz<bool>& M,GrafoP<int>::vertice capital);

int main()
{
    GrafoP<int> G ("ejercicio4.txt");

    cout << G << endl;

    //El vertice 0 sera nuestra capital, mientras que el vertice 2 sera conquistada por los rebeldes. Ademas los rebeldes tomaran la carretera del 0 -> 5

    vector<bool> V (G.numVert(),false);
    V[2] = true;
    matriz<bool> M(G.numVert(),false);

    M[0][5] = true;



    matriz<tCoste> Mcostes = zuelandia(G,V,M,0);

    cout << endl << endl << Mcostes << endl;

    return 0;
}

matriz<tCoste> zuelandia(GrafoP<int>& G, vector<bool>& V, matriz<bool>& M, GrafoP<int>::vertice capital)
{
    matriz<tCoste> Mcostes(G.numVert(),GrafoP<int>::INFINITO);

    for(size_t i = 0; i < G.numVert(); i++)
    {
        if(V[i] == true)
        {
            for(size_t j = 0; j < G.numVert(); j++)
            {
                G[i][j] = GrafoP<int>::INFINITO;
                G[j][i] = GrafoP<int>::INFINITO;
            }
        }
    }
    //La ciudad conquistada la ocultamos

    for(size_t i = 0; i < G.numVert(); i++) 
    {
        for(size_t j = 0; j < G.numVert(); j++)
        {
            if(M[i][j] == true)
            {
                G[i][j] = GrafoP<int>::INFINITO;
            }
        }
    } 
    //la carretera es cortada
    //matriz<vertice> P(G.numVert());
    //matriz<tCoste> Mcostes = Floyd(G,P);
    //NO PODEMOS USAR FLOYD, YA QUE NO NOS ASEGURA QUE PASE POR LA CAPITAL (¡Hay que usar djistra!)
    //Calcularemos los caminos mas cortos desde la capital hacia cualquier ciudad y desde cualquier ciudad
    vector<vertice> Vv1(G.numVert());
    vector<vertice> Vv2(G.numVert());
    vector<tCoste> Vd = Dijkstra(G,capital,Vv1);
    vector<tCoste> Vdi = DijkstraInv(G,capital,Vv2);

    for(size_t i = 0; i < G.numVert(); i++) 
    { 
        for(size_t j = 0; j < G.numVert(); j++)
        {
            if(i != j)
            {
                Mcostes[i][j] = suma(Vd[j],Vdi[i]);
            }

        }
    }

    for(size_t i = 0; i < G.numVert(); i++) 
    {
        for(size_t j = 0; j < G.numVert(); j++)
        {
            if(i == j)
            {
                Mcostes[i][j] = 0;
            }

        }
    }
    cout << G << endl;

    return Mcostes;
}