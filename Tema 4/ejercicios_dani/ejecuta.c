
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr,
            "Error. No se ha pasado el comando que se quería ejecutar.\n");
    return 1;
  }
  pid_t pid;
  int status;
  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Error. No se ha podido crear un proceso hijo.\n");
    return 1;
  } else if (pid == 0) {
    execvp(argv[1], argv + 1);
    printf("Error al ejecutar el comando: %s\n", strerror(errno));
    exit(1);
  } else {
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) != 0)
      if (WEXITSTATUS(status) != 0)
        printf("El comando no se ejecutó correctamente.\n");
    exit(0);
  }
  return 0;
}
