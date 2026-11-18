
/*
    Este es el código del ejemplo de la cena de los filósofos, 
    SIN SOLUCIONAR EL DEADLOCK, solo es una aclaración de las diapositivas de ayuda.
*/

#define FILOSOFOS 5
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t filosofos[FILOSOFOS]; //Inicializamos un array de tids siendo cada thread un filósofo
pthread_mutex_t palillos[FILOSOFOS]; //Los mutex serán los palillos puesto que sin palillos no puede comer

void *th_filosofo(void *arg){
    /*
        Aquí vamos a saber si es el filósofo 0,1,2,3,4
        Como le hemos pasado la dirección de memoria de las variables y eran
        de tipo int, el puntero sería de tipo int *, pero como se debe castear
        a void *, lo tenemos que volver a castear dentro de la función del hilo
        y con el * accedemos al valor de las variables.
    */

    int fil_id = *(int *) arg; 
    while(1){
        printf("Filósofo %d pensando.\n",fil_id);
        sleep((rand() % 10)+1);
        printf("Filósfo %d quiere comer.\n",fil_id);
        /*
            Cuando quiere comer un filósofo va a bloquear su palillo
            y el de la derecha para que pueda comer eso es lo que 
            indican los mutex.
        */
        pthread_mutex_lock(&palillos[fil_id]);
        pthread_mutex_lock(&palillos[(fil_id + 1) % 5]);
        printf("Filósfo %d comiendo.\n", fil_id);
        /*
            Cuando termina de comer los suelta.
            Pero ¿cúal es el problema? Si todos quieren comer a la vez, van a coger su palillo, 
            entonces ninguno va a poder coger el palillo de su derecha.
            Es decir, si los 5 quieren comer a la vez, el 0 coge su palillo,
            y como el 1 también lo ha cogido, el 0 no puede coger el 1, 
            el 1 no puede coger el 2, y así sucesivamente, porque el 4
            tendría que coger el 0 que es el que estaría a su derecha.
        */
        pthread_mutex_unlock(&palillos[fil_id]);
        pthread_mutex_unlock(&palillos[(fil_id +1) % 5]);
    }
}

int main()
{
    srand(time(NULL));
    int uno = 1, dos = 2, tres = 3, cuatro = 4, cero = 0;
    int i;
    for (i = 0; i < FILOSOFOS; i++){
        pthread_mutex_init(&palillos[i],NULL);
    }

    // Se crean los threads con cada uno de los números identificativos de cada filósofo

    pthread_create(&filosofos[0],NULL,th_filosofo,(void *) &cero);
    pthread_create(&filosofos[1],NULL,th_filosofo,(void *) &uno);
    pthread_create(&filosofos[2],NULL,th_filosofo,(void*) &dos);
    pthread_create(&filosofos[3],NULL,th_filosofo,(void *) &tres);
    pthread_create(&filosofos[4],NULL,th_filosofo,(void *) &cuatro);
    
    while (1);
    return 0;
}
