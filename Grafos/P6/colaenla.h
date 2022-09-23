/*--------------------------------------------------------*/
/* colaenla.h                                             */
/*                                                        */
/* clase Cola genérica mediante celdas enlazadas.         */
/*--------------------------------------------------------*/

#ifndef COLA_ENLA_H
#define COLA_ENLA_H
#include <cassert>

template <typename T> class Cola {
public:
   Cola();                                // Constructor
   Cola(const Cola<T>& C);                // Ctor. de copia
   Cola<T>& operator =(const Cola<T>& C); // Asignación de colas
   bool vacia() const;
   const T& frente() const;
   void pop();
   void push(const T& x);
   ~Cola();                               // Destructor
private:
   struct nodo {
      T elto;
      nodo* sig;
      nodo(const T& e, nodo* p = nullptr): elto(e), sig(p) {}
   };

   nodo *inicio, *fin;   // Extremos de la cola

   void copiar(const Cola<T>& C);
};

/*--------------------------------------------------------*/
/* clase Cola genérica mediante celdas enlazadas.         */
/*                                                        */
/* Implementación de operaciones                          */
/*--------------------------------------------------------*/

// Método privado
template <typename T>
void Cola<T>::copiar(const Cola<T>& C)
{
   if (C.inicio) {   // C no está vacía
       // Copiar el primer elto.
      inicio = fin = new nodo(C.inicio->elto);
      // Copiar el resto de elementos hasta el final de la cola.
      for (nodo *p = C.inicio->sig; p; p = p->sig) {
         fin->sig = new nodo(p->elto);
         fin = fin->sig;
      }
   }
}

template <typename T>
inline Cola<T>::Cola() : inicio(nullptr), fin(nullptr) {}

template <typename T>
inline Cola<T>::Cola(const Cola<T>& C) :
   inicio(nullptr), fin(nullptr)
{
   copiar(C);
}

template <typename T>
inline Cola<T>& Cola<T>::operator =(const Cola<T>& C)
{
   if (this != &C) {   // Evitar autoasignación
      this->~Cola();   // Vaciar la cola actual
      copiar(C);
   }
   return *this;
}

template <typename T>
inline bool Cola<T>::vacia() const
{
   return (inicio == nullptr);
}

template <typename T>
inline const T& Cola<T>::frente() const
{
   assert(!vacia());
   return inicio->elto;
}

template <typename T>
inline void Cola<T>::pop()
{
   assert(!vacia());
   nodo* p = inicio;
   inicio = p->sig;
   if (!inicio) fin = nullptr;
   delete p;
}

template <typename T>
inline void Cola<T>::push(const T& x)
{
   nodo* p = new nodo(x);
   if (inicio == nullptr)   // Cola vacía
      inicio = fin = p;
   else
      fin = fin->sig = p;
}

// Destructor: vacía la cola
template <typename T>
Cola<T>::~Cola()
{
   nodo* p;
   while (inicio) {
      p = inicio->sig;
      delete inicio;
      inicio = p;
   }
   fin = nullptr;
}

#endif // COLA_ENLA_H
