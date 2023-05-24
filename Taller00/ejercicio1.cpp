#include <iostream>
#include <cstdlib>

using namespace std;

void NumeroRandom(int arregloInt[], int tamano);
void ImprimirContenido(int arregloInt[], int *puntero, int tamano);
void ImprimirDirecciones(int arregloInt[], int *puntero, int tamano);

int main()
{
    //Ejercicio 01

    //Creaci�n de variables.

    int arreglo[10]={};
    int tamano=10; //Tama�o del arreglo.
    int *ptr; //Creaci�n del puntero.

    //Funci�n para llenar el arreglo con n�meros aleatorios.

    NumeroRandom(arreglo, tamano);

    //Funci�n para imprimir el contenido del array con punteros

    ImprimirContenido(arreglo, ptr, tamano);

    cout<<endl;

    //Funci�n para imprimir las direcciones del contenido del array

    ImprimirDirecciones(arreglo, ptr, tamano);

    cout<<endl;
}

void NumeroRandom(int arregloInt[], int tamano)
{
    //Con un ciclo se llena el arreglo con n�meros entre 0 y 25.

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
