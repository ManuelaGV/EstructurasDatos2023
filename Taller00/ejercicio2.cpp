#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

//Estructura con los datos del cliente

struct cliente{
    string nombre;
    string apellido;
    string documento;
    float canProductos;
    float totalCompra;
};

void AgregarDatos(cliente arregloVendedores[], int cantidad);
void GuardarDatos(cliente arregloVendedores[], int cantidad);

int main()
{
    int cantidad;
    cliente * ArregloVendedores;

    cout<<"Ingrese la cantidad de clientes a agregar: "<<endl;
    cin>>cantidad;

    //Se crea un arreglo de estructuras para almacenar los datos.

    ArregloVendedores = new cliente[cantidad];

    //Función encargada de pedir los datos y guardarlos

    AgregarDatos(ArregloVendedores, cantidad);

    //Función encargada de imprimir los datos en un fichero de texto.

    cout<<"\nA continuacion se van a guardar los datos de los clientes registrados hasta el momento."<<endl;
    GuardarDatos(ArregloVendedores, cantidad);

    delete[] ArregloVendedores;
}

void AgregarDatos(cliente arregloVendedores[], int cantidad)
{
    cliente * ptr;

    ptr = arregloVendedores;

    for(int i=0; i<cantidad; i++)
    {
        cout<<"---------- CLIENTE "<<i+1<<" ----------"<<endl;
        cout<<"Ingrese el nombre: "<<endl;
        cin>>ptr->nombre;
        cout<<"Ingrese el apellido: "<<endl;
        cin>>ptr->apellido;
        cout<<"Ingrese el documento: "<<endl;
        cin>>ptr->documento;
        cout<<"Ingrese la cantidad de productos comprados: "<<endl;
        cin>>ptr->documento;
        cout<<"Ingrese el total facturado: "<<endl;
        cin>>ptr->totalCompra;

        ptr++;
    }
}

void GuardarDatos(cliente arregloVendedores[], int cantidad)
{
    cliente * puntero;

    puntero = arregloVendedores;

    ofstream archivoInfo;
    string texto;

    archivoInfo.open("InformacionClientes.txt", ios::app);

    if(archivoInfo.fail())
    {
        cout<<"No se pudo abrir el archivo.";
        exit(1);
    }

    for(int i=0; i<cantidad; i++)
    {
        archivoInfo<<"---------- CLIENTE "<<i+1<<" ----------"<<endl;
        archivoInfo<<"Nombre: "<<puntero->nombre<<endl;
        archivoInfo<<"Apellido: "<<puntero->apellido<<endl;
        archivoInfo<<"Documento: "<<puntero->documento<<endl;
        archivoInfo<<"Cantidad de productos comprados: "<<puntero->canProductos<<endl;
        archivoInfo<<"Total de la compra: "<<puntero->totalCompra<<endl;
        archivoInfo<<endl;

        puntero++;
    }

    archivoInfo.close();

    cout<<"Informacion guardada.";
}
