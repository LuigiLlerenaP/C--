#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

const int MAX_CANCIONES = 20;
const int MAX_LINEAS = 20;

// Arreglo bidimensional
string letters[MAX_CANCIONES][MAX_LINEAS];

// Struct línea
struct Linea
{
    string texto;
    Linea *siguiente;
};

// Struct canción
struct Cancion
{
    string titulo;
    Linea *primeraLinea;
    Cancion *siguiente;
};

// Crear una línea
Linea *crearLinea(const string &texto)
{
    Linea *nueva = new Linea;
    nueva->texto = texto;
    nueva->siguiente = nullptr;
    return nueva;
}

// Agregar línea a canción
void agregarLinea(Cancion *cancion, const string &texto, int fila, int &columna)
{
    Linea *nueva = crearLinea(texto);
    if (!cancion->primeraLinea)
    {
        cancion->primeraLinea = nueva;
    }
    else
    {
        Linea *temp = cancion->primeraLinea;
        while (temp->siguiente)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nueva;
    }
    // Guardar en el arreglo
    if (fila < MAX_CANCIONES && columna < MAX_LINEAS)
    {
        letters[fila][columna++] = texto;
    }
}

// Crear canción
Cancion *crearCancion(const string &titulo)
{
    Cancion *nueva = new Cancion;
    nueva->titulo = titulo;
    nueva->primeraLinea = nullptr;
    nueva->siguiente = nullptr;
    return nueva;
}

// Agregar canción a lista
Cancion *agregarCancion(Cancion *&lista, const string &titulo)
{
    Cancion *nueva = crearCancion(titulo);
    if (!lista)
    {
        lista = nueva;
    }
    else
    {
        Cancion *temp = lista;
        while (temp->siguiente)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nueva;
    }
    return nueva;
}

// Leer archivo
Cancion *leerArchivo(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo.\n";
        return nullptr;
    }

    string linea;
    Cancion *lista = nullptr;
    Cancion *actual = nullptr;
    int fila = -1; // Para índice del arreglo
    int columna = 0;

    while (getline(archivo, linea))
    {
        if (linea.empty())
            continue;

        if (linea[0] == '#')
        {
            string titulo = linea.substr(1); // Título sin #
            actual = agregarCancion(lista, titulo);
            fila++;
            columna = 0;
        }
        else if (actual)
        {
            agregarLinea(actual, linea, fila, columna);
        }
    }

    archivo.close();
    return lista;
}

// Imprimir canciones
void imprimirCanciones(Cancion *lista)
{
    Cancion *c = lista;
    while (c)
    {
        cout << "Título: " << c->titulo << endl;
        Linea *l = c->primeraLinea;
        while (l)
        {
            cout << "  " << l->texto << endl;
            l = l->siguiente;
        }
        c = c->siguiente;
        cout << endl;
    }
}

// Mostrar arreglo
void mostrarArreglo()
{
    cout << "\nContenido del arreglo [20][20]:\n";
    for (int i = 0; i < MAX_CANCIONES; i++)
    {
        for (int j = 0; j < MAX_LINEAS; j++)
        {
            if (!letters[i][j].empty())
            {
                cout << "[" << i << "][" << j << "] = " << letters[i][j] << endl;
            }
        }
    }
}

// MAIN
int main()
{
    Cancion *listaCanciones = leerArchivo("canciones.txt");
    cout << "Ruta actual: " << std::filesystem::current_path() << endl;
    if (!listaCanciones)
    {
        cerr << "No se pudieron leer las canciones." << endl;
        return 1;
    }

    imprimirCanciones(listaCanciones);
    mostrarArreglo();

    return 0;
}
