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

struct result
{
    matriz<double> Mcostes;
    Particion p;
};

void tombuctu(Grafo G, vector<ciudad> Vciudad);
double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x-c2.x),2) + pow(abs(c1.y-c2.y),2));
}

int main()
{

    Grafo G("1tom.txt");

    vector<ciudad> Vciudad(5);
    Vciudad[0].x = 3; Vciudad[0].y = 5;
    Vciudad[1].x = 3; Vciudad[1].y = 2;
    Vciudad[2].x = 3; Vciudad[2].y = 1;
    Vciudad[3].x = 1; Vciudad[3].y = -1;
    Vciudad[4].x = 3; Vciudad[4].y = -1;

    tombuctu(G, Vciudad);

    return 0;
}

void tombuctu(Grafo G, vector<ciudad> Vciudad)
{
    GrafoP<double> GArchipielago(G.numVert());
    Particion p(G.numVert());

    for(vertice i = 0 ; i < G.numVert() ; i++)
    {
        for(vertice j = 0 ; j < G.numVert() ; j++)
        {
            if(G[i][j])
            {
                GArchipielago[i][j] = distancia(Vciudad[i],Vciudad[j]);

                if(p.encontrar(i) != p.encontrar(j))
                {
                    p.unir(i,j);
                }
            }
        }
    }

    matriz<vertice> Mver(G.numVert());
    matriz<double> Mcostes = Floyd(GArchipielago,Mver);

    cout << Mcostes;


}