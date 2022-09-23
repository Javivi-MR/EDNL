/*--------------------------------------------------------*/
/* grafoLA.h                                              */
/*                                                        */
/* clase Grafo: Listas de adyacencia de un grafo.         */
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

   size_t numVert() const;
      N�mero de v�rtices

   const Lista<vertice>& adyacentes(vertice v) const;
   Lista<vertice>& adyacentes(vertice v);
      V�rtices adyacentes a v.

Sobrecarga de operador externo:

   std::ostream& operator <<(std::ostream& os, const Grafo& G);
      Inserci�n de un Grafo en un flujo de salida.

----------------------------------------------------------*/

#ifndef GRAFO_LIS_ADY_H
#define GRAFO_LIS_ADY_H
#include <vector>
#include <iostream>
#include <string>
#include "listaenla.h"

class Grafo {
public:
   typedef size_t vertice;

   explicit Grafo(size_t n): ady(n) {}
   explicit Grafo(const std::string& nf);
   size_t numVert() const {return ady.size();}
   const Lista<vertice>& adyacentes(vertice v) const {return ady[v];}
   Lista<vertice>& adyacentes(vertice v) {return ady[v];}
private:
   std::vector< Lista<vertice> > ady; // vector de listas de v�rtices
};

// Inserci�n de un grafo en un flujo de salida.
std::ostream& operator <<(std::ostream& os, const Grafo& G);

#endif   // GRAFO_LIS_ADY_H
