#include <iostream>
#include <cstring>
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
} Libro;

// Arreglo que representa la tabla hash
Libro TablaHash[TOTAL_REGISTROS];

// ---------------------------------------
// Función hash basada en suma ASCII y módulo 199
// ---------------------------------------
int funcion_hash_modulo(const char *codigo)
{
    int hash = 0;
    for (int i = 0; codigo[i] != '\0'; i++)
    {
        hash += codigo[i]; // suma de valores ASCII
    }
    return hash % AREA_HASH;
}

// ---------------------------------------
// Inicializar la tabla hash
// ---------------------------------------
void creacion()
{
    Libro vacio = {"*", "", ""};
    for (int i = 0; i < TOTAL_REGISTROS; i++)
    {
        TablaHash[i] = vacio;
    }
}

// ---------------------------------------
// Insertar en tabla hash
// ---------------------------------------
void insertar(Libro nuevoLibro)
{
    int pos = funcion_hash_modulo(nuevoLibro.codigo);

    // Si está libre, insertar directo
    if (strcmp(TablaHash[pos].codigo, "*") == 0)
    {
        TablaHash[pos] = nuevoLibro;
        cout << "Insertado en zona principal, posición " << pos << endl;
        return;
    }

    // Buscar en área de desbordamiento
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, "*") == 0)
        {
            TablaHash[i] = nuevoLibro;
            cout << " Colisión. Insertado en desbordamiento, posicion " << i << endl;
            return;
        }
    }

    cout << " Error: No hay espacio en la tabla." << endl;
}

// ---------------------------------------
// Buscar libro
// ---------------------------------------
void buscar(const char *codigo)
{
    int pos = funcion_hash_modulo(codigo);

    // Buscar en zona principal
    if (strcmp(TablaHash[pos].codigo, codigo) == 0)
    {
        cout << "\nLibro encontrado en zona principal [" << pos << "]:\n";
        cout << TablaHash[pos].codigo << " | " << TablaHash[pos].autor << " | " << TablaHash[pos].titulo << endl;
        return;
    }

    // Buscar en zona de desbordamiento
    for (int i = INICIO_DESBORDAMIENTO; i <= FIN_DESBORDAMIENTO; i++)
    {
        if (strcmp(TablaHash[i].codigo, codigo) == 0)
        {
            cout << "\n Libro encontrado en desbordamiento [" << i << "]:\n";
            cout << TablaHash[i].codigo << " | " << TablaHash[i].autor << " | " << TablaHash[i].titulo << endl;
            return;
        }
    }

    cout << "\n Libro no encontrado." << endl;
}

// ---------------------------------------
// Mostrar tabla
// ---------------------------------------
void mostrarTabla()
{
    cout << "\n Tabla Hash (0-239):\n";
    for (int i = 0; i < TOTAL_REGISTROS; i++)
    {
        cout << "[" << i << "] ";
        if (strcmp(TablaHash[i].codigo, "*") == 0)
            cout << "[Vacío]\n";
        else
            cout << TablaHash[i].codigo << " | " << TablaHash[i].autor << " | " << TablaHash[i].titulo << endl;
    }
}

// ---------------------------------------
// Principal
// ---------------------------------------
int main()
{
    creacion();

    // Insertar
    insertar({"A12345", "Gabriel Garcia", "Cien Años de Soledad"});
    insertar({"B67890", "Julio Verne", "Viaje al Centro de la Tierra"});
    insertar({"C11111", "Miguel Cervantes", "Don Quijote"});
    insertar({"D22222", "Isabel Allende", "La Casa de los Espíritus"});

    mostrarTabla();

    // Búsquedas
    buscar("B67890");
    buscar("Z99999");

    return 0;
}
