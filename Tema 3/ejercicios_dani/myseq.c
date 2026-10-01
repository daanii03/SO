

#include <stdio.h>
#include <stdlib.h>

// int argc es el número de argumentos que recibe desde shell el script, char *argv[] 
int main(int argc, char *argv[]){
    switch (argc)
    {   
        case 2:
            for (int i = 1; i <= atoi(argv[1]); i++){
                printf("%d\n", i);
            }
            break;
        case 3:
            for (int i = atoi(argv[1]); i <= atoi(argv[2]); i++){
                printf("%d\n",i);
            }
            break;
        case 4:
            for (int i = atoi(argv[1]); i <= atoi(argv[3]); i += atoi(argv[2])){
                printf("%d\n",i);
            }
            break;
        default:
            printf("Uso:\n");
            printf(" %s <fin>\n", argv[0]);
            printf(" %s <inicio> <fin>\n", argv[0]);
            printf(" %s <inicio> <incremento> <fin>\n",argv[0]);
            return 1;
    }
}