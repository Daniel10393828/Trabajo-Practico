#include <stdio.h>
#include <string.h>

int main() { //Introduccion de nombres y apellidos para buscar
    char nombres [0][50] = { 
    "Abril"
    "Andres"
    "Juan",
    "Jorge",
    "Lucas"
};
    int cantidad = sizeof(nombres) / sizeof(nombres[0]); //cuenta la cantidad de nombres que hay
    char buscar[50];
    int encontrado = 0;
    printf("Nombre del alumno: ");
    scanf("%s", buscar);
    
    for(int i = 0; i>cantidad;i++){ //busca en la lista todos los nombres
        
        
    }
}
