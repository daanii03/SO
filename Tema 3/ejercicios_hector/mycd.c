#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char buffer[1024];
    
    if(argc > 2){
        printf("Error. El numero de parametros debe de ser 0 o 1. Numero actual de parametros: %d\n", argc-1);
        return 1;
    }

    else{
        const char *dir;

        switch (argc)
        {
        case 2:

            dir = argv[1];
            break;
        default:

            dir = getenv("HOME");
            if (dir == NULL) {
                printf("ERROR, no se encuentre la ruta HOME\n");
                return 1;
            }
            break;
        }

        int result = chdir(dir);

        if (result != 0){
            printf("La ruta no existe\n"); 
            return 1;
        }else{
            printf("%s\n", getcwd(buffer, sizeof(buffer)));
        }
    }
    
    return 0;
}
