
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char * argv[]){

    int status;
    int status_code;
    char * *p;
    pid_t pid;

    if (argc < 2){

        printf("Error. Número de argumentos insuficientes. Actual: %d\n", argc);
        return 1;
    }
    
    pid = fork();

    if (pid < 0){

        printf("Error al crear el proceso hijo\n");
        return 1;
    }
    else if (pid == 0){

        p = &argv[1];
        status_code = execvp(argv[1],p);

        printf("Error al ejecutar el comando %s\n", argv[1]);
        exit(status_code);
    }
    else{
        
        wait(&status);

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0){

            printf("El comando no se ha ejecutado correctamente\n");
            return 1;
        }
        }

    return 0;


}