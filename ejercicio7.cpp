#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <cstdint>

using namespace std;

std::int64_t divideNConquer(int* aux ,int* ordenLlegada , int ini , int fin){

    if( ini == fin ){ //caso base si hay 1 solo elemento 
        return 0;
    }
    
int medio = (ini + fin)/2;
std::int64_t primeraMitad = divideNConquer(aux,ordenLlegada,ini,medio);
std::int64_t segundaMitad = divideNConquer(aux,ordenLlegada,medio+1,fin);
std::int64_t total = primeraMitad + segundaMitad;


int j= medio +1 ;
for(int i = ini ; i<=medio ; i++){  
    while(j <= fin && ordenLlegada[i] >2*ordenLlegada[j] ){ //(fragmento con idea sugerida por IA) 
        j++; //por cada i de la izq,j avanza por la derecha mientras i lo remonte, cuando no remonta, frena(todo lo que quedo atras son remontadas de i )
    }
    total  = total  + (j -(medio +1));
}


// merge: juntar las dos mitades ordenadas
int i = ini;        
j = medio + 1;      
int k = ini;


while (i <= medio && j <= fin) {
    if (ordenLlegada[i] <= ordenLlegada[j]) {
        aux[k] = ordenLlegada[i];
        i++;
    } else {
        aux[k] = ordenLlegada[j];
        j++;
    }
    k++;
}

while (i <= medio) {
    aux[k] = ordenLlegada[i];
    i++;
    k++;
}

while (j <= fin) {
    aux[k] = ordenLlegada[j];
    j++;
    k++;
}

// paso el tramo ya ordenado de aux al arreglo original,
// asi el nivel de arriba recibe esta parte ordenada
for (int p = ini; p <= fin; p++) {
    ordenLlegada[p] = aux[p];
}

return total;
}

int main()
{
 int corredores;
 std:: cin >> corredores ;

 int* ordenLlegada = new int[corredores];
 for(int i = 0; i< corredores ; i++){
    cin >> ordenLlegada[i];
 }
 int* aux = new int[corredores];

for (int i = 0; i < corredores; i++)
{
   aux[i] =0 ;
}

 std::int64_t remontadas = divideNConquer(aux,ordenLlegada,0,corredores-1);
 std:: cout << remontadas << endl;

 delete [] aux;
 delete [] ordenLlegada;
return 0;
}   