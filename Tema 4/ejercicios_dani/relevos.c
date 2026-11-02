
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_SONS 4

void handler(int signum) {}

int main() {

  pid_t pids[4];
  signal(SIGUSR1, handler);

  for (int i = 0; i < NUM_SONS; i++) {
    pids[i] = fork();
    if (pids[i] < 0) {
      perror("Error al ejecutar fork");
      return 1;
    } else if (pids[i] == 0) {
      pause();
      printf("Soy el proceso %d, corriendo ...\n", getpid());
      sleep(2);
      exit(0);
    }
  }
  printf("Todos los hijos creados.\n");
  printf("Doy la salida!\n");
  for (int i = 0; i < NUM_SONS; i++) {
    kill(pids[i], SIGUSR1);
    waitpid(pids[i], NULL, 0);
    if (i < NUM_SONS - 1)
      printf("Terminé. Paso el testigo al proceso %d\n", pids[i + 1]);
    else
      printf("Terminé!\n");
  }
  printf("Todos los hijos terminaron.\n");

  return 0;
}