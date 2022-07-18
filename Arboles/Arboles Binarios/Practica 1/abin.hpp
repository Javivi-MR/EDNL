#ifndef ABIN_HPP
#define ABIN_HPP
#include <cassert>
#include <cmath>

template <typename T>
class Abin
{
    struct celda;
public:
    typedef celda* nodo;
    static const nodo NODO_NULO;
    Abin();
    void insertarRaiz(const T& e);
    void insertarHijoIzqdo(nodo n, const T& e);
    void insertarHijoDrcho(nodo n, const T& e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool arbolVacio() const;
    const T& elemento(nodo n) const; //solo lectura
    T& elemento(nodo n); //lectura/escritura
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    Abin(const Abin<T>& a); //constructor de copia
    Abin<T>& operator =(const Abin<T>& A); //asignacion
    int profundidad(nodo n);
    int altura(nodo n);
    ~Abin(); //destructor
private:
    struct celda
    {
        T elto;
        nodo padre, hizq, hder;
        celda(const T& e, nodo p = NODO_NULO) : elto(e), padre(p), hizq(NODO_NULO), hder(NODO_NULO) {}
    };
    nodo r; //nodo raiz
    void destruirNodos(nodo& n);
    nodo copiar(nodo n);
};

//definimos nodo nulo
template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(nullptr);


template <typename T>
Abin<T>::Abin() : r(NODO_NULO) {}


template <typename T>
inline void Abin<T>::insertarRaiz(const T& e)
{
    assert(r == NODO_NULO); //arbol vacio
    r = new celda(e);
}


template <typename T>
inline void Abin<T>::insertarHijoIzqdo(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hizq == NODO_NULO);
    n->hizq = new celda(e, n);
}


template <typename T>
inline void Abin<T>::insertarHijoDrcho(nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n->hder == NODO_NULO);
    n->hder = new celda(e, n);
}


template <typename T>
inline void Abin<T>::eliminarHijoIzqdo(nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hizq != NODO_NULO); //existe hijo izq
    assert(n->hizq->hizq == NODO_NULO && n->hizq->hder == NODO_NULO); //hijo izq es hoja 
    delete n->hizq;
    n->hizq = NODO_NULO;
}


template <typename T>
inline void Abin<T>::eliminarHijoDrcho(nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hder != NODO_NULO); //existe hijo der
    assert(n->hder->hizq == NODO_NULO && n->hder->hder == NODO_NULO); //hijo der es hoja 
    delete n->hder;
    n->hder = NODO_NULO;
}


template <typename T>
inline void Abin<T>::eliminarRaiz()
{
	assert(r != NODO_NULO); // árbol no vacío
	assert(r->hizq == NODO_NULO &&
		   r->hder == NODO_NULO); // la raíz es hoja
	
	delete(r);
	r = NODO_NULO;
}


template <typename T> 
inline Abin<T>::~Abin() { destruirNodos(r); }


template <typename T> inline bool Abin<T>::arbolVacio() const{ return (r == NODO_NULO); }


template <typename T>
inline const T& Abin<T>::elemento(Abin<T>::nodo n) const
{
	assert(n != NODO_NULO);
	return n->elto;
}


template <typename T>
inline T& Abin<T>::elemento(Abin<T>::nodo n)
{
	assert(n != NODO_NULO);
	return n->elto;
}


template <typename T>
inline typename Abin<T>::nodo Abin<T>::raiz() const
{
	return r;
}


template <typename T> inline
typename Abin<T>::nodo Abin<T>::padre(Abin<T>::nodo n) const
{
	assert(n != NODO_NULO);
	return n->padre;
}


template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoIzqdo(Abin<T>::nodo n) const
{
	assert(n != NODO_NULO);
	return n->hizq;
}


template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoDrcho(Abin<T>::nodo n) const
{
	assert(n != NODO_NULO);
	return n->hder;
}


template <typename T>
inline Abin<T>::Abin(const Abin<T>& a)
{
	r = copiar(a.r);
}


template <typename T>
Abin<T>& Abin<T>::operator =(const Abin<T>& a)
{
	if (this != &a) // evitar autoasignación
	{
		this->~Abin();// vaciar el árbol
		r = copiar(a.r);
	}
	return *this;
}

// Métodos privados
// Destruye un nodo y todos sus descendientes
template <typename T>
void Abin<T>::destruirNodos(Abin<T>::nodo& n)
{
	if (n != NODO_NULO)
	{
		destruirNodos(n->hizq);
		destruirNodos(n->hder);
		delete n;
		n = NODO_NULO;
	}
}

template <typename T>
int Abin<T>::altura(typename Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
        return -1;
    else 
        return 1 + std::fmax(altura(n -> hizq), altura(n -> hder));

}


template <typename T>
int Abin<T>::profundidad(typename Abin<T>::nodo n)
{
    int profundidad = 0;

    while (n != r)
    {
        profundidad++;
        n = n -> padre;
    }

    return profundidad;
}


// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Abin<T>::nodo Abin<T>::copiar(Abin<T>::nodo n)
{

	nodo m = NODO_NULO;
	if (n != NODO_NULO)
    {
		m = new celda(n->elto);  // copiar n
		m->hizq = copiar(n->hizq); // copiar subárbol izqdo.
		if (m->hizq != NODO_NULO) m->hizq->padre = m;

		m->hder = copiar(n->hder); // copiar subárbol drcho.

		if (m->hder != NODO_NULO) m->hder->padre = m;
	}
	return m;
}

#endif //ABIN_HPP