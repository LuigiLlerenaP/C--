#include <iostream>
using namespace std;

// Función recursiva para calcular el factorial
long long factorial(int n)
{
    // Caso base: factorial de 0 y 1 es 1
    if (n == 0 || n == 1)
    {
        return 1;
    }

    // Validación para números negativos
    if (n < 0)
    {
        cout << "Error: El factorial no está definido para números negativos." << endl;
        return -1;
    }

    // Caso recursivo: n! = n * (n-1)!
    return n * factorial(n - 1);
}

int main()
{
    int numero;

    cout << "Ingrese un número para calcular su factorial: ";
    cin >> numero;

    long long resultado = factorial(numero);

    if (resultado != -1)
    {
        cout << "El factorial de " << numero << " es: " << resultado << endl;
    }

    // Ejemplos adicionales
    cout << "\nEjemplos:" << endl;
    for (int i = 0; i <= 10; i++)
    {
        cout << i << "! = " << factorial(i) << endl;
    }

    return 0;
}