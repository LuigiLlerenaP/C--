#ifndef NODO_H
#define NODO_H

template <typename T>
struct Nodo
{
    T data;
    Nodo<T> *next;
    Nodo(const T &value) : data(value), next(nullptr) {}
};

#endif // NODO_H