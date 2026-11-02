
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t s1, s2;
    int fd[2];

    if (pipe(fd) < 0){
        perror("Error al crear pipe");
        return 1;
    }

    s1 = fork();
    if (s1 < 0) {
        perror("No se ha podido crear el proceso");
        close(fd[0]);
        close(fd[1]);
        return 1;
    }

    if (s1 == 0){
        close(fd[0]);
        dup2(fd[1],1);
        close(fd[1]);
        execlp("ls","ls","-la",NULL);
        perror("Error al ejecutar ls");
        exit(1);
    }
    
    s2 = fork();

    if (s2 < 0){
        perror("No se ha podido crear el proceso");
        close(fd[0]);
        close(fd[1]);
        return 1;
    }

    if (s2 == 0){
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        execlp("tr", "tr", "d", "D", NULL);
        perror("Error al ejecutar tr");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}