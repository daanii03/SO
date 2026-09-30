
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char **get_path_dirs(){

    char **dirs;

    return dirs;
}

int main(int argc, char *argv[]){
    if (argc != 1){
        fprintf(stderr,"Error. Uso \"%s archivo.\".\n", argv[0]);
        return 1;
    }
    
    char **dirs = get_path_dirs();
    
    return 0;
}