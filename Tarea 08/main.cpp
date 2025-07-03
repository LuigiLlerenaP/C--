#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

#define TOTAL_REGISTROS 240
#define AREA_HASH 199
#define INICIO_DESBORDAMIENTO 199
#define FIN_DESBORDAMIENTO 239

// Estructura para libro
typedef struct
{
    char codigo[7];
    char autor[41];
    char titulo[41];
    bool borrado;
} Libro;

// Arreglo que representa la tabla hash
Libro TablaHash[TOTAL_REGISTROS];

// Nombre del archivo para persistencia
const char *ARCHIVO_TABLA = "tabla_hash.dat";

// ---------------------------------------
// Función hash modificada - MUESTRA EL VALOR DE 'd' (Requisito 1)
// ---------------------------------------
int Transformar_Clave(const char *codigo)
{
    int hash = 0;
    cout << "\n--- Proceso de Transformación de Clave ---" << endl;
    cout << "Código: " << codigo << endl;

    for (int i = 0; codigo[i] != '\0'; i++)
    {
        int valor_ascii = (int)codigo[i];
        hash += valor_ascii;
        cout << "Carácter '" << codigo[i] << "' = " << valor_ascii << endl;
    }

    cout << "Suma total: " << hash << endl;

    int d = hash % AREA_HASH;
    cout << "Valor de 'd' = " << hash << " % " << AREA_HASH << " = " << d << endl;
    cout << "----------------------------------------" << endl;

    return d;
}

// ---------------------------------------
// Inicializar la tabla hash
// ---------------------------------------
void creacion()
{
    Libro vacio = {"*", "", "", false};
    for (int i = 0; i < TOTAL_REGISTROS; i++)
    {
        TablaHash[i] = vacio;
    }
}

// ---------------------------------------
// Guardar tabla en archivo (Requisito 3)
// ---------------------------------------
void guardarTabla()
{
    ofstream archivo(ARCHIVO_TABLA, ios::binary);
    if (archivo.is_open())
    {
        archivo.write(reinterpret_cast<char *>(TablaHash), sizeof(TablaHash));
        archivo.close();
        cout << "Tabla guardada en archivo." << endl;
    }
    else
    {
        cout << "Error al guardar la tabla." << endl;
    }
}

// ---------------------------------------
// Cargar tabla desde archivo (Requisito 3)
// ---------------------------------------
void cargarTabla()
{
    ifstream archivo(ARCHIVO_TABLA, ios::binary);
    if (archivo.is_open())
    {
        archivo.read(reinterpret_cast<char *>(TablaHash), sizeof(TablaHash));
        archivo.close();
        cout << "Tabla cargada desde archivo anterior." << endl;
    }
    else
    {
        cout << "No se encontró archivo anterior. Iniciando tabla vacía." << endl;
        creacion();
    }
}

// ---------------------------------------
// Insertar en tabla hash
// ---------------------------------------
void insertar(Libro nuevoLibro)
{
    int pos = Transformar_Clave(nuevoLibro.codigo);

    // Si está libre, insertar directo
    if (strcmp(TablaHash[pos].codigo, "*") == 0 || TablaHash[pos].borrado)
    {
        TablaHash[pos] = nuevoLibro;
        TablaHash[pos].borrado = false;
        cout << "Insertado en zona principal, posición " << pos << endl;
        guardarTabla(); // Guardar después de cada inserción
        return;
    }

    // Buscar en área de desbordamiento
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") == 0 || TablaHash[i].borrado)
        {
            TablaHash[i] = nuevoLibro;
            TablaHash[i].borrado = false;
            cout << "Colisión. Insertado en desbordamiento, posición " << i << endl;
            guardarTabla(); // Guardar después de cada inserción
            return;
        }
    }

    cout << "Error: No hay espacio en la tabla." << endl;
}

// ---------------------------------------
// Buscar libro
// ---------------------------------------
void buscar(const char *codigo)
{
    int pos = Transformar_Clave(codigo);

    // Buscar en zona principal
    if (strcmp(TablaHash[pos].codigo, codigo) == 0 && !TablaHash[pos].borrado)
    {
        cout << "\nLibro encontrado en zona principal [" << pos << "]:\n";
        cout << TablaHash[pos].codigo << " | " << TablaHash[pos].autor << " | " << TablaHash[pos].titulo << endl;
        return;
    }

    // Buscar en zona de desbordamiento
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, codigo) == 0 && !TablaHash[i].borrado)
        {
            cout << "\nLibro encontrado en desbordamiento [" << i << "]:\n";
            cout << TablaHash[i].codigo << " | " << TablaHash[i].autor << " | " << TablaHash[i].titulo << endl;
            return;
        }
    }

    cout << "\nLibro no encontrado." << endl;
}

// ---------------------------------------
// FUNCIÓN DesplegarTodo - Mostrar solo elementos activos (Requisito 2)
// ---------------------------------------
void DesplegarTodo()
{
    cout << "\n========== ELEMENTOS ALMACENADOS EN LA TABLA HASH ==========" << endl;
    cout << left << setw(10) << "Ubicación"
         << setw(12) << "Código"
         << setw(25) << "Autor"
         << setw(30) << "Título" << endl;
    cout << string(77, '-') << endl;

    bool hayElementos = false;

    // Mostrar elementos de zona principal
    for (int i = 0; i < AREA_HASH; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") != 0 && !TablaHash[i].borrado)
        {
            cout << left << setw(10) << i
                 << setw(12) << TablaHash[i].codigo
                 << setw(25) << TablaHash[i].autor
                 << setw(30) << TablaHash[i].titulo << endl;
            hayElementos = true;
        }
    }

    // Mostrar elementos de zona de desbordamiento
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") != 0 && !TablaHash[i].borrado)
        {
            cout << left << setw(10) << i
                 << setw(12) << TablaHash[i].codigo
                 << setw(25) << TablaHash[i].autor
                 << setw(30) << TablaHash[i].titulo << endl;
            hayElementos = true;
        }
    }

    if (!hayElementos)
    {
        cout << "No hay elementos para mostrar." << endl;
    }

    cout << "===========================================================" << endl;
}

// ---------------------------------------
// Eliminar libro (eliminación lógica)
// ---------------------------------------
void eliminar(const char *codigo)
{
    int pos = Transformar_Clave(codigo);

    // Buscar en zona principal
    if (strcmp(TablaHash[pos].codigo, codigo) == 0 && !TablaHash[pos].borrado)
    {
        TablaHash[pos].borrado = true;
        cout << "Libro eliminado de posición " << pos << endl;
        guardarTabla();
        return;
    }

    // Buscar en zona de desbordamiento
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, codigo) == 0 && !TablaHash[i].borrado)
        {
            TablaHash[i].borrado = true;
            cout << "Libro eliminado de posición " << i << endl;
            guardarTabla();
            return;
        }
    }

    cout << "Libro no encontrado para eliminar." << endl;
}

// ---------------------------------------
// Mostrar tabla completa (para depuración)
// ---------------------------------------
void mostrarTablaCompleta()
{
    cout << "\n========== ESTADO COMPLETO DE LA TABLA ==========\n";
    cout << "ZONA PRINCIPAL (0-198):\n";
    for (int i = 0; i < AREA_HASH; i++)
    {
        cout << "[" << setw(3) << i << "] ";
        if (strcmp(TablaHash[i].codigo, "*") == 0)
            cout << "[Vacío]";
        else if (TablaHash[i].borrado)
            cout << "[BORRADO] " << TablaHash[i].codigo;
        else
            cout << TablaHash[i].codigo << " | " << TablaHash[i].autor << " | " << TablaHash[i].titulo;
        cout << endl;
    }

    cout << "\nZONA DE DESBORDAMIENTO (199-239):\n";
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        cout << "[" << setw(3) << i << "] ";
        if (strcmp(TablaHash[i].codigo, "*") == 0)
            cout << "[Vacío]";
        else if (TablaHash[i].borrado)
            cout << "[BORRADO] " << TablaHash[i].codigo;
        else
            cout << TablaHash[i].codigo << " | " << TablaHash[i].autor << " | " << TablaHash[i].titulo;
        cout << endl;
    }
    cout << "===============================================\n";
}

// ---------------------------------------
// Insertar datos de prueba con códigos alfabéticos
// ---------------------------------------
void insertarDatosPrueba()
{
    cout << "\nInsertando 10+ libros con códigos alfabéticos..." << endl;

    insertar({"AB", "García Márquez", "Cien años de soledad", false});
    insertar({"AC", "Cervantes", "Don Quijote de la Mancha", false});
    insertar({"AD", "Borges", "Ficciones", false});
    insertar({"AX", "Cortázar", "Rayuela", false});
    insertar({"BA", "Vargas Llosa", "La ciudad y los perros", false});
    insertar({"XA", "Fuentes", "La muerte de Artemio Cruz", false});
    insertar({"BB", "Rulfo", "Pedro Páramo", false});
    insertar({"CC", "Allende", "La casa de los espíritus", false});
    insertar({"DD", "Esquivel", "Como agua para chocolate", false});
    insertar({"EE", "Benedetti", "La tregua", false});
    insertar({"FF", "Sabato", "El túnel", false});
    insertar({"GG", "Octavio Paz", "El laberinto de la soledad", false});

    cout << "Datos de prueba insertados correctamente." << endl;
}

// ---------------------------------------
// Mostrar menú
// ---------------------------------------
void mostrarMenu()
{
    cout << "\n=============== MENÚ PRINCIPAL ===============" << endl;
    cout << "1. Insertar libro" << endl;
    cout << "2. Buscar libro" << endl;
    cout << "3. Eliminar libro" << endl;
    cout << "4. Mostrar todos los libros (DesplegarTodo)" << endl;
    cout << "5. Mostrar tabla completa" << endl;
    cout << "6. Insertar datos de prueba" << endl;
    cout << "7. Salir" << endl;
    cout << "=============================================" << endl;
    cout << "Seleccione una opción: ";
}

// ---------------------------------------
// Principal
// ---------------------------------------
int main()
{
    cout << "=== PROGRAMA DE TABLA HASH CON ARCHIVOS ===" << endl;

    // CARGAR TABLA DESDE ARCHIVO (Requisito 3)
    cargarTabla();

    int opcion;
    char codigo[7], autor[41], titulo[41];

    do
    {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        switch (opcion)
        {
        case 1:
            cout << "\n--- INSERTAR LIBRO ---" << endl;
            cout << "Código (máx 6 chars): ";
            cin.getline(codigo, 7);
            cout << "Autor (máx 40 chars): ";
            cin.getline(autor, 41);
            cout << "Título (máx 40 chars): ";
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

        case 2:
            cout << "\n--- BUSCAR LIBRO ---" << endl;
            cout << "Código a buscar: ";
            cin.getline(codigo, 7);
            buscar(codigo);
            break;

        case 3:
            cout << "\n--- ELIMINAR LIBRO ---" << endl;
            cout << "Código a eliminar: ";
            cin.getline(codigo, 7);
            eliminar(codigo);
            break;

        case 4:
            DesplegarTodo(); // Requisito 2
            break;

        case 5:
            mostrarTablaCompleta();
            break;

        case 6:
            insertarDatosPrueba();
            break;

        case 7:
            cout << "Saliendo del programa..." << endl;
            guardarTabla(); // Guardar al salir
            break;

        default:
            cout << "Opción inválida." << endl;
        }

        if (opcion != 7)
        {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }

    } while (opcion != 7);

    return 0;
}