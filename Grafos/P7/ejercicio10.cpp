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
    tCoste CosteMinimo;
    tCamino Path;
};

path viajar(GrafoP<int>& GAvion,GrafoP<int>& GTren, GrafoP<int>& GAutobus, vertice origen, vertice destino, tCoste costeTrenAutobus, tCoste costeAvionTrenAutobus);

int main()
{
    GrafoP<int> GAvion ("10avion.txt");
    GrafoP<int> GTren ("10tren.txt");
    GrafoP<int> GAutobus ("10autobus.txt");

    path p = viajar(GAvion,GTren,GAutobus,0,3,2,3);

    cout << "El coste minimo para viajar desde el origen al destino es de: " << p.CosteMinimo << endl <<  " y el camino a seguir es de: ";
    Lista<vertice>::posicion pos = p.Path.primera();
    while(pos != p.Path.fin())
    {
        cout << p.Path.elemento(pos) % GAvion.numVert() << " ";
        pos = p.Path.siguiente(pos);
    }

    return 0;
}

path viajar(GrafoP<int>& GAvion,GrafoP<int>& GTren, GrafoP<int>& GAutobus, vertice origen, vertice destino, tCoste costeTrenAutobus, tCoste costeAvionTrenAutobus)
{
    size_t n = GTren.numVert();
    GrafoP<int> G (n * 3);

    for(vertice i = 0 ; i < n ; i++)
    {
        for(vertice j = 0 ; j < n ; j++)
        G[i][j] = GAvion[i][j];
    }

    for(vertice i = n ; i < n*2 ; i++)
    {
        for(vertice j = n ; j < n*2 ; j++)
        {
            G[i][j] = GTren[i-n][j-n];
        }
    }

    for(vertice i = n*2 ; i < n*3 ; i++)
    {
        for(vertice j = n*2 ; j < n*3 ; j++)
        {
            G[i][j] = GAutobus[i-(n*2)][j-(n*2)];
        }
    }

    for(vertice i = 0 ; i < n ; i++)
    {
        G[i+n][i] = costeAvionTrenAutobus;
        G[i][i+n] = costeAvionTrenAutobus;
        G[i+(n*2)][i] = costeAvionTrenAutobus;
        G[i][i+(n*2)] = costeAvionTrenAutobus;
        G[n+i][i+(n*2)] = costeTrenAutobus;
        G[i+(n*2)][n+i] = costeTrenAutobus;
    }


    vector<vertice> o1(n*3);
    vector<vertice> o2(n*3);
    vector<vertice> o3(n*3);
    vector<tCoste> coste1 = Dijkstra(G,origen,o1);
    vector<tCoste> coste2 = Dijkstra(G,origen+n,o2);
    vector<tCoste> coste3 = Dijkstra(G,origen+(n*2),o3);

    vertice o;
    vertice d;
    size_t v_vertice = 1;

    tCoste minimo = min(coste1[destino],coste1[destino + n]);
    if(coste1[destino] < coste1[destino + n])
    {
        o = origen;
        d = destino;
    }
    else
    {
        o = origen;
        d = destino + n;
    }
    
    if(coste1[destino + (n*2)] < minimo)
    {
        o = origen;
        d = destino + (n*2);
    }
    minimo = min(minimo, coste1[destino + (n*2)]);

    
    if(coste2[destino] < minimo)
    {
        o = origen + n;
        d = destino;
        v_vertice = 2;
    }
    minimo = min(minimo, coste2[destino]);

    
    if(coste2[destino + n] < minimo)
    {
        o = origen + n;
        d = destino + n;
        v_vertice = 2;
    }
    minimo = min(minimo, coste2[destino + n]);

    if(coste2[destino + (n*2)] < minimo)
    {
        o = origen + n;
        d = destino + (n*2);
        v_vertice = 2;
    }
    minimo = min(minimo, coste2[destino + (n*2)]);

    if(coste3[destino] < minimo)
    {
        o = origen + (n*2);
        d = destino;
        v_vertice = 3;
    }
    minimo = min(minimo,coste3[destino]);

    if(coste3[destino + n] < minimo)
    {
        o = origen + (n*2);
        d = destino + n;
        v_vertice = 3;
    }
    minimo = min(minimo,coste3[destino + n]);

    if(coste3[destino + (n*2)] < minimo)
    {
        o = origen + (n*2);
        d = destino + (n*2);
        v_vertice = 3;
    }
    minimo = min(minimo,coste3[destino + (n*2)]);

    path p;
    p.CosteMinimo = minimo;
    if(v_vertice == 1)
    {
        p.Path = camino<GrafoP<size_t>::vertice>(o,d,o1);
    }
    if(v_vertice == 2)
    {
        p.Path = camino<GrafoP<size_t>::vertice>(o,d,o2);
    }
    if(v_vertice == 3)
    {
        p.Path = camino<GrafoP<size_t>::vertice>(o,d,o3);
    }

    return p;
}