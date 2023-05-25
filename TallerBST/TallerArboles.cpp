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

/*Creación de la clase pública llamada NodeAVL para utilizar en el árbol AVL. Incluye el valor
    del nodo, punteros del mismo tipo a derecha e izquierda y el valor de la altura.*/

class NodeAVL{
    public:
    int data;
    struct NodeAVL *left;
    struct NodeAVL *right;
    int altura;
};

//Funciones usadas en el árbol Binario de Búsqueda.

void arbolBinario();
struct Node* nuevoNode(int item);
void InOrder(struct Node* root);
struct Node* insertar (struct Node* Node, int data);
struct Node* minimoValor(struct Node* Node);
struct Node* eliminarNodo(struct Node* root, int data);

//Funciones usadas en el árbol AVL.

void arbolAVL();
NodeAVL *insertarAVL(NodeAVL* node, int valor);
int maximo(int a, int b);
int altura(NodeAVL *nod);
NodeAVL *nuevoNodeAVL(int valor);
int getBalance(NodeAVL *nod);
NodeAVL *rotacionDerecha(NodeAVL *nodo1);
NodeAVL *rotacionIzquierda(NodeAVL *nodo1);
void InOrderAVL(struct NodeAVL* root);
void preOrder(NodeAVL *rootAVL);
NodeAVL *valorMinimo(NodeAVL* nodo);
NodeAVL *eliminarNodoAVL(NodeAVL* rootAVL, int data);

int main()
{
    //Función dirigida a lo que se va a realizar dentro del árbol de Búsqueda Binaria.
    arbolBinario();

    //Función dirigida a lo que se va a realizar dentro del árbol AVL.
    arbolAVL();

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

//----- FUNCIONES USADAS EN EL ÁRBOL AVL -----

//Función con las variables necesarias declaradas y el uso de las demás variables como insertar y eliminar.

void arbolAVL()
{
    NodeAVL *rootAVL = NULL; //Creación de un puntero nulo dirigido a la estructura del BST para inicializar un árbol.
    int nodoAux;
    int nodos[11] = {2, 3, 10, 19, 1, 40, 54, 53, 48, 23, 35}; //Arreglo con los valores a ingresar.

    rootAVL = insertarAVL(rootAVL, 32); //Se ingresa el valor que va a ser la raíz del árbol

    //Ingresar datos colocados en el arreglo dentro del árbol
    for(int i=0; i<11; i++)
    {
        nodoAux = nodos[i];
        rootAVL = insertarAVL(rootAVL, nodoAux);
    }

    //Impresión del árbol

    cout<<endl;
    cout<<"\n****** ARBOL AVL ******"<<endl;

    cout<<"\n---------- INGRESO DE LOS DATOS INICIALES ----------"<<endl;

    preOrder(rootAVL);

    cout<<"\n---------- INSERCION DE LOS VALORES 19, 20, 5, 50 Y 82 ----------"<<endl;

    rootAVL = insertarAVL(rootAVL, 19);
    rootAVL = insertarAVL(rootAVL, 20);
    rootAVL = insertarAVL(rootAVL, 5);
    rootAVL = insertarAVL(rootAVL, 82);
    rootAVL = insertarAVL(rootAVL, 50);

    preOrder(rootAVL);

    cout<<"\n---------- ELIMINACION DEL VALOR 50 ----------"<<endl;

    rootAVL = eliminarNodoAVL(rootAVL, 50);

    preOrder(rootAVL);
}

//Función que devuelve un entero con el valor máyor entre dos números.

int maximo(int a, int b)
{
    if(a > b)
        return a;
    else if(b > a)
        return b;
}

//Función que retorna el valor de la altura del árbol.

int altura(NodeAVL *nod)
{
    if(nod == NULL) //Revisa si el nodo existe, si no existe se retorna el valor 0
        return 0;

    return nod->altura; //Si existe el nodo, retorna el valor almacenado en altura del nodo.
}

//Función que crea un nuevo nodo con el valor recibido.

NodeAVL* nuevoNodeAVL(int valor)
{
    NodeAVL* nodo = new NodeAVL(); //Crea un nuevo nodo del tipo árbol AVL.
    nodo->data = valor; //Guarda el valor dentro de la variable data del nodo.
    nodo->left = nullptr; //Inicializa los punteros a derecha e izquierda con 0.
    nodo->right = nullptr;
    nodo->altura = 1; //Inicializa la altura con 1.
    return (nodo);
};

//Calcula el factor del balance dentro del árbol AVL. Está definido como la diferencia entre la altura del subárbol izquierdo y la altura del subárbol derecho.

int getBalance(NodeAVL *nod)
{
    if(nod == NULL) //Revisa si el nodo esta vacío y retorna 0 como el balance.
        return 0;
    return (altura(nod->left) - altura(nod->right)); //Retorna la diferencia entre las alturas.
}

//Realiza la rotación a derecha dentro del árbol AVL.

NodeAVL *rotacionDerecha(NodeAVL *nodo1) //La función lleva el nodo a rotar.
{
    NodeAVL *nodo2 = nodo1->left; //Cea un nuevo puntero y lo establece en el hijo izquierdo del nodo a rotar. Esto debido a que se va a realizar una rotación a la derecha, por lo que se requiere que este nodo sea la nueva raíz del árbol.
    NodeAVL *nodoAux = nodo2->right; //Se crea un nodo temporal y se establece como el hijo derecho del nodo a rotar. Esto debido a que el nodo temporal se va a convertir en el hijo izquierdo del nodo a rotar, ya que es más pequeño que la nueva raíz del árbol pero más grande que los demás nodos del subárbol izquierdo.

    nodo2->right = nodo1; //Se establece el hijo derecho de la nueva raíz en el nodo a rotar.
    nodo1->left = nodoAux; //Se establece el hijo izquierdo del nodo a rotar en el nodo temporal.

    //Se actualizan las alturas de los nodos.

    nodo1->altura = maximo(altura(nodo1->left), altura(nodo1->right)) + 1;
    nodo2->altura = maximo(altura(nodo2->left), altura(nodo2->right)) + 1;

    return nodo2; //Se retorna el puntero al nuevo nodo raíz.
};

//Realiza la rotación a izqueirda dentro del árbol AVL. Sigue los mismos pasos que la rotación a derecha.

NodeAVL *rotacionIzquierda(NodeAVL *nodo1)
{
    NodeAVL *nodo2 = nodo1->right;
    NodeAVL *nodoAux = nodo2->left;

    nodo2->left = nodo1;
    nodo1->right = nodoAux;

    nodo1->altura = maximo(altura(nodo1->left), altura(nodo1->right)) + 1;
    nodo2->altura = maximo(altura(nodo2->left), altura(nodo2->right)) + 1;

    return nodo2;
};

//Función para imprimir el árbol en PreOrder

void preOrder(NodeAVL *rootAVL)
{
    if(rootAVL != nullptr) //Si el árbol es distinto a vacío que lo imprima.
    {
        cout << rootAVL->data << " -> ";
        preOrder(rootAVL->left);
        preOrder(rootAVL->right);
    }
}

//Función para insertar dentro del árbol AVL.

NodeAVL* insertarAVL(NodeAVL* nodo, int data)
{
    //Se usa el mismo tipo de inserción que en el árbol BST pero realiza rotaciones para mantener el factor de balance entre -1 y 1

    if(nodo == nullptr) //Si el árbol esta vacío, crea un nuevo nodo y lo retorna.
        return(nuevoNodeAVL(data));

    if(data < nodo->data) //Si el valor es menor que el nodo actual, lo inserta en el subárbol izquierdo.
        nodo->left = insertarAVL(nodo->left, data);
    else if(data > nodo->data) //Si el valor es mayor que el nodo actual, lo inserta en el subárbol derecho.
        nodo->right = insertarAVL(nodo->right, data);
    else //Si los valores son iguales retorna el nodo para evitar duplicados.
        return nodo;

    //Actualiza la altura del nodo actual.
    nodo->altura = 1 + maximo(altura(nodo->left), altura(nodo->right));

    //Calcula el factor de balance del árbol haciendo uso de la función.
    int balanceArbol = getBalance(nodo);

    if((balanceArbol > 1) && (data < nodo->left->data)) //Si el balance es mayor a 1 y el nuevo valor es menor al del hijo izquierdo, realiza una rotación a derecha.
        return rotacionDerecha(nodo);

    if((balanceArbol < -1) && (data > nodo->right->data)) //Si el balance es menor a -1 y el nuevo valor es mayor al del hijo derecho, realiza una rotación a izquierda.
        return rotacionIzquierda(nodo);

    if((balanceArbol > 1) && (data > nodo->left->data)) //Si el balance es mayor a 1 y el nuevo valor es mayor al hijo izquierdo, se realiza una rotación a izquierda y a derecha.
    {
        nodo->left = rotacionIzquierda(nodo->left);
        return rotacionDerecha(nodo);
    }

    if((balanceArbol < -1) && (data < nodo->right->data)) //Si el balance es menor a -1 y el nuevo valor es menor al hijo derecho, se realiza una rotación a derecha y a izquierda.
    {
        nodo->right = rotacionDerecha(nodo->right);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

//Función que retorna el valor mínimo dentro del árbol.

NodeAVL *valorMinimo(NodeAVL* nodo)
{
    NodeAVL *minimo = nodo; //Crea un nuevo nodo inicializado en el nodo recibido.

    while (minimo->left != nullptr) //El ciclo continua mientras no haya encontrado en hijo null en el puntero a izquierda.
        minimo = minimo->left;

    return minimo; //Retorna el valor mínimo.
}

//Función para eliminar datos realizando un proceso de rotaciones.

NodeAVL *eliminarNodoAVL(NodeAVL* rootAVL, int data)
{
    if(rootAVL == nullptr) //Revisa si el árbol esta vacío, si lo está retorna el árbol.
        return rootAVL;

    if(data < rootAVL->data) //Si el valor a eliminar es menor al dato en el árbol.
        rootAVL->left = eliminarNodoAVL(rootAVL->left, data);

    else if(data > rootAVL->data) //Si el valor a eliminar es mayor al dato en el árbol.
        rootAVL->right = eliminarNodoAVL(rootAVL->right, data);

    else //Si el valor del dato es igual a la raíz del nodo.
    {
        if((rootAVL->left == nullptr) || (rootAVL->right == nullptr)) //Revisa si el nodo tiene 0 o un hijo.
        {

            NodeAVL *temporal;

            //Inicializa el puntero de la variable temporal ya sea al hijo izquierdo o derecho.
            if(rootAVL->left)
                temporal = rootAVL->left;
            else
                temporal = rootAVL->right;

            //Si no tiene hijos.
            if(temporal == nullptr)
            {
                temporal = rootAVL;
                rootAVL = nullptr;
            }
            else //Si tiene un hijo
                *rootAVL = *temporal; //Copia el contenido del hijo que no esta vacío.

            free(temporal);
        }
        else
        {
            //Nodo que tiene dos hijos, obtiene el valor mínimo para ser el sucesor.
            NodeAVL *temporal = valorMinimo(rootAVL->right);
            //Copia el valor mínimo del sucesor.
            rootAVL->data = temporal->data;
            //Elimina el sucesor para evitar duplicaciones.
            rootAVL->right = eliminarNodoAVL(rootAVL->right, temporal->data);
        }
    }

    if(rootAVL == nullptr)
        return rootAVL;

    //Se actualiza el valor de la altura.
    rootAVL->altura = 1 + maximo(altura(rootAVL->left), altura(rootAVL->right));

    //Se obtiene el valor del balanceo del árbol.
    int balanceo = getBalance(rootAVL);

    //En caso de que no este balanceado se realiza un proceso de rotación (explicado en inserción).
    if((balanceo > 1) && (getBalance(rootAVL->left) >= 0))
        return rotacionDerecha(rootAVL);

    if((balanceo > 1) && (getBalance(rootAVL->left) < 0))
    {
        rootAVL->left = rotacionIzquierda(rootAVL->left);
        return rotacionDerecha(rootAVL);
    }

    if((balanceo < -1) && getBalance(rootAVL->right) <= 0)
        return rotacionIzquierda(rootAVL);

    if((balanceo < -1) && (getBalance(rootAVL->right) > 0))
    {
        rootAVL->right = rotacionDerecha(rootAVL->right);
        return rotacionIzquierda(rootAVL);
    }

    return rootAVL;

}

