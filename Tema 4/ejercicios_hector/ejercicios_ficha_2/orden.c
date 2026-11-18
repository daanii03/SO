#include <stdio.h>
#include <pthread.h> //trabajar con hilos
#include <semaphore.h> //Trabajar con semanforos


sem_t semaforo;


void * printMessage1(void * arr){
    printf("Mensaje 1\n");
    sem_post(&semaforo);

    pthread_exit(NULL);
}

void * printMessage2(void * arr){
    sem_wait(&semaforo);
    printf("Mensaje 2\n");

    pthread_exit(NULL);
}

int main(){

    sem_init(&semaforo,0,0);

    pthread_t ph1, ph2;

    pthread_create(&ph1,NULL, printMessage1,NULL);
    pthread_create(&ph2,NULL, printMessage2,NULL);
    
    pthread_join(ph1,NULL);
    pthread_join(ph2,NULL);

    sem_destroy(&semaforo);

    return 0;
}