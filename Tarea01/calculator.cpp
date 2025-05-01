#include <iostream>
#include <utility> // For std::pair
#include <tuple>   // For std::tie
using namespace std;

// Function to get two numbers , tuple
pair<double, double> getNumbers()
{
    double a, b;
    cout << "Enter two numbers\n ";
    cout << "The first number is: ";
    cin >> a;
    cout << "The second number is: ";
    cin >> b;
    return make_pair(a, b);
}

// Function to add two numbers
void addNumbers(double a, double b)
{
    cout << "Result: " << a + b << endl;
}

// Function to subtract two numbers
void subtractNumbers(double a, double b)
{
    cout << "Result: " << a - b << endl;
}

// Function to multiply two numbers
void multiplyNumbers(double a, double b)
{
    cout << "Result: " << a * b << endl;
}

// Function to divide two numbers
void divideNumbers(double a, double b)
{
    if (b != 0)
    {
        cout << "Result: " << a / b << endl;
    }
    else
    {
        cout << "Error: Division by zero" << endl;
    }
}

// Main function to display menu and call the operations
int main()
{

    int choice;

    cout << "Choose an option  \n";
    cout << "1. Add\n2. Subtract\n3. Multiply\n4. Divide\n";
    cout << "Choose an option (1-4): ";
    cin >> choice;
    cout << "------------\n";
    double a, b;
    // Ask for numbers once and store them
    tie(a, b) = getNumbers();

    switch (choice)
    {
    case 1:
        addNumbers(a, b); // Pass numbers as parameters
        break;
    case 2:
        subtractNumbers(a, b); // Pass numbers as parameters
        break;
    case 3:
        multiplyNumbers(a, b); // Pass numbers as parameters
        break;
    case 4:
        divideNumbers(a, b); // Pass numbers as parameters
        break;
    default:
        cout << "Invalid option.\n";
    }

    return 0;
}
