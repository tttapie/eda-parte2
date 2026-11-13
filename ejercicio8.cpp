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

    std::cout << satisfaccionTab(productos, cantProductos,  limites, pesoHeladera) << std::endl;

    delete[] productos;
    delete[] limites;
    return 0;
}

int satisfaccionTab(producto *productos, int cantProductos, int *limites, int pesoHeladera)
{
    int mult[4] = {1, 4, 16, 64};
    int ***tab = new int **[cantProductos + 1];
    int cantComb = 256; // 4*4*4*4 combinaciones de comprado()
    //   idx = c0 + c1*4 + c2*16 + c3*64
    // ej: comprado = [1,0,2,0] -> idx = 1 + 0 + 32 + 0 = 33
    // asi cada combinacion cae en una casilla distinta (de 0 a 255)
    for (int i = 0; i <= cantProductos; i++)
    {
        tab[i] = new int *[pesoHeladera + 1];
        for (int j = 0; j <= pesoHeladera; j++)
        {
            tab[i][j] = new int[cantComb];

            for (int k = 0; k < cantComb; k++)
            {
                tab[i][j][k] = 0;
            }
        }
    }

    // lleno de abajo hacia arriba: la fila i usa la fila i+1 (igual que resolver(indice+1))
    for (int i = cantProductos - 1; i >= 0; i--)
    {
        int cat = productos[i].categoria;
        int peso = productos[i].peso;
        for (int j = 0; j <= pesoHeladera; j++)
        {
            for (int k = 0; k < cantComb; k++)
            {
                // opcion 1: no compro este producto
                int res = tab[i + 1][j][k];

                int compradosCat = (k / mult[cat]) % 4; // "decodifico" comprado[cat] desde k
                if (peso <= j && compradosCat < limites[cat])
                {
                    // k + mult[cat] = misma combinacion con un producto mas de esa categoria
                    int comprando = productos[i].satisfaccion + tab[i + 1][j - peso][k + mult[cat]];
                    if (comprando > res)
                    {
                        res = comprando;
                    }
                }
                tab[i][j][k] = res;
            }
        }
    }
    int resultado = tab[0][pesoHeladera][0]; // arranco desde el producto 0, tengo todos los productos disponibles para elegir
                                             // la heladera esta vacia
                                             // no compré ninguno todavía

    for (int i = 0; i <= cantProductos; i++)
    {
        for (int j = 0; j <= pesoHeladera; j++)
        {
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