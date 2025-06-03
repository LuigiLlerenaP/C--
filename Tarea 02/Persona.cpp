#include "./Persona.h"
#include <string>
#include <stdexcept> // Para lanzar excepciones std::invalid_argument

using std::string;

int Persona::counter = 0; // Inicialización del miembro estático

// Constructor
Persona::Persona(const string &identificacion, const string &lugarNacimiento,
                 float peso, float altura, const string &sexo, int edad)
    : identificacion(identificacion), lugarNacimiento(lugarNacimiento),
      peso(peso), altura(altura), sexo(sexo), edad(edad)
{
    // Validaciones
    if (sexo != "M" && sexo != "F")
    {
        throw std::invalid_argument("Sexo debe ser 'M' o 'F'.");
    }
    if (edad < 0)
    {
        throw std::invalid_argument("Edad no puede ser negativa.");
    }
    if (peso < 0)
    {
        throw std::invalid_argument("Peso no puede ser negativo.");
    }
    if (altura < 0)
    {
        throw std::invalid_argument("Altura no puede ser negativa.");
    }
    if (identificacion.empty())
    {
        throw std::invalid_argument("Identificacion no puede estar vacía.");
    }
    id = ++counter; // Incrementa el contador estático para un id único
}

// Destructor
Persona::~Persona() {}

// Getters
int Persona::getId() const { return id; }
string Persona::getIdentificacion() const { return identificacion; }
string Persona::getLugarNacimiento() const { return lugarNacimiento; }
float Persona::getPeso() const { return peso; }
float Persona::getAltura() const { return altura; }
string Persona::getSexo() const { return sexo; }
int Persona::getEdad() const { return edad; }

// Setters con validaciones
void Persona::setIdentificacion(const std::string &identificacion)
{
    if (identificacion.empty())
    {
        throw std::invalid_argument("Identificacion no puede estar vacía.");
    }
    this->identificacion = identificacion;
}

void Persona::setLugarNacimiento(const std::string &lugarNacimiento)
{
    if (lugarNacimiento.empty())
    {
        throw std::invalid_argument("Lugar de nacimiento no puede estar vacío.");
    }
    this->lugarNacimiento = lugarNacimiento;
}

void Persona::setPeso(float pesoNacimiento)
{
    if (pesoNacimiento < 0)
    {
        throw std::invalid_argument("Peso no puede ser negativo.");
    }
    this->peso = pesoNacimiento;
}

void Persona::setAltura(float altura)
{
    if (altura < 0)
    {
        throw std::invalid_argument("Altura no puede ser negativa.");
    }
    this->altura = altura;
}

void Persona::setSexo(const std::string &sexo)
{
    if (sexo != "M" && sexo != "F")
    {
        throw std::invalid_argument("Sexo debe ser 'M' o 'F'.");
    }
    this->sexo = sexo;
}

void Persona::setEdad(int edad)
{
    if (edad < 0)
    {
        throw std::invalid_argument("Edad no puede ser negativa.");
    }
    this->edad = edad;
}
