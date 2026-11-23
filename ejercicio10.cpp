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

std::int64_t palabraANumero(string palabra, int *valores) //arma el número multiplicando por 10 y sumando el dígito de cada letra.
{
    std::int64_t numero = 0;
    for (int i = 0; i < palabra.length(); i++)
    {
        numero = numero * 10 + valores[palabra[i] - 'A'];
    }
    return numero;
}

bool esMejor(std::int64_t *actual, std::int64_t *mejor, int cantSumandos){//solo compara, devuelve true si actual es mejor que mejor
    bool res = false;
    if (actual[cantSumandos] != mejor[cantSumandos])
    {
        res = actual[cantSumandos] < mejor[cantSumandos];
    }
    else
    {
        bool decidido = false;
        for (int i = 0; i < cantSumandos && !decidido; i++) //Gana el menor resultado,si empatan, gana el menor primer sumando,si siguen empatando, el menor segundo sumando, y así.
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
void evaluarSolucion(int *valores, int cantSumandos, string *sumandos, string resultado, std::int64_t *mejor, bool &hay){
    std::int64_t *actual = new std::int64_t[cantSumandos + 1];
    std::int64_t suma = 0;

    for (int i = 0; i < cantSumandos; i++){ // paso todas las palabras a numero
    
        actual[i] = palabraANumero(sumandos[i], valores);
        suma = suma + actual[i];
    }
//en actual guarda el nro de cada palabra y el resultado al final

    actual[cantSumandos] = palabraANumero(resultado, valores);// paso el resultado a numero

    if (suma == actual[cantSumandos]) // si la suma es = al resultado en numeros
    {
        // si es la primera que encuentro, o es mejor que la guardada, la guardo
        if (!hay || esMejor(actual, mejor, cantSumandos)) //entra si es la primera solucion que encuentra o si es mejor que la guardada
        {
            for (int i = 0; i <= cantSumandos; i++)
            {
                mejor[i] = actual[i]; // copia actial en mejor posicion x posicion(se actualiza mejor)
            }
            hay = true; // pone el hay en true si no lo estaba(es el 1ero que encuentra)
        }
    }
    delete[] actual;
}
//la mejor solucion queda guardada en mejor y hay
void backtracking(int pos, int *valores, int cantSumandos, bool *valoresDispoibles, bool *esInicial, string *sumandos, string resultado, std::int64_t *mejor, bool &hay){
   // mejor y &hay: aca se guarda la mejor solucion
   //el & hace que el cambio en hay se vea afuera de la funcion
    if (pos == 26)// si recorri todas las palabras
    {
        evaluarSolucion(valores, cantSumandos, sumandos, resultado, mejor, hay);//con la asignación completa, chequea si la suma da bien y, si es mejor, la guarda en mejor
    }
    else
    {
        if (valores[pos] == -2){ // esta letra no esta en el acertijo
            backtracking(pos + 1, valores, cantSumandos, valoresDispoibles, esInicial, sumandos, resultado, mejor, hay); // si el valor es -2 esa letra no aparece, continuo con pos+1
        }
        else // la letra aparece: pruebo cada digito
        {
            for (int d = 0; d < 10; d++) // pruebo cada digito para la letra (letra es pos)
            {
                if (valoresDispoibles[d] && !(d == 0 && esInicial[pos])) // el digito d esta disponible y 
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
//podas para backtracking
//Si un sumando tiene más letras que el resultado, es imposible: ese sumando solo ya es más grande que el resultado, porque no puede empezar con 0.
//comparar el largo de cada sumando, y si alguno es mas largo que la solucion entonces no hay solucion 
//claude: Poda por columnas (la importante)

// devuelve la solucion (sumandos y al final el resultado), o NULL si no tiene
std::int64_t *solucionAcertijo(int cantSumandos, string *sumandos, string resultado)
{
    std::int64_t* sol = new std::int64_t[cantSumandos + 1];

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
    return sol; // en sol queda la mejor solucion , NULL si no tienen sol
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
