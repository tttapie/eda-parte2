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

    delete[] producto;
    return 0;
}


int resolver(producto *productos, int cantProductos, int indiceProducto, int pesoRestante, int *limites, int *comprado)
{
    if (indiceProducto == cantProductos)
        return 0;

    int mejorSat = resolver(productos, cantProductos, indiceProducto + 1, pesoRestante, limites, comprado);

    producto p = productos[indiceProducto];
    if (p.peso > pesoRestante)
        return mejorSat;
    else
    {
        if (comprado[p.categoria] < limites[p.categoria])
        {
            comprado[p.categoria]++;
            int conProducto = p.satisfaccion + resolver(productos, cantProductos, indiceProducto + 1, pesoRestante - p.peso, limites, comprado);

            comprado[p.categoria]--;

            if (conProducto > mejorSat)
                mejorSat = conProducto;
        }
    }
    return mejorSat;
}


int satisfaccionMaxima(producto *productos, int cantProductos,
                       int pesoHeladera, int *limites)
{
    int comprado[4] = {0, 0, 0, 0};

    return resolver(productos, cantProductos, 0, pesoHeladera,
                    limites, comprado);
}


 /*
int resolver(producto *productos, int cantProductos, int indiceProducto, int pesoRestante, int *limites, int *comprado)
{
    int res = 0;
    if (indiceProducto < cantProductos) {
        // opcion 1: no compro este producto
        int sinComprar = resolver(productos, cantProductos, indiceProducto + 1, pesoRestante, limites, comprado); // veo el caso en que no lo compro 
        res = sinComprar;

        // opcion 2: lo compro, si entra y no me paso del limite de su categoria
        int cat = productos[indiceProducto].categoria;
        int peso = productos[indiceProducto].peso;
        if (peso <= pesoRestante && comprado[cat] < limites[cat]) { // veo el caso en el que compro 
            comprado[cat]++;
            int comprando = productos[indiceProducto].satisfaccion
                + resolver(productos, cantProductos, indiceProducto + 1, pesoRestante - peso, limites, comprado);
            comprado[cat]--;   // deshago para no afectar otras ramas

            if (comprando > res) { // en el caso que comprando sea mayor la satisfaccion que el comprado, entonces la satisfaccion se toma como la del comprando
                res = comprando;
            }
        }
    }
    return res;
}
/*