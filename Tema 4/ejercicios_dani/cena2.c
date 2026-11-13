#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FILOSOFOS 5

pthread_mutex_t mutex;
pthread_cond_t hay_palillo[FILOSOFOS];
int estado_filosofo[5];
const char *nombres_estado[] = {"pensando","esperando","comiendo"};

void* th_filosofo(void* arg) {
    int fil_id = *(int*)arg;

    while (1) {
        printf("Filósofo %d pensando\n", fil_id);
        pthread_mutex_lock(&mutex);
        printf("Estado: ");
        for(int i = 0; i < FILOSOFOS; i++){

            printf("%d => %s ",i,nombres_estado[estado_filosofo[i]]);
        }
        printf("\n");
        estado_filosofo[fil_id] = 0;
        pthread_mutex_unlock(&mutex);
        sleep((rand() % 5) + 1);
        printf("Filósofo %d quiere comer\n", fil_id);
        pthread_mutex_lock(&mutex);
        estado_filosofo[fil_id] = 1;
        while (estado_filosofo[(fil_id + 4) % 5] == 2 || estado_filosofo[(fil_id +1) % 5] == 2){
            pthread_cond_wait(&hay_palillo[fil_id],&mutex);
        }

        printf("Filósofo %d comiendo\n", fil_id);
        estado_filosofo[fil_id] = 2;
        pthread_mutex_unlock(&mutex);
        sleep((rand() % 5) + 1);

        pthread_mutex_lock(&mutex);
        estado_filosofo[fil_id] = 0;
        pthread_cond_signal(&hay_palillo[(fil_id +4) % 5]);
        pthread_cond_signal(&hay_palillo[(fil_id +1) % 5]);
        pthread_mutex_unlock(&mutex);

    }
}

int main() {
    srand(time(NULL));
    pthread_t filosofo[FILOSOFOS];
    int uno = 1, dos = 2, tres = 3, cuatro = 4, cero = 0;
    int i;

    pthread_mutex_init(&mutex,NULL);
    for (i = 0; i < FILOSOFOS; i++) pthread_cond_init(&hay_palillo[i],NULL);
    pthread_create(&filosofo[0], NULL, th_filosofo, &cero);
    pthread_create(&filosofo[1], NULL, th_filosofo, &uno);
    pthread_create(&filosofo[2], NULL, th_filosofo, &dos);
    pthread_create(&filosofo[3], NULL, th_filosofo, &tres);
    pthread_create(&filosofo[4], NULL, th_filosofo, &cuatro);

    while (1);
    return 0;
}