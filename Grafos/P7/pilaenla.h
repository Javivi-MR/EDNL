/*--------------------------------------------------------*/
/* pilaenla.h                                             */
/*                                                        */
/* clase Pila genérica mediante celdas enlazadas.         */
/*--------------------------------------------------------*/

#ifndef PILA_ENLA_H
#define PILA_ENLA_H
#include <cassert>

template <typename T> class Pila {
public:
   Pila();                                // Constructor
   Pila(const Pila<T>& P);                // Ctor. de copia
   Pila<T>& operator =(const Pila<T>& P); // Asignación de pilas
   bool vacia() const;
   const T& tope() const;
   void pop();
   void push(const T& x);
   ~Pila();                               // Destructor
private:
   struct nodo {
      T elto;
      nodo* sig;
      nodo(const T& e, nodo* p = nullptr): elto(e), sig(p) {}
   };

   nodo* tope_;

   void copiar(const Pila<T>& P);
};

/*--------------------------------------------------------*/
/* clase Pila genérica mediante celdas enlazadas.         */
/*                                                        */
/* Implementación de operaciones                          */
/*--------------------------------------------------------*/

// Método privado
template <typename T>
void Pila<T>::copiar(const Pila<T>& P)
{
   if (!P.vacia()) {
      tope_ = new nodo(P.tope()); // Copiar el primer elto
      // Copiar el resto de elementos hasta el fondo de la pila.
      nodo* p = tope_;         // Recorre la pila destino
      nodo* q = P.tope_->sig;  // 2º nodo, recorre la pila origen
      while (q) {
         p->sig = new nodo(q->elto);
         p = p->sig;
         q = q->sig;
      }
   }
}

template <typename T>
inline Pila<T>::Pila() : tope_(nullptr) {}

template <typename T>
Pila<T>::Pila(const Pila<T>& P) : tope_(nullptr)
{
   copiar(P);
}

template <typename T>
Pila<T>& Pila<T>::operator =(const Pila<T>& P)
{
   if (this != &P) {   // Evitar autoasignación
      this->~Pila();   // Vaciar la pila actual
      copiar(P);
   }
   return *this;
}

template <typename T>
inline bool Pila<T>::vacia() const
{ return (tope_ == nullptr); }

template <typename T>
inline const T& Pila<T>::tope() const
{
   assert(!vacia());
   return tope_->elto;
}

template <typename T>
inline void Pila<T>::pop()
{
   assert(!vacia());
   nodo* p = tope_;
   tope_ = p->sig;
   delete p;
}

template <typename T>
inline void Pila<T>::push(const T& x)
{
   tope_ = new nodo(x, tope_);
}

// Destructor: vací­a la pila
template <typename T>
Pila<T>::~Pila()
{
   nodo* p;
   while (tope_) {
      p = tope_->sig;
      delete tope_;
      tope_ = p;
   }
}

#endif // PILA_ENLA_H
