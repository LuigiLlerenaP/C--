#include <iostream>
namespace std;

int initializeArray(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = 0;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int numbers[] = {1, -2, 3, -4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    initializeArray(numbers, size);

    cout << "The result is:" < < < < endl;
    return 0;
}
