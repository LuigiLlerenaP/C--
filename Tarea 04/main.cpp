#include "./Utilites/ConsoleUtils.h"
#include <iostream>
#include <limits>
#include "./ImplementList/PersonaListaEnlazada.h"
#include "./Persona/Persona.h"

using namespace ConsoleUtils;
using namespace std;

int main()
{
    PersonaListaEnlazada listaPersonas;

    ConsoleMenu::addMenuOption("Agregar persona nacida");
    ConsoleMenu::addMenuOption("Ver detalles de personas nacidas");
    ConsoleMenu::addMenuOption("Cargar números múltiplos de 5");
    ConsoleMenu::addMenuOption("Cargar números pares");
    ConsoleMenu::addMenuOption("Cargar números primos");
    ConsoleMenu::addMenuOption("Cargar números de la serie de Fibonacci");
    ConsoleMenu::addMenuOption("Salir");

    bool exitProgram = false;

    while (!exitProgram)
    {
        ConsoleMenu::showMenuOption();

        int option;
        cin >> option;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ConsoleMenu::printSeparator("Entrada inválida. Por favor, ingresa un número.");
            continue;
        }

        switch (option)
        {
        case 1:
        {
            ConsoleMenu::printSeparator("Agregar persona nacida seleccionado");

            string identificacion, lugarNacimiento, sexo;
            float peso, altura;
            int edadMadre;

            cout << "Identificación: ";
            cin >> identificacion;
            cout << "Lugar de nacimiento: ";
            cin >> lugarNacimiento;
            cout << "Peso: ";
            cin >> peso;
            cout << "Altura: ";
            cin >> altura;
            cout << "Sexo: ";
            cin >> sexo;
            cout << "Edad de la madre: ";
            cin >> edadMadre;

            Persona p(identificacion, lugarNacimiento, peso, altura, sexo, edadMadre);
            listaPersonas.agregarPersona(p);

            cout << "Persona agregada con éxito.\n";
            break;
        }
        case 2:
        {
            ConsoleMenu::printSeparator("Ver detalles de personas nacidas seleccionado");
            listaPersonas.mostrarPersonas();

            cout << "Peso promedio: " << listaPersonas.pesoPromedio() << "\n";
            cout << "Talla promedio: " << listaPersonas.tallaPromedio() << "\n";
            cout << "Edad promedio de la madre: " << listaPersonas.edadMadrePromedio() << "\n";
            break;
        }
        case 3:
            ConsoleMenu::printSeparator("Números múltiplos de 5");
            break;
        case 4:
            ConsoleMenu::printSeparator("Números pares");
            break;
        case 5:
            ConsoleMenu::printSeparator("Números primos");
            break;
        case 6:
            ConsoleMenu::printSeparator("Serie de Fibonacci");
            break;
        case 7:
            ConsoleMenu::printSeparator("Saliendo...");
            exitProgram = true;
            continue;
        default:
            ConsoleMenu::printSeparator("Opción no válida, intenta de nuevo.");
        }

        string input = ConsoleMenu::shouldReturnToMenu();
        if (!ConsoleMenu::shouldContinue(input))
        {
            exitProgram = true;
        }
    }

    return 0;
}
