#include <iostream>
using namespace std;

void inicializar(int vector)
{
    vector[0] = 5;

    for (i = 1; i < 5; i++)
    {
        vector[i] = vector[i - 1] + 5;
    }
}

// colocar en un vector la serie de fibonacci
// Como poner los n primero numero de fibonacci en arreglo

void resultado(int vector)
{
    int valor = 0;
    for (i = 0; i < count; i++)
    {
        valor[i] += vector[i + 1] * 5;
    }
    return valor;
}
int main()
{
    int n[10];
    resultado(n);

    cout << "El resultado es: " << resultado(n) << endl;
    return 0;
}