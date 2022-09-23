#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;

tCoste Viajar(GrafoP<int>& GTren,GrafoP<int>& GAutobus, vertice origen, vertice destino);

int main()
{
    GrafoP<int> GTren ("8tren.txt");
    GrafoP<int> GAutobus ("8autobus.txt");

    tCoste costeMin = Viajar(GTren,GAutobus,0,3);

    cout << costeMin << endl;

    return 0;
}


tCoste Viajar(GrafoP<int>& GTren,GrafoP<int>& GAutobus, vertice origen, vertice destino)
{
    vector<vertice> pt(GTren.numVert()); vector<vertice> pa(GTren.numVert());
    vector<vertice> pti(GTren.numVert()); vector<vertice> pai(GTren.numVert());
    vector<tCoste> costeTren = Dijkstra(GTren,origen,pt);
    vector<tCoste> costeTrenInv = DijkstraInv(GTren,destino,pti);
    vector<tCoste> costeAutobus = Dijkstra(GAutobus,origen,pa);
    vector<tCoste> costeAutobusInv = DijkstraInv(GAutobus,origen,pai);

    tCoste minimo = min(costeTren[destino],costeTren[destino]);

    for(size_t i = 0 ; i < GTren.numVert() ; i++)
    {
        if(i != origen || i != destino)
        {
            minimo = min(minimo, min(suma(costeTren[i],costeAutobusInv[i]),suma(costeAutobus[i],costeTrenInv[i])));
        }
    }

    return minimo;
}