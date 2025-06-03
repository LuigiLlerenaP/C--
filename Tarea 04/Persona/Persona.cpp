#include "Persona.h"

// Definición del atributo estático de clase para llevar el conteo de instancias creadas
int Persona::counter = 0;

/// @brief Constructor de la clase Persona.
/// @param identificacion Número o código de identificación de la persona.
/// @param lugarNacimiento Ciudad o lugar donde nació la persona.
/// @param peso Peso de la persona en kilogramos.
/// @param altura Altura de la persona en metros.
/// @param sexo Sexo de la persona (por ejemplo, "masculino", "femenino").
/// @param edadMadre Edad de la madre al momento del nacimiento.
Persona::Persona(const string &identificacion, const string &lugarNacimiento,
                 float peso, float altura, const string &sexo, int edadMadre)
    : identificacion(identificacion), lugarNacimiento(lugarNacimiento),
      peso(peso), altura(altura), sexo(sexo), edadMadre(edadMadre)
{

    id = ++counter;
}

/// @brief Destructor de la clase Persona.
Persona::~Persona() {}

// ===================
// Getters
// ===================

int Persona::getId() const { return id; }
string Persona::getIdentificacion() const { return identificacion; }
string Persona::getLugarNacimiento() const { return lugarNacimiento; }
float Persona::getPeso() const { return peso; }
float Persona::getAltura() const { return altura; }
string Persona::getSexo() const { return sexo; }
int Persona::getEdadMadre() const { return edadMadre; }

// ===================
// Setters
// ===================

void Persona::setIdentificacion(const string &identificacion) { this->identificacion = identificacion; }
void Persona::setLugarNacimiento(const string &lugarNacimiento) { this->lugarNacimiento = lugarNacimiento; }
void Persona::setPeso(float peso) { this->peso = peso; }
void Persona::setAltura(float altura) { this->altura = altura; }
void Persona::setSexo(const string &sexo) { this->sexo = sexo; }
void Persona::setEdadMadre(int edadMadre) { this->edadMadre = edadMadre; }
