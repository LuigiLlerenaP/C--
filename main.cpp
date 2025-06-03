#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
using namespace std;

// === Clase Persona ===
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
    int edad;

public:
    Persona() = default;
    Persona(const string &, const string &, float, float, const string &, int);
    ~Persona();

    // Getters
    int getId() const;
    string getIdentificacion() const;
    string getLugarNacimiento() const;
    float getPeso() const;
    float getAltura() const;
    string getSexo() const;
    int getEdad() const;

    // Setters
    void setIdentificacion(const string &);
    void setLugarNacimiento(const string &);
    void setPeso(float);
    void setAltura(float);
    void setSexo(const string &);
    void setEdad(int);
};

int Persona::counter = 0;

Persona::Persona(const string &identificacion, const string &lugarNacimiento, float peso, float altura, const string &sexo, int edad)
    : identificacion(identificacion), lugarNacimiento(lugarNacimiento), peso(peso), altura(altura), sexo(sexo), edad(edad)
{
    if (sexo != "M" && sexo != "F")
        throw invalid_argument("Sexo debe ser 'M' o 'F'");
    if (edad < 0 || peso < 0 || altura < 0 || identificacion.empty())
        throw invalid_argument("Datos inválidos");
    id = ++counter;
}

Persona::~Persona() {}

int Persona::getId() const { return id; }
string Persona::getIdentificacion() const { return identificacion; }
string Persona::getLugarNacimiento() const { return lugarNacimiento; }
float Persona::getPeso() const { return peso; }
float Persona::getAltura() const { return altura; }
string Persona::getSexo() const { return sexo; }
int Persona::getEdad() const { return edad; }

void Persona::setIdentificacion(const string &v)
{
    if (v.empty())
        throw invalid_argument("Identificación vacía");
    identificacion = v;
}
void Persona::setLugarNacimiento(const string &v)
{
    if (v.empty())
        throw invalid_argument("Lugar vacío");
    lugarNacimiento = v;
}
void Persona::setPeso(float v)
{
    if (v < 0)
        throw invalid_argument("Peso negativo");
    peso = v;
}
void Persona::setAltura(float v)
{
    if (v < 0)
        throw invalid_argument("Altura negativa");
    altura = v;
}
void Persona::setSexo(const string &v)
{
    if (v != "M" && v != "F")
        throw invalid_argument("Sexo inválido");
    sexo = v;
}
void Persona::setEdad(int v)
{
    if (v < 0)
        throw invalid_argument("Edad negativa");
    edad = v;
}

// === Clase PersonaNacida ===
class PersonaNacida
{
private:
    static const int MAX_PERSONAS = 25;
    Persona personasNacidas[MAX_PERSONAS];
    int cantidadNacidos = 0;
    float promedioPesoNacido = 0;
    float promedioAlturaNacido = 0;
    int cantidadNacidosMujeres = 0;
    int cantidadNacidosHombres = 0;

public:
    bool setPersonaNacida(const Persona &);
    void calcularPromedios();
    void printPersonasNacidas() const;

    float getPromedioPesoNacido() const { return promedioPesoNacido; }
    float getPromedioAlturaNacido() const { return promedioAlturaNacido; }
    int getCantidadNacidos() const { return cantidadNacidos; }
    int getCantidadNacidosMujeres() const { return cantidadNacidosMujeres; }
    int getCantidadNacidosHombres() const { return cantidadNacidosHombres; }
};

bool PersonaNacida::setPersonaNacida(const Persona &persona)
{
    if (cantidadNacidos >= MAX_PERSONAS)
    {
        cout << "Capacidad máxima alcanzada.\n";
        return false;
    }
    personasNacidas[cantidadNacidos++] = persona;
    return true;
}

void PersonaNacida::calcularPromedios()
{
    if (cantidadNacidos == 0)
        throw invalid_argument("No hay personas nacidas.");

    float totalPeso = 0, totalAltura = 0;
    cantidadNacidosHombres = cantidadNacidosMujeres = 0;

    for (int i = 0; i < cantidadNacidos; ++i)
    {
        const Persona &p = personasNacidas[i];
        totalPeso += p.getPeso();
        totalAltura += p.getAltura();
        if (p.getSexo() == "M")
            cantidadNacidosHombres++;
        else if (p.getSexo() == "F")
            cantidadNacidosMujeres++;
    }

    promedioPesoNacido = totalPeso / cantidadNacidos;
    promedioAlturaNacido = totalAltura / cantidadNacidos;
}

void PersonaNacida::printPersonasNacidas() const
{
    cout << "\n"
         << left << setw(10) << "RegID"
         << setw(15) << "DNI"
         << setw(15) << "Lugar"
         << setw(10) << "Peso"
         << setw(10) << "Altura"
         << setw(10) << "Sexo"
         << setw(10) << "Edad" << "\n";
    cout << string(80, '-') << "\n";

    for (int i = 0; i < cantidadNacidos; ++i)
    {
        const Persona &p = personasNacidas[i];
        cout << left << setw(10) << p.getId()
             << setw(15) << p.getIdentificacion()
             << setw(15) << p.getLugarNacimiento()
             << setw(10) << p.getPeso()
             << setw(10) << p.getAltura()
             << setw(10) << p.getSexo()
             << setw(10) << p.getEdad() << "\n";
    }
    cout << "\n";
}

// === Funciones ===
void showMenuOption()
{
    cout << "\n1) Agregar persona nacida\n2) Ver detalles\n3) Salir\n\nSeleccione opción: ";
}

bool shouldContinue(const string &input)
{
    string s = input;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s == "yes" || s == "y";
}

Persona addPersonBorn()
{
    string id, lugar, sexo;
    float peso, altura;
    int edad;
    cout << "Identificación: ";
    cin >> id;
    cout << "Lugar Nacimiento: ";
    cin >> lugar;
    cout << "Peso: ";
    cin >> peso;
    cout << "Altura: ";
    cin >> altura;
    cout << "Sexo (M/F): ";
    cin >> sexo;
    cout << "Edad: ";
    cin >> edad;
    return Persona(id, lugar, peso, altura, sexo, edad);
}

void handlerAddPersonBorn(PersonaNacida &pn)
{
    string cont;
    do
    {
        Persona p = addPersonBorn();
        if (!pn.setPersonaNacida(p))
            break;
        cout << "¿Agregar otra persona? (yes/no): ";
        cin >> cont;
    } while (shouldContinue(cont));
}

void handlerShowDetailsPersonBorn(PersonaNacida &pn)
{
    pn.printPersonasNacidas();
    pn.calcularPromedios();
    cout << "---------Promedio---------" << endl;
    cout << "Promedio peso: " << pn.getPromedioPesoNacido() << endl;
    cout << "Promedio altura: " << pn.getPromedioAlturaNacido() << endl;
    cout << "Total: " << pn.getCantidadNacidos() << endl;
    cout << "Mujeres: " << pn.getCantidadNacidosMujeres() << ", Hombres: " << pn.getCantidadNacidosHombres() << endl;
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

int main()
{
    PersonaNacida personaNacida;
    int option;
    do
    {
        showMenuOption();
        cin >> option;
        switch (option)
        {
        case 1:
            handlerAddPersonBorn(personaNacida);
            break;
        case 2:
            handlerShowDetailsPersonBorn(personaNacida);
            break;
        case 3:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción inválida.\n";
            break;
        }
    } while (option != 3);

    return 0;
}
