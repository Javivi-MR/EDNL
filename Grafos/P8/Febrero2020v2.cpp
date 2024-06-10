/*El archipielago de Grecoland (Nozuelandia) está formado unicamente por tres islas, Fobos, Deimos y Europa y tienen N1, N2 y N3 ciudades, respectivamente, todas ellas costeras.

Se dispone de la relacion de ciudades de cada una de las tres islas, representadas por sus coordenadas cartesianas.

Dentro del programa COMUNICA de la ONU hemos conseguido fondos para comunicar todas las ciudades de Grecoland. Las condiciones del programa COMUNICA indican que se sufragaran
todos los costes de construcción de las comunicaciones (carreteras y puentes) al menor coste posible.

Se sabe que la mera construccion de un puente o carretera ya implica una serie de costes fijos, que difieren para el caso de carretera y puente.
Además, el coste por unidad de longitud para carreteras y puentes tambien es distinto.

En estas condiciones se debe calcular (mediante una funcion) que carreteras y puentes deben construirse para comunicar entre si todas las ciudades de Grecoland, dados los siguientes datos:

    1. Relacion de las ciudades de Fobos, representadas mediante sus coordenadas cartesianas
    2. Relacion de las ciudades de Deimos, representadas mediante sus coordenadas cartesianas
    3. Relacion de las ciudades de Europa, representadas mediante sus coordenadas cartesianas
    4. Coste inicial de construccion de un puente
    5. Coste inicial de construccion de una carreteras
    6. Coste adicional por unidad de longitud de construccion de un puente
    7. Coste adicional por unidad de longitud de construccion de una carretera
*/

#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>
#include <cmath>
#include <algorithm>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

using namespace std;

struct ciudad
{
    double x, y;
};

struct puente
{
    vertice v1, v2;
    ciudad c1, c2;
    double coste;
};

struct puentes
{
    puente p1, p2;
};

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x - c2.x), 2) + pow(abs(c1.y - c2.y), 2));
}

double construirGrecoland(vector<ciudad>& ciudadesFobos, vector<ciudad>& ciudadesDeimos,
vector<ciudad>& ciudadesEuropa, double costeFPuente, double costeFCarretera,
double costeVPuente, double costeVCarretera)
{
    size_t nf = ciudadesFobos.size();
    size_t nd = ciudadesDeimos.size();
    size_t ne = ciudadesEuropa.size();
    double CosteConstruccion = 0;

    //FOBOS
    GrafoP<double> GFobos (nf);
    for (vertice i = 0; i < nf; i++)
    {
        for (vertice j = 0; i < nf; i++)
        {
            if(i != j)
                GFobos[i][j] = distancia(ciudadesFobos[i], ciudadesFobos[j]);
        }
    }
    
    GrafoP<double> GFobosPrim = Prim(GFobos);
    for (vertice i = 0; i < nf; i++)
    {
        for (vertice j = 0; i < nf; i++)
        {
            if(GFobosPrim[i][j] != GrafoP<double>::INFINITO)
                CosteConstruccion = CosteConstruccion + costeFCarretera + (costeVCarretera * GFobosPrim[i][j]);
        }
    }


    //DEIMOS
    GrafoP<double> GDeimos (nd);
    for (vertice i = 0; i < nd; i++)
    {
        for (vertice j = 0; i < nd; i++)
        {
            if(i != j)
                GDeimos[i][j] = distancia(ciudadesDeimos[i], ciudadesDeimos[j]);
        }
    }
    
    GrafoP<double> GDeimosPrim = Prim(GDeimos);
    for (vertice i = 0; i < nd; i++)
    {
        for (vertice j = 0; i < nd; i++)
        {
            if(GDeimosPrim[i][j] != GrafoP<double>::INFINITO)
                CosteConstruccion = CosteConstruccion + costeFCarretera + (costeVCarretera * GDeimosPrim[i][j]);
        }
    }


    //EUROPA
    GrafoP<double> GEuropa (ne);
    for (vertice i = 0; i < ne; i++)
    {
        for (vertice j = 0; i < ne; i++)
        {
            if(i != j)
                GEuropa[i][j] = distancia(ciudadesEuropa[i], ciudadesEuropa[j]);
        }
    }
    
    GrafoP<double> GEuropaPrim = Prim(GEuropa);
    for (vertice i = 0; i < ne; i++)
    {
        for (vertice j = 0; i < ne; i++)
        {
            if(GEuropaPrim[i][j] != GrafoP<double>::INFINITO)
                CosteConstruccion = CosteConstruccion + costeFCarretera + (costeVCarretera * GEuropaPrim[i][j]);
        }
    }

    //GRAFO GRECOLAND
    GrafoP<double> Grecoland (nf+nd+ne);
    for (vertice i = 0; i < nf; i++)
    {
        for (vertice j = 0; j < nf; j++)
        {
            Grecoland[i][j] = GFobosPrim[i][j];
        }
    }
    
    for (vertice i = nf; i < nf+nd; i++)
    {
        for (vertice j = nf; j < nf+nd; j++)
        {
            Grecoland[i][j] = GDeimosPrim[i-nf][j-nf];
        }
    }

    for (vertice i = nf+nd; i < nf+nd+ne; i++)
    {
        for (vertice j = nf+nd; j < nf+nd+ne; j++)
        {
            Grecoland[i][j] = GFobosPrim[i-nf-nd][j-nf-nd];
        }
    }

    puentes p = mejoresPuentes(ciudadesFobos, ciudadesDeimos, ciudadesEuropa);

    puente p1 = p.p1;
    puente p2 = p.p2;

    Grecoland[p1.v1][p1.v2] = p1.coste;
    CosteConstruccion = CosteConstruccion + costeFPuente + (costeVPuente * p1.coste);
    Grecoland[p1.v2][p1.v1] = p1.coste;
    CosteConstruccion = CosteConstruccion + costeFPuente + (costeVPuente * p1.coste);

    Grecoland[p2.v1][p2.v2] = p2.coste;
    CosteConstruccion = CosteConstruccion + costeFPuente + (costeVPuente * p2.coste);
    Grecoland[p2.v2][p2.v1] = p2.coste;
    CosteConstruccion = CosteConstruccion + costeFPuente + (costeVPuente * p2.coste);
    
    return CosteConstruccion;
}

puentes mejoresPuentes(vector<ciudad> ciudadesFobos, vector<ciudad> ciudadesDeimos,
vector<ciudad> ciudadesEuropa)
{
    puentes p;
    puente p1, p2;
    puente FD, FE, DE;
    FD.coste = GrafoP<double>::INFINITO;
    FE.coste = GrafoP<double>::INFINITO;
    DE.coste = GrafoP<double>::INFINITO;

    //FOBOS-DEIMOS
    for(size_t i = 0; i < ciudadesFobos.size(); i++)
    {
        for(size_t j = 0; j < ciudadesDeimos.size(); j++)
        {
            double coste = distancia(ciudadesFobos[i], ciudadesDeimos[j]);
            if(coste < FD.coste)
            {
                FD.coste = coste;
                FD.c1 = ciudadesFobos[i];
                FD.c2 = ciudadesDeimos[j];
            }
        }
    }

    //FOBOS-EUROPA
    for(size_t i = 0; i < ciudadesFobos.size(); i++)
    {
        for(size_t j = 0; j < ciudadesEuropa.size(); j++)
        {
            double coste = distancia(ciudadesFobos[i], ciudadesEuropa[j]);
            if(coste < FE.coste)
            {
                FE.coste = coste;
                FE.c1 = ciudadesFobos[i];
                FE.c2 = ciudadesEuropa[j];
            }
        }
    }

    //DEIMOS-EUROPA
    for(size_t i = 0; i < ciudadesDeimos.size(); i++)
    {
        for(size_t j = 0; j < ciudadesEuropa.size(); j++)
        {
            double coste = distancia(ciudadesDeimos[i], ciudadesEuropa[j]);
            if(coste < DE.coste)
            {
                DE.coste = coste;
                DE.c1 = ciudadesDeimos[i];
                DE.c2 = ciudadesEuropa[j];
            }
        }
    }

    p1.coste = min({FD.coste, FE.coste, DE.coste});

    if(p1.coste == FD.coste)
    {
        p1.c1 = FD.c1;
        p1.c2 = FD.c2;
        p2.coste = min(FE.coste, DE.coste);

        if(p2.coste == FE.coste)
        {
            p2.c1 = FE.c1;
            p2.c2 = FE.c2;
        }
        else
        {
            p2.c1 = DE.c1;
            p2.c2 = DE.c2;
        }
    }

    if(p1.coste == FE.coste)
    {
        p1.c1 = FE.c1;
        p1.c2 = FE.c2;
        p2.coste = min(FD.coste, DE.coste);

        if(p2.coste == FD.coste)
        {
            p2.c1 = FD.c1;
            p2.c2 = FD.c2;
        }
        else
        {
            p2.c1 = DE.c1;
            p2.c2 = DE.c2;
        }
    }

    if(p1.coste == DE.coste)
    {
        p1.c1 = DE.c1;
        p1.c2 = DE.c2;
        p2.coste = min(FD.coste, FE.coste);

        if(p2.coste == FD.coste)
        {
            p2.c1 = FD.c1;
            p2.c2 = FD.c2;
        }
        else
        {
            p2.c1 = FE.c1;
            p2.c2 = FE.c2;
        }
    }

    p.p1 = p1;
    p.p2 = p2;
    return p;
}