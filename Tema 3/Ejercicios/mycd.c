
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   
    char *dir;

    switch (argc)
    {
        case 1:
            chdir(getenv("HOME"));
            break;
        case 2:
            chdir(argv[1]);
            break;
        default:
            printf("Error. Uso: \"%s  [dir]\"",argv[0]);
            return 1;
    }
    dir = getcwd(NULL,0);
    printf("%s\n",dir);
   
}