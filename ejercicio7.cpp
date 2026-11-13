#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <cstdint>

using namespace std;

std::int64_t divideNConquer(int* aux ,int* ordenLlegada , int ini , int fin){ // ini fin , son del array

    if( ini == fin ){ //caso base si hay 1 solo elemento 
        return 0;
    }
    
int medio = (ini + fin)/2;
std::int64_t primeraMitad = divideNConquer(aux,ordenLlegada,ini,medio);//conquistar(llamar recursivo con cada mitad)
std::int64_t segundaMitad = divideNConquer(aux,ordenLlegada,medio+1,fin);
std::int64_t total = primeraMitad + segundaMitad;


int j= medio +1 ;
for(int i = ini ; i<=medio ; i++){  
    while(j <= fin && ordenLlegada[i] >2*ordenLlegada[j] ){ //parte modificada con ia 
        j++; //por cada i de la izq,j avanza por la derecha mientras i lo remonte, cuando no remonta, frena(todo lo que quedo atras son remontadas de i )
    }
    total  = total  + (j -(medio +1));//( j -(medio +1) son las remontadas de cada i)
}


// merge: juntar las dos mitades ordenadas
int i = ini;        
j = medio + 1;      
int k = ini; // posicion de aux


// copio a aux el menor de los dos y avanzo ese puntero
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

// si la derecha se termino primero, copio lo que quedo de la izquierda
while (i <= medio) {
    aux[k] = ordenLlegada[i];
    i++;
    k++;
}

// si la izquierda se termino primero, copio lo que quedo de la derecha
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