#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;


int* Cantvalores(int* nrosPlacas, int placas) {
    int* valores = new int[1001]; 
    for (int i = 0; i <= 1000; i++) {
        valores[i] = 0;
    }
    for (int i = 0; i < placas; i++) {
        valores[nrosPlacas[i]]++; // valores tiene cuantas veces aparece cada valor en las placas
    }
    return valores;
}

int* secuenciaOptima(int*nrosPlacas,int placas,int& largo){
    int* valores = Cantvalores(nrosPlacas,placas);
    int* cartel = new int[placas];
    int cant = 0; //placas de la mitad izquierda
    int centro = -1;
    for (int i = 1000; i >= 0; i--) {
 
            int pares = valores[i] / 2;

         for (int j = 0; j < pares; j++) {
            cartel[cant] = i;
            cant++;
            }
        
    if (valores[i] % 2 == 1 && centro == -1 ) {
        centro = i; 
    }

}


if(centro != -1){ 
cartel[cant]=centro;

for( int i = 1; i <= cant; i++){
    cartel[cant + i] = cartel[cant-i]; //espejo con centro
}

largo = 2 * cant + 1;

} else{

    for( int i = 0; i < cant; i++){
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
    std:: cin >> placas ;

    int* nrosPlacas = new int[placas];

    for(int i=0;i<placas;i++){
        std::cin>>nrosPlacas[i] ;
    }

int largo;
int* cartel = secuenciaOptima(nrosPlacas, placas, largo);

for(int i = 0 ; i < largo ; i++){
    if (i > 0) {
        std::cout << " ";
    }
    std::cout << cartel[i];
}
std::cout << std::endl;

delete[] nrosPlacas;
delete[] cartel;
return 0;

}