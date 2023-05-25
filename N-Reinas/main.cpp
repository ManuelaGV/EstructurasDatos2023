#include <iostream>
#include <bits/stdc++.h>
#define N 6

using namespace std;

/*
1. Inicializar un tablero de ajedrez vacío de NxN.
2. Empezar con la primera columna de la izquierda y colocar una reina en la primera fila de esa columna.
3. Moverse a la siguiente columna y colocar una reina en la primera fila de esa columna.
4. Repetir el paso 3 hasta que las N reinas hayan sido colocadas o hasta que sea imposible de colocar una reina en la columna actual sin violar las reglas del problema.
5. Si todas las reinas fueron colocadas, imprimir la solución.
6. Si no es posible colocar a una reina n la posición actual sin violar las reglas del problema, backtrack a la columna anterior.
7. Remover la reina de la columna anterior y moverla una fila abajo.
8. Repetir los pasos del 4 al 7 hasta que todas las posibles configuraciones se hayan intentado.
*/

void imprimirSolucion(int tablero[N][N]);
bool esSeguro(int tablero[N][N], int fila, int col);
bool solucion(int tablero[N][N], int col);
bool solicionNQ();

int main()
{
    solicionNQ();
    return 0;
}

//Función que imprime la solución.

void imprimirSolucion(int tablero[N][N])
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(tablero[i][j])
                cout<<" R ";
            else
                cout<<" - ";
        }
        cout<<endl;
    }
}

//Verifica si es seguro colocar una reina en una posición específica del tablero. Para esto realiza 3 chequeos: si hay uan reina en la misma columna o si hay una reina en las diagonales.

bool esSeguro(int tablero[N][N], int fila, int col)
{
    int i, j;

    //Chequea esta columna en el lado izquierdo
    for(i = 0; i < col; i++)
    {
        if(tablero[fila][i])
            return false;
    }

    //Chequea la diagonal superior izquierda
    for(i = fila, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if(tablero[i][j])
            return false;
    }

    //Chequea la diagonal inferior izquierda
    for(i = fila, j = col; j >= 0 && i < N; i++, j--)
    {
        if(tablero[i][j])
            return false;
    }

    return true;
}

//Usando la técnica de backtracking, se intenta encontrar una solución colocando una reina en cada columna del tablero.

bool solucion(int tablero[N][N], int col)
{
    //Si todas las reinas han sido colocadas (solución válida).
    if (col >= N)
        return true;

    //Tomando esta columna y tratando de colocar uan reina en todas las filas, una por una.
    for (int i = 0; i < N; i++)
    {
        //Chequear si la reina puede ser colocada en tablero[i][col]
        if (esSeguro(tablero, i, col))
        {
            //Colocar la reina en tablero[i][col]
            tablero[i][col] = 1;

            //Colocar el resto de las reinas
            if (solucion(tablero, col + 1))
                return true;

            //Si al colcoar la reina en tablero [i][col] no lleva a una solución, remover la reina del tablero.
            tablero[i][col] = 0;
        }
    }

    //Si la reina no pudo ser colcoada en niguna fila de esta columna retornar false.
    return false;
}

//Resuelve el problema de las N-reinas e imprime la solución encontrada.

bool solicionNQ()
{
    int tablero[N][N] = { { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 } };

    if (solucion(tablero, 0) == false)
    {
        cout << "La solucion no existe.";
        return false;
    }

    imprimirSolucion(tablero);
    return true;
}
