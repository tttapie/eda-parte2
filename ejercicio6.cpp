#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;


int* Cantvalores(int* nrosPlacas, int placas) {
    int* valores = new int[1001]; // 1001 para que entre el indice 1000
    for (int i = 0; i <= 1000; i++) {
        valores[i] = 0; // inicializar en 0, new no lo hace
    }
    for (int i = 0; i < placas; i++) {
        valores[nrosPlacas[i]]++; // valores tiene cuantas veces aparece cada valor en las placas
    }
    return valores;
}

int* secuenciaOptima(int*nrosPlacas,int placas,int& largo){
    int* valores = Cantvalores(nrosPlacas,placas);
    int* cartel = new int[placas];// el cartel nunca tiene mas de n placas
    int cant = 0;
    int centro = -1;
    for (int i = 1000; i >= 0; i--) {
 
            int pares = valores[i] / 2; //para los valores que tengan 2 o mas, si tiene 1 da 0

         for (int j = 0; j < pares; j++) { // lo agrego al final del array (mitad izquierda) ;las mitad de las veces que aparece
            cartel[cant] = i;
            cant++;
            }
        
    if (valores[i] % 2 == 1 && centro == -1 ) {
        centro = i; // el  centro toma el mas grande que tenga valor impar de todos pqe el array se recorre de atras para ademante
    }

}


if(centro != -1){ 
cartel[cant]=centro; // agrego el centro luego de agregar todos los pares

for( int i = 1; i <= cant; i++){
    cartel[cant + i] = cartel[cant-i]; //espejo con centro
}

largo = 2 * cant + 1;

} else{//sino se cumple esto significa que todos eran pares 

    for( int i = 0; i < placas; i++){
    cartel[cant + i] = cartel[cant-1-i]; //espejo sin centro
    }
largo = 2 * cant;
}


      delete[] valores;
    return cartel;
}


int main()
{
    int placas;
    std:: cin >> placas ;  //>> es de lectura

    int* nrosPlacas = new int[placas];

    for(int i=0;i<placas;i++){ // tomo todos los numeros de las placas
        std::cin>>nrosPlacas[i] ;
    }

int largo;
int* cartel = secuenciaOptima(nrosPlacas, placas, largo);

for(int i = 0 ; i < largo ; i++){
    if (i > 0) {
        std::cout << " "; // espacio antes de cada numero menos el primero
    }
    std::cout << cartel[i];
}
std::cout << std::endl;

delete[] nrosPlacas;
delete[] cartel;
return 0;

}