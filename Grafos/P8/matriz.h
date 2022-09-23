#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>

using std::vector;

// matriz cuadrada
template <typename T> class matriz {
public:
   matriz() {}
   explicit matriz(size_t n, const T& x = T()): m(n, vector<T>(n, x)) {}
   size_t dimension() const {return m.size();}
   const vector<T>& operator [](size_t i) const {return m[i];}
   vector<T>& operator [](size_t i) {return m[i];}
private:
   vector< vector<T> > m;
};

#endif  // MATRIZ_H
