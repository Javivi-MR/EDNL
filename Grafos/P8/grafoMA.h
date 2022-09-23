/*--------------------------------------------------------*/
/* grafoMA.h                                              */
/*                                                        */
/* clase Grafo: Matriz de adyacencia de un grafo.         */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* �2016 Jos� Fidel Argudo                                */
/*--------------------------------------------------------*/
/*
Tipo p�blico:

   Grafo::vertice // un valor entre 0 y Grafo::numVert()-1

M�todos p�blicos:

   explicit Grafo(size_t n);
      Grafo de n v�rtices sin aristas.

   explicit Grafo(const std::string& nf);
      Grafo extra�do desde un fichero de texto de nombre nf,
      que contiene el n�mero de v�rtices seguido en cada l�nea
      de un v�rtice, el car�cter ':' y la lista de sus adyacentes
      separados por espacios.
      Ejemplo:
      5
      0: 1 2 3
      1: 4
      2: 1 3
      3: 4
      4: 2

   template <typename T> Grafo(const GrafoP<T>& G);
      Constructor de conversi�n. Construye un Grafo a partir
      de uno ponderado representado mediante matriz de costes,
      es decir, cambiando la representaci�n a matriz de adyacencia.

   size_t numVert() const;
      N�mero de v�rtices

   const vector<bool>& operator [](vertice v) const;
   vector<bool>& operator [](vertice v);
      V�rtices adyacentes a v. Fila v de la matriz de adyacencia.

   bool esDirigido() const;
      Indica si un grafo es dirigido (true) o no (false).

Sobrecarga de operador externo:

   std::ostream& operator <<(std::ostream& os, const Grafo& G);
      Inserci�n de un Grafo en un flujo de salida.

----------------------------------------------------------*/

#ifndef GRAFO_MADY_H
#define GRAFO_MADY_H
#include <vector>
#include <ostream>
#include <string>

using std::vector;

template <typename tCoste> class GrafoP;

class Grafo {
public:
   typedef size_t vertice;

   explicit Grafo(size_t n): ady(n, vector<bool>(n, false)) {}
   explicit Grafo(const std::string& nf);
   template <typename T> Grafo(const GrafoP<T>& G);
   size_t numVert() const {return ady.size();}
   const vector<bool>& operator [](vertice v) const {return ady[v];}
   vector<bool>& operator [](vertice v) {return ady[v];}
   bool esDirigido() const;
private:
   vector< vector<bool> > ady;
};

// Construye un Grafo a partir de uno ponderado representado
// mediante matriz de costes, es decir, cambiando la representaci�n
// a matriz de adyacencia.
template <typename T> Grafo::Grafo(const GrafoP<T>& G):
   ady(G.numVert(), vector<bool>(G.numVert()))
{
   const size_t n = G.numVert();
   for (vertice i = 0; i < n; i++)
      for (vertice j = 0; j < n; j++)
         ady[i][j] = (G[i][j] != GrafoP<T>::INFINITO);
}

// Inserci�n de un Grafo en un flujo de salida.
std::ostream& operator <<(std::ostream& os, const Grafo& G);

#endif   // GRAFO_MADY_H
