
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pipe_des[2], pipe_des2[2], status;
  pid_t pid;
  char buf[1024];
  FILE *dad_write, *dad_read, *son_write, *son_read;

  if (pipe(pipe_des) == -1) {
    fprintf(stderr, "No se ha podido crear la pipe.\n");
    return 1;
  }
  if (pipe(pipe_des2) == -1) {
    close(pipe_des[0]);
    close(pipe_des[1]);
    fprintf(stderr, "No se ha podido crear la pipe.\n");
    return 1;
  }
  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Error. No se ha podido crear un proceso hijo: %s.\n",
            strerror(errno));
    return 1;
  } else if (pid == 0) {
    close(pipe_des[1]);
    close(pipe_des2[0]);
    son_read = fdopen(pipe_des[0], "r");
    if (!son_read) {
      fprintf(stderr, "No se ha podido abrir el descriptor de la pipe.\n");
      exit(1);
    }
    son_write = fdopen(pipe_des2[1], "w");
    if (!son_write) {
      fprintf(stderr, "No se ha podido abrir el descriptor de la pipe.\n");
      exit(1);
    }
    while ((fgets(buf, sizeof(buf), son_read)) != NULL) {
      int i = 0;
      while (buf[i] != '\0') {
        buf[i] = toupper(buf[i]);
        i++;
      }
      fputs(buf, son_write);
      fflush(son_write);
    }
    fclose(son_read);
    fclose(son_write);
    exit(0);
  } else {
    close(pipe_des[0]);
    close(pipe_des2[1]);
    dad_write = fdopen(pipe_des[1], "w");
    if (!dad_write) {
      fprintf(stderr, "No se ha podido abrir el descriptor de la pipe.\n");
      return 1;
    }
    dad_read = fdopen(pipe_des2[0], "r");
    if (!dad_read) {
      fprintf(stderr, "No se ha podido abrir el descriptor de la pipe.\n");
      return 1;
    }
    while ((fgets(buf, sizeof(buf), stdin)) != NULL) {
      fputs(buf, dad_write);
      fflush(dad_write);
      if ((fgets(buf, sizeof(buf), dad_read)) == NULL) {
        fprintf(stderr, "El hijo ha muerto de forma prematura.\n");
        return 1;
      }
      fputs(buf, stdout);
    }
    fclose(dad_write);
    fclose(dad_read);
    wait(&status);
  }
  return 0;
}