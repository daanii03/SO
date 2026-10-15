#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[]){

    if (argc == 0){
        printf("Error");
        return 1;
    }

    for (int i = argc - 1; i > 0; i--){
        for (int j = strlen(argv[i]) - 1; j >= 0; j--){
            printf("%c", argv[i][j]);
        }
        printf("\n");
    }

    return 0;
}