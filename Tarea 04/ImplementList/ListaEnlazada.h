#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
#include "Nodo.h"

template <typename T>
class ListaEnlazada
{
private:
    Nodo<T> *cabeza;

public:
    ListaEnlazada() : cabeza(nullptr) {}
    ~ListaEnlazada();

    void agregar(const T &value);
    void mostrar() const;

    Nodo<T> *getCabeza() const { return cabeza; }
};

#endif // LISTA_ENLAZADA_H
