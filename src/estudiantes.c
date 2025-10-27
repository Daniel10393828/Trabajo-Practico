#include "estudiantes.h"
#include <stdio.h>
#include <stdlib.h>
#define INICIAL_CAPACIDAD 10

static void asegurarCapacidad(Estudiantes *lista)
{
    if (lista->cantidadGuardados < lista->capacidad)
        return;

    int nuevaCapacidad = (lista->capacidad == 0) ? INICIAL_CAPACIDAD : lista->capacidad * 2;
    Estudiante *nuevoEstudiante = (Estudiante *)realloc(lista->data, nuevaCapacidad * sizeof(Estudiante));
    if (nuevoEstudiante == NULL)
    {
        fprintf(stderr, "Error sin Memoria al redimensionar la lista\n");
        exit(1);
    }

    lista->data = nuevoEstudiante;
    lista->capacidad = nuevaCapacidad;
}

// Funcion para inicializar Estudiantes

void inicializarListaDeEstudiantes(Estudiantes *lista)
{
    lista->data = NULL;
    lista->cantidadGuardados = 0;
    lista->capacidad = 0;
    lista->next_id = 1;
}

// Funcion para Liberar la Lista

void vaciarEstudiantes(Estudiantes *lista)
{
    free(lista->data);
    lista->data = NULL;
    lista->cantidadGuardados = 0;
    lista->capacidad = 0;
}

// Funcion para dar de alta un Estudiante

int altaEstudiante(Estudiantes *lista, const char *nombre, int edad)
{
    asegurarCapacidad(lista);

    Estudiante nuevoEstudiante;
    nuevoEstudiante.id = lista->next_id++;
    snprintf(nuevoEstudiante.nombre, NOMBRE_MAX, "%s", nombre);

    nuevoEstudiante.nombre[NOMBRE_MAX - 1] = '\0'; // Asegurar terminacion nula
    nuevoEstudiante.edad = edad;

    lista->data[lista->cantidadGuardados++] = nuevoEstudiante;
    return nuevoEstudiante.id;
}

// Funcion para Buscar la posicion de un Estudiante dentro del arreglo por ID

int buscarEstudiantePorID(const Estudiantes *lista, int id)
{
    for (int i = 0; i < lista->cantidadGuardados; i++)
    {
        if (lista->data[i].id == id)
        {
            return i;
        }
    }
    return -1; // No encontrado
}

// Funcion para dar de Baja a un Estudiante por ID

bool bajaEstudiante(Estudiantes *lista, int id)
{
    int indiceEstudiante = buscarEstudiantePorID(lista, id);
    if (indiceEstudiante == -1)
    {
        return false; // No encontrado
    }

    // Mover el ultimo estudiante a la posicion del eliminado
    lista->data[indiceEstudiante] = lista->data[lista->cantidadGuardados - 1];
    lista->cantidadGuardados--;
    return true;
}