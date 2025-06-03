#ifndef PERSONANACIDA_H
#define PERSONANACIDA_H

#include "./Persona.h"
#include <vector>
#include <string>

class PersonaNacida
{
private:
    std::vector<Persona> personasNacidas;
    float promedioPesoNacido;
    float promedioAlturaNacido;
    int cantidadNacidos;
    int cantidadNacidosMujeres;
    int cantidadNacidosHombres;

public:
    // Constructor
    PersonaNacida();

    // Destructor
    ~PersonaNacida();

    // Getters
    std::vector<Persona> getPersonasNacidas() const;
    float getPromedioPesoNacido() const;
    float getPromedioAlturaNacido() const;
    int getCantidadNacidos() const;
    int getCantidadNacidosMujeres() const;
    int getCantidadNacidosHombres() const;

    // Setters
    void setPersonaNacida(const Persona &persona);
    void setPromedioPesoNacido(float promedioPesoNacido);
    void setPromedioAlturaNacido(float promedioAlturaNacido);
    void setCantidadNacidos(int cantidadNacidos);
    void setCantidadNacidosMujeres(int cantidadNacidosMujeres);
    void setCantidadNacidosHombres(int cantidadNacidosHombres);

    // Métodos adicionales
    void printPersonasNacidas() const;
    void calcularPromedios();
    void personaNacida() const;
};

#endif
