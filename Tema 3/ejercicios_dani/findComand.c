#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **get_path_dirs() {
  // Variable para guardar lo que hay dentro de PATH.
  char *path_env = getenv("PATH");
  int n = 10;

  // Si no hay nada en env devuelvo null.
  if (!path_env) return NULL;

  // Copio las rutas a otra variable para evitar que se modifique, 
  // porque getenv devuleve un puntero a la variable PATH.
  char *path = strdup(path_env);

  if (!path) return NULL;

  //Hago el array reservando inicialmente 10 punteros a char (strings)
  char **dirs = (char **)malloc(n * sizeof(char *));

  // Si no reserva la memoria libero la memoría del path.
  if (!dirs) {
    free(path);
    return NULL;
  }

  int i = 0;

  // Cogemos el primer directorio del path 
  char *token = strtok(path, ":");
  while (token != NULL) {
    // Si nos quedamos cortos reservamos el doble de memoría con realloc.
    if (i >= n) {
      n *= 2;
      dirs = (char **)realloc(dirs, n * sizeof(char *));
    }
    // En dirs en la posición i le asigno un puntero duplicado con el string y aumento i.
    dirs[i++] = strdup(token);

    // Le ponemos NULL para indicar que siga por la cadena en la que estaba en la primera llamada de token
    token = strtok(NULL, ":");
  }
  // Si hemos llegado a las posiciones que hemos reservado añadimos una más para poner null al final para
  // saber donde acaba el array.
  if (i >= n) {
    dirs = (char **)realloc(dirs, (n + 1) * sizeof(char *));
  }
  dirs[i] = NULL;

  // Liberamos path.
  free(path);
  return dirs;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error. Uso \"%s archivo.\".\n", argv[0]);
    return 1;
  }

  char **dirs = get_path_dirs();
  if (!dirs) return 1;
  // Variable para saber si hemos encontrado el comando.
  int found = -1;
  int i = 0;
  while(dirs[i] != NULL) {
    if (found != 0){
      // Variable que indica el tamaño que tenemos que reservar para el path entero donde buscamos el comando
      size_t len = strlen(dirs[i]) + 1 + strlen(argv[1]) + 1;
      // Reservamos memoría para la ruta completa 
      char *full_path = (char *) malloc(len);
      if (full_path  != NULL){
        // Copiamos el directorio[i] en full path
        strcpy(full_path,dirs[i]);
        // Concatenamos la barra para que sepamos que un directorio
        strcat(full_path,"/");
        // Concatenamos el comando para que se haga la busqueda
        strcat(full_path,argv[1]);

        // Si existe en la ruta dejamos de buscar y imprimimos por pantalla donde está el comando.
        if (access(full_path, F_OK) == 0) {
          printf("%s está en %s.\n", argv[1], full_path);
          found = 0;
        }
        // Liberamos la memoría de la ruta.
        free(full_path);
      }
    }
    // Liberamos cada uno de los punteros que hemos usado en el array de strings
    free(dirs[i]);
    i++;
  }
  // Liberamos la memoría del array.
  free(dirs);
  if (found == -1) printf("No se ha encontrado %s en la variable PATH.\n", argv[1]);
  return 0;
}