#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*Creación de la clase publica llamada Node para utilizar en el árbol de Búsqueda Binaria.
    Incluye el valor del nodo, y punteros del mismo tipo a derecha e izquierda.*/

class Node{
    public:
    int data;
    struct Node *left;
    struct Node *right;
};

//Funciones usadas en el árbol Binario de Búsqueda.

void arbolBinario();
struct Node* nuevoNode(int item);
void InOrder(struct Node* root);
struct Node* insertar (struct Node* Node, int data);
struct Node* minimoValor(struct Node* Node);
struct Node* eliminarNodo(struct Node* root, int data);

int main()
{
    //Función dirigida a lo que se va a realizar dentro del árbol de Búsqueda Binaria.
    arbolBinario();

    return 0;
}

//----- FUNCIONES USADAS EN EL ÁRBOL BINARIO DE BÚSQUEDA -----

//Función con las variables necesarias declaradas y el uso de las demás variables como insertar y eliminar.

void arbolBinario()
{
    struct Node* root = nullptr; //Creación de un puntero nulo dirigido a la estructura del BST para inicializar un árbol.
    int nodoAux;

    root = insertar(root, 32); //Se ingresa el valor que va a ser la raíz del árbol.
    int nodos[11] = {2, 3, 10, 19, 1, 40, 54, 53, 48, 23, 35}; //Arreglo con los valores a insertar.

    //Ciclo para usar la función de insertar con cada uno de los valores del arreglo.

    for(int i=0; i<11; i++)
    {
        nodoAux = nodos[i];
        insertar(root, nodoAux);
    }

    //Impresión de los datos del árbol haciendo uso de funciones.

    cout<<"****** ARBOL BINARIO DE BUSQUEDA ******"<<endl;

    cout<<"\n---------- INGRESO DE LOS DATOS INICIALES ----------"<<endl;

    InOrder(root);

    cout<<"\n---------- ELIMINACION DE LOS VALORES 2 Y 32 ----------"<<endl;

    root = eliminarNodo(root, 2);
    root = eliminarNodo(root, 32);

    InOrder(root);

    cout<<"\n---------- INSERCION DEL VALOR 41 ----------"<<endl;

    insertar(root, 41);

    InOrder(root);
}

//Función para crear y retornar un nuevo nodo del árbol BST

struct Node* nuevoNode(int item)
{
    struct Node* temp = new Node; //Crea un nuevo nodo asignandolo a temp
    temp->data = item; //Asigna el valor recibido dentro de la variable data dentro del nodo del árbol.
    temp->left = temp->right = nullptr; //Inicializa los punteros a derecha e izquierda como null.
    return temp;
};

//Función para imprimir el árbol en InOrder

void InOrder(struct Node* root)
{
    if(root != nullptr) //Si el árbol es distinto a vacío que lo imprima.
    {
        InOrder(root->left); //Recursividad
        cout<<root->data<<" -> ";
        InOrder(root->right); //Recursividad
    }
}

//Función para ingresar elementos dentro del árbol.

struct Node* insertar (struct Node* Node, int data)
{
    //En caso de que este vacío el árbol, crea un nuevo nodo y lo retorna
    if(Node == nullptr)
        return nuevoNode(data);

    //Si no esta vacío, verifica el valor del dato para ubicarlo dentro del árbol
    if(data < Node->data) //Si es menor que la raíz
        Node->left = insertar(Node->left, data); //Se usa recursividad para llamar la función en el subárbol izquierdo para ingresar el dato
    else if(data > Node->data) //Si es mayor que la raíz.
        Node->right = insertar(Node->right, data);
}

//Función para obtener el valor mínimo del árbol para usar en la eliminación.
/*Funciona recorriendo la parte izquierda y los nodos izquierdos del árbol hasta que alcance el mínimo valor.*/

struct Node* minimoValor(struct Node* Node)
{
    struct Node* auxiliar = Node; //Creación de un nodo auxiliar dle árbol BST.

    while(auxiliar && auxiliar->left != nullptr) //Se sigue recorriendo mientras el valor sea distinto a nulo.
        auxiliar = auxiliar->left;

    return auxiliar; //Se retorna el valor mínimo.
}

//Función para la eliminación de un valor específico.

struct Node* eliminarNodo(struct Node* root, int data)
{
    //Si el árbol esta vacío devuelve el árbol
    if(root == nullptr)
        return root;

    //Si el valor a eliminar es menor que la raíz del árbol, se dirige hacía la rama izquierda.
    if(data < root->data)
        root->left = eliminarNodo(root->left, data);

    //Si el valor a eliminar es mayor que la raíz del árbol, se dirige hacía la rama derecha.
    else if(data > root->data)
        root->right = eliminarNodo(root->right, data);

    else{ //Si el valor a eliminar es igual que el de la raíz.

        //Se tiene que revisar cuantos hijos el nodo tiene.

        //Cuando el nodo no tiene hijos retorna null, eliminando el nodo del árbol.
        if(root->left == nullptr && root->right == nullptr)
        return nullptr;

        //Cuando el nodo tiene un hijo
        else if(root->left == nullptr)
        {
            struct Node* temporal = root->right;
            free(root);
            return temporal; //Retorna el nodo del hijo, removiendo el nodo.
        }

        else if(root->right == nullptr)
        {
            struct Node* temporal = root->left;
            free(root);
            return temporal;
        }

        //Cuando tiene 2 hijos

        struct Node* temporal = minimoValor(root->right); //Encuentra el mínimo valor del subárbol derecho, el cuál será la nueva raíz después de la eliminación.
        root->data = temporal->data; //Reemplaza el valor del nodo a eliminar con el nodo del valor mínimo (raíz).
        root->right = eliminarNodo(root->right, temporal->data); //Recursividad para eliminar el nodo usado como la nueva raíz.
    }

    return root;
}
