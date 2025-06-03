#include <iostream>
#include <climits>
#include <utility>
#include <vector>
#include <algorithm> // Para transform
using namespace std;

// Function to calculate the minimum even number in the matrix
// It iterates through the matrix and finds the minimum even number
// if my element is pair and less than the element in the matrix and have the minimum value
int calculatePairNumberLessThan(const vector<vector<int>> &matrix)
{
    int minValue = matrix[0][0];
    cout << "Calculate..." << endl;
    // Iterating through each row in the matrix
    for (const auto &row : matrix)
    {
        // Iterating through each element in the row
        for (const auto &element : row)
        {
            if (element % 2 != 0)
            {
                continue; // Skip odd numbers;
            }
            // If the element is even and less than the current minValue, update minValue
            if (element < minValue)
            {
                minValue = element;
            }
        }
    }
    return minValue;
}

// Function to calculate the maximum odd number in the matrix
// It iterates through the matrix and finds the maximum odd number
// If an element is odd and greater than the current maxValue, it updates the maxValue
int calculateOddNumberGreaterThan(const vector<vector<int>> &matrix)
{
    int maxValue = matrix[0][0];
    cout << "Calculate..." << endl;
    // Iterating through each row in the matrix
    for (const auto &row : matrix)
    {
        // Iterating through each element in the row
        for (const auto &element : row)
        {
            if (element % 2 == 0)
            {
                continue; // Skip even numbers;
            }
            // If the element is odd and greater than the current maxValue, update maxValue
            if (element > maxValue)
            {
                maxValue = element;
            }
        }
    }
    return maxValue;
}

// Function to calculate the sum of even diagonal elements in the matrix
// It iterates through the diagonal elements of the matrix and sums them if they are even
// It uses the index i to access the diagonal elements matrix[i][i]
int calculatePairDiagonalElement(const vector<vector<int>> &matrix)
{
    int sumPairDiagonalElement = 0;
    cout << "Calculate..." << endl;
    // Iterating through the diagonal elements of the matrix
    for (int i = 0; i < matrix.size(); i++)
    {
        int element = matrix[i][i]; // Get the diagonal element
        // Check if the element is even
        if (element % 2 == 0)
        {
            sumPairDiagonalElement += element; // Add even elements to the sum
        }
    }
    return sumPairDiagonalElement;
}

// Show the result of the minimum even number or maximum odd number in the matrix
// It checks if the result is found and displays the result
void showNumberResult(const int &result, string resultType = "par menor")
{
    cout << "El número " << resultType << " en la matriz es: " << result << endl;
}

// Separador de formato
void separateFormat(string title = "")
{
    cout << title << endl;
    cout << "----------------------------------------" << endl;
    cout << "----------------------------------------" << endl;
}

// Functions to request values from the user
// Returns pair of integers representing the number of rows and columns
pair<int, int> requestValues()
{
    int rows, columns;
    cout << "Introduce el número de filas: ";
    cin >> rows;
    cout << "Introduce el número de columnas: ";
    cin >> columns;
    return make_pair(rows, columns);
}

// Function to create a matrix of integers
// Takes the number of rows and columns as input and returns a 2D vector (matrix)
vector<vector<int>> createMatrix(int rows, int columns)
{
    vector<vector<int>> matrix(rows, vector<int>(columns));
    cout << "Introduce los elementos de la matriz: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << "Elemento [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

// Function to display the matrix, show the elements in the vector
// Auto deduction of the type of the matrix
// & refers to the matrix to avoid copying it
void showMatrix(const vector<vector<int>> &matrix)
{
    cout << "Matriz: " << endl;
    for (const auto &row : matrix)
    {
        for (const auto &element : row)
        {
            cout << element << " ";
        }
        cout << endl;
    }
}

// Handler for finding the minimum even number
void handlerPairNumberLessThan()
{
    pair<int, int> dimensions = requestValues();
    vector<vector<int>> matrix = createMatrix(dimensions.first, dimensions.second);
    separateFormat();
    showMatrix(matrix);
    separateFormat();

    separateFormat("Calculando el número par menor en la matriz:");
    int result = calculatePairNumberLessThan(matrix);
    showNumberResult(result);
    separateFormat();
}

// Handler for finding the maximum odd number
void handlerOddNumberGreaterThan()
{
    pair<int, int> dimensions = requestValues();
    vector<vector<int>> matrix = createMatrix(dimensions.first, dimensions.second);
    separateFormat();
    showMatrix(matrix);
    separateFormat();

    separateFormat("Calculando el número impar mayor en la matriz:");
    int result = calculateOddNumberGreaterThan(matrix);
    showNumberResult(result, "impar mayor");
    separateFormat();
}

//
void handlerlenDiagonalElements()
{
    pair<int, int> dimensions = requestValues();
    vector<vector<int>> matrix = createMatrix(dimensions.first, dimensions.second);
    separateFormat();
    showMatrix(matrix);
    separateFormat();

    separateFormat("Calculando los elementos pares de la diagonal:");
    int result = calculatePairDiagonalElement(matrix);
    showNumberResult(result, "suma de los elementos pares de la diagonal");
    separateFormat();
}

// Continue the program until the user decides to exit
// It checks if the user input is "yes" or "y" (case insensitive) to continue
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

// Menu options
void showMenuOption()
{
    cout << "\n=== MENÚ PRINCIPAL ===" << endl;
    cout << "1) Encontrar el número mayor (impar)" << endl;
    cout << "2) Encontrar el número menor (par)" << endl;
    cout << "3) Elementos Pares de la Diagonal de una matriz." << endl;
    cout << "4) Salir" << endl;
    cout << "\nSeleccione una opción: " << endl;
}

// Handle the selected menu option
void handleMenuSelection(int option)
{
    if (option == 1)
    {
        cout << "Encontrar el número mayor (impar)" << endl;
        handlerOddNumberGreaterThan();
        return;
    }
    if (option == 2)
    {
        cout << "Encontrar el número menor (par)" << endl;
        handlerPairNumberLessThan();
        return;
    }
    if (option == 3)
    {
        cout << "Elementos Pares de la Diagonal de una matriz." << endl;
        handlerlenDiagonalElements();
        return;
    }
}

// Select Option
void selectOptionMenu()
{
    int option;
    bool exitProgram = false;

    while (!exitProgram)
    {
        showMenuOption();
        cin >> option;

        handleMenuSelection(option);

        if (option == 4) // Opción para salir
        {
            exitProgram = true;
            return;
        }
        exitProgram = shouldReturnToMenu();
    }
}

// Function principal to execute the program
int main(int argc, char const *argv[])
{
    selectOptionMenu();

    return 0;
}
