#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
#include "ListaEnlazada.h"

template <typename T>

class ListaEnlazada
{
private:
    Nodo<T> *cabeza;

public:
    ListaEnlazada() : cabeza(nullptr) {}

    ~ListaEnlazada()
    {
        Nodo<T> *actual = cabeza;
        while (actual != nullptr)
        {
            Nodo<T> *temp = actual;
            actual = actual->next;
            delete temp;
        }
    }

    void agregar(const T &value)
    {
        Nodo<T> *nuevo = new Nodo<T>(value);
        if (cabeza == nullptr)
        {
            cabeza = nuevo;
        }
        else
        {
            Nodo<T> *actual = cabeza;
            while (actual->next != nullptr)
            {
                actual = actual->next;
            }
            actual->next = nuevo;
        }
    }

    void mostrar() const
    {
        Nodo<T> *actual = cabeza;
        while (actual != nullptr)
        {
            actual->data.mostrar();
            actual = actual->next;
        }
        std::cout << "nullptr\n";
    }

    Nodo<T> *getCabeza() const { return cabeza; }
};

#endif // LISTA_ENLAZADA_H