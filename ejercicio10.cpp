#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int* solucionAcertijo(int cantSumandos, string* sumandos ){
        int* sol = new int*[cantSumandos + 1];
}


int main()
{
    int cantAcertijos;
    std::cin>> cantAcertijos; 

    for (int i = 0; i < cantAcertijos; i++)
    {
        int cantSumandos;
        std:: cin >> cantSumandos;
        string* sumandos = new string[cantSumandos];
            for ( int j = 0; j < cantSumandos; j++)
            {
                    std:: cin >> sumandos[j];
            }
        
        string resultado;
        std:: cin >> resultado;
    }
    return 0;
}