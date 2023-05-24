#include <iostream>
#include <cstdlib>

using namespace std;

void NumeroRandom(int arregloInt[], int tamano);
void ImprimirContenido(int arregloInt[], int *puntero, int tamano);
void ImprimirDirecciones(int arregloInt[], int *puntero, int tamano);

int main()
{
    //Ejercicio 01

    //Creación de variables.

    int arreglo[10]={};
    int tamano=10; //Tamaño del arreglo.
    int *ptr; //Creación del puntero.

    //Función para llenar el arreglo con números aleatorios.

    NumeroRandom(arreglo, tamano);

    //Función para imprimir el contenido del array con punteros

    ImprimirContenido(arreglo, ptr, tamano);

    cout<<endl;

    //Función para imprimir las direcciones del contenido del array

    ImprimirDirecciones(arreglo, ptr, tamano);

    cout<<endl;
}

void NumeroRandom(int arregloInt[], int tamano)
{
    //Con un ciclo se llena el arreglo con números entre 0 y 25.

    for(int i=0; i<tamano; i++)
    {
        arregloInt[i] = rand() % 25;
    }
}

void ImprimirContenido(int arregloInt[], int *puntero, int tamano)
{
    puntero = arregloInt;

    cout<<"Impresion del contenido del arreglo: "<<endl;

    //Se imprime cada uno de los elementos del array con un puntero

    for(int i=0; i<tamano; i++)
    {
        cout<<*puntero++<<" - ";
    }
}

void ImprimirDirecciones(int arregloInt[], int *puntero, int tamano)
{
    puntero = arregloInt;

    cout<<"\nImpresion de las direcciones del contenido del array: "<<endl;

    //Se imprime cada una de las direcciones del contenido del array

    for(int i=0; i<tamano; i++)
    {
        cout<<puntero++<<" - ";
    }
}
