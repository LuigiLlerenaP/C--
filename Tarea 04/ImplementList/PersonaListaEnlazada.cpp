#include "PersonaListaEnlazada.h"
#include "../Persona/Persona.h"
#include <iostream>

void PersonaListaEnlazada::agregarPersona(const Persona &persona)
{
    lista.agregar(persona);
}

// Muestra todas las personas de la lista
void PersonaListaEnlazada::mostrarPersonas() const
{
    lista.mostrar();
}

// Calcula el peso promedio de todas las personas en la lista
float PersonaListaEnlazada::pesoPromedio() const
{
    Nodo<Persona> *actual = lista.getCabeza();
    if (!actual)
        return 0.0f;

    int count = 0;
    float sumaPeso = 0.0f;

    while (actual != nullptr)
    {
        sumaPeso += actual->data.getPeso();
        count++;
        actual = actual->next;
    }

    return (count > 0) ? (sumaPeso / count) : 0.0f;
}

// Calcula la talla promedio de todas las personas en la lista
float PersonaListaEnlazada::tallaPromedio() const
{
    Nodo<Persona> *actual = lista.getCabeza();
    if (!actual)
        return 0.0f;

    int count = 0;
    float sumaAltura = 0.0f;

    while (actual != nullptr)
    {
        sumaAltura += actual->data.getAltura();
        count++;
        actual = actual->next;
    }

    return (count > 0) ? (sumaAltura / count) : 0.0f;
}

// Calcula el promedio de edad de la madre de todas las personas en la lista
float PersonaListaEnlazada::edadMadrePromedio() const
{
    Nodo<Persona> *actual = lista.getCabeza();
    if (!actual)
        return 0.0f;

    int count = 0;
    float sumaEdadMadre = 0.0f;

    while (actual != nullptr)
    {
        sumaEdadMadre += actual->data.getEdadMadre();
        count++;
        actual = actual->next;
    }

    return (count > 0) ? (sumaEdadMadre / count) : 0.0f;
}