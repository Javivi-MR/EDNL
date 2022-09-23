#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;


struct parte
{
    vertice destino;
    int carga;
};


tCoste calcularViaje(GrafoP<int>& G, vector<parte>& P, vertice o);

int main()
{
    GrafoP<int> G ("4.txt");
    vector<parte> P(3); // Haremos 3 partes 
    P[0].carga = 10;    P[1].carga = 4;     P[2].carga = 2;
    P[0].destino = 2;   P[1].destino = 1;   P[2].destino = 3;
    //La capital de zuelandia estará en el vertice 0
    tCoste totalKm = calcularViaje(G,P,0);

    cout << "El total de km que han de recorrer los camiones es de: " << totalKm << endl;

    return 0;
}

tCoste calcularViaje(GrafoP<int>& G, vector<parte>& P, vertice o)
{
    vector<vertice> PD (G.numVert());
    vector<tCoste> VD = Dijkstra(G,o,PD);
    vector<vertice> PI (G.numVert());
    vector<tCoste> VI = DijkstraInv(G,o,PI);

    tCoste distMinima = 0;

    for(size_t i = 0; i < P.size(); i++)
    {
        distMinima = distMinima + VD[P[i].destino] * P[i].carga;
        distMinima = distMinima + VI[P[i].destino] * P[i].carga;
    }

    return distMinima;
}