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

struct path 
{
    tCoste coste;
    tCamino c; //Camino
};

path viajar(GrafoP<int>& GTren, GrafoP<int>& GAutobus, vertice origen, vertice destino, vertice cambio1, vertice cambio2);

int main()
{
    GrafoP<int> GTren ("7tren.txt");
    GrafoP<int> GAutobus ("7autobus.txt");

    path p = viajar(GTren, GAutobus, 0, 4, 2, 3);

    cout << "El coste del camino es de: " << p.coste << endl << "Y el camino del origen al destino es: ";
    Lista<size_t>::posicion pos = p.c.primera();
    while (pos != p.c.fin())
    {
        cout << p.c.elemento(pos) << " ";
        pos = p.c.siguiente(pos);
    }

    return 0;
}

path viajar(GrafoP<int>& GTren, GrafoP<int>& GAutobus, vertice origen, vertice destino, vertice cambio1, vertice cambio2)
{
    vector<vertice> P1(GTren.numVert());
    vector<vertice> P2(GTren.numVert());

    vector<tCoste> VD = Dijkstra(GTren,origen,P1);
    vector<tCoste> VI = DijkstraInv(GAutobus,destino,P2);

    path P;

    if(VD[cambio1] + VI[cambio1] < VD[cambio2] + VI[cambio2])
    {
        P.coste = VD[cambio1] + VI[cambio1];
        tCamino ruta1 = camino<GrafoP<size_t>::vertice>(origen,cambio1,P1);
        tCamino ruta2 = camino<GrafoP<size_t>::vertice>(destino,cambio1,P2);

        Lista<size_t>::posicion pos = ruta2.primera();

        while(pos != ruta2.fin())
        {
            ruta1.insertar(ruta2.elemento(pos),ruta1.fin());
            pos = ruta2.siguiente(pos);
        }

        P.c = ruta1;
    }
    else
    {
        P.coste = VD[cambio2] + VI[cambio2];
        tCamino ruta1 = camino<GrafoP<size_t>::vertice>(origen,cambio2,P1);
        tCamino ruta2 = camino<GrafoP<size_t>::vertice>(destino,cambio2,P2);

        Lista<size_t>::posicion pos = ruta2.primera();

        while(pos != ruta2.fin())
        {
            ruta1.insertar(ruta2.elemento(pos),ruta1.fin());
            pos = ruta2.siguiente(pos);
        }

        P.c = ruta1;
    }
    return P;
}