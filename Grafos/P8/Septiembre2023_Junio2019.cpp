/*El archipiélago de Tombuctú está formado por un número desconocido de 
islas, cada una de las cuales tiene, a su vez, un número desconocido de 
ciudades, las cuales tienen en común que todas y cada una de ellas dispone de 
un aeropuerto. 

Sí que se conoce el número total de ciudades del archipiélago (podemos llamarlo 
N, por ejemplo). Dentro de cada una de las islas existen 
carreteras que permiten viajar entre todas las ciudades de la isla. No existen 
puentes que unan las islas y se ha decidido que la opción de comunicación 
más económica de implantar será el avión. Se dispone de las coordenadas 
cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. 

Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe 
carretera directa entre cualesquiera dos ciudades del archipiélago. El objetivo 
de nuestro problema es encontrar qué líneas aéreas debemos implantar para
poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes 
criterios: 1)Se implantará una y sólo una línea aérea entre cada par de islas.
2)La línea aérea escogida entre cada par de islas será la más corta entre todas
las posibles. Así pues, dados los siguientes datos:


•Lista de ciudades de Tombuctú representada cada una de ellas por sus
coordenadas cartesianas.

•Matriz de adyacencia de Tombuctú que indica las carreteras existentes en
dicho archipiélago,

Implementen un subprograma que calcule y devuelva las líneas aéreas 
necesarias para comunicar adecuadamente el archipiélago siguiendo los 
criterios anteriormente expuestos.*/

#include "alg_grafoPMC.h"
#include "grafoMA.h"
#include "grafoPMC.h"
#include "particion.h"
#include "apo.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;


struct ciudad
{
    double x, y;
};

struct LineaAerea
{
    ciudad c1;
    ciudad c2;
    double coste;
    LineaAerea(ciudad c1, ciudad c2) : c1(c1), c2(c2), coste(distancia(c1, c2)){}
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
    return i-1;
}

vector<LineaAerea> Tombuctu(Grafo MA, vector<ciudad> ciudades)
{
    size_t n = MA.numVert();
    GrafoP<double> G(n);
    for(vertice i = 0; i < n; i++)
    {
        for (size_t j = 0; i < n; j++)
        {
            if(MA[i][j])
                G[i][j] = distancia(ciudades[i], ciudades[j]);
            if(MA[j][i])
                G[j][i] = distancia(ciudades[i], ciudades[j]);
        }
        
    }

    matriz<vertice> mVer;
    matriz<double> mCostes = Floyd(G, mVer); //conectamos todas las ciudades posibles

    size_t nIslas = n;
    Particion Islas(n);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; i < n; j++)
        {
            if(mCostes[i][j] != GrafoP<double>::INFINITO || mCostes[j][i] != GrafoP<double>::INFINITO && Islas.encontrar(i) != Islas.encontrar(j))
            {
                Islas.unir(i, j); //unimos las ciudades que son de la misma isla
                nIslas--; //y calculamos el numero de islas
            }
        }
    }

    Apo<LineaAerea> apoLineas(n * (n-1)/2); //para ordenar las lineas aereas por coste

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i; j < n; j++)
        {
            if(Islas.encontrar(i) != Islas.encontrar(j))
            {
                apoLineas.insertar(LineaAerea(ciudades[i], ciudades[j])); //insertamos las ciudades de distintas islas
            }
        }
        
    }

    Grafo IslasConectadas(nIslas);
    vector<LineaAerea> Lineas (nIslas * (nIslas-1)/2);
    for (size_t i = 0; i < Lineas.size(); i++)
    {
        LineaAerea l = apoLineas.cima();
        apoLineas.suprimir();
        vertice v = BuscarCiudad(l.c1, ciudades) % nIslas;
        vertice w = BuscarCiudad(l.c2, ciudades) % nIslas;
        if(!IslasConectadas[v][w])
        {
            IslasConectadas[v][w] = true; //marcamos las islas que se conectan
            IslasConectadas[w][v] = true;
            Lineas.push_back(l); //añadimos la linea aerea
        }
    }
    
    return Lineas;
    
}



/*

 ______                    __                      __
/\__  _\                  /\ \                    /\ \__
\/_/\ \/   ___     ___ ___\ \ \____  __  __    ___\ \ ,_\  __  __
   \ \ \  / __`\ /' __` __`\ \ '__`\/\ \/\ \  /'___\ \ \/ /\ \/\ \
    \ \ \/\ \L\ \/\ \/\ \/\ \ \ \L\ \ \ \_\ \/\ \__/\ \ \_\ \ \_\ \ 2
     \ \_\ \____/\ \_\ \_\ \_\ \_,__/\ \____/\ \____\\ \__\\ \____/
      \/_/\/___/  \/_/\/_/\/_/\/___/  \/___/  \/____/ \/__/ \/___/


*/
