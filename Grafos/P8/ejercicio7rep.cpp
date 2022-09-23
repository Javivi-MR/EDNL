#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "alg_grafoMA.h"
#include "grafoMA.h"
#include "grafoMA.cpp"
#include "particion.h"
#include "particion.cpp"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;

struct ciudad
{
    double x,y;
};

struct puente
{
    vertice v1,v2;
    double coste;
};

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x-c2.x),2) + pow(abs(c1.y-c2.y),2));
}

double viajar(vector<ciudad> ciudadesFobos, vector<ciudad> ciudadesDeimos, vector<vertice> costerasFobos,vector<vertice> costerasDeimos , vertice origen, vertice destino);
puente Puenteminimo(vector<ciudad> ciudadesFobos,vector<ciudad> ciudadesDeimos, vector<vertice> costerasFobos, vector<vertice> costerasDeimos);

int main()
{
    vector<ciudad> ciudadesFobos(4);
    ciudadesFobos[0].x = 1; ciudadesFobos[0].y = 2;
    ciudadesFobos[1].x = 2; ciudadesFobos[1].y = 2;
    ciudadesFobos[2].x = 3; ciudadesFobos[2].y = 2;
    ciudadesFobos[3].x = 5; ciudadesFobos[3].y = 2;

    vector<ciudad> ciudadesDeimos(4);
    ciudadesDeimos[0].x = 3; ciudadesDeimos[0].y = -1;
    ciudadesDeimos[1].x = 3; ciudadesDeimos[1].y = -3;
    ciudadesDeimos[2].x = 3; ciudadesDeimos[2].y = -4;
    ciudadesDeimos[3].x = 3; ciudadesDeimos[3].y = -5;

    vector<vertice> costerasFobos{0,2};
    vector<vertice> costerasDeimos{0,3};

    double costemin = viajar(ciudadesFobos,ciudadesDeimos,costerasFobos,costerasDeimos,0,5);

    cout << "El coste minimo para llegar desde el origen hasta el destino es de: " << costemin;

    return 0;
}

double viajar(vector<ciudad> ciudadesFobos, vector<ciudad> ciudadesDeimos, vector<vertice> costerasFobos,vector<vertice> costerasDeimos , vertice origen, vertice destino)
{
    size_t nf = ciudadesFobos.size();
    size_t nd = ciudadesDeimos.size();

    GrafoP<double> GFobos(nf);

    for(vertice i = 0 ; i < nf ; i++)
    {
        for(vertice j = 0 ; j < nf ; j++)
        {
            if(i != j)
            {
                GFobos[i][j] = distancia(ciudadesFobos[i],ciudadesFobos[j]);
            }
        }
    }
    GrafoP<double> GFobosPrim = Prim(GFobos);

    GrafoP<double> GDeimos(nd);

    for(vertice i = 0 ; i < nd ; i++)
    {
        for(vertice j = 0 ; j < nd ; j++)
        {
            if(i != j)
            {
                GDeimos[i][j] = distancia(ciudadesDeimos[i],ciudadesDeimos[j]);
            }
        }
    }
    GrafoP<double> GDeimosPrim = Prim(GDeimos);

    GrafoP<double> Grecoland (nf+nd);

    for(vertice i = 0 ; i < nf ; i++)
    {
        for(vertice j = 0 ; j < nf ; j++)
        {
            Grecoland[i][j] = GFobosPrim[i][j];
        }
    }

    for(vertice i = nf ; i < nf+nd ; i++)
    {
        for(vertice j = nf ; j < nf+nd ; j++)
        {
            Grecoland[i][j] = GDeimosPrim[i-nf][j-nf];
        }
    }

    puente p = Puenteminimo(ciudadesFobos,ciudadesDeimos,costerasFobos,costerasDeimos);
    p.v2 = p.v2 + nf;

    Grecoland[p.v1][p.v2] = p.coste;
    Grecoland[p.v2][p.v1] = p.coste;

    vector<vertice> P(nf+nd);
    vector<double> D = Dijkstra(Grecoland,origen,P);

    return D[destino];
}


puente Puenteminimo(vector<ciudad> ciudadesFobos,vector<ciudad> ciudadesDeimos, vector<vertice> costerasFobos, vector<vertice> costerasDeimos)
{
    puente p;
    p.coste = GrafoP<double>::INFINITO;

    for(size_t i = 0; i < costerasFobos.size() ; i++)
    {
        for(size_t j = 0 ; j < costerasDeimos.size() ; j++)
        {
            double cost = distancia(ciudadesFobos[costerasFobos[i]], ciudadesDeimos[costerasDeimos[j]]);
            if(cost < p.coste)
            {
                p.coste = cost;
                p.v1 = costerasFobos[i];
                p.v2 = costerasDeimos[j];
            }
        }
    }
    return p;
}