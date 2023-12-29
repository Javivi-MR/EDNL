/*El archipìélago de Grecoland (Zuelandia) está formado únicamente por tres islas, Fobos, Deimos y Europa,
que tienen N1, N2 y N3 ciudades, respectivamente, de las cuales C1, C2 y C3 ciudaqdes son costeras
(obviamente C1 <= N1, C2 <= N2 y C3 <= N3). Se dispone de las coordenadas cartesianas (x, y) de todas
y cada una de las ciudades del archipiélago. El huracán Isadore acaba de devastar el archipiélago, con lo
que todas las carreteras y puentes construidos en su día han desaparecido. En esta terrible situación se pide ayuda 
a la ONU, que acepta reconstruir el archipiélago (es decir volver a comunicar todas las ciudades del archipiélago)
siempre que se haga al mínimo coste.

De cara a poder comparar costes de posibles reconstrucciones se asume lo siguiente:

1. El coste de construir cualquier carretera o cualquier puente es proporcional a su longitud (distancia euclídea
entre las poblaciones de inicio y fin de la carretera o el puente).
2. Cualquier puente que se construya siempre será más barato que cualquier carretera que se cconstruya.

En estas condiciones, implementa un subprograma que calcule el coste mínimo de viajar entre dos ciudades de
Grecoland origen y destino, después de haberse reconstruido el archpiélago, dados los siguientes datos:

·Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
·Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas.
·Lista de ciudades de Europa representadas mediante sus coordenadas cartesianas.
·Lista de ciudades costeras de Fobos.
·Lista de ciudades costeras de Deimos.
·Lista de ciudades costeras de Europa.
·Ciudad origen del viaje.
·Ciudad destino del viaje.
*/

#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include <vector>
#include <cmath>

using namespace std;

typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;

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

double distancia(ciudad c1, ciudad c2)
{
    return sqrt(pow(abs(c1.x - c2.x), 2) + pow(abs(c1.y - c2.y), 2));
}

vertice BuscarCiudad(ciudad c, vector<ciudad> ciudades)
{
    bool encontrada = false;
    size_t i;
    for(i = 0; i < ciudades.size() && !encontrada; i++)
    {
        if(c.x == ciudades[i].x && c.y == ciudades[i].y)
            encontrada = true;
    }
    if(encontrada)
        return i;
    else
        return -1;
}

double Grecoland(vector<ciudad> ciudadesFobos, vector<ciudad> ciudadesDeimos, vector<ciudad> ciudadesEuropa, 
vector<ciudad> costerasFobos, vector<ciudad> costerasDeimos, vector<ciudad> costerasEuropa, ciudad origen, ciudad destino) 
{
    size_t nf = ciudadesFobos.size();
    size_t nd = ciudadesDeimos.size();
    size_t ne = ciudadesEuropa.size();

    GrafoP<double> G(nf + nd + ne);
    double puenteMasCaro;
    int aux = 0;


    /**********PUENTES***********/

    puente p1 = mejorPuente(ciudadesFobos, ciudadesDeimos, ciudadesEuropa, costerasFobos, costerasDeimos, costerasEuropa, aux);
    if(aux == 1) //Fobos y Deimos
    {
        p1.v2 = p1.v2 + nf;
    }
    if(aux == 2) //Fobos y Europa
    {
        p1.v2 = p1.v2 + nf + nd;
    }
    if(aux == 3) //Deimos y Europa
    {
        p1.v1 = p1.v1 + nf;
        p1.v2 = p1.v2 + nf + nd;
    }

    puente p2 = mejorPuente(ciudadesFobos, ciudadesDeimos, ciudadesEuropa, costerasFobos, costerasDeimos, costerasEuropa, aux);
    if(aux == 1) //Fobos y Deimos
    {
        p2.v2 = p2.v2 + nf;
    }
    if(aux == 2) //Fobos y Europa
    {
        p2.v2 = p2.v2 + nf + nd;
    }
    if(aux == 3) //Deimos y Europa
    {
        p2.v1 = p2.v1 + nf;
        p2.v2 = p2.v2 + nf + nd;
    }

    if(p1.coste > p2.coste)
        puenteMasCaro = p1.coste;
    else
        puenteMasCaro = p2.coste;

    /********CARRETERAS********/



    //FOBOS

    for (vertice i = 0; i < nf - 1; i++)
    {
        for (vertice j = i + 1; i < nf; j++)
        {
            G[i][j] = distancia(ciudadesFobos[i], ciudadesFobos[j]) + puenteMasCaro;
            G[j][i] = distancia(ciudadesFobos[i], ciudadesFobos[j]) + puenteMasCaro;
        }    
    }
    
    //DEIMOS

    for (vertice i = nf; i < nf + nd - 1; i++)
    {
        for (vertice j = i + 1; i < nf + nd; j++)
        {
            G[i][j] = distancia(ciudadesDeimos[i-nf], ciudadesDeimos[j-nf]) + puenteMasCaro;
            G[j][i] = distancia(ciudadesDeimos[i-nf], ciudadesDeimos[j-nf]) + puenteMasCaro;
        }    
    }

    //EUROPA

    for (vertice i = nf + nd; i < nf + nd + ne - 1; i++)
    {
        for (vertice j = i + 1; i < nf + nd + ne; j++)
        {
            G[i][j] = distancia(ciudadesEuropa[i-nf-ne], ciudadesEuropa[j-nf-ne]) + puenteMasCaro;
            G[j][i] = distancia(ciudadesEuropa[i-nf-ne], ciudadesEuropa[j-nf-ne]) + puenteMasCaro;
        }    
    }

    for (vertice i = 0; i < nf + nd + ne; i++)
    {
        G[i][i] = 0;
    }
    

    GrafoP<double> GrecolandPrim(nf + nd + ne);
    GrecolandPrim = Prim(G); //Ya tenemos las carreteras al menor coste y los puentes reconstruidos


    vector<vertice> P(nf + nd + ne);
    vector<double> D(nf + nd + ne);

    //Buscamos las ciudades origen y destino
    vertice o = BuscarCiudad(origen, ciudadesFobos);
    if(o == -1)
    {
        o = BuscarCiudad(origen, ciudadesDeimos);
        if(o == -1)
            o = BuscarCiudad(origen, ciudadesEuropa);
    }

    vertice d = BuscarCiudad(destino, ciudadesFobos);
    if(d == -1)
    {
        d = BuscarCiudad(destino, ciudadesDeimos);
        if(d == -1)
            d = BuscarCiudad(destino, ciudadesEuropa);
    }

    
    D = Dijkstra(GrecolandPrim, o, P);

    return D[d];
}

puente mejorPuente(vector<ciudad> ciudadesFobos, vector<ciudad> ciudadesDeimos,
vector<ciudad> ciudadesEuropa, vector<ciudad> costerasFobos, vector<ciudad> costerasDeimos, vector<ciudad> costerasEuropa, int& aux)
{
    puente paux;
    paux.coste = GrafoP<double>::INFINITO;

    if(aux == 0)
    {
        //FOBOS - DEIMOS

        for (size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            vertice cf = BuscarCiudad(costerasFobos[i], ciudadesFobos);
            for (size_t j = 0; j < ciudadesDeimos.size(); j++)
            {
                vertice cd = BuscarCiudad(costerasDeimos[j], ciudadesDeimos);
                double costeaux = distancia(costerasFobos[i], costerasDeimos[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.c1 = ciudadesFobos[cf];
                    paux.c2 = ciudadesDeimos[cd];
                    paux.v1 = cf;
                    paux.v2 = cd;
                    aux = 1;
                }
            }
        }
        
        //FOBOS - EUROPA

        for (size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            vertice cf = BuscarCiudad(costerasFobos[i], ciudadesFobos);
            for (size_t j = 0; j < ciudadesEuropa.size(); j++)
            {
                vertice ce = BuscarCiudad(costerasEuropa[j], ciudadesEuropa);
                double costeaux = distancia(costerasFobos[i], costerasEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.c1 = ciudadesFobos[cf];
                    paux.c2 = ciudadesEuropa[ce];
                    paux.v1 = cf;
                    paux.v2 = ce;
                    aux = 2;
                }
            }
        }

        //DEIMOS - EUROPA

        for (size_t i = 0; i < ciudadesDeimos.size(); i++)
        {
            vertice cd = BuscarCiudad(costerasDeimos[i], ciudadesDeimos);
            for (size_t j = 0; j < ciudadesEuropa.size(); j++)
            {
                vertice ce = BuscarCiudad(costerasEuropa[j], ciudadesEuropa);
                double costeaux = distancia(costerasDeimos[i], costerasEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.c1 = ciudadesDeimos[cd];
                    paux.c2 = ciudadesEuropa[ce];
                    paux.v1 = cd;
                    paux.v2 = ce;
                    aux = 1;
                }
            }
        }
    }

    if(aux == 1)
    {
        
        //FOBOS - EUROPA

        for (size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            vertice cf = BuscarCiudad(costerasFobos[i], ciudadesFobos);
            for (size_t j = 0; j < ciudadesEuropa.size(); j++)
            {
                vertice ce = BuscarCiudad(costerasEuropa[j], ciudadesEuropa);
                double costeaux = distancia(costerasFobos[i], costerasEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.c1 = ciudadesFobos[cf];
                    paux.c2 = ciudadesEuropa[ce];
                    paux.v1 = cf;
                    paux.v2 = ce;
                    aux = 2;
                }
            }
        }

        //DEIMOS - EUROPA

        for (size_t i = 0; i < ciudadesDeimos.size(); i++)
        {
            vertice cd = BuscarCiudad(costerasDeimos[i], ciudadesDeimos);
            for (size_t j = 0; j < ciudadesEuropa.size(); j++)
            {
                vertice ce = BuscarCiudad(costerasEuropa[j], ciudadesEuropa);
                double costeaux = distancia(costerasDeimos[i], costerasEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.c1 = ciudadesDeimos[cd];
                    paux.c2 = ciudadesEuropa[ce];
                    paux.v1 = cd;
                    paux.v2 = ce;
                    aux = 1;
                }
            }
        }
    }

    if(aux == 2)
    {
        //FOBOS - DEIMOS

        for (size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            vertice cf = BuscarCiudad(costerasFobos[i], ciudadesFobos);
            for (size_t j = 0; j < ciudadesDeimos.size(); j++)
            {
                vertice cd = BuscarCiudad(costerasDeimos[j], ciudadesDeimos);
                double costeaux = distancia(costerasFobos[i], costerasDeimos[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.c1 = ciudadesFobos[cf];
                    paux.c2 = ciudadesDeimos[cd];
                    paux.v1 = cf;
                    paux.v2 = cd;
                    aux = 1;
                }
            }
        }

        //DEIMOS - EUROPA

        for (size_t i = 0; i < ciudadesDeimos.size(); i++)
        {
            vertice cd = BuscarCiudad(costerasDeimos[i], ciudadesDeimos);
            for (size_t j = 0; j < ciudadesEuropa.size(); j++)
            {
                vertice ce = BuscarCiudad(costerasEuropa[j], ciudadesEuropa);
                double costeaux = distancia(costerasDeimos[i], costerasEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.c1 = ciudadesDeimos[cd];
                    paux.c2 = ciudadesEuropa[ce];
                    paux.v1 = cd;
                    paux.v2 = ce;
                    aux = 1;
                }
            }
        }
    }

    if(aux == 3)
    {
        //FOBOS - DEIMOS

        for (size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            vertice cf = BuscarCiudad(costerasFobos[i], ciudadesFobos);
            for (size_t j = 0; j < ciudadesDeimos.size(); j++)
            {
                vertice cd = BuscarCiudad(costerasDeimos[j], ciudadesDeimos);
                double costeaux = distancia(costerasFobos[i], costerasDeimos[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.c1 = ciudadesFobos[cf];
                    paux.c2 = ciudadesDeimos[cd];
                    paux.v1 = cf;
                    paux.v2 = cd;
                    aux = 1;
                }
            }
        }
        
        //FOBOS - EUROPA

        for (size_t i = 0; i < ciudadesFobos.size(); i++)
        {
            vertice cf = BuscarCiudad(costerasFobos[i], ciudadesFobos);
            for (size_t j = 0; j < ciudadesEuropa.size(); j++)
            {
                vertice ce = BuscarCiudad(costerasEuropa[j], ciudadesEuropa);
                double costeaux = distancia(costerasFobos[i], costerasEuropa[j]);
                if(costeaux < paux.coste)
                {
                    paux.coste = costeaux;
                    paux.c1 = ciudadesFobos[cf];
                    paux.c2 = ciudadesEuropa[ce];
                    paux.v1 = cf;
                    paux.v2 = ce;
                    aux = 2;
                }
            }
        }
    }

    return paux;
}