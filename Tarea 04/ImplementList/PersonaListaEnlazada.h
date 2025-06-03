#ifndef PERSONA_LISTA_ENLAZADA_H
#define PERSONA_LISTA_ENLAZADA_H

#include "ListaEnlazada.h"
#include "../Persona/Persona.h"

class PersonaListaEnlazada
{
private:
    ListaEnlazada<Persona> lista;

public:
    PersonaListaEnlazada() = default;

    void agregarPersona(const Persona &persona);

    void mostrarPersonas() const;

    float pesoPromedio() const;

    float tallaPromedio() const;

    float edadMadrePromedio() const;
};

#endif // PERSONA_LISTA_ENLAZADA_H
