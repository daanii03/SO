
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    
    if (argc <= 1){
        printf("Uso \"%s [word1] [word2] [...]\".\n",argv[0]);
        return 1;
    }

    for (int i = argc-1; i >= 1; i--){
        char *word = argv[i];
        int len = strlen(word);
        for(int j = len-1; j >= 0; j--){
            printf("%c",word[j]);
        }
        printf(" ");
    }
    printf("\n");
    return 0;
}