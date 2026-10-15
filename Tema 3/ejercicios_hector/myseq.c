#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]){
    switch (argc){
        case 2:
            for(int i = 1; i <= atoi(argv[1]); i++){
                printf("%d\n", i); 
            }
            break;
        case 3:
            for(int i = atoi(argv[1]); i <= atoi(argv[2]); i++){
                printf("%d\n", i); 
            }
            break;
        case 4:
            for(int i = atoi(argv[1]); i <= atoi(argv[3]); i+= atoi(argv[2])){
                printf("%d\n", i); 
            }
            break;
        default:
            printf("Uso:\n");
            printf(" %s LAST\n", argv[0]);
            printf(" %s FIRST LAST\n", argv[0]);
            printf(" %s FIRST INCREMENT LAST\n",argv[0]);   
            return 1; 
        }

    return 0;
}