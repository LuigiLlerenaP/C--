#ifndef NODO_H
#define NODO_H

#include <iostream>

template <typename T>
class Nodo
{
public:
    T dato;
    Nodo<T> *siguiente;
    Nodo<T> *subLista;

    Nodo(const T &valor)
        : dato(valor), siguiente(nullptr), subLista(nullptr) {}

    ~Nodo() = default;

    static void agregarElemento(Nodo<T> *&cabeza, const T &valor);
    static void agregarASubLista(Nodo<T> *&subLista, const T &valor);
    void mostrarElementos() const;
};

template <typename T>
void Nodo<T>::agregarElemento(Nodo<T> *&cabeza, const T &valor)
{
    Nodo<T> *nuevo = new Nodo<T>(valor);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

template <typename T>
void Nodo<T>::agregarASubLista(Nodo<T> *&subLista, const T &valor)
{
    Nodo<T> *nuevo = new Nodo<T>(valor);
    nuevo->siguiente = subLista;
    subLista = nuevo;
}

template <typename T>
void Nodo<T>::mostrarElementos() const
{
    const Nodo<T> *actual = this;

    while (actual)
    {
        std::cout << "Nodo: " << actual->dato << " -> SubLista: ";
        Nodo<T> *sub = actual->subLista;
        while (sub)
        {
            std::cout << sub->dato << " ";
            sub = sub->siguiente;
        }
        std::cout << std::endl;
        actual = actual->siguiente;
    }
    std::cout << std::endl;
}

#endif
