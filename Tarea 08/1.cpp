#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
using namespace std;

const int TAMAÑO_TABLA = 17; // Número primo para mejor distribución
const string NOMBRE_ARCHIVO = "tabla_hash.dat";

struct Libro
{
    char codigo[20];
    char autor[50];
    char titulo[100];
    bool activo; // Para marcar si el registro está activo

    Libro()
    {
        strcpy(codigo, "");
        strcpy(autor, "");
        strcpy(titulo, "");
        activo = false;
    }

    bool estaVacio() const
    {
        return strlen(codigo) == 0 || !activo;
    }
};

class TablaHash
{
private:
    fstream archivo;

    void inicializarArchivo()
    {
        archivo.open(NOMBRE_ARCHIVO, ios::binary | ios::out);
        if (archivo.is_open())
        {
            Libro libroVacio;
            for (int i = 0; i < TAMAÑO_TABLA; i++)
            {
                archivo.write(reinterpret_cast<char *>(&libroVacio), sizeof(Libro));
            }
            archivo.close();
        }
    }

public:
    TablaHash()
    {
        // Verificar si el archivo existe
        ifstream test(NOMBRE_ARCHIVO);
        if (!test.good())
        {
            inicializarArchivo();
        }
        test.close();
    }

    int transformarClave(const string &codigo)
    {
        int suma = 0;
        cout << "\n--- Proceso de Transformación de Clave ---" << endl;
        cout << "Código: " << codigo << endl;

        // Sumar valores ASCII de cada carácter
        for (int i = 0; i < codigo.length(); i++)
        {
            suma += (int)codigo[i];
            cout << "Carácter '" << codigo[i] << "' = " << (int)codigo[i] << endl;
        }

        cout << "Suma total: " << suma << endl;

        int d = suma % TAMAÑO_TABLA;
        cout << "d = " << suma << " % " << TAMAÑO_TABLA << " = " << d << endl;
        cout << "Posición inicial calculada: " << d << endl;
        cout << "----------------------------------------" << endl;

        return d;
    }

    bool insertar(const string &codigo, const string &autor, const string &titulo)
    {
        int posicion = transformarClave(codigo);
        int posicionOriginal = posicion;
        int intentos = 0;

        archivo.open(NOMBRE_ARCHIVO, ios::binary | ios::in | ios::out);
        if (!archivo.is_open())
        {
            cout << "Error al abrir el archivo" << endl;
            return false;
        }

        Libro libro;

        do
        {
            // Leer el registro en la posición actual
            archivo.seekg(posicion * sizeof(Libro));
            archivo.read(reinterpret_cast<char *>(&libro), sizeof(Libro));

            // Si la posición está vacía o el registro está inactivo
            if (libro.estaVacio())
            {
                // Crear nuevo libro
                Libro nuevoLibro;
                strcpy(nuevoLibro.codigo, codigo.c_str());
                strcpy(nuevoLibro.autor, autor.c_str());
                strcpy(nuevoLibro.titulo, titulo.c_str());
                nuevoLibro.activo = true;

                // Escribir en el archivo
                archivo.seekp(posicion * sizeof(Libro));
                archivo.write(reinterpret_cast<char *>(&nuevoLibro), sizeof(Libro));

                cout << "Libro insertado en posición: " << posicion << endl;
                archivo.close();
                return true;
            }

            // Si el código ya existe (y está activo)
            if (strcmp(libro.codigo, codigo.c_str()) == 0 && libro.activo)
            {
                cout << "El código ya existe en la tabla" << endl;
                archivo.close();
                return false;
            }

            // Sondeo lineal
            posicion = (posicion + 1) % TAMAÑO_TABLA;
            intentos++;

        } while (posicion != posicionOriginal && intentos < TAMAÑO_TABLA);

        cout << "Tabla hash llena" << endl;
        archivo.close();
        return false;
    }

    bool buscar(const string &codigo)
    {
        int posicion = transformarClave(codigo);
        int posicionOriginal = posicion;
        int intentos = 0;

        archivo.open(NOMBRE_ARCHIVO, ios::binary | ios::in);
        if (!archivo.is_open())
        {
            cout << "Error al abrir el archivo" << endl;
            return false;
        }

        Libro libro;

        do
        {
            archivo.seekg(posicion * sizeof(Libro));
            archivo.read(reinterpret_cast<char *>(&libro), sizeof(Libro));

            // Si encontramos el código y está activo
            if (strcmp(libro.codigo, codigo.c_str()) == 0 && libro.activo)
            {
                cout << "\n--- Libro Encontrado ---" << endl;
                cout << "Posición: " << posicion << endl;
                cout << "Código: " << libro.codigo << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Título: " << libro.titulo << endl;
                cout << "------------------------" << endl;
                archivo.close();
                return true;
            }

            // Si la posición está vacía, no existe
            if (libro.estaVacio())
            {
                break;
            }

            posicion = (posicion + 1) % TAMAÑO_TABLA;
            intentos++;

        } while (posicion != posicionOriginal && intentos < TAMAÑO_TABLA);

        cout << "Libro no encontrado" << endl;
        archivo.close();
        return false;
    }

    bool eliminar(const string &codigo)
    {
        int posicion = transformarClave(codigo);
        int posicionOriginal = posicion;
        int intentos = 0;

        archivo.open(NOMBRE_ARCHIVO, ios::binary | ios::in | ios::out);
        if (!archivo.is_open())
        {
            cout << "Error al abrir el archivo" << endl;
            return false;
        }

        Libro libro;

        do
        {
            archivo.seekg(posicion * sizeof(Libro));
            archivo.read(reinterpret_cast<char *>(&libro), sizeof(Libro));

            // Si encontramos el código y está activo
            if (strcmp(libro.codigo, codigo.c_str()) == 0 && libro.activo)
            {
                // Marcar como inactivo (borrado lógico)
                libro.activo = false;

                archivo.seekp(posicion * sizeof(Libro));
                archivo.write(reinterpret_cast<char *>(&libro), sizeof(Libro));

                cout << "Libro eliminado de la posición: " << posicion << endl;
                archivo.close();
                return true;
            }

            // Si la posición está vacía, no existe
            if (libro.estaVacio())
            {
                break;
            }

            posicion = (posicion + 1) % TAMAÑO_TABLA;
            intentos++;

        } while (posicion != posicionOriginal && intentos < TAMAÑO_TABLA);

        cout << "Libro no encontrado para eliminar" << endl;
        archivo.close();
        return false;
    }

    void desplegarTodo()
    {
        archivo.open(NOMBRE_ARCHIVO, ios::binary | ios::in);
        if (!archivo.is_open())
        {
            cout << "Error al abrir el archivo" << endl;
            return;
        }

        cout << "\n=== CONTENIDO DE LA TABLA HASH ===" << endl;
        cout << left << setw(10) << "Posición"
             << setw(15) << "Código"
             << setw(25) << "Autor"
             << setw(35) << "Título" << endl;
        cout << string(85, '-') << endl;

        Libro libro;
        int registrosActivos = 0;

        for (int i = 0; i < TAMAÑO_TABLA; i++)
        {
            archivo.seekg(i * sizeof(Libro));
            archivo.read(reinterpret_cast<char *>(&libro), sizeof(Libro));

            // Solo mostrar registros activos (no vacíos ni eliminados)
            if (!libro.estaVacio())
            {
                cout << left << setw(10) << i
                     << setw(15) << libro.codigo
                     << setw(25) << libro.autor
                     << setw(35) << libro.titulo << endl;
                registrosActivos++;
            }
        }

        if (registrosActivos == 0)
        {
            cout << "No hay registros activos en la tabla hash." << endl;
        }
        else
        {
            cout << string(85, '-') << endl;
            cout << "Total de registros activos: " << registrosActivos << endl;
        }

        archivo.close();
    }

    void insertarLibrosPredefinidos()
    {
        cout << "\nInsertando libros predefinidos..." << endl;

        // Insertar 10 libros con códigos alfabéticos
        insertar("LIB001", "Gabriel García Márquez", "Cien años de soledad");
        insertar("LIB002", "Mario Vargas Llosa", "La ciudad y los perros");
        insertar("LIB003", "Isabel Allende", "La casa de los espíritus");
        insertar("LIB004", "Jorge Luis Borges", "El Aleph");
        insertar("LIB005", "Octavio Paz", "El laberinto de la soledad");
        insertar("LIB006", "Carlos Fuentes", "La muerte de Artemio Cruz");
        insertar("LIB007", "Julio Cortázar", "Rayuela");
        insertar("LIB008", "Pablo Neruda", "Veinte poemas de amor");
        insertar("LIB009", "Laura Esquivel", "Como agua para chocolate");
        insertar("LIB010", "Roberto Bolaño", "Los detectives salvajes");

        cout << "Libros predefinidos insertados correctamente." << endl;
    }
};

void mostrarMenu()
{
    cout << "\n=== SISTEMA DE GESTIÓN DE LIBROS (HASH CON ARCHIVOS) ===" << endl;
    cout << "1. Insertar libro" << endl;
    cout << "2. Buscar libro" << endl;
    cout << "3. Eliminar libro" << endl;
    cout << "4. Mostrar todos los libros" << endl;
    cout << "5. Insertar libros predefinidos" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main()
{
    TablaHash tabla;
    int opcion;
    string codigo, autor, titulo;

    do
    {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        switch (opcion)
        {
        case 1:
            cout << "\n--- Insertar Libro ---" << endl;
            cout << "Ingrese código: ";
            getline(cin, codigo);
            cout << "Ingrese autor: ";
            getline(cin, autor);
            cout << "Ingrese título: ";
            getline(cin, titulo);
            tabla.insertar(codigo, autor, titulo);
            break;

        case 2:
            cout << "\n--- Buscar Libro ---" << endl;
            cout << "Ingrese código a buscar: ";
            getline(cin, codigo);
            tabla.buscar(codigo);
            break;

        case 3:
            cout << "\n--- Eliminar Libro ---" << endl;
            cout << "Ingrese código a eliminar: ";
            getline(cin, codigo);
            tabla.eliminar(codigo);
            break;

        case 4:
            tabla.desplegarTodo();
            break;

        case 5:
            tabla.insertarLibrosPredefinidos();
            break;

        case 6:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opción no válida" << endl;
        }

    } while (opcion != 6);

    return 0;
}