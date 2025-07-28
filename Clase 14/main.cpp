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
void LeerDesdeTeclado(node *&pRaiz);
int main()
{
    node *pRaiz = NULL;
    cout << "Arbol Binario de Busqueda\n";
    LeerDesdeTeclado(pRaiz);

    cout << "En orden:\n";
    DesplegarArbol_EnOrden(pRaiz);
    cout << "Pre Orden:\n";
    DesplegarArbol_PreOrden(pRaiz);
    cout << "Post Orden:\n";
    DesplegarArbol_PostOrden(pRaiz);
}

void LeerDesdeTeclado(node *&pRaiz)
{
    int valor;
    cout << "Ingrese numeros para insertar en el arbol (0 para terminar):\n";

    while (true)
    {
        cout << "Valor: ";
        cin >> valor;

        if (valor == 0)
            break;

        Insertar(pRaiz, valor);
    }
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

void ImprimirNodoConEspacios(int data, int espacio, int nivel)
{
    cout << endl;
    for (int i = nivel; i < espacio; i++)
        cout << " ";
    cout << data << "\n";
}
