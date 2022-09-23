/*
El archipiélago de Grecoland está formado únicamente por dos islas, Fobos y Demos, 
que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2 son costeras (Obviamente C1 <= N1 y C2 <= N2).

Nos planteamos la construcción de un puente entre las posibles ciudades costeras, cuyo coste directo de viajar por él,
al igual que en el caso de las carreteras, coincidirá con su distancia euclídea.

Se asume que se realizarán exactamente el mismo número de viajes entre cualesquiera ciudades del archipiélago. 
Por ejemplo, se considerará que el número de viajes entre la ciudad P de Fobos y la Q de Deimos será el mismo que entre las ciudades R y S de la misma isla. 
Dicho de otra forma, todos los posibles trayectos a realizar dentro del archipiélago son igual de importantes.

Dada la matriz de adyacencia del archipiélago, las coordenadas cartesianas de cada ciudad y la lista de ciudades costeras de Fobos y Deimos, 
implementa una función que calcule que dos ciudades unirán el puente.
*/

#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "alg_grafoMA.h"
#include "grafoMA.h"
#include "grafoMA.cpp"
#include "grafoPMC.h"
#include "matriz.h"
#include <cmath>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

using namespace std;

struct ciudad
{
    double x,y;
};

struct puente
{
    ciudad c1,c2;
    double coste;
};

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

puente construirPuente(Grafo G,vector<ciudad> ciudadesArchipielago,vector<ciudad> costerasFobos,vector<ciudad> costerasDeimos);
puente mejorPuente (vector<ciudad> costerasFobos,vector<ciudad> costerasDeimos);

int main()
{
    Grafo G("examenSept2019.txt");//matriz de adyacencia del archipielago

    vector<ciudad> ciudadesArchipielago(6);
    ciudadesArchipielago[0].x = 3; ciudadesArchipielago[0].y = 1;
    ciudadesArchipielago[1].x = 3; ciudadesArchipielago[1].y = 3;
    ciudadesArchipielago[2].x = 3; ciudadesArchipielago[2].y = 4;
    ciudadesArchipielago[3].x = 3; ciudadesArchipielago[3].y = -3;
    ciudadesArchipielago[4].x = 4; ciudadesArchipielago[4].y = -3;
    ciudadesArchipielago[5].x = 6; ciudadesArchipielago[5].y = -3;

    vector<ciudad> costerasFobos(2);
    costerasFobos[0].x = 3; costerasFobos[0].y = 1;
    costerasFobos[1].x = 3; costerasFobos[1].y = 3;

    vector<ciudad> costerasDeimos(2);
    costerasDeimos[0].x = 3; costerasDeimos[0].y = -3;
    costerasDeimos[1].x = 4; costerasDeimos[1].y = -3;

    puente p = construirPuente(G,ciudadesArchipielago,costerasFobos,costerasDeimos);

    cout << "Las ciudades que unira el puente seran: " << endl << "Ciudad 1: x=" << p.c1.x << " y=" << p.c1.y << endl << "Ciudad 2: x=" << p.c2.x << " y=" << p.c2.y; 

    return 0;
}

puente construirPuente(Grafo G,vector<ciudad> ciudadesArchipielago,vector<ciudad> costerasFobos,vector<ciudad> costerasDeimos)
{
    size_t n = G.numVert();
    GrafoP<double> GPond(n);

    for(vertice i = 0 ; i < n ; i++)
    {
        for(vertice j = 0 ; j < n ; j++)
        {
            if(G[i][j])
            {
                GPond[i][j] = distancia(ciudadesArchipielago[i], ciudadesArchipielago[j]);
            }
        }
    }

    puente p = mejorPuente(costerasFobos,costerasDeimos);
    vertice v1,v2;
    for(size_t i = 0 ; i < ciudadesArchipielago.size() ; i++)
    {
        if(ciudadesArchipielago[i].x == p.c1.x && ciudadesArchipielago[i].y == p.c1.y)
        {
            v1 = i;
        }
        if(ciudadesArchipielago[i].x == p.c2.x && ciudadesArchipielago[i].y == p.c2.y)
        {
            v2 = i;
        }
    }

    GPond[v1][v2] = p.coste;
    GPond[v2][v1] = p.coste;

    cout << "El grafo resultante de construir el puente es de: " << endl << GPond << endl;

    return p;
}

puente mejorPuente (vector<ciudad> costerasFobos,vector<ciudad> costerasDeimos)
{
    puente p;
    p.coste = GrafoP<double>::INFINITO;
    double costemin;

    for(size_t i = 0 ; i < costerasFobos.size() ; i++)
    {
        for(size_t j = 0 ; j < costerasDeimos.size() ; j++)
        {
            costemin = distancia(costerasFobos[i],costerasDeimos[j]);
            if(costemin < p.coste)
            {
                p.coste = costemin;
                p.c1 = costerasFobos[i];
                p.c2 = costerasDeimos[j];
            }
        }   
    }
    return p;
}