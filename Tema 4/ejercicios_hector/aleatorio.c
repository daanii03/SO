
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int pipe_son[2];

void num_aleatorio(int sig){
    int num = rand() % 11;
    
    write(pipe_son[1], &num ,sizeof num);
    
}
int main(int argc, char * argv[]){

    signal(SIGUSR1, num_aleatorio); //Cuando se reciba esta señal, que se ejecute esa función.

    srand(getpid()); //se usa para cambiar la "semilla aleatoria" en cada ejecución. Si no, siempre seria la misma semilla

    int pid;
    pipe(pipe_son);

    pid = fork();
    
    char buffer[1024];

    int num_aleatorio;

    if (pid < 0) {
        printf("Error al crear el proceso hijo");
        return 1;

    }else if (pid == 0){

        close(pipe_son[0]);
        while (1){
            
        }

    }else {
        close(pipe_son[1]);

        while(fgets(buffer,sizeof buffer, stdin) != NULL){
            kill(pid,SIGUSR1);

            read(pipe_son[0],&num_aleatorio, sizeof num_aleatorio);
            printf("%d\n", num_aleatorio);
        }
        close(pipe_son[0]);
        kill(pid, SIGTERM); //Cuando el padre termine, matamos 
        wait(NULL);
    }


    return 0;
}