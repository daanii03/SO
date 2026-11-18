#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){

    int pipe_dest[2];
    
    pid_t pids[2];
    
    pipe(pipe_dest);
    for (int i = 0; i < 2; i++){
        pids[i] = fork();
    
    
    if (pids[i] < 0 ){
        printf("Error al crear el proceso hijo");
        return 0;
    }else if (pids[i] == 0){
        if (i == 0){
            close(pipe_dest[0]);
            dup2(pipe_dest[1],STDOUT_FILENO); //Cambia la salida estandar por la entrada de escritura de la pipe.
            close(pipe_dest[1]);
            execlp("ls","ls","-la",NULL);
            exit(0);
        }else{
            close(pipe_dest[1]);
            dup2(pipe_dest[0], STDIN_FILENO);  // Redirige stdin a la lectura del pipe
            close(pipe_dest[0]);               // Cierra el descriptor original ya duplicado
            execlp("tr", "tr", "d", "D",NULL);
            exit(0);
        }

    }
}
    close(pipe_dest[0]);
    close(pipe_dest[1]);
    for (int i = 0; i < 2; i++){
        wait(NULL);
    }

    return 0;
}