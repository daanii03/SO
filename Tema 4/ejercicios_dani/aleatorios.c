
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int fd[2];

void handler(int signum) {
  (void) signum;
  int num = rand() % 11;
  if (write(fd[1], &num, sizeof(num)) == -1) {
    perror("Error en write dentro del handler");
  }
}

int main() {
  pid_t pid;
  int status;
  int num;
  char buf[1024];

  if (pipe(fd) == -1) {
    perror("Error al crear el pipe");
    return 1;
  }

  pid = fork();
  if (pid < 0) {
    perror("Error en fork");
    close(fd[0]);
    close(fd[1]);
    return 1;
  } else if (pid == 0) {
    if (close(fd[0]) == -1)
      perror("Error al cerrar fd[0] en el hijo");
    srand(time(NULL));
    if (signal(SIGUSR1, handler) == SIG_ERR) {
      perror("Error al registrar el manejador de SIGUSR1 en el hijo");
      close(fd[1]);
      exit(1);
    }
    while (1)
      pause();
  } else {

    if (close(fd[1]) == -1)
      perror("Error al cerrar el fd[1] en el padre");

    while ((fgets(buf, sizeof(buf), stdin)) != NULL) {
      if (kill(pid, SIGUSR1) == -1) {
        perror("Error al enviar SIGUSR1 al hijo");
        break;
      }

      ssize_t bytes_leidos = read(fd[0], &num, sizeof(num));
      if (bytes_leidos == -1) {
        perror("Error al leer del pipe en el padre");
        break;
      } else if (bytes_leidos == 0) {
        fprintf(stderr, "El hijo cerró el pipe inesperadamente\n");
        break;
      }

      printf("%d\n", num);
    }
    kill(pid, SIGTERM);
    if (close(fd[0]) == -1)
      perror("Error al cerrar fd[0] en el padre");
    if (wait(&status) == -1) {
      perror("Error en wait");
      return 1;
    }
  }
  return 0;
}
