/*
Añadir una función genérica, llamada DijkstraInv, en el fichero alg_grafoPMC.h para resolver el problema inverso al de Dijkstra, con los mismos 
tipos de parámetros y de resultado que la función ya incluida para éste. La nueva función, por tanto, debe hallar el camino de coste mínimo 
hasta un destino desde cada vértice del grafo y su correspondiente coste. 
*/

#include <iostream>
#include <vector>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"

using namespace std;

int main()
{
    GrafoP<int> G ("ejercicio1.txt");

    cout << G << endl;

    vector<size_t> P;
    vector<int> D = DijkstraInv(G,2,P);

    cout << D << endl;

    return 0;
}

/*
FUNCION DijkstraInv implementada en alg_grafoPMC.h

//Añadido en ejercicio 1 P6
template <typename tCoste>
vector<tCoste> DijkstraInv(const GrafoP<tCoste>& G,
                        typename GrafoP<tCoste>::vertice destino,
                        vector<typename GrafoP<tCoste>::vertice>& P)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   vertice v, w;
   const size_t n = G.numVert();
   vector<bool> S(n, false);
   vector<tCoste> D(n,GrafoP<tCoste>::INFINITO);

   //INICIAR D Y P CON CAMINOS DIRECTOR HACIA EL VERTICE DESTINOS DEL
   for(int i = 0; i < n; i++)
   {
      D[i] = G[i][destino];
   }

   S[destino] = true;   //Destino comprobado
   P = vector<vertice>(n,destino);

   for(size_t i = 1; i <= n-1; i++)
   {

      tCoste costeMin = GrafoP<tCoste>::INFINITO;
      for(v = 0; v < n; v++)
      {
         if(!S[v] && D[v] <= costeMin)
         {
            costeMin = D[v];
            w = v;
         }
      }
      S[w] = true;   // Nuevo vertice
      //recalculamos coste
      for(v = 0; v < n; v++)
      {
         if(!S[v])
         {
            tCoste aux = suma(D[w],G[v][w]);
            if(aux < D[v])
            {
               D[v] = aux;
               P[v] = w;
            }
         }
      }
   }
   return D;
}

*/