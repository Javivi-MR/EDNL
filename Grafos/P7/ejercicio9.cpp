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
    tCoste CostePath;
    tCamino Path;
};

path viajar(GrafoP<int>& GTren, GrafoP<int>& GAutobus, vertice origen, vertice destino, tCoste CosteTaxi);

int main()
{
    GrafoP<int> GTren ("8tren.txt");
    GrafoP<int> GAutobus ("8autobus.txt");
    tCoste CosteTaxi = 4;

    path resultado = viajar(GTren,GAutobus,0,3,CosteTaxi);

    cout << endl << endl;

    cout << "El coste minimo para llegar del origen hacia el destino es de: " << resultado.CostePath << " Y el recorrido a hacer es: ";
    Lista<vertice>::posicion pos = resultado.Path.primera();
    while(pos != resultado.Path.fin())
    {
        cout << resultado.Path.elemento(pos) % GTren.numVert() << " ";
        pos = resultado.Path.siguiente(pos);
    }



    return 0;
}

path viajar(GrafoP<int>& GTren, GrafoP<int>& GAutobus, vertice origen, vertice destino, tCoste CosteTaxi)
{
    size_t n = GTren.numVert();
    GrafoP<int> G(n * 2); // Creamos grafo de 2 veces el tamaño de los grafos (GTren es de 5 so G sera de 10) 

    /*
    El objetivo de crear este  grafo es poder transportarnos de un grafo y otro
    Los nodos del i = 0 - 4 y j = 0 - 4 representara la matriz de costes del tren, y i = 5 - 9 j = 5 - 9 (es decir 0 + n ||1 + n ||2 + n ... hasta 4) representara a la matriz de costes del bus
    Luego ademas añadiremos un coste de "CosteTaxi" (en este ejemplo 4) en los transportes de un vertice de la matriz de costes de tren hacia su similar de la de buses
    es decir 0 <-> 5 luego del 1 <-> 6, 2 <-> 7 ... asi hasta i <-> i+n
    */

    
    for(size_t i = 0 ; i < n ; i++)
    {
        G[n+i][i] = CosteTaxi;  //coste de taxi de transportarse de un grafo a otro
        G[i][n+i] = CosteTaxi;  //same
        for(size_t j = 0 ; j < n ; j++)
        {
            G[i][j] = GTren[i][j];  // rellenamos nuestro grafo auxiliar del 0 - 4 con la m de costes del tren
            G[n+i][n+j] = GAutobus[i][j];   //same pero del 5 - 9 con la m de costes del bus
        }
    }
    //Aqui nuestro grafo auxiliar esta lista
    cout << G << endl;

    vector<vertice> caminoOrigenTren;
    vector<tCoste> costesOrigenTren = Dijkstra(G,origen,caminoOrigenTren); // hacemos un dijkstra con el origen (0) para calcular el camino mas corto a todos los nodos 
    //notese que el nodo origen realmente tambien podria ser su similar es decir el 5 (partiendo del origen desde la m de costes del bus)

    cout << costesOrigenTren << endl;

    vector<vertice> caminoOrigenBus; //por el motivo anterior hacemos un dijkstra con el origen desde la m de costes del tren
    vector<tCoste> costesOrigenBus = Dijkstra(G,origen + n,caminoOrigenBus);

    cout << costesOrigenBus << endl;

    //Una vez tenemos las distancias minimas desde el origen (ambos) hacia cualquier nodo, tenemos que coger la minima distancia hacia el destino (Recordemos que disponemos
    //de 2 destinos tambien, en este caso destino(3) en la m de costes del tren y destino(3+5) en la m de costes del bus.
    //asi que guardaremos el minimo valor de estos valores que sera la minima distacia. :)

    vertice o = origen, d = destino;    //esta variable nos indicara si partimos desde 
    size_t v_vertice = 1; // 1 de tren o 2 de bus

    tCoste minimo = min(costesOrigenTren[destino],costesOrigenTren[destino + n]);

    if(costesOrigenTren[destino + n] < costesOrigenTren[destino])
    {
        d = destino + n;
    }

    minimo = min(minimo,costesOrigenBus[destino]);
    if(minimo < costesOrigenBus[destino]) 
    {
        o = origen + n;
        v_vertice = 2;
    }

    minimo = min(minimo,costesOrigenBus[destino+n]);
    if(minimo < costesOrigenBus[destino + n])
    {
        o = origen + n;
        destino = destino + n;
        v_vertice = 2;
    }

    path p;
    p.CostePath = minimo;
    if(v_vertice == 1)
    {
        p.Path = camino<GrafoP<size_t>::vertice>(o,d,caminoOrigenTren);
    }
    else
    {
        p.Path = camino<GrafoP<size_t>::vertice>(o,d,caminoOrigenBus);
    }

    return p;
}