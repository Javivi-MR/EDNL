/*--------------------------------------------------------*/
/* grafoLA.h                                              */
/*                                                        */
/* clase Grafo: Listas de adyacencia de un grafo.         */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* ©2016 José Fidel Argudo                                */
/*--------------------------------------------------------*/
/*
Tipo público:

   Grafo::vertice // un valor entre 0 y Grafo::numVert()-1

Métodos públicos:

   explicit Grafo(size_t n);
      Grafo de n vértices sin aristas.

   explicit Grafo(const std::string& nf);
      Grafo extraído desde un fichero de texto de nombre nf,
      que contiene el número de vértices seguido en cada línea
      de un vértice, el carácter ':' y la lista de sus adyacentes
      separados por espacios.
      Ejemplo:
      5
      0: 1 2 3
      1: 4
      2: 1 3
      3: 4
      4: 2

   size_t numVert() const;
      Número de vértices

   const Lista<vertice>& adyacentes(vertice v) const;
   Lista<vertice>& adyacentes(vertice v);
      Vértices adyacentes a v.

Sobrecarga de operador externo:

   std::ostream& operator <<(std::ostream& os, const Grafo& G);
      Inserción de un Grafo en un flujo de salida.

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
   std::vector< Lista<vertice> > ady; // vector de listas de vértices
};

// Inserción de un grafo en un flujo de salida.
std::ostream& operator <<(std::ostream& os, const Grafo& G);

#endif   // GRAFO_LIS_ADY_H
