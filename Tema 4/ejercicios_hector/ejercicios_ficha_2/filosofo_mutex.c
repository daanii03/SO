#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5

pthread_mutex_t mutex_smph[NUM_FILOSOFOS];
pthread_mutex_t mutex_estado;
int state_fil[NUM_FILOSOFOS];

void print_state(){
    printf("Estado:");
    for (int j = 0; j < NUM_FILOSOFOS; j++){
        switch (state_fil[j]){
            case 0:
                printf("Estado %d: pensando ",j);
                break;

            case 1:
                printf("Estado %d: comiendo ",j);
                break;
            
            case 2:
                printf("Estado %d: esperando ",j);
                break;
        }
    }
    printf("\n");
}
void * th_filosofos(void * arr){
    
    int filosofo_act = *(int *) arr;

    while (1){
        pthread_mutex_lock(&mutex_estado);
        state_fil[filosofo_act] = 0;
        printf("Filosofo %d pensando\n", filosofo_act);
        print_state();
        pthread_mutex_unlock(&mutex_estado);

        sleep(rand() % 10 + 1);

        pthread_mutex_lock(&mutex_estado);
        state_fil[filosofo_act] = 2;
        printf("El filosofo %d quiere comer\n", filosofo_act);
        print_state();
        pthread_mutex_unlock(&mutex_estado);

        if (filosofo_act % 2 == 0){
            pthread_mutex_lock(&mutex_smph[filosofo_act]);
            pthread_mutex_lock(&mutex_smph[(filosofo_act + 1) % NUM_FILOSOFOS]);
        }else{
            pthread_mutex_lock(&mutex_smph[(filosofo_act + 1) % NUM_FILOSOFOS]);
            pthread_mutex_lock(&mutex_smph[filosofo_act]);
        }

        pthread_mutex_lock(&mutex_estado);
        state_fil[filosofo_act] = 1;
        printf("El filosofo %d esta comiendo\n", filosofo_act);
        print_state();
        pthread_mutex_unlock(&mutex_estado);

        sleep(rand() % 10 + 1);

        pthread_mutex_unlock(&mutex_smph[filosofo_act]);
        pthread_mutex_unlock(&mutex_smph[(filosofo_act + 1) % NUM_FILOSOFOS]);
        
        pthread_mutex_lock(&mutex_estado);
        state_fil[filosofo_act] = 0;
        pthread_mutex_unlock(&mutex_estado);
    }

    pthread_exit(NULL);
}

int main(){

    srand(time(NULL));

    int ids[NUM_FILOSOFOS];
    for (int i = 0; i < NUM_FILOSOFOS; i++){
        ids[i] = i;
        state_fil[i] = 0;
    } 

    for (int i = 0; i < NUM_FILOSOFOS; i++){
        pthread_mutex_init(&mutex_smph[i], NULL);
    }
    pthread_mutex_init(&mutex_estado, NULL);

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
        pthread_mutex_destroy(&mutex_smph[i]);
    }
    pthread_mutex_destroy(&mutex_estado);

    return 0;
}