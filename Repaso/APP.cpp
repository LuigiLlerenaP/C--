#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

// Lógica
void sumParNumbers(const vector<int> &numbers)
{
    cout << "Sumando...." << endl;

    int sum = 0;
    int i = 0;
    while (i < numbers.size())
    {
        if (numbers[i] % 2 == 0)
        {
            sum += numbers[i];
            cout << "Número par encontrado: " << numbers[i] << endl;
        }
        i++;
    }
    cout << "La suma de los números pares es: " << sum << endl;
}
void sumOddNumbers(const vector<int> &numbers)
{
    cout << "Sumando...." << endl;
    int sum = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] % 2 != 0)
        {
            sum += numbers[i];
            cout << "Número impar  encontrado: " << numbers[i] << endl;
        }
    }
    cout << "La suma de los números impares es: " << sum << endl;
}
void findMaxNumber(const vector<int> &numbers)
{
    if (numbers.empty())
    {
        cout << "No se proporcionaron números." << endl;
        return;
    }
    int maxNumber = numbers[0];
    for (int num : numbers)
    {
        if (num > maxNumber)
        {
            maxNumber = num;
        }
    }
    cout << "El número mayor es: " << maxNumber << endl;
}
void findMinNumber(const vector<int> &numbers)
{
    if (numbers.empty())
    {
        cout << "No se proporcionaron números." << endl;
        return;
    }
    int minNumber = numbers[0];
    for (int num : numbers)
    {
        if (num < minNumber)
        {
            minNumber = num;
        }
    }
    cout << "El número menor es: " << minNumber << endl;
}
void calculateCircleAreaAndPerimeter()
{
    double radius, area, perimeter;
    const double PI = 3.14159265359;
    cout << "Introduce el radio de la circunferencia: ";
    cin >> radius;

    if (radius <= 0)
    {
        cout << "El radio debe ser un número positivo." << endl;
        return;
    }

    area = PI * pow(radius, 2);
    perimeter = 2 * PI * radius;

    cout << "Área de la circunferencia: " << area << endl;
    cout << "Perímetro de la circunferencia: " << perimeter << endl;
}

long long factorial(int n)
{
    long long result = 1;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

void calculateFactorialSeries()
{
    int N;
    cout << "Ingrese un número N: ";
    cin >> N;

    if (N <= 0)
    {
        cout << "N debe ser un número entero positivo." << endl;
        return;
    }

    long long sum = 0;
    for (int i = 1; i <= N; i++)
    {
        long long f = factorial(i);
        sum += f;
        cout << i << "! = " << f << endl;
    }

    cout << "La suma de la serie S = 1! + 2! + ... + " << N << "! es: " << sum << endl;
}
void showRegisteredNumbers(const vector<int> &numbers)
{
    cout << "\nLos números registrados son: ";
    for (int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
}

bool shouldContinue(const string &userInput)
{
    string inputLower = userInput;
    transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);
    return inputLower == "yes" || inputLower == "y";
}

bool shouldReturnToMenu()
{
    string continueInput;
    cout << "¿Deseas regresar al menú? (yes/no) :";
    cin >> continueInput;
    return !shouldContinue(continueInput);
}

vector<int> registerNumbers()
{
    int number = 0;
    vector<int> numbers;
    string continueInput = "yes";

    cout << "-- Inserte los números a guardar --" << endl;

    while (shouldContinue(continueInput))
    {
        cout << "Inserte un número: ";
        cin >> number;
        numbers.push_back(number);

        cout << "¿Deseas agregar otro número? (yes/no): ";
        cin >> continueInput;
    }

    return numbers;
}

void handleSumEvenNumbers()
{
    cout << "Seleccionaste: Sumar números pares (while)" << endl;
    vector<int> numbersToWork = registerNumbers();
    showRegisteredNumbers(numbersToWork);
    sumParNumbers(numbersToWork);
}
void handleSumOdNumbers()
{
    cout << "Seleccionaste: Sumar números pares (while)" << endl;
    vector<int> numbersToWork = registerNumbers();
    showRegisteredNumbers(numbersToWork);
    sumOddNumbers(numbersToWork);
}
void handleFindMaxNumber()
{
    cout << "Encontrar el número mayor" << endl;
    vector<int> numbersToWork = registerNumbers();
    showRegisteredNumbers(numbersToWork);
    findMaxNumber(numbersToWork);
}
void handleFindMinNumber()
{
    cout << "Encontrar el número mayor" << endl;
    vector<int> numbersToWork = registerNumbers();
    showRegisteredNumbers(numbersToWork);
    findMinNumber(numbersToWork);
}

void showMenuOption()
{
    cout << "\n=== MENÚ PRINCIPAL ===" << endl;
    cout << "1) Sumar números pares (while)" << endl;
    cout << "2) Sumar números impares (for)" << endl;
    cout << "3) Encontrar el número mayor" << endl;
    cout << "4) Encontrar el número menor" << endl;
    cout << "5) Calcular área y perímetro (circunferencia)" << endl;
    cout << "6) Calcular S = 1! + 2! + ... + N! (Serie de factoriales)" << endl;
    cout << "7) Salir" << endl;
    cout << "\nSeleccione una opción: " << endl;
}

void handleMenuSelection(int option)
{
    if (option == 1)
    {
        handleSumEvenNumbers();
        return;
    }
    if (option == 2)
    {
        handleSumOdNumbers();
        return;
    }
    if (option == 3)
    {
        handleFindMaxNumber();
        return;
    }
    if (option == 4)
    {
        handleFindMinNumber();
        return;
    }

    if (option == 5)
    {
        calculateCircleAreaAndPerimeter();
        return;
    }
    if (option == 6)
    {
        calculateFactorialSeries();
        return;
    }

    if (option == 7)
    {
        return;
    }
}

void selectOptionMenu()
{
    int option;
    bool exitProgram = false;

    while (!exitProgram)
    {
        showMenuOption();
        cin >> option;

        handleMenuSelection(option);

        if (option == 7)
        {
            exitProgram = true;
            return;
        }
        exitProgram = shouldReturnToMenu();
    }
}

int main()
{
    selectOptionMenu();
    return 0;
}
