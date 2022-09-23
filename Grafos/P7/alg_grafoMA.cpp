/*--------------------------------------------------------*/
/* alg_grafoMA.cpp                                        */
/*                                                        */
/* Implementación de algoritmos para grafos no ponderados */
/* representados mediante matriz de adyacencia.           */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* ©2016 José Fidel Argudo                                */
/*--------------------------------------------------------*/

#include "alg_grafoMA.h"
#include "pilaenla.h"  // requerido por Profundidad2()
#include "colaenla.h"  // requerido por Anchura()

using namespace std;

matriz<bool> Warshall(const Grafo& G)
// Determina si hay un camino entre cada par de vértices
// del grafo G.
// Devuelve una matriz booleana A de tamaño n x n, tal que
// A[i][j] == true si existe al menos un camino entre
// el vértice i y el vértice j, y A[i][j] == false si no
// existe ningún camino entre los vértices i y j.
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();

   // Inicializar A con la matriz de adyacencia de G
   matriz<bool> A(n);
   for (vertice i = 0; i < n; i++) {
      A[i] = G[i];
      A[i][i] = true;
   }

   // Comprobar camino entre cada par de vértices i, j
   // a través de cada vértice k
   for (vertice k = 0; k < n; k++)
      for (vertice i = 0; i < n; i++)
         for (vertice j = 0; j < n; j++)
            if (!A[i][j])
               A[i][j] = A[i][k] && A[k][j];
   return A;
}

/*----------------------------------------------------------------------------*/
/* Recorridos de grafos no ponderados                                         */
/*----------------------------------------------------------------------------*/
enum visitas {NO_VISITADO, VISITADO};

static Lista<Grafo::vertice> Profun(const Grafo& G, Grafo::vertice v,
                                    vector<visitas>& marcas)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   Lista<vertice> Lv;

   marcas[v] = VISITADO;
   Lv.insertar(v, Lv.fin());
   for (vertice w = 0; w < n; w++)
      if (G[v][w] && marcas[w] == NO_VISITADO)
            Lv += Profun(G, w, marcas);
   return Lv;
}

Lista<Grafo::vertice> Profundidad(const Grafo& G, Grafo::vertice v)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   vector<visitas> marcas(n, NO_VISITADO);
   Lista<vertice> Lv;
   vertice i = v;

   do {
      if (marcas[i] == NO_VISITADO)
         Lv += Profun(G, i, marcas);
      i = (i+1) % n;
   } while (i != v);
   return Lv;
}

Lista<Grafo::vertice> Profundidad2(const Grafo& G, Grafo::vertice u)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   vector<visitas> marcas(n, NO_VISITADO);
   Pila<vertice> P;
   Lista<vertice> Lv;
   vertice i = u;

   do {
      if (marcas[i] == NO_VISITADO) {
         P.push(i);
         do {
            vertice v = P.tope();
            P.pop();
            if (marcas[v] == NO_VISITADO) {
               // Marcar y procesar v
               marcas[v] = VISITADO;
               Lv.insertar(v, Lv.fin());
               // Meter en la pila los adyacentes no visitados
               for (vertice w = n; w > 0; w--)
                  if (G[v][w-1] && marcas[w-1] == NO_VISITADO)
                     P.push(w-1);
            }
         } while (!P.vacia());
      }
      i = (i+1) % n;
   } while (i != u);
   return Lv;
}

Lista<Grafo::vertice> Anchura(const Grafo& G, Grafo::vertice u)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   vector<visitas> marcas(n, NO_VISITADO);
   Cola<vertice> C;
   Lista<vertice> Lv;
   vertice i = u;

   do {
      if (marcas[i] == NO_VISITADO) {
         C.push(i);
         do {
            vertice v = C.frente();
            C.pop();
            if (marcas[v] == NO_VISITADO) {
               // Marcar y procesar v
               marcas[v] = VISITADO;
               Lv.insertar(v, Lv.fin());
               // Meter en la cola los adyacentes no visitados
               for (vertice w = n; w > 0; w--)
                  if (G[v][w-1] && marcas[w-1] == NO_VISITADO)
                     C.push(w-1);
            }
         } while (!C.vacia());
      }
      i = (i+1) % n;
   } while (i != u);
   return Lv;
}
