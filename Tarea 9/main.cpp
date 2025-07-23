#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdexcept>
using namespace std;

// DEFINICIÓN DE ESTRUCTURAS
struct Significado
{
    int id;
    char texto[100];
    Significado *siguiente;
    Significado *anterior;
};

struct Sinonimo
{
    int id;
    char texto[60];
    Sinonimo *siguiente;
    Sinonimo *anterior;
};

struct Antonimo
{
    int id;
    char texto[60];
    Antonimo *siguiente;
    Antonimo *anterior;
};

struct Palabra
{
    int id;
    char palabra[60];

    Significado *primerSignificado;
    Significado *ultimoSignificado;

    Sinonimo *primerSinonimo;
    Sinonimo *ultimoSinonimo;

    Antonimo *primerAntonimo;
    Antonimo *ultimoAntonimo;

    Palabra *siguiente;
    Palabra *anterior;
};

// VARIABLES GLOBALES (DESPUÉS de las estructuras)
int contadorIdentificador = 1;
Palabra *primeraPalabra = nullptr;
Palabra *ultimaPalabra = nullptr;

// ---------- DECLARACIÓN DE FUNCIONES -----------

// Operaciones para la palabra
void agregarPalabra();
void eliminarPalabra();

// Operaciones para el significado
void agregarSignificado();
void eliminarSignificado();

// Operaciones para sinónimos
void agregarSinonimo();
void eliminarSinonimo();

// Operaciones para antónimos
void agregarAntonimo();
void eliminarAntonimo();

// Operaciones de búsqueda
void buscarPalabra();
void mostrarPalabra(Palabra *p);
Palabra *buscarPalabraPorId(int id);
Palabra *buscarPalabraPorTexto(const char *texto);

// Operaciones de visualización y archivo
void guardarArchivo();
void cargarArchivo();
void mostrarMenu();
void mostrarTodasPalabras();

// Funciones auxiliares
void inicializarPunterosPalabra(Palabra *palabra);
void liberarSignificados(Palabra *palabra);
void liberarSinonimos(Palabra *palabra);
void liberarAntonimos(Palabra *palabra);
void liberarPalabra(Palabra *palabra);
void agregarPalabraAlInicio(Palabra *nuevaPalabra);
void agregarPalabraAlFinal(Palabra *nuevaPalabra);
void removerPalabraDeLista(Palabra *palabraEliminar);
void limpiarBuffer();
void pausar();
void executeOptions();
template <typename T>
void agregarNodoHorizontal(T **primero, T **ultimo, T *nuevoNodo);
template <typename T>
T *eliminarPrimerNodoHorizontal(T **primero, T **ultimo);
Palabra *obtenerPalabraParaOperacion();

// ---------- IMPLEMENTACIÓN DE FUNCIONES -----------

// ========== FUNCIONES AUXILIARES ==========
void inicializarPunterosPalabra(Palabra *palabra)
{
    if (palabra == nullptr)
        return;

    palabra->primerSignificado = nullptr;
    palabra->ultimoSignificado = nullptr;
    palabra->primerSinonimo = nullptr;
    palabra->ultimoSinonimo = nullptr;
    palabra->primerAntonimo = nullptr;
    palabra->ultimoAntonimo = nullptr;
    palabra->siguiente = nullptr;
    palabra->anterior = nullptr;
}

template <typename T>
void liberarLista(T *&inicio)
{
    while (inicio != nullptr)
    {
        T *temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
    }
}

void liberarSignificados(Palabra *palabra)
{
    if (palabra == nullptr)
        return;
    liberarLista(palabra->primerSignificado);
    palabra->ultimoSignificado = nullptr;
}

void liberarSinonimos(Palabra *palabra)
{
    if (palabra == nullptr)
        return;
    liberarLista(palabra->primerSinonimo);
    palabra->ultimoSinonimo = nullptr;
}

void liberarAntonimos(Palabra *palabra)
{
    if (palabra == nullptr)
        return;
    liberarLista(palabra->primerAntonimo);
    palabra->ultimoAntonimo = nullptr;
}

void liberarPalabra(Palabra *palabra)
{
    if (palabra == nullptr)
        return;
    liberarSignificados(palabra);
    liberarSinonimos(palabra);
    liberarAntonimos(palabra);
    delete palabra;
}

void mostrarMensajeNoHayPalabras()
{
    cout << "No hay palabras en el diccionario." << endl;
    pausar();
}

void pausar()
{
    cout << "Presione Enter para continuar...";
    cin.ignore(1000, '\n');
    cin.get();
}

void agregarPalabraAlInicio(Palabra *nuevaPalabra)
{
    if (nuevaPalabra == nullptr)
        return;

    if (primeraPalabra == nullptr)
    {
        primeraPalabra = nuevaPalabra;
        ultimaPalabra = nuevaPalabra;
    }
    else
    {
        nuevaPalabra->siguiente = primeraPalabra;
        primeraPalabra->anterior = nuevaPalabra;
        primeraPalabra = nuevaPalabra;
    }
}

void agregarPalabraAlFinal(Palabra *nuevaPalabra)
{
    if (nuevaPalabra == nullptr)
        return;

    if (primeraPalabra == nullptr)
    {
        primeraPalabra = nuevaPalabra;
        ultimaPalabra = nuevaPalabra;
    }
    else
    {
        ultimaPalabra->siguiente = nuevaPalabra;
        nuevaPalabra->anterior = ultimaPalabra;
        ultimaPalabra = nuevaPalabra;
    }
}

void removerPalabraDeLista(Palabra *palabraEliminar)
{
    if (palabraEliminar == nullptr)
        return;

    if (palabraEliminar->anterior != nullptr)
    {
        palabraEliminar->anterior->siguiente = palabraEliminar->siguiente;
    }
    else
    {
        primeraPalabra = palabraEliminar->siguiente;
    }

    if (palabraEliminar->siguiente != nullptr)
    {
        palabraEliminar->siguiente->anterior = palabraEliminar->anterior;
    }
    else
    {
        ultimaPalabra = palabraEliminar->anterior;
    }
}

template <typename T>
void agregarNodoHorizontal(T **primero, T **ultimo, T *nuevoNodo)
{
    if (nuevoNodo == nullptr)
        return;

    nuevoNodo->siguiente = nullptr;
    nuevoNodo->anterior = nullptr;

    if (*primero == nullptr)
    {
        *primero = nuevoNodo;
        *ultimo = nuevoNodo;
    }
    else
    {
        nuevoNodo->siguiente = *primero;
        (*primero)->anterior = nuevoNodo;
        *primero = nuevoNodo;
    }
}

template <typename T>
T *eliminarPrimerNodoHorizontal(T **primero, T **ultimo)
{
    if (*primero == nullptr)
    {
        return nullptr;
    }

    T *nodoEliminar = *primero;
    *primero = nodoEliminar->siguiente;

    if (*primero != nullptr)
    {
        (*primero)->anterior = nullptr;
    }
    else
    {
        *ultimo = nullptr;
    }

    return nodoEliminar;
}

void limpiarBuffer()
{
    while (cin.peek() == '\n')
    {
        cin.ignore();
    }
}

Palabra *obtenerPalabraParaOperacion()
{
    if (primeraPalabra == nullptr)
    {
        cout << "No hay palabras disponibles. Agregue una palabra primero." << endl;
        pausar();
        return nullptr;
    }

    cout << "Palabras disponibles:" << endl;
    mostrarTodasPalabras();

    int idPalabra;
    cout << "Ingrese el ID de la palabra: ";
    cin >> idPalabra;

    Palabra *palabra = buscarPalabraPorId(idPalabra);
    if (palabra == nullptr)
    {
        cout << "Palabra no encontrada." << endl;
        pausar();
    }

    return palabra;
}

// ========== OPERACIONES PRINCIPALES ==========
void agregarPalabra()
{
    Palabra *nuevaPalabra = new Palabra;
    nuevaPalabra->id = contadorIdentificador++;

    cout << "Ingrese la palabra: ";
    limpiarBuffer();
    cin.getline(nuevaPalabra->palabra, 60);

    inicializarPunterosPalabra(nuevaPalabra);
    agregarPalabraAlInicio(nuevaPalabra);

    cout << "Palabra agregada con ID: " << nuevaPalabra->id << endl;
    pausar();
}

void eliminarPalabra()
{
    if (primeraPalabra == nullptr)
    {
        mostrarMensajeNoHayPalabras();
        return;
    }

    cout << "Palabras disponibles:" << endl;
    mostrarTodasPalabras();

    int id;
    cout << "Ingrese el ID de la palabra a eliminar: ";
    cin >> id;

    Palabra *palabraEliminar = buscarPalabraPorId(id);
    if (palabraEliminar == nullptr)
    {
        cout << "Palabra no encontrada." << endl;
        pausar();
        return;
    }

    removerPalabraDeLista(palabraEliminar);
    liberarPalabra(palabraEliminar);

    cout << "Palabra eliminada exitosamente." << endl;
    pausar();
}

void agregarSignificado()
{
    Palabra *palabra = obtenerPalabraParaOperacion();
    if (palabra == nullptr)
    {
        return;
    }

    Significado *nuevoSignificado = new Significado;
    nuevoSignificado->id = contadorIdentificador++;

    cout << "Ingrese el significado: ";
    limpiarBuffer();
    cin.getline(nuevoSignificado->texto, 100);

    agregarNodoHorizontal(&palabra->primerSignificado, &palabra->ultimoSignificado, nuevoSignificado);

    cout << "Significado agregado exitosamente." << endl;
    pausar();
}

void eliminarSignificado()
{
    Palabra *palabra = obtenerPalabraParaOperacion();
    if (palabra == nullptr)
    {
        return;
    }

    if (palabra->primerSignificado == nullptr)
    {
        cout << "No hay significados para eliminar." << endl;
        pausar();
        return;
    }

    Significado *significadoEliminar = eliminarPrimerNodoHorizontal(&palabra->primerSignificado, &palabra->ultimoSignificado);

    cout << "Significado eliminado: " << significadoEliminar->texto << endl;
    delete significadoEliminar;
    pausar();
}

void agregarSinonimo()
{
    Palabra *palabra = obtenerPalabraParaOperacion();
    if (palabra == nullptr)
    {
        return;
    }

    Sinonimo *nuevoSinonimo = new Sinonimo;
    nuevoSinonimo->id = contadorIdentificador++;

    cout << "Ingrese el sinónimo: ";
    limpiarBuffer();
    cin.getline(nuevoSinonimo->texto, 60);

    agregarNodoHorizontal(&palabra->primerSinonimo, &palabra->ultimoSinonimo, nuevoSinonimo);

    cout << "Sinónimo agregado exitosamente." << endl;
    pausar();
}

void eliminarSinonimo()
{
    Palabra *palabra = obtenerPalabraParaOperacion();
    if (palabra == nullptr)
    {
        return;
    }

    if (palabra->primerSinonimo == nullptr)
    {
        cout << "No hay sinónimos para eliminar." << endl;
        pausar();
        return;
    }

    Sinonimo *sinonimoEliminar = eliminarPrimerNodoHorizontal(&palabra->primerSinonimo, &palabra->ultimoSinonimo);

    cout << "Sinónimo eliminado: " << sinonimoEliminar->texto << endl;
    delete sinonimoEliminar;
    pausar();
}

void agregarAntonimo()
{
    Palabra *palabra = obtenerPalabraParaOperacion();
    if (palabra == nullptr)
    {
        return;
    }

    Antonimo *nuevoAntonimo = new Antonimo;
    nuevoAntonimo->id = contadorIdentificador++;

    cout << "Ingrese el antónimo: ";
    limpiarBuffer();
    cin.getline(nuevoAntonimo->texto, 60);

    agregarNodoHorizontal(&palabra->primerAntonimo, &palabra->ultimoAntonimo, nuevoAntonimo);

    cout << "Antónimo agregado exitosamente." << endl;
    pausar();
}

void eliminarAntonimo()
{
    Palabra *palabra = obtenerPalabraParaOperacion();
    if (palabra == nullptr)
    {
        return;
    }

    if (palabra->primerAntonimo == nullptr)
    {
        cout << "No hay antónimos para eliminar." << endl;
        pausar();
        return;
    }

    Antonimo *antonimoEliminar = eliminarPrimerNodoHorizontal(&palabra->primerAntonimo, &palabra->ultimoAntonimo);

    cout << "Antónimo eliminado: " << antonimoEliminar->texto << endl;
    delete antonimoEliminar;
    pausar();
}

void buscarPalabra()
{
    if (primeraPalabra == nullptr)
    {
        cout << "No hay palabras en el diccionario." << endl;
        pausar();
        return;
    }

    char textoBuscar[60];
    cout << "Ingrese la palabra a buscar: ";
    limpiarBuffer();
    cin.getline(textoBuscar, 60);

    Palabra *palabraEncontrada = buscarPalabraPorTexto(textoBuscar);
    if (palabraEncontrada != nullptr)
    {
        mostrarPalabra(palabraEncontrada);
    }
    else
    {
        cout << "Palabra no encontrada." << endl;
    }
    pausar();
}

void mostrarPalabra(Palabra *p)
{
    if (p == nullptr)
        return;

    cout << "\n========================================" << endl;
    cout << "ID: " << p->id << " | Palabra: " << p->palabra << endl;
    cout << "========================================" << endl;

    cout << "SIGNIFICADOS:" << endl;
    Significado *sig = p->primerSignificado;
    if (sig == nullptr)
    {
        cout << "  - No hay significados registrados." << endl;
    }
    else
    {
        while (sig != nullptr)
        {
            cout << "  - " << sig->texto << endl;
            sig = sig->siguiente;
        }
    }

    cout << "\nSINONIMOS:" << endl;
    Sinonimo *sin = p->primerSinonimo;
    if (sin == nullptr)
    {
        cout << "  - No hay sinonimos registrados." << endl;
    }
    else
    {
        while (sin != nullptr)
        {
            cout << "  - " << sin->texto << endl;
            sin = sin->siguiente;
        }
    }

    cout << "\nANTONIMOS:" << endl;
    Antonimo *ant = p->primerAntonimo;
    if (ant == nullptr)
    {
        cout << "  - No hay antonimos registrados." << endl;
    }
    else
    {
        while (ant != nullptr)
        {
            cout << "  - " << ant->texto << endl;
            ant = ant->siguiente;
        }
    }
    cout << "========================================\n"
         << endl;
}

Palabra *buscarPalabraPorId(int id)
{
    Palabra *actual = primeraPalabra;
    while (actual != nullptr)
    {
        if (actual->id == id)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

Palabra *buscarPalabraPorTexto(const char *texto)
{
    if (texto == nullptr)
        return nullptr;

    Palabra *actual = primeraPalabra;
    while (actual != nullptr)
    {
        if (strcmp(actual->palabra, texto) == 0)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void mostrarTodasPalabras()
{
    if (primeraPalabra == nullptr)
    {
        cout << "No hay palabras en el diccionario." << endl;
        pausar();
        return;
    }

    Palabra *actual = primeraPalabra;
    while (actual != nullptr)
    {
        cout << "ID: " << actual->id << " - " << actual->palabra << endl;
        actual = actual->siguiente;
    }
    pausar();
}

void guardarArchivo()
{
    ofstream archivo("diccionario.txt");
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para escritura." << endl;
        pausar();
        return;
    }

    // Guardar contador
    archivo << contadorIdentificador << endl;

    Palabra *palabraActual = primeraPalabra;
    while (palabraActual != nullptr)
    {
        archivo << "PALABRA:" << palabraActual->id << ":" << palabraActual->palabra << endl;

        Significado *sig = palabraActual->primerSignificado;
        while (sig != nullptr)
        {
            archivo << "SIGNIFICADO:" << sig->id << ":" << sig->texto << endl;
            sig = sig->siguiente;
        }

        Sinonimo *sin = palabraActual->primerSinonimo;
        while (sin != nullptr)
        {
            archivo << "SINONIMO:" << sin->id << ":" << sin->texto << endl;
            sin = sin->siguiente;
        }

        Antonimo *ant = palabraActual->primerAntonimo;
        while (ant != nullptr)
        {
            archivo << "ANTONIMO:" << ant->id << ":" << ant->texto << endl;
            ant = ant->siguiente;
        }

        archivo << "FIN_PALABRA" << endl;
        palabraActual = palabraActual->siguiente;
    }

    archivo.close();
    cout << "Datos guardados exitosamente en 'diccionario.txt'." << endl;
    pausar();
}

void cargarArchivo()
{
    ifstream archivo("diccionario.txt");
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo 'diccionario.txt'. Comenzando con diccionario vacío." << endl;
        pausar();
        return;
    }

    while (primeraPalabra != nullptr)
    {
        Palabra *palabraTemp = primeraPalabra;
        primeraPalabra = primeraPalabra->siguiente;
        liberarPalabra(palabraTemp);
    }
    ultimaPalabra = nullptr;

    try
    {
        archivo >> contadorIdentificador;
        archivo.ignore();

        string linea;
        Palabra *palabraActual = nullptr;

        while (getline(archivo, linea))
        {
            if (linea.find("PALABRA:") == 0)
            {
                palabraActual = new Palabra;

                size_t pos1 = linea.find(':', 8);
                if (pos1 == string::npos)
                {
                    delete palabraActual;
                    palabraActual = nullptr;
                    continue;
                }

                string idStr = linea.substr(8, pos1 - 8);
                string palabraStr = linea.substr(pos1 + 1);

                palabraActual->id = stoi(idStr);
                strncpy(palabraActual->palabra, palabraStr.c_str(), 59);
                palabraActual->palabra[59] = '\0';

                inicializarPunterosPalabra(palabraActual);
                agregarPalabraAlFinal(palabraActual);
            }
            else if (linea.find("SIGNIFICADO:") == 0 && palabraActual != nullptr)
            {
                Significado *nuevoSig = new Significado;
                size_t pos1 = linea.find(':', 12);
                if (pos1 == string::npos)
                {
                    delete nuevoSig;
                    continue;
                }

                string idStr = linea.substr(12, pos1 - 12);
                string textoStr = linea.substr(pos1 + 1);

                nuevoSig->id = stoi(idStr);
                strncpy(nuevoSig->texto, textoStr.c_str(), 99);
                nuevoSig->texto[99] = '\0';

                agregarNodoHorizontal(&palabraActual->primerSignificado,
                                      &palabraActual->ultimoSignificado,
                                      nuevoSig);
            }
            else if (linea.find("SINONIMO:") == 0 && palabraActual != nullptr)
            {
                Sinonimo *nuevoSin = new Sinonimo;
                size_t pos1 = linea.find(':', 9);
                if (pos1 == string::npos)
                {
                    delete nuevoSin;
                    continue;
                }

                string idStr = linea.substr(9, pos1 - 9);
                string textoStr = linea.substr(pos1 + 1);

                nuevoSin->id = stoi(idStr);
                strncpy(nuevoSin->texto, textoStr.c_str(), 59);
                nuevoSin->texto[59] = '\0';

                agregarNodoHorizontal(&palabraActual->primerSinonimo,
                                      &palabraActual->ultimoSinonimo,
                                      nuevoSin);
            }
            else if (linea.find("ANTONIMO:") == 0 && palabraActual != nullptr)
            {
                Antonimo *nuevoAnt = new Antonimo;
                size_t pos1 = linea.find(':', 9);
                if (pos1 == string::npos)
                {
                    delete nuevoAnt;
                    continue;
                }

                string idStr = linea.substr(9, pos1 - 9);
                string textoStr = linea.substr(pos1 + 1);

                nuevoAnt->id = stoi(idStr);
                strncpy(nuevoAnt->texto, textoStr.c_str(), 59);
                nuevoAnt->texto[59] = '\0';

                agregarNodoHorizontal(&palabraActual->primerAntonimo,
                                      &palabraActual->ultimoAntonimo,
                                      nuevoAnt);
            }
        }
    }
    catch (const exception &e)
    {
        cout << "Error al cargar archivo: " << e.what() << endl;
        cout << "Algunos datos pueden no haberse cargado correctamente." << endl;
    }

    archivo.close();
    cout << "Datos cargados exitosamente desde 'diccionario.txt'." << endl;
    pausar();
}

void mostrarMenu()
{
    cout << "\n======== DICCIONARIO DINAMICO ========" << endl;
    cout << "1. Agregar palabra" << endl;
    cout << "2. Eliminar palabra" << endl;
    cout << "3. Agregar significado" << endl;
    cout << "4. Eliminar significado" << endl;
    cout << "5. Agregar sinónimo" << endl;
    cout << "6. Eliminar sinonimo" << endl;
    cout << "7. Agregar antonimo" << endl;
    cout << "8. Eliminar antónimo" << endl;
    cout << "9. Buscar palabra" << endl;
    cout << "10. Mostrar todas las palabras" << endl;
    cout << "11. Guardar en archivo" << endl;
    cout << "12. Cargar desde archivo" << endl;
    cout << "0. Salir" << endl;
    cout << "=======================================" << endl;
    cout << "Seleccione una opción: ";
}

int main()
{
    cout << "Inicializando diccionario dinamico..." << endl;
    cout << "Inicie con una palabra para continuar..." << endl;
    cargarArchivo();

    int opcion;
    do
    {
        mostrarMenu();
        cin >> opcion;

        // Validar entrada
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada inválida. Por favor ingrese un número." << endl;
            pausar();
            continue;
        }

        switch (opcion)
        {
        case 1:
            agregarPalabra();
            break;
        case 2:
            eliminarPalabra();
            break;
        case 3:
            agregarSignificado();
            break;
        case 4:
            eliminarSignificado();
            break;
        case 5:
            agregarSinonimo();
            break;
        case 6:
            eliminarSinonimo();
            break;
        case 7:
            agregarAntonimo();
            break;
        case 8:
            eliminarAntonimo();
            break;
        case 9:
            buscarPalabra();
            break;
        case 10:
            mostrarTodasPalabras();
            break;
        case 11:
            guardarArchivo();
            break;
        case 12:
            cargarArchivo();
            break;
        case 0:
            cout << "Guardando datos antes de salir..." << endl;
            guardarArchivo();
            cout << "¡Hasta luego!" << endl;
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            pausar();
        }
    } while (opcion != 0);

    // Liberación de memoria
    while (primeraPalabra != nullptr)
    {
        Palabra *temp = primeraPalabra;
        primeraPalabra = primeraPalabra->siguiente;
        liberarPalabra(temp);
    }

    return 0;
}