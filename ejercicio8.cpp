#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
struct producto
{
    int peso;
    int satisfaccion;
    int categoria;
};

int satisfaccionTab(producto *productos, int cantProductos, int *limites, int pesoHeladera);

int main()
{
    int cantProductos;
    int pesoHeladera;

    std::cin >> cantProductos >> pesoHeladera;

    int *limites = new int[4];

    for (int i = 0; i < 4; i++)
    { // tomo datos de los limites
        std::cin >> limites[i];
    }

    producto *productos = new producto[cantProductos];

    for (int i = 0; i < cantProductos; i++)
    { // lista productos
        std::cin >> productos[i].peso >> productos[i].satisfaccion >> productos[i].categoria;
    }

    std::cout << satisfaccionTab(productos, cantProductos, limites, pesoHeladera) << std::endl;

    delete[] productos;
    delete[] limites;
    return 0;
}

int satisfaccionTab(producto *productos, int cantProductos, int *limites, int pesoHeladera)
{
    // tab[i][peso][c0][c1][c2][c3] = maxima satisfaccion que puedo sacar
    // desde el producto i en adelante, con "peso" libre en la heladera,
    // habiendo comprado c0 de la cat 0, c1 de la cat 1, c2 de la cat 2 y c3 de la cat 3.
    // cada c va de 0 a su limite, por eso cada dimension tiene tamaño limite + 1


    // caso base, no quedan productos (i == cantProductos), ahi la satisfaccion es 0 sin importar el peso libre
    int ******tab = new int *****[cantProductos + 1];
    for (int i = 0; i <= cantProductos; i++)
    {

        tab[i] = new int ****[pesoHeladera + 1];

        for (int j = 0; j <= pesoHeladera; j++)
        {

            tab[i][j] = new int ***[limites[0] + 1];

            for (int c0 = 0; c0 <= limites[0]; c0++)
            {

                tab[i][j][c0] = new int **[limites[1] + 1];

                for (int c1 = 0; c1 <= limites[1]; c1++)
                {

                    tab[i][j][c0][c1] = new int *[limites[2] + 1];

                    for (int c2 = 0; c2 <= limites[2]; c2++)
                    {

                        tab[i][j][c0][c1][c2] = new int[limites[3] + 1];

                        for (int c3 = 0; c3 <= limites[3]; c3++)
                        {
                            tab[i][j][c0][c1][c2][c3] = 0; // inicializo toda la matriz en 0
                        }
                    }
                }
            }
        }
    }

    // lleno de abajo hacia arriba: la hoja i usa la hoja i+1 (igual que resolver(indice+1))
    for (int i = cantProductos - 1; i >= 0; i--)
    {
        int cat = productos[i].categoria; //categoria de cada producto
        int peso = productos[i].peso; // peso del producto

        for (int j = 0; j <= pesoHeladera; j++)
        {
            for (int c0 = 0; c0 <= limites[0]; c0++)
            {
                for (int c1 = 0; c1 <= limites[1]; c1++)
                {
                    for (int c2 = 0; c2 <= limites[2]; c2++)
                    {
                        for (int c3 = 0; c3 <= limites[3]; c3++)
                        {

                            // opcion 1: no compro este producto
                            int res = tab[i + 1][j][c0][c1][c2][c3];

                            // armo comprado para poder fijarme en la categoria del producto
                            int comprado[4] = {c0, c1, c2, c3};

                            // opcion 2: lo compro, si entra y no me paso del limite de su categoria
                            if (peso <= j && comprado[cat] < limites[cat]) 
                            {
                                comprado[cat]++; // un producto mas de esa categoria
                                int comprando = productos[i].satisfaccion + tab[i + 1][j - peso][comprado[0]][comprado[1]][comprado[2]][comprado[3]];// i+1 pasa al sig pproducto y se le resta el peso del producto a J que es el espacio que te queda en la heladera 
                                if (comprando > res)
                                {
                                    res = comprando;
                                }
                            }
                            tab[i][j][c0][c1][c2][c3] = res; // guardo
                        }
                    }
                }
            }
        }
    }

    // arranco desde el producto 0 ,tengo todos para elegir,
    // la heladera esta vacia y no compre nada 
    int resultado = tab[0][pesoHeladera][0][0][0][0];

    // libero la memoria
    for (int i = 0; i <= cantProductos; i++)
    {
        for (int j = 0; j <= pesoHeladera; j++)
        {
            for (int c0 = 0; c0 <= limites[0]; c0++)
            {
                for (int c1 = 0; c1 <= limites[1]; c1++)
                {
                    for (int c2 = 0; c2 <= limites[2]; c2++)
                    {
                        delete[] tab[i][j][c0][c1][c2];
                    }
                    delete[] tab[i][j][c0][c1];
                }
                delete[] tab[i][j][c0];
            }
            delete[] tab[i][j];
        }
        delete[] tab[i];
    }
    delete[] tab;

    return resultado;
}

/* Manera recursiva
int satisfaccionMaxima(producto *productos, int cantProductos,
                       int pesoHeladera, int *limites)
{
    int comprado[4] = {0, 0, 0, 0};

    return resolver(productos, cantProductos, 0, pesoHeladera,
                    limites, comprado);
}

int resolver(producto *productos, int cantProductos, int indiceProducto, int pesoRestante, int *limites, int *comprado)
{
    int res = 0;
    if (indiceProducto < cantProductos)
    {
        // opcion 1: no compro este producto
        int sinComprar = resolver(productos, cantProductos, indiceProducto + 1, pesoRestante, limites, comprado); // veo el caso en que no lo compro
        res = sinComprar;

        // opcion 2: lo compro, si entra y no me paso del limite de su categoria
        int cat = productos[indiceProducto].categoria;
        int peso = productos[indiceProducto].peso;
        if (peso <= pesoRestante && comprado[cat] < limites[cat])
        { // veo el caso en el que compro
            comprado[cat]++;
            int comprando = productos[indiceProducto].satisfaccion + resolver(productos, cantProductos, indiceProducto + 1, pesoRestante - peso, limites, comprado);
            comprado[cat]--; // deshago para no afectar otras ramas

            if (comprando > res)
            { // en el caso que comprando sea mayor la satisfaccion que el comprado, entonces la satisfaccion se toma como la del comprando
                res = comprando;
            }
        }
    }
    return res;
}
*/