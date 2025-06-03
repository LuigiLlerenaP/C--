#include <iostream>
using namespace std;

const int SIZE = 50;

void Multiplos3y5(int V1[])
{
    int count = 0;
    int num = 3;

    while (count < SIZE)
    {
        if (num % 3 == 0 && num % 5 == 0)
        {
            V1[count] = num;
            count++;
        }
        num++;
    }
}

void CopiarImpares(int V1[], int M1[][SIZE])
{
    int i = 0;
    int col = 0;

    while (i < SIZE)
    {
        if (V1[i] % 2 != 0)
        {
            M1[0][col] = V1[i];
            col++;
        }
        i++;
    }
}

void CalcularSumaVector(int V1[])
{
    int i = 0;
    int suma = 0;

    while (i < SIZE)
    {
        suma += V1[i];
        i++;
    }

    cout << "Suma de los elementos del vector V1: " << suma << endl;
}

void CalcularSumaMatriz(int M1[][SIZE])
{
    int i = 0;
    int suma = 0;

    while (i < SIZE)
    {
        int j = 0;
        while (j < SIZE)
        {
            if (M1[i][j] % 2 != 0)
            {
                suma += M1[i][j];
            }
            j++;
        }
        i++;
    }

    cout << "Suma de los elementos impares en la matriz M1: " << suma << endl;
}

int main()
{
    int V1[SIZE] = {0};
    int M1[SIZE][SIZE] = {0};

    Multiplos3y5(V1);
    CopiarImpares(V1, M1);
    CalcularSumaVector(V1);
    CalcularSumaMatriz(M1);

    return 0;
}
