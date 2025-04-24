#include <iostream> // Librería para entrada/salida
using namespace std;

int main(int argc, char const *argv[])
{

    int number = 0;

    int numbers[] = {1, -2, 3, -4, 5};

    int maxlength = sizeof(numbers) / sizeof(numbers[0]);

    int resultNegative = 0;
    int resultPositive = 0;
    int total = 0;

    for (int i = 0; i < maxlength; i++)
    {
        if (numbers[i] < 0)
        {
            resultNegative += numbers[i];
        }
        resultPositive += numbers[i];
        total += numbers[i];
    }
    cout << "The result positive is:" << resultPositive << endl; // Imprimir la cadena ingresada
    cout << "The result negative is:" << resultNegative << endl; // Imprimir la cadena ingresada
    cout << "The result is:" << total << endl;                   // Imprimir la cadena ingresada

    return 0;
}
