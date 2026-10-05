// Imprimir mi nombre, imprimir nºargumentos,imprimir el primer arg, pedir línea por teclado, abrir fichero, escribir linea.

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    char *name = "Daniel";
    char *linea;
    printf("Mi nombres es: %s.\n",name);

    printf("El número de argumentos de mi script es: %d.\n",argc);
    printf("El primer argumento es: %s.\n",argv[1]);
    printf("Escribe algo: ");
    scanf("%s",linea);
    open();
    return 0;
}