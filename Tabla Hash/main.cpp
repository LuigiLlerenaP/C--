#include <iostream>
#include <string>
#include <limits>

const int MAX_TABLE = 50;

struct File
{
    std::string nombre;
    std::string extension;
    std::string content;

    File() = default;

    File(const std::string &nombre, const std::string &extension, const std::string &content)
        : nombre(nombre), extension(extension), content(content) {}
};

struct Node
{
    File file;
    Node *next;

    Node(const File &file) : file(file), next(nullptr) {}
};

Node *hashTable[MAX_TABLE] = {nullptr};

int hashFunction(const std::string &key)
{
    const unsigned int FNV_PRIME = 0x1000193;
    const unsigned int FNV_OFFSET = 0x811c9dc5;

    unsigned int salt = 0;
    for (size_t i = 0; i < std::min<size_t>(key.size(), 4); ++i)
    {
        salt = (salt << 5) | (static_cast<unsigned char>(key[i]) & 0x1F);
    }

    unsigned int hash = FNV_OFFSET ^ salt;

    for (char ch : key)
    {
        hash ^= static_cast<unsigned char>(ch);
        hash *= FNV_PRIME;
        hash = (hash << 5) | (hash >> (32 - 5));
    }

    hash ^= (hash >> 13);
    hash *= 0x5bd1e995;
    hash ^= (hash >> 15);

    return hash % MAX_TABLE;
}

void insertFile(const File &file)
{
    int index = hashFunction(file.nombre);

    Node *newNode = new Node(file);

    if (hashTable[index] == nullptr)
    {
        hashTable[index] = newNode;
    }
    else
    {
        Node *current = hashTable[index];
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    std::cout << "Archivo insertado correctamente:\n";
    std::cout << "  Indice     : " << index << "\n";
    std::cout << "  Nombre     : " << file.nombre << "\n";
    std::cout << "  Extension  : " << file.extension << "\n";
    std::cout << "  Contenido  : " << file.content << "\n";
}

std::string calculateCollisionOccupancy()
{
    int totalElementos = 0;
    int elementosEnColisiones = 0;
    for (int i = 0; i < MAX_TABLE; ++i)
    {
        Node *current = hashTable[i];
        int count = 0;

        while (current != nullptr)
        {
            count++;
            current = current->next;
        }

        if (count > 1)
        {
            elementosEnColisiones += (count - 1);
        }
        totalElementos += count;
    }

    double porcentaje = totalElementos == 0 ? 0.0 : (static_cast<double>(elementosEnColisiones) / totalElementos) * 100.0;

    std::cout << "Elementos totales insertados           : " << totalElementos << std::endl;
    std::cout << "Elementos en area de colisiones        : " << elementosEnColisiones << std::endl;
    std::cout << "Porcentaje de ocupacion en colisiones  : " << porcentaje << "%" << std::endl;

    std::string mensaje = (porcentaje <= 20.0) ? "Cumple con el maximo del 20% de colisiones"
                                               : "No cumple con el maximo permitido (20%)";

    std::cout << mensaje << std::endl;

    return "Elementos insertados: " + std::to_string(totalElementos) + ". " + mensaje + ".";
}

void requestFile()
{
    std::string nombre, extension, content;

    std::cout << "Ingrese el nombre del archivo: ";
    std::cin >> nombre;
    std::cout << "Ingrese la extension del archivo: ";
    std::cin >> extension;
    std::cout << "Ingrese el contenido del archivo: ";
    std::cin.ignore();
    std::getline(std::cin, content);

    File file(nombre, extension, content);
    insertFile(file);
}

void mainOptions()
{
    std::cout << "1. Crear archivo" << std::endl;
    std::cout << "2. Mostrar ocupacion de colisiones" << std::endl;
    std::cout << "0. Salir" << std::endl;
}

void Options(int option)
{
    switch (option)
    {
    case 1:
        std::cout << "Crear archivo seleccionado." << std::endl;
        requestFile();
        std::cout << "Archivo creado exitosamente." << std::endl;
        break;
    case 2:
        std::cout << "Calculando ocupacion de area de colisiones..." << std::endl;
        {
            std::string resultado = calculateCollisionOccupancy();
        }
        break;
    case 0:
        std::cout << "Saliendo del programa." << std::endl;
        break;
    default:
        std::cout << "Opcion no valida. Intente nuevamente." << std::endl;
        break;
    }
}

void pausar()
{
    std::cout << "Presione Enter para continuar..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void executeOptions()
{
    int option;
    do
    {
        std::cout << "Seleccione una opcion:" << std::endl;
        std::cout << "========================================" << std::endl;
        mainOptions();
        std::cout << "========================================" << std::endl;
        std::cin >> option;
        std::cout << "......." << std::endl;
        Options(option);
        pausar();
    } while (option != 0);
}

void initalValues()
{
    std::string nombres[20] = {
        "app", "main", "style", "component", "utils",
        "index", "config", "header", "footer", "theme",
        "service", "controller", "router", "store", "model",
        "helper", "validator", "api", "middleware", "database"};

    std::string extensiones[5] = {"js", "ts", "css", "cpp", "cs"};

    std::string contenidos[5] = {
        "// Codigo JavaScript base",
        "// Codigo TypeScript base",
        "/* Estilos CSS base */",
        "// Codigo C++ base",
        "// Codigo C# base"};

    for (int i = 0; i < 20; i++)
    {
        File file(nombres[i], extensiones[i % 5], contenidos[i % 5]);
        insertFile(file);
    }
}

int main()
{
    std::cout << "========================================" << std::endl;
    initalValues();
    std::cout << "Inicializando tabla hash..." << std::endl;
    std::cout << "========================================" << std::endl;
    executeOptions();
    return 0;
}
