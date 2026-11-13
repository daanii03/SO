#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

#define FILOSOFOS 5

sem_t palillo[FILOSOFOS];

void* th_filosofo(void* arg) {
    int fil_id = *(int*)arg;

    while (1) {
        printf("Filósofo %d pensando\n", fil_id);
        sleep((rand() % 5) + 1);
        printf("Filósofo %d quiere comer\n", fil_id);

        if (fil_id % 2 == 0) {
            sem_wait(&palillo[(fil_id + 1) % 5]);
            sem_wait(&palillo[fil_id]);
        }

        else {
            sem_wait(&palillo[fil_id]);
            sem_wait(&palillo[(fil_id + 1) % 5]);
        }

        printf("Filósofo %d comiendo\n", fil_id);
        sleep((rand() % 10) + 1);

        sem_post(&palillo[fil_id]);
        sem_post(&palillo[(fil_id + 1) % 5]);
    }
}

int main() {
    srand(time(NULL));
    pthread_t filosofo[FILOSOFOS];
    int uno = 1, dos = 2, tres = 3, cuatro = 4, cero = 0;
    int i;

    for (i = 0; i < FILOSOFOS; i++) {
       sem_init(&palillo[i], 0,1);
    }

    pthread_create(&filosofo[0], NULL, th_filosofo, &cero);
    pthread_create(&filosofo[1], NULL, th_filosofo, &uno);
    pthread_create(&filosofo[2], NULL, th_filosofo, &dos);
    pthread_create(&filosofo[3], NULL, th_filosofo, &tres);
    pthread_create(&filosofo[4], NULL, th_filosofo, &cuatro);

    while (1);
    return 0;
}