#include <iostream>  // Librería para entrada/salida
#include <string>    // Librería para manipulación de cadenas
using namespace std; // Usar el espacio de nombres estándar
#include <cctype>
// Función para pedir al usuario una cadena de texto

string askForInput()
{
    string input;
    cout << "Enter a string:";
    cin >> input; // Asignar el valor de entrada a la variable input
    return input;
}

bool isPalindrome(const string &letter)
{
    int lengthMiddleLetter = (letter.length() / 2);
    int lastPosition = letter.length() - 1;
    for (int i = 0; i < lengthMiddleLetter; i++)
    {
        if (tolower(letter[i]) != tolower(letter[lastPosition]))
        {
            return false;
        }
        lastPosition--;
    }

    return true;
}

// Función inicial
int main(int argc, char const *argv[])
{
    string inputUser = askForInput();
    string palindrome = isPalindrome(inputUser) ? "is a palindrome" : "is not a palindrome";
    cout << "The string" << inputUser << "is:" << palindrome << endl; // Imprimir la cadena ingresada
    return 0;
}
