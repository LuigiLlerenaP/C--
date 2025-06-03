#include <iostream>
#include <cmath>
using namespace std;

/**
 * Función que determina si un número es primo.
 * Un número primo es mayor que 1 y solo divisible por 1 y por sí mismo.
 *
 * @param num Número entero a evaluar.
 * @return true si el número es primo, false en caso contrario.
 */
bool esPrimo(int num)
{
    if (num <= 1)
    {
        return false; // Los números menores o iguales a 1 no son primos
    }
    if (num <= 3)
    {
        return true; // 2 y 3 son primos
    }
    if (num % 2 == 0 || num % 3 == 0)
    {
        return false; // Descarta múltiplos de 2 y 3
    }

    // Optimización: Solo verifica hasta la raíz cuadrada de num,
    // revisando divisibilidad con números de la forma 6k ± 1
    for (int i = 5; i * i <= num; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
        {
            return false;
        }
    }
    return true; // Si no se encontró divisor, es primo
}

int main()
{
    int N;

    // Solicita al usuario cuántos números primos desea sumar
    cout << "Ingrese el valor de N (cantidad de números primos a sumar): ";
    cin >> N;

    int suma = 0;     // Acumulador para la suma de primos
    int contador = 0; // Cuenta cuántos primos se han encontrado
    int numero = 2;   // Inicia la búsqueda desde el primer número primo

    cout << "Los primeros " << N << " números primos son: ";

    // Bucle que encuentra y suma los N primeros números primos
    while (contador < N)
    {
        if (esPrimo(numero))
        {
            cout << numero;
            suma += numero; // Suma el número primo
            contador++;     // Incrementa la cantidad de primos encontrados

            if (contador < N)
            {
                cout << ", "; // Imprime coma si no es el último número
            }
        }
        numero++; // Prueba el siguiente número
    }

    // Muestra la suma total de los primos encontrados
    cout << "\nLa suma de los primeros " << N << " números primos es: " << suma << endl;

    return 0;
}
