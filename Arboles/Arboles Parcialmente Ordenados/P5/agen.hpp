#ifndef AGEN_HPP_
#define AGEN_HPP_
#include <cassert>

template <typename T>
class Agen
{
    struct celda;
public:
    typedef celda *nodo;
    static const nodo NODO_NULO;
    Agen(); // constructor
    void insertarRaiz(const T &e);
    void insertarHijoIzqdo(nodo n, const T &e);
    void insertarHermDrcho(nodo n, const T &e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHermDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    const T &elemento(nodo n) const; // acceso a elto, lectura
    T &elemento(nodo n);             // acceso a elto, lectura/escritura
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hermDrcho(nodo n) const;
    Agen(const Agen<T> &a); // ctor. de copia
    Agen<T> &operator=(const Agen<T> &a);
    ~Agen(); // destructor
    unsigned altura(nodo n) const;
private:
    struct celda
    {
        T elto;
        nodo padre, hizq, heder;
        celda(const T &e, nodo p = NODO_NULO) : elto(e), padre(p), hizq(NODO_NULO), heder(NODO_NULO) {}
    };
    nodo r;
    void destruirNodos(nodo &n);
    nodo copiar(nodo n);
};

template <typename T>
unsigned Agen<T>::altura(nodo n) const
{
    typename Agen<T>::nodo hijo = this->hijoIzqdo(n);
    int max = 0, alt;
    if (hijo != Agen<T>::NODO_NULO)
    {
        max = 1 + altura(hijo);
        hijo = this->hermDrcho(hijo);
        while (hijo != Agen<T>::NODO_NULO)
        {
            alt = 1 + altura(hijo);
            if (max < alt)
                max = alt;

            hijo = this->hermDrcho(hijo);
        }
    }
    return max;
}
/* Definición del nodo nulo */
template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(nullptr);

template <typename T>
inline Agen<T>::Agen() : r(NODO_NULO) {}

template <typename T>
inline void Agen<T>::insertarRaiz(const T &e)
{
    assert(r == NODO_NULO); // árbol vacío
    r = new celda(e);
}

template <typename T>
inline void Agen<T>::insertarHijoIzqdo(Agen<T>::nodo n, const T &e)
{
    assert(n != NODO_NULO);
    nodo hizqdo = n->hizq; // hijo izqdo actual
    n->hizq = new celda(e, n);
    n->hizq->heder = hizqdo; // El actual hijo izqdo. se convierte en
    // hermano drcho. del nuevo hijo
}
template <typename T>
inline void Agen<T>::insertarHermDrcho(Agen<T>::nodo n, const T &e)
{
    assert(n != NODO_NULO);
    assert(n != r); // n no es la raíz
    nodo hedrcho = n->heder;
    n->heder = new celda(e, n->padre);
    n->heder->heder = hedrcho; // El actual hermano drcho. se convierte
    // en hermano drcho. del nuevo
}

template <typename T>
inline void Agen<T>::eliminarHijoIzqdo(Agen<T>::nodo n)
{
    nodo hizqdo;
    assert(n != NODO_NULO);
    hizqdo = n->hizq;
    assert(hizqdo != NODO_NULO);       // existe hijo izqdo.
    assert(hizqdo->hizq == NODO_NULO); // hijo izqdo. es hoja
    // el hermano drcho. pasa a ser el nuevo hijo izqdo.
    n->hizq = hizqdo->heder;
    delete (hizqdo);
}

template <typename T>
inline void Agen<T>::eliminarHermDrcho(Agen<T>::nodo n)
{
    nodo hedrcho;
    assert(n != NODO_NULO);
    hedrcho = n->heder;
    assert(hedrcho != NODO_NULO);       // existe hermano drcho.
    assert(hedrcho->hizq == NODO_NULO); // hermano drcho. es hoja
    // el hermano del hermano se convierte en el
    // nuevo hermano drcho. de n
    n->heder = hedrcho->heder;
    delete (hedrcho);
}

template <typename T>
inline void Agen<T>::eliminarRaiz()
{
    assert(r != NODO_NULO);       // árbol no vacío
    assert(r->hizq == NODO_NULO); // la raíz es hoja
    delete (r);
    r = NODO_NULO;
}

template <typename T>
inline bool Agen<T>::arbolVacio() const
{
    return (r == NODO_NULO);
}

template <typename T>
inline const T &Agen<T>::elemento(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline T &Agen<T>::elemento(Agen<T>::nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::raiz() const
{
    return r;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::padre(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::hijoIzqdo(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::hermDrcho(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->heder;
}

template <typename T>
Agen<T>::Agen(const Agen<T> &a)
{
    r = copiar(a.r);
}

template <typename T>
Agen<T> &Agen<T>::operator=(const Agen<T> &a)
{
    if (this != &a)
    {                  // evitar autoasignación
        this->~Agen(); // vaciar el árbol
        r = copiar(a.r);
    }
    return *this;
}

template <typename T>
inline Agen<T>::~Agen()
{
    destruirNodos(r); // vacía el árbol
}

// Métodos privados
// Destruye un nodo y todos sus descendientes
template <typename T>
void Agen<T>::destruirNodos(Agen<T>::nodo &n)
{
    if (n != NODO_NULO)
    {
        if (n->hizq != NODO_NULO)
        { // destruir hermanos del hijo izqdo.
            nodo hedrcho = n->hizq->heder;
            while (hedrcho != NODO_NULO)
            {
                n->hizq->heder = hedrcho->heder;
                destruirNodos(hedrcho);
                hedrcho = n->hizq->heder;
            }
            destruirNodos(n->hizq); // destruir el hijo izqdo.
        }
        delete (n);
        n = NODO_NULO;
    }
}

// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Agen<T>::nodo Agen<T>::copiar(Agen<T>::nodo n)
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO)
    {
        m = new celda(n->elto);   // copiar n
        if (n->hizq != NODO_NULO) // n tiene descendientes
        {
            m->hizq = copiar(n->hizq); // copiar primer subárbol
            m->hizq->padre = m;
            // copiar el resto de subárboles
            nodo hijo = m->hizq;           // último subárbol copiado
            nodo hedrcho = n->hizq->heder; // siguiente subárbol a copiar
            while (hedrcho != NODO_NULO)
            {
                hijo = hijo->heder = copiar(hedrcho);
                hijo->padre = m;
                hedrcho = hedrcho->heder;
            }
        }
    }
    return m;
}
#endif // AGEN_HPP