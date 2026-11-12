
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void *print_first(void *t){
    printf("%s\n", (char*) t);
    sem_post(&sem);
    pthread_exit(NULL);
}

void *print_second(void* t) {
    sem_wait(&sem);
    printf("%s\n", (char*)t);
    pthread_exit(NULL);
}

int main(){

    pthread_t th1,th2;
    sem_init(&sem,0,0);
    pthread_create(&th1,NULL,print_first,"Hola desde el hilo 1");
    pthread_create(&th2,NULL,print_second,"Hola desde el hilo 2");
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    sem_destroy(&sem);
    return 0;
}