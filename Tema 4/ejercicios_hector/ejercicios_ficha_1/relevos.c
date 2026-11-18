
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

#define num_hijos 4
int i;
pid_t pids[num_hijos];

void relevo(int sig){
    printf("Soy el proceso %d, corriendo . . .\n ",getpid());
    sleep(1);
    if (i == 3){
        printf("Termine\n");

    } else{
        
        printf("Termine, le paso el relevo al proceso %d\n", pids[i+1]);
        kill(pids[i+1],SIGUSR1);
        
    }
    exit(0);
}

int main(){

    signal(SIGUSR1, relevo);

    

    for (i = (num_hijos -1) ; i >= 0; i--){

        pids[i] = fork();

        if (pids[i] < 0){

        printf("Error al crear uno de los hijos\n");
        return 1;
        
    }else if (pids[i] == 0){ //Eres un hijo.
       while (1){}
    }
    }
    
    printf("Todos los hijos creados\n");
    printf("Comienza la carrera\n");

    kill(pids[0],SIGUSR1);

    for (i = (num_hijos - 1); i >= 0; i--) {
        
        wait(NULL);
    }

    printf("Todos los hijos terminaron\n");


    return 0;
}