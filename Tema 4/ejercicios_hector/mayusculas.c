
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

    
    FILE * dad_write,  * dad_read, *son_read, *son_write;

    int pid,pipe_dad[2], pipe_son[2];

    char buffer[1024];

    pipe(pipe_dad);
    pipe(pipe_son);
    
    pid = fork();

    if (pid < 0){
        printf("Error al crear el hijo");
        return 1;
    }else if (pid == 0){ 

        close(pipe_dad[1]);
        son_read = fdopen(pipe_dad[0],"r");
        
        close(pipe_son[0]);
        son_write = fdopen(pipe_son[1],"w");

        while (fgets(buffer, sizeof buffer, son_read) != NULL){
            for (int i = 0; buffer[i] != 0; i++){
                buffer[i] = (char) toupper(buffer[i]);
            }

            fputs(buffer,son_write);
            fflush(son_write);
        }

        close(pipe_son[1]);



    }else{

        close(pipe_dad[0]);
        dad_write = fdopen(pipe_dad[1],"w"); //1º Agrumento: Descriptor abierto. 2º Argumento: Modo de acceso (r = read y w = write). Devuelve un puntero a ese fichero.
        
        close(pipe_son[1]);
        dad_read = fdopen(pipe_son[0],"r");

        while(fgets(buffer, sizeof buffer, stdin) != NULL){
            fputs(buffer, dad_write); //Copia el valor del buffer dentro de la entrada de escritura de la pipe.
            fflush(dad_write); //Enviamos el mensaje.            
            
            
            fgets(buffer, sizeof buffer, dad_read);
            fputs(buffer,stdout);
        }
    
        close(pipe_dad[1]);
        wait(NULL);
        
    }


    return 0;

}