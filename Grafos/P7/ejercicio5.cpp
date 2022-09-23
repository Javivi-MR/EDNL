#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

enum TipoViaje
{carretera,tren,avion};

vector<vertice> viajar(GrafoP<int>& G1, GrafoP<int>& G2,GrafoP<int>& G3, TipoViaje alergia, unsigned dinero,vertice origen);
GrafoP<int> viajeminimo (GrafoP<int>& G1, GrafoP<int>& G2);

int main()
{
    GrafoP<int> G1 ("5carretera.txt");
    GrafoP<int> G2 ("5tren.txt");
    GrafoP<int> G3 ("5avion.txt");

    TipoViaje alergia = carretera;

    unsigned dinero = 12;

    //0 sera el punto de partida
    vector<vertice> posiblesViajes = viajar(G1,G2,G3,alergia,dinero,0);

    cout << "El viajero alergico puede ir a las siguientes ciudades: " << posiblesViajes << endl;

    return 0;
}

vector<vertice> viajar(GrafoP<int>& G1, GrafoP<int>& G2,GrafoP<int>& G3, TipoViaje alergia, unsigned dinero,vertice origen)
{
    GrafoP<int> Gaux(G1.numVert());
    switch(alergia)
    {
        case carretera:
            Gaux = viajeminimo(G2,G3);
        break;
        case tren:
            Gaux = viajeminimo(G1,G3);
        break;
        case avion:
            Gaux = viajeminimo(G1,G2);
        break;
    }

    vector<vertice> P (Gaux.numVert());
    vector<tCoste> D = Dijkstra(Gaux,origen,P);

    vector<vertice> resultado;

    for(int i = 0; i < D.size(); i++)
    {
        if(D[i] != GrafoP<int>::INFINITO && i != origen && dinero >= D[i])
        {
            resultado.push_back(i);
        }
    }
    return resultado;
}

GrafoP<int> viajeminimo (GrafoP<int>& G1, GrafoP<int>& G2)
{
    GrafoP<int> Gaux = G1;

    for(vertice i = 0 ; i < G1.numVert() ; i++)
    {
        for(vertice j = 0 ; j < G1.numVert() ; j++)
        {
            Gaux[i][j] = min(G1[i][j] , G2[i][j]);
        }
    }

    return Gaux;
}