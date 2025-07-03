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
    cout << "Posición calculada: " << d << endl;
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
    cout << "Tabla hash inicializada con " << TOTAL_REGISTROS << " posiciones." << endl;
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
        cout << "✓ Tabla guardada exitosamente en: " << ARCHIVO_TABLA << endl;
    }
    else
    {
        cout << "✗ Error al guardar la tabla en archivo." << endl;
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
        cout << "✓ Tabla cargada exitosamente desde: " << ARCHIVO_TABLA << endl;

        // Contar elementos cargados
        int elementosActivos = 0;
        for (int i = 0; i < TOTAL_REGISTROS; i++)
        {
            if (strcmp(TablaHash[i].codigo, "*") != 0 && !TablaHash[i].borrado)
                elementosActivos++;
        }
        cout << "Elementos activos encontrados: " << elementosActivos << endl;
    }
    else
    {
        cout << "No se encontró archivo anterior (" << ARCHIVO_TABLA << ")" << endl;
        cout << "Iniciando con tabla vacía..." << endl;
        creacion();
    }
}

// ---------------------------------------
// Verificar si un código ya existe
// ---------------------------------------
bool codigoExiste(const char *codigo)
{
    int pos = Transformar_Clave(codigo);

    // Verificar en zona principal
    if (strcmp(TablaHash[pos].codigo, codigo) == 0 && !TablaHash[pos].borrado)
        return true;

    // Verificar en zona de desbordamiento
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, codigo) == 0 && !TablaHash[i].borrado)
            return true;
    }
    return false;
}

// ---------------------------------------
// Insertar en tabla hash
// ---------------------------------------
void insertar(Libro nuevoLibro)
{
    // Verificar si el código ya existe
    if (codigoExiste(nuevoLibro.codigo))
    {
        cout << "✗ Error: El código '" << nuevoLibro.codigo << "' ya existe en la tabla." << endl;
        return;
    }

    int pos = Transformar_Clave(nuevoLibro.codigo);

    // Si está libre, insertar directo
    if (strcmp(TablaHash[pos].codigo, "*") == 0 || TablaHash[pos].borrado)
    {
        TablaHash[pos] = nuevoLibro;
        TablaHash[pos].borrado = false;
        cout << "✓ Insertado en zona principal, posición " << pos << endl;
        guardarTabla();
        return;
    }

    // Buscar en área de desbordamiento
    cout << "⚠ Colisión detectada en posición " << pos << ". Buscando en área de desbordamiento..." << endl;
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") == 0 || TablaHash[i].borrado)
        {
            TablaHash[i] = nuevoLibro;
            TablaHash[i].borrado = false;
            cout << "✓ Insertado en área de desbordamiento, posición " << i << endl;
            guardarTabla();
            return;
        }
    }

    cout << "✗ Error: No hay espacio disponible en la tabla hash." << endl;
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
        cout << "\n📚 Libro encontrado en zona principal [" << pos << "]:" << endl;
        cout << "Código: " << TablaHash[pos].codigo << endl;
        cout << "Autor: " << TablaHash[pos].autor << endl;
        cout << "Título: " << TablaHash[pos].titulo << endl;
        return;
    }

    // Buscar en zona de desbordamiento
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, codigo) == 0 && !TablaHash[i].borrado)
        {
            cout << "\n📚 Libro encontrado en área de desbordamiento [" << i << "]:" << endl;
            cout << "Código: " << TablaHash[i].codigo << endl;
            cout << "Autor: " << TablaHash[i].autor << endl;
            cout << "Título: " << TablaHash[i].titulo << endl;
            return;
        }
    }

    cout << "\n❌ Libro con código '" << codigo << "' no encontrado." << endl;
}

// ---------------------------------------
// FUNCIÓN DesplegarTodo - Mostrar solo elementos activos (Requisito 2)
// ---------------------------------------
void DesplegarTodo()
{
    cout << "\n"
         << string(85, '=') << endl;
    cout << "               ELEMENTOS ALMACENADOS EN LA TABLA HASH" << endl;
    cout << string(85, '=') << endl;

    cout << left << setw(12) << "Ubicación"
         << setw(10) << "Código"
         << setw(25) << "Autor"
         << setw(35) << "Título" << endl;
    cout << string(85, '-') << endl;

    int contador = 0;

    // Mostrar elementos de zona principal
    for (int i = 0; i < AREA_HASH; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") != 0 && !TablaHash[i].borrado)
        {
            cout << left << setw(12) << i
                 << setw(10) << TablaHash[i].codigo
                 << setw(25) << TablaHash[i].autor
                 << setw(35) << TablaHash[i].titulo << endl;
            contador++;
        }
    }

    // Mostrar elementos de zona de desbordamiento
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") != 0 && !TablaHash[i].borrado)
        {
            cout << left << setw(12) << (to_string(i) + " (D)")
                 << setw(10) << TablaHash[i].codigo
                 << setw(25) << TablaHash[i].autor
                 << setw(35) << TablaHash[i].titulo << endl;
            contador++;
        }
    }

    cout << string(85, '-') << endl;
    if (contador == 0)
    {
        cout << "No hay elementos almacenados en la tabla." << endl;
    }
    else
    {
        cout << "Total de libros almacenados: " << contador << endl;
        cout << "Nota: (D) indica área de desbordamiento" << endl;
    }
    cout << string(85, '=') << endl;
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
        cout << "✓ Libro eliminado de posición " << pos << " (zona principal)" << endl;
        guardarTabla();
        return;
    }

    // Buscar en zona de desbordamiento
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, codigo) == 0 && !TablaHash[i].borrado)
        {
            TablaHash[i].borrado = true;
            cout << "✓ Libro eliminado de posición " << i << " (área de desbordamiento)" << endl;
            guardarTabla();
            return;
        }
    }

    cout << "❌ Libro con código '" << codigo << "' no encontrado para eliminar." << endl;
}

// ---------------------------------------
// Mostrar estadísticas de la tabla
// ---------------------------------------
void mostrarEstadisticas()
{
    int zonaPrincipal = 0, areaDesbordamiento = 0, espaciosVacios = 0, elementosBorrados = 0;

    for (int i = 0; i < AREA_HASH; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") == 0)
            espaciosVacios++;
        else if (TablaHash[i].borrado)
            elementosBorrados++;
        else
            zonaPrincipal++;
    }

    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") == 0)
            espaciosVacios++;
        else if (TablaHash[i].borrado)
            elementosBorrados++;
        else
            areaDesbordamiento++;
    }

    cout << "\n========== ESTADÍSTICAS DE LA TABLA HASH ==========" << endl;
    cout << "Elementos en zona principal: " << zonaPrincipal << endl;
    cout << "Elementos en área de desbordamiento: " << areaDesbordamiento << endl;
    cout << "Total elementos activos: " << (zonaPrincipal + areaDesbordamiento) << endl;
    cout << "Elementos borrados: " << elementosBorrados << endl;
    cout << "Espacios vacíos: " << espaciosVacios << endl;
    cout << "Capacidad total: " << TOTAL_REGISTROS << endl;
    cout << "Porcentaje de ocupación: " << fixed << setprecision(2)
         << ((float)(zonaPrincipal + areaDesbordamiento) / TOTAL_REGISTROS * 100) << "%" << endl;
    cout << "===================================================" << endl;
}

// ---------------------------------------
// Insertar datos de prueba con códigos alfabéticos
// ---------------------------------------
void insertarDatosPrueba()
{
    cout << "\n🔄 Insertando datos de prueba con códigos alfabéticos..." << endl;
    cout << "Nota: Se omitirán códigos que ya existan." << endl
         << endl;

    Libro libros[] = {
        {"AB", "García Márquez", "Cien años de soledad", false},
        {"AC", "Cervantes", "Don Quijote de la Mancha", false},
        {"AD", "Borges", "Ficciones", false},
        {"AX", "Cortázar", "Rayuela", false},
        {"BA", "Vargas Llosa", "La ciudad y los perros", false},
        {"XA", "Fuentes", "La muerte de Artemio Cruz", false},
        {"BB", "Rulfo", "Pedro Páramo", false},
        {"CC", "Allende", "La casa de los espíritus", false},
        {"DD", "Esquivel", "Como agua para chocolate", false},
        {"EE", "Benedetti", "La tregua", false},
        {"FF", "Sabato", "El túnel", false},
        {"GG", "Octavio Paz", "El laberinto de la soledad", false}};

    int insertados = 0;
    for (int i = 0; i < 12; i++)
    {
        if (!codigoExiste(libros[i].codigo))
        {
            insertar(libros[i]);
            insertados++;
        }
        else
        {
            cout << "⚠ Código '" << libros[i].codigo << "' ya existe, omitiendo..." << endl;
        }
    }

    cout << "\n✓ Proceso completado. Libros insertados: " << insertados << endl;
}

// ---------------------------------------
// Mostrar menú
// ---------------------------------------
void mostrarMenu()
{
    cout << "\n"
         << string(50, '=') << endl;
    cout << "           MENÚ PRINCIPAL - TABLA HASH" << endl;
    cout << string(50, '=') << endl;
    cout << "1. Insertar libro" << endl;
    cout << "2. Buscar libro" << endl;
    cout << "3. Eliminar libro" << endl;
    cout << "4. Mostrar todos los libros (DesplegarTodo)" << endl;
    cout << "5. Mostrar estadísticas de la tabla" << endl;
    cout << "6. Insertar datos de prueba" << endl;
    cout << "7. Guardar tabla manualmente" << endl;
    cout << "8. Salir" << endl;
    cout << string(50, '=') << endl;
    cout << "Seleccione una opción: ";
}

// ---------------------------------------
// Principal
// ---------------------------------------
int main()
{
    cout << string(60, '=') << endl;
    cout << "     PROGRAMA DE TABLA HASH CON PERSISTENCIA" << endl;
    cout << "              Versión Mejorada 2024" << endl;
    cout << string(60, '=') << endl;

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
            cout << "\n--- INSERTAR NUEVO LIBRO ---" << endl;
            cout << "Código (máx 6 caracteres): ";
            cin.getline(codigo, 7);

            if (strlen(codigo) == 0)
            {
                cout << "❌ El código no puede estar vacío." << endl;
                break;
            }

            cout << "Autor (máx 40 caracteres): ";
            cin.getline(autor, 41);
            cout << "Título (máx 40 caracteres): ";
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
            if (strlen(codigo) > 0)
                buscar(codigo);
            else
                cout << "❌ Debe ingresar un código válido." << endl;
            break;

        case 3:
            cout << "\n--- ELIMINAR LIBRO ---" << endl;
            cout << "Código a eliminar: ";
            cin.getline(codigo, 7);
            if (strlen(codigo) > 0)
                eliminar(codigo);
            else
                cout << "❌ Debe ingresar un código válido." << endl;
            break;

        case 4:
            DesplegarTodo(); // Requisito 2
            break;

        case 5:
            mostrarEstadisticas();
            break;

        case 6:
            insertarDatosPrueba();
            break;

        case 7:
            guardarTabla();
            break;

        case 8:
            cout << "\n👋 Cerrando programa..." << endl;
            guardarTabla(); // Guardar al salir
            cout << "¡Hasta luego!" << endl;
            break;

        default:
            cout << "❌ Opción inválida. Seleccione del 1 al 8." << endl;
        }

        if (opcion != 8)
        {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }

    } while (opcion != 8);

    return 0;
}