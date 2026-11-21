#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <cstdint>

using namespace std;
// devuelve un array con una posicion por letra (A..Z)
// valores[letra - 'A'] = digito que tiene esa letra
// -1 = la letra aparece en el acertijo pero todavia no tiene digito
// -2 = la letra no aparece en el acertijo
int *listaValores(string *sumandos, int cantSumandos, string resultado)
{
    int *valores = new int[26];
    for (int i = 0; i < 26; i++)
    {
        valores[i] = -2;
    }

    for (int i = 0; i < cantSumandos; i++)
    {
        for (int j = 0; j < sumandos[i].length(); j++) // por cada sumando agarran su largo y poner que existe;
        {
            char letra = sumandos[i][j]; // ver cada letra de la palabra
            valores[letra - 'A'] = -1;   // poner que existe
        }
    }
    // marcar letras del resultado
    for (int j = 0; j < resultado.length(); j++)
    {
        char letra = resultado[j];
        valores[letra - 'A'] = -1;
    }

    return valores;
}

std::int64_t palabraANumero(string palabra, int *valores)
{
    std::int64_t numero = 0;
    for (int i = 0; i < palabra.length(); i++)
    {
        numero = numero * 10 + valores[palabra[i] - 'A'];
    }
    return numero;
}

bool esMejor(std::int64_t *actual, std::int64_t *mejor, int cantSumandos)
{
    bool res = false;
    if (actual[cantSumandos] != mejor[cantSumandos])
    {
        res = actual[cantSumandos] < mejor[cantSumandos];
    }
    else
    {
        bool decidido = false;
        for (int i = 0; i < cantSumandos && !decidido; i++)
        {
            if (actual[i] != mejor[i])
            {
                res = actual[i] < mejor[i];
                decidido = true;
            }
        }
    }
    return res;
}

// se llama cuando todas las letras tienen digito
// pasa las palabras a numero, chequea la suma y si es mejor la guarda
void evaluarSolucion(int *valores, int cantSumandos, string *sumandos, string resultado,
                     std::int64_t *mejor, bool &hay)
{
    std::int64_t *actual = new std::int64_t[cantSumandos + 1];
    std::int64_t suma = 0;
    for (int i = 0; i < cantSumandos; i++)
    {
        actual[i] = palabraANumero(sumandos[i], valores);
        suma = suma + actual[i];
    }
    actual[cantSumandos] = palabraANumero(resultado, valores);

    if (suma == actual[cantSumandos])
    {
        // si es la primera que encuentro, o es mejor que la guardada, la guardo
        if (!hay || esMejor(actual, mejor, cantSumandos))
        {
            for (int i = 0; i <= cantSumandos; i++)
            {
                mejor[i] = actual[i];
            }
            hay = true;
        }
    }
    delete[] actual;
}

void backtracking(int pos, int *valores, int cantSumandos, bool *valoresDispoibles, bool *esInicial, string *sumandos, string resultado, std::int64_t *mejor, bool &hay)
{
    if (pos == 26)
    {
        evaluarSolucion(valores, cantSumandos, sumandos, resultado, mejor, hay);
    }
    else
    {
        if (valores[pos] == -2)
        {
            backtracking(pos + 1, valores, cantSumandos, valoresDispoibles, esInicial, sumandos, resultado, mejor, hay); // si el valor es -2 esa letra no aparece
        }
        else // la letra aparece: pruebo cada digito
        {
            for (int d = 0; d < 10; d++) // pruebo cada digito para la letra (letra es pos)
            {
                if (valoresDispoibles[d] && (d != 0 || !esInicial[pos]))
                {
                    valores[pos] = d;             // tomo el valor y lo pongo el chat que corresponde (pos)
                    valoresDispoibles[d] = false; // ocupo el valor

                    backtracking(pos + 1, valores, cantSumandos, valoresDispoibles, esInicial, sumandos, resultado, mejor, hay); // hago backtrack con el siguiente

                    valoresDispoibles[d] = true; // lo libero
                    valores[pos] = -1;
                }
            }
        }
    }
}

// devuelve la solucion (sumandos y al final el resultado), o NULL si no tiene
std::int64_t *solucionAcertijo(int cantSumandos, string *sumandos, string resultado)
{
    std::int64_t *sol = new std::int64_t[cantSumandos + 1];

    bool *valoresDispoibles = new bool[10]; // de 0 a 9
    for (int i = 0; i < 10; i++)
    {
        valoresDispoibles[i] = true;
    }

    int *valores = listaValores(sumandos, cantSumandos, resultado); // para cada letra

    bool *esInicial = new bool[26];
    for (int i = 0; i < 26; i++)
    {
        esInicial[i] = false; // arrancar todo en false
    }

    for (int i = 0; i < cantSumandos; i++)
    {
        if (sumandos[i].length() > 1) // si tiene mas de una letra
        {
            esInicial[sumandos[i][0] - 'A'] = true; // las letras iniciales de las palabras se ponen en true
        }
    }
    if (resultado.length() > 1)
    { // lo mismo para el resultado
        esInicial[resultado[0] - 'A'] = true;
    }

    bool hay = false;
    backtracking(0, valores, cantSumandos, valoresDispoibles, esInicial, sumandos, resultado, sol, hay);

    // libero la memoria
    delete[] valoresDispoibles;
    delete[] valores;
    delete[] esInicial;

    if (!hay)
    {
        delete[] sol;
        return NULL;
    }
    return sol;
}

int main()
{
    int cantAcertijos;
    std::cin >> cantAcertijos;

    for (int i = 0; i < cantAcertijos; i++)
    {
        int cantSumandos;
        std::cin >> cantSumandos;
        string *sumandos = new string[cantSumandos];
        for (int j = 0; j < cantSumandos; j++)
        {
            std::cin >> sumandos[j];
        }

        string resultado;
        std::cin >> resultado;

        std::int64_t *sol = solucionAcertijo(cantSumandos, sumandos, resultado);

        if (sol == NULL)
        {
            cout << "imposible" << endl;
        }
        else
        {
            for (int j = 0; j < cantSumandos; j++)
            {
                if (j > 0)
                {
                    cout << " + ";
                }
                cout << sol[j];
            }
            cout << " = " << sol[cantSumandos] << endl;
            delete[] sol;
        }
        delete[] sumandos;
    }
    return 0;
}
