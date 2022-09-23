/*--------------------------------------------------------*/
/* grafoMA.cpp                                            */
/*                                                        */
/* Fichero de implementación de la clase Grafo (matriz de */
/* adyacencia).                                           */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* ©2016 José Fidel Argudo                                */
/*--------------------------------------------------------*/

#include "grafoMA.h"
#include <fstream>
#include <sstream>
#include <iomanip>

// Constructor desde fichero
Grafo::Grafo(const std::string& nf)
{
   char c;
   std::string cad;
   vertice v, w;
   std::ifstream fg(nf);           // apertura del fichero
   unsigned n;                     // núm. vértices

   fg >> n;
   ady = vector< vector<bool> >(n, vector<bool>(n, false));
   while (fg >> v) {
      fg >> c; // extrae ':'
      std::getline(fg, cad);
      std::istringstream ss(cad);
      while (ss >> w)
         ady[v][w] = true;
   }
   fg.close();
}

// dirigido = true, no dirigido = false
bool Grafo::esDirigido() const
{
   bool s = true;   // matriz simétrica ==> no dirigido
   const size_t n = numVert();
   vertice i = 0;
   while (s && i < n) {
      vertice j = i+1;
      while (s && j < n) {
         s = (ady[i][j] == ady[j][i]);
         ++j;
      }
      ++i;
   }
   return !s;   // no simétrica ==> dirigido
}

// Inserción de un Grafo en un flujo de salida.
std::ostream& operator <<(std::ostream& os, const Grafo& G)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   os << n << " vertices" << std::endl;
   os << "   ";
   for (vertice j = 0; j< n; j++)
      os << std::setw(3) << j;
   os << std::endl;
   for (vertice i = 0; i < n; i++) {
      os << std::setw(3) << i;
      for (vertice j = 0; j < n; j++)
         os << std::setw(3) << G[i][j];
      os << std::endl;
   }
   return os;
}
