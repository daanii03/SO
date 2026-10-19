#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc != 2){
        printf("Error. Uso: %s mandato\n", argv[0]);
        return 0;
    }

    const char *mandt = argv[1];

    char *logDir = getenv("PATH");

    char *dirPath = strtok(logDir, ":");

    char dir[1024];

    while (dirPath != NULL) {
        
        strcpy(dir, dirPath);  
        strcat(dir, "/");      
        strcat(dir, mandt);
        dirPath = strtok(NULL,":");
        
        if (access(dir, X_OK) == 0) {
            printf("Éxito: El archivo %s puede ejecutarse.\n", dir);
        }
        else {
            printf("Fallo: El archivo no puede ejecutarse.\n");
        }

    }

    return 0;
}
