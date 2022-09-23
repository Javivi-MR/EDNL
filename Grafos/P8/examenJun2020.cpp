/*
Un repartidor de una empresa de distribución de bebidas tiene que visitar a todos sus
clientes cada día. Pero, al comenzar su jornada de trabajo, no conoce qué cantidad de bebidas
tiene que servir a cada cliente, por lo que no puede planificar una ruta óptima para visitarlos a
todos. Por tanto, nuestro repartidor decide llevar a cabo la siguiente estrategia:

- El camión parte del almacén con la máxima carga permitida rumbo a su cliente más
próximo.

- El repartidor descarga las cajas de bebidas que le pide el cliente. Si no tiene suficientes
cajas en el camión, le entrega todas las que tiene. Este cliente terminará de ser servido en
algún otro momento a lo largo del día, cuando la estrategia de reparto vuelva a llevar al
repartidor hasta él.

- Después de servir a un cliente:
    o Si quedan bebidas en el camión, el repartidor consulta su sistema de navegación
    basado en GPS para conocer la ruta que le lleva hasta su cliente más próximo
    pendiente de ser servido.

    o Si no quedan bebidas en el camión, vuelve al almacén por el camino más corto y
    otra vez carga el camión completamente.
- Después de cargar el camión, el repartidor consulta su sistema de navegación y se va por
el camino más corto a visitar al cliente pendiente de ser servido más próximo.
Implementa un subprograma que calcule y devuelva la distancia total recorrida en un
día por nuestro repartidor, a partir de lo siguiente:
    
    1. Grafo representado mediante matriz de costes con las distancias de los caminos directos
    entre los clientes y entre ellos y la central.

    2. Capacidad máxima del camión (cantidad de cajas de bebidas).
    
    3. Asumiremos que existe una función int Pedido() que devuelve el número de cajas que
    quedan por servir al cliente en el que se encuentra el repartidor.
*/



#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

using namespace std;

int pedido(vertice v);

tCoste repartir(GrafoP<int> G, int capacidadCamion,vertice origen);
bool quedanClientes (vector<bool> clientesTerminados);
vertice siguienteCliente(matriz<tCoste> MFloyd, vertice actual, vector<bool> clientesTerminados,vector<int> FaltaPorRepartir, tCoste& costeAcumulado, int capacidadActual,vertice origen);

int main()
{
    GrafoP<int> G("examenJun2020.txt");
    int  capacidadCamion = 50;

    tCoste costetotal = repartir(G,capacidadCamion,0);

    cout << "El coste minimo para repatir a todos los clientes es de: " << costetotal;

    return 0;
}

tCoste repartir(GrafoP<int> G, int capacidadCamion,vertice origen)
{
    size_t n = G.numVert();
    int capacidadActual = capacidadCamion;
    vector<bool> clientesTerminados (n,false);
    clientesTerminados[origen] = true;
    tCoste costeAcumulado = 0;
    vertice actual = origen;
    matriz<vertice> Mver(n);
    matriz<tCoste> MFloyd = Floyd(G,Mver);
    vector<int> FaltaPorRepartir(n);


    for(size_t i = 0; i < FaltaPorRepartir.size(); i++)
    {
        FaltaPorRepartir[i] = pedido(i);
    } 


    while(!quedanClientes(clientesTerminados))
    {
        if(actual == origen)
        {
            capacidadActual = capacidadCamion;
            actual = siguienteCliente(MFloyd,actual,clientesTerminados,FaltaPorRepartir,costeAcumulado,capacidadActual,origen);
        }
        else
        {
            if(capacidadActual > FaltaPorRepartir[actual])
            {
                capacidadActual = capacidadActual - FaltaPorRepartir[actual];
                clientesTerminados[actual] = true;
                FaltaPorRepartir[actual] = 0;
                actual = siguienteCliente(MFloyd,actual,clientesTerminados,FaltaPorRepartir,costeAcumulado,capacidadActual,origen);
            }
            else
            {

                FaltaPorRepartir[actual] = FaltaPorRepartir[actual] - capacidadActual;
                capacidadActual = 0;
                actual = siguienteCliente(MFloyd,actual,clientesTerminados,FaltaPorRepartir,costeAcumulado,capacidadActual,origen);
            }
        }
    }
    return costeAcumulado;
}

bool quedanClientes (vector<bool> clientesTerminados)
{
    bool aux = true;
    for(size_t i = 0; i < clientesTerminados.size(); i++)
    {
        if(clientesTerminados[i] == false)
        {
            aux = false;
        }
    }
    return aux;
}

vertice siguienteCliente(matriz<tCoste> MFloyd, vertice actual, vector<bool> clientesTerminados, vector<int> FaltaPorRepartir, tCoste& costeAcumulado, int capacidadActual,vertice origen)
{
    vertice v;
    tCoste carreteramin = GrafoP<int>::INFINITO;
    if(capacidadActual == 0)
    {
        costeAcumulado = costeAcumulado + MFloyd[actual][origen];
        return origen;
    }
    else
    {
        if(quedanClientes(clientesTerminados))
        {
            return origen;
        }
        else
        {
            for(vertice i = 0 ; i < FaltaPorRepartir.size() ; i++)
            {
                if(FaltaPorRepartir[i] > 0 && MFloyd[actual][i] < carreteramin)
                {
                    v = i;
                    carreteramin = MFloyd[actual][i];
                }
            }
        }
    }

    costeAcumulado = costeAcumulado + MFloyd[actual][v];

    return v;
}

int pedido(vertice v)
{
    int aux;
    switch(v)
    {
        case 0:
            aux = 0;
        break;
        case 1:
            aux = 20;
        break;
        case 2:
            aux = 50;
        break;
        case 3:
            aux = 10;
        break;
        case 4:
            aux = 5;
        break;
    }
    return aux;
}