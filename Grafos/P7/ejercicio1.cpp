#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct Viaje
{
    tCoste coste;
    typename GrafoP<tCoste>::vertice origen, destino;
};

Viaje viajemaslargo (GrafoP<int>& G);

int main()
{
    GrafoP<int> G ("1.txt");
    matriz<vertice> P(G.numVert());

    Viaje v = viajemaslargo(G);

    cout << "el viaje mas costoso, tiene un coste de: " << v.coste << " y parte del vertice: " << v.origen << " y va hacia: " << v.destino << endl;

    return 0;
}

Viaje viajemaslargo (GrafoP<int>& G)
{
    Viaje aux;

    matriz<tCoste> McostesMaximos = FloydMax(G);

    tCoste costemaximo = 0;
    vertice origen,destino;

    for(vertice i = 0; i < G.numVert(); i++)
    {
        for(vertice j = 0; j < G.numVert(); j++)
        {
            if(costemaximo < McostesMaximos[i][j] && McostesMaximos[i][j] != GrafoP<int>::INFINITO)
            {
                costemaximo = McostesMaximos[i][j];
                origen = i;
                destino = j;
            }
        }
    }

    aux.coste = costemaximo;
    aux.origen = origen;
    aux.destino = destino;

    return aux;
}

/*

Funcion FloydMax en alg_grafoPMC.h

template <typename tCoste>
matriz<tCoste> FloydMax(const GrafoP<tCoste>& G)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   const size_t n = G.numVert();
   matriz<tCoste> A(n);   // matriz de costes mínimos
   
   for (vertice i = 0; i < n; i++) 
   {
      A[i] = G[i];                    // copia costes del grafo
      A[i][i] = 0;                    // diagonal a 0
   }

   for(vertice k = 0; k < n; k++) 
   {
      for(vertice i = 0; i < n; i++)
      {
         for(vertice j = 0; j < n; j++)
         {
            tCoste kij = suma(A[i][k],A[k][j]);
            if(kij != GrafoP<int>::INFINITO && (kij > A[i][j] || A[i][j] == GrafoP<int>::INFINITO)) //HAY QUE AÑADIR LA CONDICION A[i][j] == GrafoP<int>::INFINITO PARA QUE HAYA UN CAMINO POSIBLE ENTRE DOS NODOS NO CONECTADOS
            {
               A[i][j] = kij;
            }
         }
      }
   }
   return A;
}

*/