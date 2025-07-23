#include <iostream>
using namespace std;
struct node
{
    int data;
    struct node *izq;
    struct node *der;
};
void Insertar(node *&pRaiz, int Valor);
void DesplegarArbol_EnOrden(node *&pRaiz);
void DesplegarArbol_PreOrden(node *&pRaiz);
void DesplegarArbol_PostOrden(node *&pRaiz);

int main()
{
    // Mensaje Consola
    std::cout << "Arboles\n";
    // Declaración de variables
    node *pRaiz = NULL;
    node *pNodeX = NULL;
    // Inicialización del árbol
    pRaiz = new node;
    pRaiz->data = 7;
    pRaiz->izq = new node;
    pRaiz->der = new node;
    // Inicialización de los nodos hijos
    pNodeX = pRaiz->izq;
    pNodeX->data = 1;
    pNodeX->izq = NULL;
    pNodeX->der = NULL;
    pNodeX = pRaiz->der;
    pNodeX->data = 14;
    pNodeX->izq = NULL;
    pNodeX->der = NULL;
    // Inicialización
    pRaiz = NULL;
    int Valores[11] = {3, 8, 5, 11, 22, 17, 4, 15, 21, 14, 18};
    for (int i = 0; i < 11; i++)
    {
        Insertar(pRaiz, Valores[i]);
    };
    cout << "En orden:\n";
    DesplegarArbol_EnOrden(pRaiz);
    cout << "Pre Orden:\n";
    DesplegarArbol_PreOrden(pRaiz);
    cout << "Post Orden:\n";
    DesplegarArbol_PostOrden(pRaiz);
}

void Insertar(node *&pRaiz, int Valor)
{
    node *pX = pRaiz;
    node *pUltimoNodo = NULL;
    while (pX != NULL && pX->data != Valor)
    {
        pUltimoNodo = pX;
        if (pX->data < Valor)
            pX = pX->der;
        else
            pX = pX->izq;
    }
    if (pX == NULL)
    {
        node *pNuevo = new node;
        if (pNuevo != NULL)
        {
            pNuevo->data = Valor;
            pNuevo->izq = NULL;
            pNuevo->der = NULL;
            if (pUltimoNodo == NULL)
                pRaiz = pNuevo;
            else
            {
                if (pUltimoNodo->data < Valor)
                    pUltimoNodo->der = pNuevo;
                else
                    pUltimoNodo->izq = pNuevo;
            };
        }
        else
        {
            cout << "Error al solicitar memoria";
        }
    }
}

void DesplegarArbol_EnOrden(node *&pRaiz)
{
    if (pRaiz != NULL) // condición de parada
    {
        DesplegarArbol_EnOrden(pRaiz->izq); // llamada recursiva
        cout << pRaiz->data << "\n";
        DesplegarArbol_EnOrden(pRaiz->der);
    }
}

void DesplegarArbol_PreOrden(node *&pRaiz)
{
    if (pRaiz != NULL)
    {
        cout << pRaiz->data << "\n";
        DesplegarArbol_PreOrden(pRaiz->izq);
        DesplegarArbol_PreOrden(pRaiz->der);
    }
}

void DesplegarArbol_PostOrden(node *&pRaiz)
{
    if (pRaiz != NULL)
    {
        DesplegarArbol_PostOrden(pRaiz->der);
        cout << pRaiz->data << "\n";
        DesplegarArbol_PostOrden(pRaiz->izq);
    }
}