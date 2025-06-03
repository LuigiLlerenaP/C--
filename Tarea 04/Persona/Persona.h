#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using std::string;

class Persona
{
private:
    static int counter;
    int id;
    string identificacion;
    string lugarNacimiento;
    float peso;
    float altura;
    string sexo;
    int edadMadre;

public:
    Persona(const string &identificacion, const string &lugarNacimiento,
            float peso, float altura, const string &sexo, int edadMadre);

    ~Persona();

    // Getters
    int getId() const;
    string getIdentificacion() const;
    string getLugarNacimiento() const;
    float getPeso() const;
    float getAltura() const;
    string getSexo() const;
    int getEdadMadre() const;

    // Setters
    void setIdentificacion(const string &identificacion);
    void setLugarNacimiento(const string &lugarNacimiento);
    void setPeso(float peso);
    void setAltura(float altura);
    void setSexo(const string &sexo);
    void setEdadMadre(int edadMadre);
};

#endif // PERSONA_H
