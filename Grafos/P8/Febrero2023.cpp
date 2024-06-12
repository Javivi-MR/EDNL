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
2. Cualquier puente que se construya siempre será más barato que cualquier carretera que se construya.

En estas condiciones, implementa un subprograma que calcule el coste mínimo de viajar entre dos ciudades de
Grecoland origen y destino, después de haberse reconstruido el archipiélago, dados los siguientes datos:

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
    double puenteMasCaro = 0;

    /*PUENTES*/

    /*FOBOS-DEIMOS*/
    for(vertice i = 0; i < costerasFobos.size(); i++)
    {
        vertice Cf = BuscarCiudad(costerasFobos[i], ciudadesFobos);
        for(vertice j = 0; j < costerasDeimos.size(); j++)
        {
            vertice Cd = BuscarCiudad(costerasDeimos[j], ciudadesDeimos) + nf;
            double dist = distancia(costerasFobos[i], costerasDeimos[j]);
            G[Cf][Cd] = G[Cd][Cf] = dist;

            if(dist > puenteMasCaro)
                puenteMasCaro = dist;
        }
    }

    /*FOBOS-EUROPA*/
    for(vertice i = 0; i < costerasFobos.size(); i++)
    {
        vertice Cf = BuscarCiudad(costerasFobos[i], ciudadesFobos);
        for(vertice j = 0; j < costerasEuropa.size(); j++)
        {
            vertice Ce = BuscarCiudad(costerasEuropa[j], ciudadesEuropa) + nf + nd;
            double dist = distancia(costerasFobos[i], costerasEuropa[j]);
            G[Cf][Ce] = G[Ce][Cf] = dist;

            if(dist > puenteMasCaro)
                puenteMasCaro = dist;
        }
    }

    /*DEIMOS-EUROPA*/
    for(vertice i = 0; i < costerasDeimos.size(); i++)
    {
        vertice Cd = BuscarCiudad(costerasDeimos[i], ciudadesDeimos) + nf;
        for(vertice j = 0; j < costerasEuropa.size(); j++)
        {
            vertice Ce = BuscarCiudad(costerasEuropa[j], ciudadesEuropa) + nf + nd;
            double dist = distancia(costerasDeimos[i], costerasEuropa[j]);
            G[Cd][Ce] = G[Ce][Cd] = dist;

            if(dist > puenteMasCaro)
                puenteMasCaro = dist;
        }
    }

    /*CARRETERAS*/

    /*FOBOS*/

    for(vertice i = 0; i < nf; i++)
    {
        for(vertice j = 0; j < nf; j++)
        {
            if(i != j)
                G[i][j] = G[j][i] = distancia(ciudadesFobos[i], ciudadesFobos[j]) + puenteMasCaro;
        }
    }

    /*DEIMOS*/

    for(vertice i = 0; i < nd; i++)
    {
        for(vertice j = 0; j < nd; j++)
        {
            if(i != j)
                G[i+nf][j+nf] = G[j+nf][i+nf] = distancia(ciudadesDeimos[i], ciudadesDeimos[j]) + puenteMasCaro;
        }
    }

    /*EUROPA*/

    for(vertice i = 0; i < ne; i++)
    {
        for(vertice j = 0; j < ne; j++)
        {
            if(i != j)
                G[i+nf+nd][j+nf+nd] = G[j+nf+nd][i+nf+nd] = distancia(ciudadesEuropa[i], ciudadesEuropa[j]) + puenteMasCaro;
        }
    }

    for (vertice i = 0; i < G.numVert(); i++)
        G[i][i] = 0;
    
    /*ELIMINAR ARISTAS SOBRANTES CON KRUSKAL (DLH APRENDE A ESCRIBIRLO BIEN ULTIMO AVISO >:( )*/
    GrafoP<double> K(G.numVert());
    K = Kruskall(G);

    /*CALCULAR COSTE ENTRE CIUDADES*/

    vertice o = BuscarCiudad(origen, ciudadesFobos);
    if(o == -1)
        o = BuscarCiudad(origen, ciudadesDeimos);
    if(o == -1)
        o = BuscarCiudad(origen, ciudadesEuropa);

    vertice d = BuscarCiudad(destino, ciudadesFobos);
    if(d == -1)
        d = BuscarCiudad(destino, ciudadesDeimos);
    if(d == -1)
        d = BuscarCiudad(destino, ciudadesEuropa);

    vector<vertice> P;

    vector<double> D = Dijkstra(K, o, P);

    return D[d];
}
