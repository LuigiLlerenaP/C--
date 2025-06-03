#include "./Persona.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

class PersonaNacida
{
private:
    std::vector<Persona> personasNacidas{};
    float promedioPesoNacido{0};
    float promedioAlturaNacido{0};
    int cantidadNacidos{0};
    int cantidadNacidosMujeres{0};
    int cantidadNacidosHombres{0};

public:
    PersonaNacida()
        : personasNacidas{} {} // Constructor por defecto

    ~PersonaNacida() = default;

    // Getters
    std::vector<Persona> getPersonasNacidas() const { return personasNacidas; }
    float getPromedioPesoNacido() const { return promedioPesoNacido; }
    float getPromedioAlturaNacido() const { return promedioAlturaNacido; }
    int getCantidadNacidos() const { return cantidadNacidos; }
    int getCantidadNacidosMujeres() const { return cantidadNacidosMujeres; }
    int getCantidadNacidosHombres() const { return cantidadNacidosHombres; }

    // Setters
    void setPersonaNacida(const Persona &persona) { personasNacidas.push_back(persona); }
    void setPromedioPesoNacido(float p) { promedioPesoNacido = p; }
    void setPromedioAlturaNacido(float a) { promedioAlturaNacido = a; }
    void setCantidadNacidos(int c) { cantidadNacidos = c; }
    void setCantidadNacidosMujeres(int c) { cantidadNacidosMujeres = c; }
    void setCantidadNacidosHombres(int c) { cantidadNacidosHombres = c; }

    // Métodos adicionales
    void printPersonasNacidas() const
    {
        for (const auto &persona : personasNacidas)
        {
            std::cout << "ID: " << persona.getId()
                      << ", Identificacion: " << persona.getIdentificacion()
                      << ", Lugar Nacimiento: " << persona.getLugarNacimiento()
                      << ", Peso: " << persona.getPeso()
                      << ", Altura: " << persona.getAltura()
                      << ", Sexo: " << persona.getSexo()
                      << ", Edad: " << persona.getEdad() << std::endl;
        }
    }

    void personaNacida(int id) const
    {
        if (id < 0 || id >= personasNacidas.size())
        {
            throw std::out_of_range("ID fuera de rango.");
        }

        for (int i = 0; i < personasNacidas.size(); i++)
        {
            if (personasNacidas[i].getId() != id)
            {
                continue; // Si no coincide, continuar
            }
            std::cout << "ID: " << personasNacidas[i].getId()
                      << ", Identificacion: " << personasNacidas[i].getIdentificacion()
                      << ", Lugar Nacimiento: " << personasNacidas[i].getLugarNacimiento()
                      << ", Peso: " << personasNacidas[i].getPeso()
                      << ", Altura: " << personasNacidas[i].getAltura()
                      << ", Sexo: " << personasNacidas[i].getSexo()
                      << ", Edad: " << personasNacidas[i].getEdad() << std::endl;
        }
    }

    void calcularPromedios()
    {
        if (personasNacidas.empty())
        {
            throw std::invalid_argument("No hay personas nacidas para calcular promedios.");
        }

        float totalPeso = 0;
        float totalAltura = 0;
        cantidadNacidosMujeres = 0;
        cantidadNacidosHombres = 0;

        for (const auto &persona : personasNacidas)
        {
            totalPeso += persona.getPeso();
            totalAltura += persona.getAltura();

            if (persona.getSexo() == "F")
                cantidadNacidosMujeres++;
            else if (persona.getSexo() == "M")
                cantidadNacidosHombres++;
        }

        promedioPesoNacido = totalPeso / personasNacidas.size();
        promedioAlturaNacido = totalAltura / personasNacidas.size();
    }
};
