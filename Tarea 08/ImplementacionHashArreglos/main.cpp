#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

// PASO 1: DEFINIR CONSTANTES
#define TOTAL_REGISTROS 240       // Total de posiciones en la tabla
#define AREA_HASH 199             // Posiciones de la zona principal
#define INICIO_DESBORDAMIENTO 199 // Inicio del área de desbordamiento
#define FIN_DESBORDAMIENTO 239    // Fin del área de desbordamiento

// PASO 2: DEFINIR LA ESTRUCTURA DEL LIBRO
typedef struct
{
    char codigo[7];  // Código del libro
    char autor[41];  // Autor
    char titulo[41]; // Título
    bool borrado;    // Soft delete bandera
} Libro;

// PASO 3: DECLARAR LA TABLA HASH GLOBAL
Libro TablaHash[TOTAL_REGISTROS];

// PASO 4: PERSISTENCIA
const char *ARCHIVO_TABLA = "tabla_hash.dat"; // Nombre del archivo para guardar la tabla

// Declaración de funciones
void mostrarMenu();
void ejecutarPrograma();

// 1 : INICIALIZAR LA TABLA HASH
void creacion()
{
    Libro vacio = {"*", "", "", false}; // Inicializar con valores por defecto
    for (int i = 0; i < TOTAL_REGISTROS; i++)
    {
        TablaHash[i] = vacio; // Asignar el libro vacío a cada posición
    }
}

// 2: FUNCIÓN HASH MODIFICADA
int Transformar_Clave(const char *codigo)
{
    int hash = 0;
    cout << "\n--- Proceso de Transformacion de Clave ---" << endl;
    cout << "Codigo: " << codigo << endl;

    for (int i = 0; codigo[i] != '\0'; i++)
    {
        int valor_ascii = (int)codigo[i];
        hash += valor_ascii;
        cout << "Caracter '" << codigo[i] << "' = " << valor_ascii << endl;
    }

    cout << "Suma total: " << hash << endl;

    int d = hash % AREA_HASH;
    cout << "Valor de 'd' = " << hash << " % " << AREA_HASH << " = " << d << endl;
    cout << "Posicion calculada: " << d << endl;
    cout << "----------------------------------------" << endl;

    return d;
}

// 3: FUNCIÓN Guardar Tabla
void guardarTabla()
{
    ofstream archivo(ARCHIVO_TABLA, ios::binary);
    if (archivo.is_open())
    {
        archivo.write(reinterpret_cast<char *>(TablaHash), sizeof(TablaHash));
        archivo.close();
        cout << "Tabla guardada exitosamente en: " << ARCHIVO_TABLA << endl;
    }
    else
    {
        cout << "Error al guardar la tabla en archivo." << endl;
    }
}

// 4.0 Encontrar los elementos cargados
void contarElementosCargados()
{
    int elementosActivos = 0;
    for (int i = 0; i < TOTAL_REGISTROS; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") != 0 && !TablaHash[i].borrado)
            elementosActivos++;
    }
    cout << "Elementos activos encontrados: " << elementosActivos << endl;
}

// 4.1 FUNCIÓN Cargar Tabla
void cargarTabla()
{
    ifstream archivo(ARCHIVO_TABLA, ios::binary);
    if (archivo.is_open())
    {
        archivo.read(reinterpret_cast<char *>(TablaHash), sizeof(TablaHash));
        archivo.close();
        cout << "Tabla cargada exitosamente desde: " << ARCHIVO_TABLA << endl;
        contarElementosCargados();
    }
    else
    {
        cout << "Error al cargar la tabla desde archivo." << endl;
    }
}

// 5: FUNCIÓN Verificar si un código ya existe
bool codigoExiste(const char *codigo)
{
    int pos = Transformar_Clave(codigo);
    if (strcmp(TablaHash[pos].codigo, codigo) == 0 && !TablaHash[pos].borrado)
        return true;

    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, codigo) == 0 && !TablaHash[i].borrado)
            return true;
    }
    return false;
}

// Buscar en área de desbordamiento
int buscarDesbordamiento(const char *codigo)
{
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, codigo) == 0 && !TablaHash[i].borrado)
        {
            return i;
        }
    }
    return -1; // No encontrado
}

// Encontrar posición libre en área de desbordamiento
int encontrarPosicionLibreDesbordamiento()
{
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") == 0 || TablaHash[i].borrado)
        {
            return i;
        }
    }
    return -1; // No hay espacio disponible
}

// 6. FUNCIÓN Insertar en tabla hash
void insertar(Libro nuevoLibro)
{
    if (codigoExiste(nuevoLibro.codigo))
    {
        cout << "Error: El codigo '" << nuevoLibro.codigo << "' ya existe en la tabla." << endl;
        return;
    }

    int pos = Transformar_Clave(nuevoLibro.codigo);

    // Intentar insertar en la posición calculada
    if (strcmp(TablaHash[pos].codigo, "*") == 0 || TablaHash[pos].borrado)
    {
        TablaHash[pos] = nuevoLibro;
        TablaHash[pos].borrado = false;
        cout << "Libro insertado en la posicion " << pos << endl;
        guardarTabla();
        return;
    }

    // Colision detectada, buscar en area de desbordamiento
    cout << "Colision detectada en posicion " << pos << ". Buscando en area de desbordamiento..." << endl;

    int posDesbordamiento = encontrarPosicionLibreDesbordamiento();
    if (posDesbordamiento != -1)
    {
        TablaHash[posDesbordamiento] = nuevoLibro;
        TablaHash[posDesbordamiento].borrado = false;
        cout << "Libro insertado en area de desbordamiento, posicion " << posDesbordamiento << endl;
        guardarTabla();
    }
    else
    {
        cout << "Error: No hay espacio disponible en el area de desbordamiento." << endl;
    }
}

// 7: FUNCIÓN Buscar libro
void buscar(const char *codigo)
{
    int pos = Transformar_Clave(codigo);

    // Buscar en la posición calculada
    if (strcmp(TablaHash[pos].codigo, codigo) == 0 && !TablaHash[pos].borrado)
    {
        cout << "\nLibro encontrado en zona principal [" << pos << "]:" << endl;
        cout << "Codigo: " << TablaHash[pos].codigo << endl;
        cout << "Autor: " << TablaHash[pos].autor << endl;
        cout << "Titulo: " << TablaHash[pos].titulo << endl;
        return;
    }

    // Buscar en area de desbordamiento
    int desbordamientoPos = buscarDesbordamiento(codigo);
    if (desbordamientoPos != -1)
    {
        cout << "\nLibro encontrado en area de desbordamiento [" << desbordamientoPos << "]:" << endl;
        cout << "Codigo: " << TablaHash[desbordamientoPos].codigo << endl;
        cout << "Autor: " << TablaHash[desbordamientoPos].autor << endl;
        cout << "Titulo: " << TablaHash[desbordamientoPos].titulo << endl;
        return;
    }

    cout << "\nLibro con codigo '" << codigo << "' no encontrado." << endl;
}

// 8: FUNCIÓN Desplegar Todo
void DesplegarTodo()
{
    int count = 0;

    cout << "\n=== LIBROS EN ZONA PRINCIPAL ===" << endl;
    for (int i = 0; i < AREA_HASH; i++)
    {
        if (!TablaHash[i].borrado && strcmp(TablaHash[i].codigo, "*") != 0)
        {
            cout << "Posicion [" << i << "]: ";
            cout << TablaHash[i].codigo << " | " << TablaHash[i].autor << " | " << TablaHash[i].titulo << endl;
            count++;
        }
    }

    cout << "\n=== LIBROS EN AREA DE DESBORDAMIENTO ===" << endl;
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (!TablaHash[i].borrado && strcmp(TablaHash[i].codigo, "*") != 0)
        {
            cout << "Posicion [" << i << "]: ";
            cout << TablaHash[i].codigo << " | " << TablaHash[i].autor << " | " << TablaHash[i].titulo << endl;
            count++;
        }
    }

    if (count > 0)
    {
        cout << "\nTotal de libros activos: " << count << endl;
    }
    else
    {
        cout << "\nNo hay libros activos en la tabla." << endl;
    }
}

// 9: FUNCIÓN Eliminar
void eliminar(const char *codigo)
{
    int pos = Transformar_Clave(codigo);

    // Buscar en la posicion calculada
    if (strcmp(TablaHash[pos].codigo, codigo) == 0 && !TablaHash[pos].borrado)
    {
        TablaHash[pos].borrado = true;
        cout << "Libro eliminado de la posicion " << pos << endl;
        guardarTabla();
        return;
    }

    // Buscar en area de desbordamiento
    int desbordamientoPos = buscarDesbordamiento(codigo);
    if (desbordamientoPos != -1)
    {
        TablaHash[desbordamientoPos].borrado = true;
        cout << "Libro eliminado de la posicion " << desbordamientoPos << endl;
        guardarTabla();
        return;
    }

    cout << "Libro con codigo '" << codigo << "' no encontrado para eliminar." << endl;
}

void mostrarMenu()
{
    cout << "\n===== MENU PRINCIPAL =====" << endl;
    cout << "1. Insertar libro" << endl;
    cout << "2. Buscar libro" << endl;
    cout << "3. Eliminar libro" << endl;
    cout << "4. Mostrar todos los libros" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void ejecutarPrograma()
{
    int opcion;
    char codigo[7], autor[41], titulo[41];

    do
    {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion)
        {
        case 1: // Insertar libro
            cout << "\n--- Insertar Libro ---" << endl;
            cout << "Ingrese codigo (max 6 chars): ";
            cin.getline(codigo, 7);
            cout << "Ingrese autor (max 40 chars): ";
            cin.getline(autor, 41);
            cout << "Ingrese titulo (max 40 chars): ";
            cin.getline(titulo, 41);

            {
                Libro nuevoLibro;
                strcpy(nuevoLibro.codigo, codigo);
                strcpy(nuevoLibro.autor, autor);
                strcpy(nuevoLibro.titulo, titulo);
                nuevoLibro.borrado = false;
                insertar(nuevoLibro);
            }
            break;

        case 2: // Buscar libro
            cout << "\n--- Buscar Libro ---" << endl;
            cout << "Ingrese codigo a buscar: ";
            cin.getline(codigo, 7);
            buscar(codigo);
            break;

        case 3: // Eliminar libro
            cout << "\n--- Eliminar Libro ---" << endl;
            cout << "Ingrese codigo a eliminar: ";
            cin.getline(codigo, 7);
            eliminar(codigo);
            break;

        case 4: // Mostrar todos los libros
            DesplegarTodo();
            break;

        case 5: // Salir
            cout << "\n¡Gracias por usar el programa!" << endl;
            break;

        default:
            cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    } while (opcion != 5);
}

int main(int argc, char const *argv[])
{
    cout << "=== PROGRAMA DE TABLA HASH CON ARCHIVOS ===" << endl;
    cout << "Inicializando sistema..." << endl;

    creacion();    // Inicializar la tabla hash
    cargarTabla(); // Cargar la tabla desde el archivo

    ejecutarPrograma(); // Ejecutar el programa principal

    return 0;
}