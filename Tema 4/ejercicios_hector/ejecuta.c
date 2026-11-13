#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

    pid_t pid;
    int status;

    if(argc < 2){
        printf("Error");
        return 1;
    }

    pid = fork();

    
    if (pid < 0){
        fprintf(stderr, "Fallo el fork %s \n", strerror(errno));
        exit(-1);
    }
    else if (pid == 0){
        execvp(argv[1], argv+1  );
        /*Si llega aqui es que ha ocurrido un error*/
        printf("Error al ejecutar el comando: %s\n", strerror(errno));
        exit(1);
    }
    else{
        wait(&status);
        if(WIFEXITED(status) != 0){
            if(WEXITSTATUS(status) != 0){
                printf("El comando no se ejecuto correctamente\n");
            }
        }
        exit(0);
    }
    

}