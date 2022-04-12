int contar3nietos (Abin <T>& A)
{
    return contar3nietosREC(A,A.raiz());
}

int contar3nietosREC (Abin <T>& A,Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else
        if(A.hijoizqdo((A.hijoizqdo(n) != Abin<T>::NODO_NULO && A.hijodrcho(A.hijoizqdo(n) != Abin<T>::NODO_NULO && A.hijoizqdo(A.hijodrcho(n) != Abin<T>::NODO_NULO && A.hijodrcho(A.hijodrcho(n) == Abin<T>::NODO_NULO) ||
        (A.hijoizqdo(n) != Abin<T>::NODO_NULO && A.hijodrcho(A.hijoizqdo(n) != Abin<T>::NODO_NULO && A.hijoizqdo(A.hijodrcho(n) == Abin<T>::NODO_NULO && A.hijodrcho(A.hijodrcho(n) != Abin<T>::NODO_NULO) ||
        (A.hijoizqdo(n) != Abin<T>::NODO_NULO && A.hijodrcho(A.hijoizqdo(n) == Abin<T>::NODO_NULO && A.hijoizqdo(A.hijodrcho(n) != Abin<T>::NODO_NULO && A.hijodrcho(A.hijodrcho(n) != Abin<T>::NODO_NULO) ||
        (A.hijoizqdo(n) == Abin<T>::NODO_NULO && A.hijodrcho(A.hijoizqdo(n) != Abin<T>::NODO_NULO && A.hijoizqdo(A.hijodrcho(n) != Abin<T>::NODO_NULO && A.hijodrcho(A.hijodrcho(n) != Abin<T>::NODO_NULO))
            return 1 + contar3nietosREC(A,A.hijoizqdo(n)) + contar3nietosREC(A,A.hijodrcho(n));
        else
            return contar3nietosREC(A,A.hijoizqdo(n)) + contar3nietosREC(A,A.hijodrcho(n));
}
