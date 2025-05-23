#include "Interface.h"
#include <stdio.h>

void printWelcomeMenu(){
    printf("Bienvenido al gestor de la BDD de datos AGENDA de SABIDURIA\n");
    printf("A continuacion se mostrarán las funcionalidades disponibles\n");
}

void printOptionsMenu(){
    printf("1. Consultar referencia\n");
    printf("2. Insertar referencia\n");
    printf("3. Borrar referencia\n");
    printf("4. Mostrar BDD\n");
    printf("5. Salir sin guardar\n");
    printf("6. Salir y guardar\n");
}

void printEndMessage(){
    printf("Saliendo del programa\n");

    //Todo: Hacer una transicion de puntos con sleep
}