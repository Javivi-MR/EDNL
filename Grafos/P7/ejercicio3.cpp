#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct path 
{
    vector<size_t> cantidadesAlmacenadas;
    tCoste costeTotal;
};

path distribucion(GrafoP<int>& G, vertice o,int cantidadProducto, vector<size_t>& capacidades, vector<float>& subvenciones);

int main()
{
    GrafoP<int> G("3.txt");

    vector<size_t> capacidades(4);
    //CAPACIDADES DE CADA CIUDAD
    capacidades[0] = 0; // en el origen no se puede almacenar nada
    capacidades[1] = 100;
    capacidades[2] = 25;
    capacidades[3] = 50;
    //FIN CAPACIDADES DE CADA CIUDAD

    vector<float> subvenciones(4);
    //SUBVENCIONES DE CADA CIUDAD
    subvenciones[0] = 0; // en el origen no se dan subvenciones
    subvenciones[1] = 0.25;
    subvenciones[2] = 0.67;
    subvenciones[3] = 0.75;
    //FIN SUBVENCIONES DE CADA CIUDAD

    //El vertice 0 es nuestro centro de produccion || 60 es la cantidad de uds. del producto a repartir || 
    path P = distribucion(G,0,60,capacidades,subvenciones);


    cout << "Las cantidades almacenadas en cada ciudad es de: " << endl;
    for(int i = 0; i < P.cantidadesAlmacenadas.size(); i++)
    {
        if(i != 0)  //no tenemos en cuenta el origen
        {
            cout << "ciudad " << i << " almacena " << P.cantidadesAlmacenadas[i] << " uds" << endl;
        }
    }
    cout << "Y el coste total (minimo) de transporte es de " << P.costeTotal << endl;



    return 0;
}

path distribucion(GrafoP<int>& G, vertice o,int cantidadProducto, vector<size_t>& capacidades, vector<float>& subvenciones)
{
    for(vertice i = 0 ; i < G.numVert() ; i++)
    {
        for(vertice j = 0 ; j < G.numVert() ; j++)
        {
            if(G[i][j] != GrafoP<int>::INFINITO)
            {
                G[i][j] = G[i][j] - (G[i][j] * subvenciones[j]);
            } 
        }
    }
    //aplicamos las subvenciones al grafo

    vector<vertice> P (G.numVert());
    vector<tCoste> D = Dijkstra(G,o,P);

    vector<size_t> total(G.numVert(), 0);
    tCoste costemin = 0;

    while(cantidadProducto > 0)
    {
        tCoste minimo = GrafoP<int>::INFINITO;
        vertice ciudad = o;

        for(int i = 0; i < G.numVert(); i++)
        {
            if(i != ciudad && i != o && D[i] < minimo && capacidades[i] > 0 && total[i] == 0)
            {
                ciudad = i;
                minimo = D[i];
            }  
        }

        if(capacidades[ciudad] < cantidadProducto)
        {
            total[ciudad] = capacidades[ciudad];
            cantidadProducto = cantidadProducto - capacidades[ciudad];
            costemin = costemin + (D[ciudad] * capacidades[ciudad]);
        }
        else
        {
            total[ciudad] = cantidadProducto;
            cantidadProducto = 0;
            costemin = costemin + (D[ciudad]* capacidades[ciudad]);
        }
    }
    path resultado;

    resultado.cantidadesAlmacenadas = total;
    resultado.costeTotal = costemin;

    return resultado;
}