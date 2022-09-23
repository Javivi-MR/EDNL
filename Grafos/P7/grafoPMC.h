/*--------------------------------------------------------*/
/* grafoPMC.h                                             */
/*                                                        */
/* clase GrafoP<T>: Matriz de costes de un grafo.         */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* �2016 Jos� Fidel Argudo                                */
/*--------------------------------------------------------*/
/*
Tipos p�blicos:

   GrafoP<T>::tCoste      // tipo de los pesos de las aristas
   GrafoP<T>::vertice // valores entre 0 y Grafo::numVert()-1
   GrafoP<T>::arista          // arista de un grafo ponderado
      Miembros p�blicos:
         vertice orig, dest;   // extremos de la arista
         tCoste coste;         // coste de la arista
         // Constructor
         explicit arista(vertice v = vertice(),
                         vertice w = vertice(),
                         tCoste c = tCoste());
         // Orden de aristas para Prim y Kruskall
         bool operator <(const arista& a) const;
   GrafoP<T>::tCamino // secuencia de v�rtices que forman un camino

Atributo p�blico:

   static const tCoste GrafoP<T>::INFINITO = std::numeric_limits<T>::max();
      M�ximo del rango de valores de tCoste. Peso de una arista inexistente.

M�todos p�blicos:

   explicit GrafoP(size_t n);
      Grafo ponderado de n v�rtices sin aristas.

   explicit GrafoP(const std::string& nf);
      Grafo ponderado extra�do desde un fichero de texto de
      nombre nf, que contiene el n�mero de v�rtices seguido de
      los pesos de las aristas en forma de matriz de costes.
      Ejemplo: tCoste = unsignded int, INFINITO = 4294967295
      5
      4294967295         60         10        100 4294967295
      4294967295 4294967295 4294967295 4294967295          5
      4294967295         40 4294967295         30 4294967295
      4294967295 4294967295 4294967295 4294967295         20
      4294967295 4294967295          5 4294967295 4294967295

   GrafoP(const Grafo& G);
      Constructor de conversi�n. Construye un GrafoP<T> a partir
      de uno no ponderado representado mediante matriz de adyacencia,
      es decir, cambiando la representaci�n a matriz de costes con
      aristas de coste 1.

   size_t numVert() const;
      N�mero de v�rtices

   const vector<tCoste>& operator [](vertice v) const;
   vector<tCoste>& operator [](vertice v);
      Pesos de las aristas adyacentes al v�rtice v.
      Fila v de la matriz de costes.

   bool esDirigido() const;
      Indica si un grafo ponderado es dirigido (true) o no (false).

Sobrecarga de operador externo:

   template <typename T>
   std::ostream& operator <<(std::ostream& os, const GrafoP<T>& G);
      Inserci�n de un grafo ponderado en un flujo de salida.

----------------------------------------------------------*/

#ifndef GRAFO_PON_H
#define GRAFO_PON_H
#include <vector>
#include <limits>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "listaenla.h" // requerido por GrafoP<T>::tCamino
#include "grafoMA.h"   // requerido por GrafoP<T>::GrafoP(const Grafo&)

using std::vector;

template <typename T> class GrafoP {
public:
   typedef T tCoste;
   typedef size_t vertice;
   struct arista {
      vertice orig, dest;
      tCoste coste;
      explicit arista(vertice v = vertice(), vertice w = vertice(),
                      tCoste c = tCoste()): orig(v), dest(w), coste(c) {}
      bool operator <(const arista& a) const {return coste < a.coste;}
   };
   typedef Lista<vertice> tCamino;

   static const tCoste INFINITO;

   explicit GrafoP(size_t n): costes(n, vector<tCoste>(n, INFINITO)) {}
   explicit GrafoP(const std::string& nf);
   GrafoP(const Grafo& G);
   size_t numVert() const {return costes.size();}
   const vector<tCoste>& operator [](vertice v) const {return costes[v];}
   vector<tCoste>& operator [](vertice v) {return costes[v];}
   bool esDirigido() const;
private:
   vector< vector<tCoste> > costes;
};

// Definici�n de INFINITO
template <typename T>
const T GrafoP<T>::INFINITO = std::numeric_limits<T>::max();

// Constructor desde fichero
template <typename T>
GrafoP<T>::GrafoP(const std::string& nf)
{
   std::ifstream fg(nf);           // apertura del fichero
   unsigned n;                     // n�m. v�rtices
   fg >> n;
   costes = vector<vector<T> >(n, vector<T>(n));
   for (vertice i = 0; i < n; i++)
      for (vertice j = 0; j < n; j++)
         fg >> costes[i][j];
   fg.close();                     // cierre del fichero
}

// Construye un GrafoP<T> a partir de uno no ponderado representado
// mediante matriz de adyacencia, es decir, cambiando la representaci�n
// a matriz de costes con aristas de coste 1.
template <typename T>
GrafoP<T>::GrafoP(const Grafo& G):
   costes(G.numVert(), vector<T>(G.numVert()))
{
   const size_t n = G.numVert();
   for (vertice i = 0; i < n; i++)
      for (vertice j = 0; j < n; j++)
         costes[i][j] = G[i][j] ? 1 : GrafoP<T>::INFINITO;
}

// dirigido = true, no dirigido = false
template <typename T>
bool GrafoP<T>::esDirigido() const
{
   bool s = true;   // matriz sim�trica ==> no dirigido
   const size_t n = numVert();
   vertice i = 0;
   while (s && i < n) {
      vertice j = i+1;
      while (s && j < n) {
         s = (costes[i][j] == costes[j][i]);
         ++j;
      }
      ++i;
   }
   return !s;   // no sim�trica ==> dirigido
}

// Inserci�n de un grafo ponderado en un flujo de salida.
template <typename T>
std::ostream& operator <<(std::ostream& os, const GrafoP<T>& G)
{
   typedef typename GrafoP<T>::vertice vertice;
   const size_t n = G.numVert();
   os << n << " vertices" << std::endl;
   os << "    ";
   for (vertice j = 0; j < n; j++)
      os << std::setw(4) << j;
   os << std::endl;
   for (vertice i = 0; i < n; i++) {
      os << std::setw(4) << i;
      for (vertice j = 0; j < n; j++) {
         os << std::setw(4);
         if (G[i][j] == GrafoP<T>::INFINITO)
            os << "-";
         else
            os << G[i][j];
      }
      os << std::endl;
   }
   return os;
}

#endif   // GRAFO_PON_H
