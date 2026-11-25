#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <cstdint>

using namespace std;
// devuelve un array con una posicion por letra (A...Z)
// valores[letra - 'A'] = digito que tiene esa letra
// -1 , la letra aparece en el acertijo pero todavia no tiene digito
// -2 , la letra no aparece en el acertijo
int *listaValores(string *sumandos, int cantSumandos, string resultado)
{
    int *valores = new int[26];
    for (int i = 0; i < 26; i++)
    {
        valores[i] = -2;
    }

    for (int i = 0; i < cantSumandos; i++)
    {
        for (int j = 0; j < sumandos[i].length(); j++)
        {
            char letra = sumandos[i][j];
            valores[letra - 'A'] = -1;
        }
    }
    for (int j = 0; j < resultado.length(); j++)
    {
        char letra = resultado[j];
        valores[letra - 'A'] = -1;
    }

    return valores;
}

std::int64_t palabraANumero(string palabra, int *valores) // arma el número a base de la palabra multiplicando por 10 y sumando el dígito de cada letra
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
        for (int i = 0; i < cantSumandos && !decidido; i++) // Gana el menor resultado,si empatan, gana el menor primer sumando,si siguen empatando, el menor segundo sumando, y asi
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
void evaluarSolucion(int *valores, int cantSumandos, string *sumandos, string resultado, std::int64_t *mejor, bool &hay)
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
// devuelve el digito que tiene la palabra en esa columna
// si la palabra es mas corta y no llega a esa columna, devuelve 0
// si la letra todavia no tiene digito, devuelve -1
int digitoEnColumna(string palabra, int columna, int *valores) //(funcion separada de podaColumnas por IA)
{
    int digito = 0;
    int largo = palabra.length();
    if (columna < largo)
    {
        char letra = palabra[largo - 1 - columna];
        digito = valores[letra - 'A'];
    }
    return digito;
}

// hace la suma columna por columna desde la derecha
// devuelve true si alguna columna no cierra
// frena cuando llega a una columna con alguna letra sin digito
bool podaColumnas(int *valores, int cantSumandos, string *sumandos, string resultado)
{
    bool hayQuePodar = false;
    bool sigo = true;
    int acarreo = 0;

    for (int columna = 0; columna < resultado.length() && sigo; columna++)
    {
        int suma = acarreo;
        for (int i = 0; i < cantSumandos && sigo; i++)
        {
            int digito = digitoEnColumna(sumandos[i], columna, valores);
            if (digito == -1)
            {
                sigo = false; // falta asignar una letra, esta columna no se puede revisar
            }
            else
            {
                suma = suma + digito;
            }
        }

        if (sigo)
        {
            int digitoResultado = digitoEnColumna(resultado, columna, valores);
            if (digitoResultado == -1)
            {
                sigo = false; // la letra del resultado todavia no tiene digito
            }
            else
            {
                if (suma % 10 != digitoResultado)
                {
                    hayQuePodar = true;
                    sigo = false;
                }
                acarreo = suma / 10;
            }
        }
    }
    return hayQuePodar;
}


void backtracking(int pos, int *orden, int cantLetras, int *valores, int cantSumandos, bool *valoresDispoibles, bool *esInicial, string *sumandos, string resultado, std::int64_t *mejor, bool &hay){
    if (pos == cantLetras)// si ya le di digito a todas las letras (fragmento generado por IA)
    {
        evaluarSolucion(valores, cantSumandos, sumandos, resultado, mejor, hay);
    }
    else
    {
        int letra = orden[pos]; 
        for (int d = 0; d < 10; d++)
            {
                if (valoresDispoibles[d] && !(d == 0 && esInicial[letra]) ) // el digito d esta disponible y no puede pasar que si el d es 0 la letra sea inicial
                {
                    valores[letra] = d;
                    valoresDispoibles[d] = false;

                    if(!podaColumnas(valores,cantSumandos,sumandos,resultado)){
                         backtracking(pos + 1, orden, cantLetras, valores, cantSumandos, valoresDispoibles, esInicial, sumandos, resultado, mejor, hay);

                    }
                   
                    valoresDispoibles[d] = true;
                    valores[letra] = -1;
                }
            }
    }
}


std::int64_t *solucionAcertijo(int cantSumandos, string *sumandos, string resultado)
{
    std::int64_t *sol = new std::int64_t[cantSumandos + 1];

    bool *valoresDispoibles = new bool[10];
    for (int i = 0; i < 10; i++)
    {
        valoresDispoibles[i] = true;
    }

    int *valores = listaValores(sumandos, cantSumandos, resultado);

    bool *esInicial = new bool[26];
    for (int i = 0; i < 26; i++)
    {
        esInicial[i] = false;
    }

    for (int i = 0; i < cantSumandos; i++)
    {
        if (sumandos[i].length() > 1)
        {
            esInicial[sumandos[i][0] - 'A'] = true;
        }
    }
    if (resultado.length() > 1)
    {
        esInicial[resultado[0] - 'A'] = true;
    }

    bool hay = false;

    bool posible = true;
    for (int i = 0; i < cantSumandos && posible; i++)
    {
        if (sumandos[i].length() > resultado.length()) 
        {
            posible = false;
        }
    }

    int *orden = new int[10]; //(fragmento generado por IA)
    int cantLetras = 0;
    bool *agregada = new bool[26];
    for (int i = 0; i < 26; i++)
    {
        agregada[i] = false;
    }
    for (int columna = 0; columna < resultado.length(); columna++)
    {
        for (int i = 0; i <= cantSumandos; i++) 
        {
            string palabra = resultado;
            if (i < cantSumandos)
            {
                palabra = sumandos[i];
            }
            int largo = palabra.length();
            if (columna < largo)
            {
                int letra = palabra[largo - 1 - columna] - 'A';
                if (!agregada[letra])
                {
                    agregada[letra] = true;
                    orden[cantLetras] = letra;
                    cantLetras++;
                }
            }
        }
    }

    if (posible)
    {
        backtracking(0, orden, cantLetras, valores, cantSumandos, valoresDispoibles, esInicial, sumandos, resultado, sol, hay);
    }

    delete[] valoresDispoibles;
    delete[] valores;
    delete[] esInicial;
    delete[] orden;
    delete[] agregada;

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
