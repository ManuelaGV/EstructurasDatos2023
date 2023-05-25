#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*Creaci�n de la clase publica llamada Node para utilizar en el �rbol de B�squeda Binaria.
    Incluye el valor del nodo, y punteros del mismo tipo a derecha e izquierda.*/

class Node{
    public:
    int data;
    struct Node *left;
    struct Node *right;
};

//Funciones usadas en el �rbol Binario de B�squeda.

void arbolBinario();
struct Node* nuevoNode(int item);
void InOrder(struct Node* root);
struct Node* insertar (struct Node* Node, int data);
struct Node* minimoValor(struct Node* Node);
struct Node* eliminarNodo(struct Node* root, int data);

int main()
{
    //Funci�n dirigida a lo que se va a realizar dentro del �rbol de B�squeda Binaria.
    arbolBinario();

    return 0;
}

//----- FUNCIONES USADAS EN EL �RBOL BINARIO DE B�SQUEDA -----

//Funci�n con las variables necesarias declaradas y el uso de las dem�s variables como insertar y eliminar.

void arbolBinario()
{
    struct Node* root = nullptr; //Creaci�n de un puntero nulo dirigido a la estructura del BST para inicializar un �rbol.
    int nodoAux;

    root = insertar(root, 32); //Se ingresa el valor que va a ser la ra�z del �rbol.
    int nodos[11] = {2, 3, 10, 19, 1, 40, 54, 53, 48, 23, 35}; //Arreglo con los valores a insertar.

    //Ciclo para usar la funci�n de insertar con cada uno de los valores del arreglo.

    for(int i=0; i<11; i++)
    {
        nodoAux = nodos[i];
        insertar(root, nodoAux);
    }

    //Impresi�n de los datos del �rbol haciendo uso de funciones.

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

//Funci�n para crear y retornar un nuevo nodo del �rbol BST

struct Node* nuevoNode(int item)
{
    struct Node* temp = new Node; //Crea un nuevo nodo asignandolo a temp
    temp->data = item; //Asigna el valor recibido dentro de la variable data dentro del nodo del �rbol.
    temp->left = temp->right = nullptr; //Inicializa los punteros a derecha e izquierda como null.
    return temp;
};

//Funci�n para imprimir el �rbol en InOrder

void InOrder(struct Node* root)
{
    if(root != nullptr) //Si el �rbol es distinto a vac�o que lo imprima.
    {
        InOrder(root->left); //Recursividad
        cout<<root->data<<" -> ";
        InOrder(root->right); //Recursividad
    }
}

//Funci�n para ingresar elementos dentro del �rbol.

struct Node* insertar (struct Node* Node, int data)
{
    //En caso de que este vac�o el �rbol, crea un nuevo nodo y lo retorna
    if(Node == nullptr)
        return nuevoNode(data);

    //Si no esta vac�o, verifica el valor del dato para ubicarlo dentro del �rbol
    if(data < Node->data) //Si es menor que la ra�z
        Node->left = insertar(Node->left, data); //Se usa recursividad para llamar la funci�n en el sub�rbol izquierdo para ingresar el dato
    else if(data > Node->data) //Si es mayor que la ra�z.
        Node->right = insertar(Node->right, data);
}

//Funci�n para obtener el valor m�nimo del �rbol para usar en la eliminaci�n.
/*Funciona recorriendo la parte izquierda y los nodos izquierdos del �rbol hasta que alcance el m�nimo valor.*/

struct Node* minimoValor(struct Node* Node)
{
    struct Node* auxiliar = Node; //Creaci�n de un nodo auxiliar dle �rbol BST.

    while(auxiliar && auxiliar->left != nullptr) //Se sigue recorriendo mientras el valor sea distinto a nulo.
        auxiliar = auxiliar->left;

    return auxiliar; //Se retorna el valor m�nimo.
}

//Funci�n para la eliminaci�n de un valor espec�fico.

struct Node* eliminarNodo(struct Node* root, int data)
{
    //Si el �rbol esta vac�o devuelve el �rbol
    if(root == nullptr)
        return root;

    //Si el valor a eliminar es menor que la ra�z del �rbol, se dirige hac�a la rama izquierda.
    if(data < root->data)
        root->left = eliminarNodo(root->left, data);

    //Si el valor a eliminar es mayor que la ra�z del �rbol, se dirige hac�a la rama derecha.
    else if(data > root->data)
        root->right = eliminarNodo(root->right, data);

    else{ //Si el valor a eliminar es igual que el de la ra�z.

        //Se tiene que revisar cuantos hijos el nodo tiene.

        //Cuando el nodo no tiene hijos retorna null, eliminando el nodo del �rbol.
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

        struct Node* temporal = minimoValor(root->right); //Encuentra el m�nimo valor del sub�rbol derecho, el cu�l ser� la nueva ra�z despu�s de la eliminaci�n.
        root->data = temporal->data; //Reemplaza el valor del nodo a eliminar con el nodo del valor m�nimo (ra�z).
        root->right = eliminarNodo(root->right, temporal->data); //Recursividad para eliminar el nodo usado como la nueva ra�z.
    }

    return root;
}
