
#include <stdio.h>
#include <pthread.h>

#define MAX_BUFFER 10000

volatile int buffer[MAX_BUFFER];
volatile int err = 0;
int use_mutex = 0;
pthread_mutex_t mutex;

void *write_buff(){
    
    int num = 0;
    while (!err){
        if (use_mutex) pthread_mutex_lock(&mutex);
        for (int i = 0; i < MAX_BUFFER; i++){
            buffer[i] = num;
        }
        if (use_mutex) pthread_mutex_unlock(&mutex);
        num++;
    }
    pthread_exit(NULL);
}

void *read_buff(){
    while (!err){
        if (use_mutex) pthread_mutex_lock(&mutex);
        for (int i = 0; i < MAX_BUFFER; i++){
            if (buffer[i] != buffer[0]){
                fprintf(stderr, "Error. No sigue el mismo patrón.\n");
                err = 1;
                if (use_mutex) pthread_mutex_unlock(&mutex);
                pthread_exit(NULL);
            }
        }
        printf("Todo bien.\n");
        if (use_mutex) pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    pthread_t th1,th2;
    pthread_mutex_init(&mutex, NULL);
    if (argc > 1) use_mutex = 1;
    
    pthread_create(&th1,NULL,write_buff,NULL);
    pthread_create(&th2,NULL,read_buff,NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
