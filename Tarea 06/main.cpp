#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct SubLista
{
    string dato;
    SubLista *siguiente;

    SubLista(const string &valor) : dato(valor), siguiente(nullptr) {}
};

struct Lista
{
    string dato;
    SubLista *subLista;
    Lista *siguiente;

    Lista(const string &valor) : dato(valor), subLista(nullptr), siguiente(nullptr) {}
};

void agregarElemento(Lista *&cabeza, const string &valor)
{
    Lista *nuevo = new Lista(valor);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

void agregarASubLista(SubLista *&cabeza, const string &valor)
{
    SubLista *nuevo = new SubLista(valor);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

void mostrarElementos(const Lista *cabeza)
{
    const Lista *actual = cabeza;
    while (actual)
    {
        cout << "Nodo: " << actual->dato << " -> SubLista: ";
        SubLista *sub = actual->subLista;
        while (sub)
        {
            cout << sub->dato << " ";
            sub = sub->siguiente;
        }
        cout << endl;
        actual = actual->siguiente;
    }
}

void guardarEnArchivo(const string &nombreArchivo, const Lista *cabeza)
{
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    const Lista *actual = cabeza;
    while (actual)
    {
        archivo << actual->dato << " ";
        SubLista *sub = actual->subLista;
        while (sub)
        {
            archivo << sub->dato << " ";
            sub = sub->siguiente;
        }
        archivo << endl;
        actual = actual->siguiente;
    }

    archivo.close();
}

int main()
{
    Lista *lista = nullptr;

    agregarElemento(lista, "Principal1");
    agregarElemento(lista, "Principal2");

    agregarASubLista(lista->subLista, "Sub1");
    agregarASubLista(lista->subLista, "Sub2");

    agregarASubLista(lista->siguiente->subLista, "SubA");
    agregarASubLista(lista->siguiente->subLista, "SubB");

    mostrarElementos(lista);

    guardarEnArchivo("datos.txt", lista);

    cout << "Datos guardados en datos.txt" << endl;

    return 0;
}
