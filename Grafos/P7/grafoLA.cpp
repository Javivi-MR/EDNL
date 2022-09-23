/*--------------------------------------------------------*/
/* grafoLA.cpp                                            */
/*                                                        */
/* Fichero de implementación de la clase Grafo (listas de */
/* adyacencia).                                           */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* ©2016 José Fidel Argudo                                */
/*--------------------------------------------------------*/

#include "grafoLA.h"
#include <fstream>
#include <sstream>
#include <iomanip>

Grafo::Grafo(const std::string& nf)
{
   char c;
   std::string cad;
   vertice v, w;
   std::ifstream fg(nf);           // apertura del fichero
   unsigned n;                     // núm. vértices

   fg >> n;
   ady = std::vector< Lista<vertice> >(n);
   while (fg >> v) {
      fg >> c; // extrae ':'
      std::getline(fg, cad);
      std::istringstream ss(cad);
      while (ss >> w)
         ady[v].insertar(w, ady[v].fin());
   }
   fg.close();                     // cierre del fichero
}

// Inserción de un grafo en un flujo de salida.
std::ostream& operator <<(std::ostream& os, const Grafo& G)
{
   typedef Grafo::vertice vertice;
   typedef typename Lista<Grafo::vertice>::posicion posicion;
   const size_t n = G.numVert();
   os << n << " vertices" << std::endl;
   for (vertice i = 0; i < n; i++)
      if (G.adyacentes(i).primera() != G.adyacentes(i).fin()) {
         os << i << ':';
         for (posicion p = G.adyacentes(i).primera();
              p != G.adyacentes(i).fin();
              p = G.adyacentes(i).siguiente(p))
            os << ' ' << G.adyacentes(i).elemento(p);
         os << std::endl;
      }
   return os;
}
