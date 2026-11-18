#include <stdio.h>
#include <pthread.h>

#define NUMELEMENT 10

pthread_mutex_t mutex;

int buffer[NUMELEMENT];

void * printBuffer(void * arr){

    pthread_mutex_lock(&mutex);
    for (int i = 0; i < NUMELEMENT; i++){
        
        printf("%d\n",buffer[i]);
        
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void * changeBuffer(void * arr){

    pthread_mutex_lock(&mutex);
    for (int i = 0; i < NUMELEMENT; i++){
         
        buffer[i] += 1;
        
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}


int main(){

    pthread_t ph1, ph2;

    pthread_create(&ph1, NULL, changeBuffer, NULL);
    pthread_create(&ph2,NULL,printBuffer,NULL);

    pthread_mutex_init(&mutex,NULL);

    pthread_join(ph1,NULL);
    pthread_join(ph2,NULL);

    pthread_mutex_destroy(&mutex); // Destruir mutex



}