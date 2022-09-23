/*--------------------------------------------------------*/
/* alg_grafo_E-S.h                                        */
/*                                                        */
/* Operadores de inserción en flujos de salida para       */
/* visualizar los resultados de los algoritmos de grafos  */
/* implementados en alg_grafoMA.[h|cpp] y alg_grafoPMC.h  */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* ©2016 José Fidel Argudo                                */
/*--------------------------------------------------------*/
/*
Sobrecarga de operadores:

   template <typename T>
   ostream& operator <<(ostream& os, const vector<T>& v);
      Inserción de vector<T> en un ostream (para probar Dijkstra).

   template <typename T>
   ostream& operator << (ostream& os, const matriz<T>& m);
      Inserción de matriz<T> en un ostream (para probar Floyd).

   template <>
   ostream& operator << <bool>(ostream& os, const matriz<bool>& m);
      Especialización para matriz<bool> del operador << para la
      clase genérica matriz<T> (para probar Warshall).

   template <>
   ostream& operator << <size_t>(ostream& os, const Lista<size_t>& L);
      Inserción de una lista de vértices (size_t) de un grafo en un
      flujo de salida (para probar recorridos y caminos de Dijkstra
      y Floyd).

----------------------------------------------------------*/

#ifndef ALG_GRAFO_E_S_H
#define ALG_GRAFO_E_S_H
#include "grafoPMC.h"  // grafo ponderado
#include <vector>
#include "matriz.h"    // matriz cuadrada
#include "listaenla.h" // para mostrar listas de vértices
#include <ostream>

using std::ostream;

// Inserción de vector<T> en un ostream (para probar Dijkstra)
template <typename T>
ostream& operator <<(ostream& os, const vector<T>& v)
{
   for (size_t i = 0; i < v.size(); i++) {
      os << std::setw(4);
      if (v[i] != GrafoP<T>::INFINITO)
         os << v[i];
      else
         os << "-";
   }
   return os;
}

// Inserta una matriz<T> en un flujo de salida (para probar Floyd)
template <typename T>
ostream& operator << (ostream& os, const matriz<T>& m)
{
   const size_t n = m.dimension();
   os << "    ";
   for (size_t j = 0; j < n; ++j)
      os << std::setw(4) << j;
   os << std::endl;
   for (size_t i = 0; i < n; ++i) {
      os << std::setw(4) << i;
      for (size_t j = 0; j < n; ++j) {
         os << std::setw(4);
         if (m[i][j] == GrafoP<T>::INFINITO)
            os << "-";
         else
            os << m[i][j];
      }
      os << std::endl;
   }
   return os;
}

// Inserción de matriz<bool> en un flujo de salida (para probar Warshall)
template <>
ostream& operator << <bool>(ostream& os, const matriz<bool>& m);

// Inserción de Lista<size_t> en un ostream (para probar recorridos
// y caminos de Dijkstra y Floyd))
template <typename T>
ostream& operator <<(ostream&, const Lista<T>&);
template <>
ostream& operator << <size_t>(ostream& os, const Lista<size_t>& c);

#endif   // ALG_GRAFO_E_S_H
