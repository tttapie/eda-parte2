#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int cantMaxLikes(int*** memo, int cantRondas, int rondaActual, int diferenciaAyB, int estadoBaileAnterior, int* pateadores, int* likes) {

      int maxLikes = 0;
       if (rondaActual < cantRondas) {

        if(memo[rondaActual][diferenciaAyB][estadoBaileAnterior] != -1){
            maxLikes = memo[rondaActual][diferenciaAyB][estadoBaileAnterior]; //si ya lo calcule, lo uso

        }else{
             int diferenciaTrasPateoA = diferenciaAyB + pateadores[rondaActual];

            //decide no bailar
             maxLikes = cantMaxLikes(memo, cantRondas, rondaActual + 1, diferenciaTrasPateoA, 0, pateadores, likes);

            //baila 
            if(diferenciaTrasPateoA > 0 ){
                int likesDelBaile = likes[rondaActual];

                   if (estadoBaileAnterior == 1) { 
                    likesDelBaile = likesDelBaile / 2;   
                    }

                int likesSiBaila =  likesDelBaile + cantMaxLikes(memo, cantRondas, rondaActual + 1, diferenciaTrasPateoA - 1, 1, pateadores, likes);
                    //pato baila entonces meten gol, x eso se resta a diferenciaTrasPateoA 
                if (likesSiBaila > maxLikes) {
                    maxLikes = likesSiBaila;
                }

            }
           memo[rondaActual][diferenciaAyB][estadoBaileAnterior] = maxLikes;
        }
      
       }
           return maxLikes;
}

int main()
{
    int cantRondas = 0;
   std:: cin >> cantRondas;

   int* pateadoresA = new int[cantRondas];
   for (int i = 0; i < cantRondas; i++)
   {
    std:: cin >>pateadoresA[i];
   }

   int* likes = new int[cantRondas];
   for (int i = 0; i < cantRondas; i++)
   {
    std:: cin >> likes[i];
   }
//memo[i][d][p]\, i son las rondas, d es la ventaja de A al empezar la ronda  y p es si bailo en el tiro anterior(variables del estado)
int*** memo = new int**[cantRondas];
for (int i = 0; i < cantRondas; i++) {
    memo[i] = new int*[cantRondas];
    for (int j = 0; j < cantRondas; j++) {
        memo[i][j] = new int[2];
        memo[i][j][0] = -1;
        memo[i][j][1] = -1;
    }
}
     
   cout << cantMaxLikes(memo, cantRondas, 0, 0, 0, pateadoresA, likes) << endl;
}


/* Manera recursiva
int cantMaxLikes(int cantRondas, int rondaActual, int diferenciaAyB, int estadoBaileAnterior, int* pateadores, int* likes) {
    int maxLikes = 0;                                   // caso base: no quedan rondas
    if (rondaActual < cantRondas) {
        int diferenciaTrasPateoA = diferenciaAyB + pateadores[rondaActual];

        // opcion 1: no bailar
        maxLikes = cantMaxLikes(cantRondas, rondaActual + 1, diferenciaTrasPateoA, 0, pateadores, likes);

        // opcion 2: bailar, solo si A no queda abajo despues del gol de B
        if (diferenciaTrasPateoA >= 1) {
            int likesDelBaile = likes[rondaActual];
            if (estadoBaileAnterior == 1) {
                likesDelBaile = likes[rondaActual] / 2;
            }
            int likesSiBaila = likesDelBaile + cantMaxLikes(cantRondas, rondaActual + 1, diferenciaTrasPateoA - 1, 1, pateadores, likes);
            if (likesSiBaila > maxLikes) {
                maxLikes = likesSiBaila;
            }
        }
    }
    return maxLikes;
}
*/