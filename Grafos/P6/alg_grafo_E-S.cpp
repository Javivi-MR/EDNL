/*--------------------------------------------------------*/
/* alg_grafo_E-S.cpp                                      */
/*                                                        */
/* Implementación de operadores de inserción en flujos de */
/* salida para visualizar los resultados de los           */
/* algoritmos de grafos implementados en                  */
/* alg_grafoMA.[h|cpp] y alg_grafoPMC.h                   */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* ©2016 José Fidel Argudo                                */
/*--------------------------------------------------------*/

#include "alg_grafo_E-S.h"
#include <iomanip>           // std::setw

// Inserción de matriz<bool> en un flujo de salida (para probar Warshall)
template <>
ostream& operator << <bool>(ostream& os, const matriz<bool>& m)
{
   const size_t n = m.dimension();
   os << "   ";
   for (size_t j = 0; j < n; ++j)
      os << std::setw(3) << j;
   os << std::endl;
   for (size_t i = 0; i < n; ++i) {
      os << std::setw(3) << i;
      for (size_t j = 0; j < n; ++j)
         os << std::setw(3) << m[i][j];
      os << std::endl;
   }
   return os;
}

// Inserción de Lista<size_t> en un ostream (para probar recorridos
// y caminos de Dijkstra y Floyd))
template <>
ostream& operator << <size_t>(ostream& os, const Lista<size_t>& L)
{
   typedef Lista<Grafo::vertice>::posicion posicion;
   for (posicion i = L.primera(); i != L.fin(); i = L.siguiente(i))
      os << L.elemento(i) << ' ';
   return os;
}
