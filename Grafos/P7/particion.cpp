/*--------------------------------------------------------*/
/* particion.cpp                                          */
/*                                                        */
/* Implementación de la clase Particion:                  */
/* Bosque de árboles con unión por altura y búsqueda con  */
/* compresión de caminos.                                 */
/*--------------------------------------------------------*/

#include "particion.h"

// El árbol con mayor altura se convierte en subárbol del otro.
void Particion::unir(int a, int b)
{
   if (padre[b] < padre[a])
      padre[a] = b;
   else {
      if (padre[a] == padre[b])
         padre[a]--; // El árbol resultante tiene un nivel más.
      padre[b] = a;
   }
}

int Particion::encontrar(int x) const
{
   int y, raiz = x;

   while (padre[raiz] > -1)
      raiz = padre[raiz];
   // Compresión del camino de x a raíz: Los nodos
   // del camino se hacen hijos de la raíz
   while (padre[x] > -1) {
      y = padre[x];
      padre[x] = raiz;
      x = y;
   }
   return raiz;
}
