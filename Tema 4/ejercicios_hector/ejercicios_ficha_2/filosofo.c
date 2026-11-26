#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5

sem_t arr_smph[NUM_FILOSOFOS];

void * th_filosofos(void * arr){
    
    int filosofo_act = *(int *) arr;

    while (1){
        printf("Filosofo %d pensando\n", filosofo_act);

        sleep(rand() % 10 + 1);

        printf("El filosofo %d quiere comer\n", filosofo_act);

        if (filosofo_act % 2 == 0){
            sem_wait(&arr_smph[filosofo_act]);
            sem_wait(&arr_smph[(filosofo_act + 1) % NUM_FILOSOFOS]);
        }else{
            sem_wait(&arr_smph[(filosofo_act + 1) % NUM_FILOSOFOS]);
            sem_wait(&arr_smph[filosofo_act]);
        }
 
        printf("El filosofo %d esta comiendo\n", filosofo_act);

        sleep(rand() % 10 + 1);

        sem_post(&arr_smph[filosofo_act]);
        sem_post(&arr_smph[(filosofo_act + 1) % NUM_FILOSOFOS]);
    }

    pthread_exit(NULL);
}

int main(){

    srand(time(NULL));

    int ids[NUM_FILOSOFOS];
    for (int i = 0; i < NUM_FILOSOFOS; i++){
        ids[i] = i;
    } 

    for (int i = 0; i < NUM_FILOSOFOS; i++){
        sem_init(&arr_smph[i], 0, 1);
    }   

    pthread_t ph1, ph2, ph3, ph4, ph5;

    pthread_create(&ph1, NULL, th_filosofos, (void *) &ids[0]);
    pthread_create(&ph2, NULL, th_filosofos, (void *) &ids[1]);
    pthread_create(&ph3, NULL, th_filosofos, (void *) &ids[2]);
    pthread_create(&ph4, NULL, th_filosofos, (void *) &ids[3]);
    pthread_create(&ph5, NULL, th_filosofos, (void *) &ids[4]);

    pthread_join(ph1, NULL);
    pthread_join(ph2, NULL);
    pthread_join(ph3, NULL);
    pthread_join(ph4, NULL);
    pthread_join(ph5, NULL);
    
    for (int i = 0; i < NUM_FILOSOFOS; i++){
        sem_destroy(&arr_smph[i]);
    }

    return 0;
}