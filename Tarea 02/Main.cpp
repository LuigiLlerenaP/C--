#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include "./Persona.h"
#include "./PersonaNacida.h"
using namespace std;

// Función para mostrar el menú principal
void showMenuOption()
{
    cout << "\n=== MENÚ PRINCIPAL ===\n"
         << endl;
    cout << "1) Agregar persona nacida" << endl;
    cout << "2) Ver detalles de personas nacidas" << endl;
    cout << "3) Salir" << endl;
    cout << "\nSeleccione una opción (1-3): ";
}

// Convierte la entrada a minúsculas y evalúa si se debe continuar
bool shouldContinue(const string &userInput)
{
    string inputLower = userInput;
    transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);
    return inputLower == "yes" || inputLower == "y";
}

// Pregunta al usuario si desea regresar al menú
bool shouldReturnToMenu()
{
    string continueInput;
    cout << "\n¿Deseas regresar al menú? (yes/no): ";
    cin >> continueInput;
    return shouldContinue(continueInput);
}

// Formato visual para separar secciones
void separateFormat(const string &title = "")
{
    cout << "\n"
         << title << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
}

Persona addPersonBorn()
{
    string identificacion, lugarNacimiento, sexo;
    float peso, altura;
    int edad;
    cout << "Ingrese identificación: ";
    cin >> identificacion;
    cout << "Ingrese lugar de nacimiento: ";
    cin >> lugarNacimiento;
    cout << "Ingrese peso: ";
    cin >> peso;
    cout << "Ingrese altura: ";
    cin >> altura;
    cout << "Ingrese sexo (M/F): ";
    cin >> sexo;
    cout << "Ingrese edad: ";
    cin >> edad;

    return Persona(identificacion, lugarNacimiento, peso, altura, sexo, edad);
}

void handlerAddPersonBorn(PersonaNacida &personaNacida)
{
    separateFormat("AGREGAR PERSONA NACIDA");
    string continuar;
    do
    {
        Persona persona = addPersonBorn();
        personaNacida.setPersonaNacida(persona);
        cout << "\n¿Desea agregar otra persona? (yes/no): ";
        cin >> continuar;

    } while (shouldContinue(continuar));
}

void handlerShowDetailsPersonBorn(PersonaNacida &personaNacida)
{
    separateFormat("DETALLES DE PERSONAS NACIDAS");
    personaNacida.printPersonasNacidas();
    separateFormat();
    personaNacida.calcularPromedios();
    cout << "Promedio de peso: " << personaNacida.getPromedioPesoNacido() << endl;
    cout << "Promedio de altura: " << personaNacida.getPromedioAlturaNacido() << endl;
    cout << "Cantidad total de nacidos: " << personaNacida.getCantidadNacidos() << endl;
    cout << "Cantidad de nacidos mujeres: " << personaNacida.getCantidadNacidosMujeres() << endl;
    cout << "Cantidad de nacidos hombres: " << personaNacida.getCantidadNacidosHombres() << endl;
    cout << "----------------------------------------" << endl;
}

// Maneja la selección del menú según la opción elegida
void handleMenuSelection(int option, PersonaNacida &personaNacida)
{
    switch (option)
    {
    case 1:
        handlerAddPersonBorn(personaNacida);
        break;
    case 2:
        handlerShowDetailsPersonBorn(personaNacida);
        break;
    case 3:
        cout << "\nSaliendo del programa. ¡Hasta pronto!\n";
        break;
    default:
        cout << "\nOpción no válida. Intente nuevamente.\n";
        break;
    }
}

// Controlador principal del menú
void selectOptionMenu(PersonaNacida &personaNacida)
{
    int option;
    bool exitProgram = false;

    while (!exitProgram)
    {
        showMenuOption();
        cin >> option;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descarta el resto de la línea
            cout << "\nEntrada inválida. Por favor, ingrese un número del 1 al 3.\n";
            continue;
        }

        handleMenuSelection(option, personaNacida);

        if (option == 3)
        {
            exitProgram = true;
        }

        exitProgram = !shouldReturnToMenu();
    }
}

// Función principal
int main()
{
    PersonaNacida personaNacida;
    selectOptionMenu(personaNacida);
    return 0;
}