#include <iostream>
#include <utility> // For std::pair
#include <tuple>   // For std::tie
using namespace std;

int FuncionDesconocidaX1(int N)
{

    int Resultado = 0, Signo = 1;
    for (int i = 1; i <= N; i++)
    {
        int f = i;
        for (int j = (i - 1); j > 1; j--)
            f = f * j;

        Resultado = Resultado + (f * Signo);
        Signo = Signo * (-1);
    }
    return Resultado;
}

int main(int argc, char const *argv[])
{
    int N = 10;
    int Resultado = 0, Signo = 1;
    for (int i = 1; i <= N; i++)
    {
        int f = i;
        for (int j = (i - 1); j > 1; j--)
            f = f * j;

        Resultado = Resultado + (f * Signo);
        Signo = Signo * (-1);
    }
    std::cout << "Resultado final: " << Resultado << std::endl;
    return 0;
}
