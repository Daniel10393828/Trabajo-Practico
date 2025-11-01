#include <stdio.h>
#include <string.h>
#include "estudiantes.h"
#include "materias.h"

// Función para agregar un nuevo estudiante
void agregarEstudiante(Estudiante estudiantes[], int *totalEstudiantes)
{
    Estudiante nuevoEstudiante;

    printf("Ingrese el ID del estudiante: ");
    scanf("%d", &nuevoEstudiante.id);

    // Verificar si el ID es único
    if (!esIdUnico(estudiantes, *totalEstudiantes, nuevoEstudiante.id))
    {
        printf("El ID ya existe. Intente con otro ID.\n");
        return;
    }

    printf("Ingrese el nombre del estudiante: ");
    getchar(); // Para consumir el salto de línea residual
    fgets(nuevoEstudiante.nombre, sizeof(nuevoEstudiante.nombre), stdin);
    nuevoEstudiante.nombre[strcspn(nuevoEstudiante.nombre, "\n")] = 0; // Eliminar salto de línea

    printf("Ingrese la edad del estudiante: ");
    scanf("%d", &nuevoEstudiante.edad);

    nuevoEstudiante.cantidadMaterias = 0; // Inicialmente no está inscrito en ninguna materia
    nuevoEstudiante.promedio = 0.0;       // Inicialmente no tiene promedio

    // Agregar al array de estudiantes
    estudiantes[*totalEstudiantes] = nuevoEstudiante;
    (*totalEstudiantes)++;
    printf("Estudiante agregado con éxito.\n");
}

// Función para listar todos los estudiantes
void listarEstudiantes(Estudiante estudiantes[], int totalEstudiantes)
{
    if (totalEstudiantes == 0)
    {
        printf("No hay estudiantes registrados.\n");
        return;
    }

    printf("\nLista de Estudiantes:\n");
    for (int i = 0; i < totalEstudiantes; i++)
    {
        printf("ID: %d | Nombre: %s | Edad: %d | Promedio: %.2f\n", estudiantes[i].id, estudiantes[i].nombre, estudiantes[i].edad, estudiantes[i].promedio);
    }
}

// Función para modificar los datos de un estudiante
void modificarEstudiante(Estudiante estudiantes[], int totalEstudiantes)
{
    int id;
    printf("Ingrese el ID del estudiante a modificar: ");
    scanf("%d", &id);

    Estudiante *estudiante = buscarEstudiantePorNombre(estudiantes, totalEstudiantes, id);
    if (estudiante != NULL)
    {
        printf("Modificar nombre del estudiante (actual: %s): ", estudiante->nombre);
        getchar(); // Para consumir el salto de línea residual
        fgets(estudiante->nombre, sizeof(estudiante->nombre), stdin);
        estudiante->nombre[strcspn(estudiante->nombre, "\n")] = 0;

        printf("Modificar edad del estudiante (actual: %d): ", estudiante->edad);
        scanf("%d", &estudiante->edad);
        printf("Estudiante modificado con éxito.\n");
    }
    else
    {
        printf("Estudiante no encontrado.\n");
    }
}

// Función para eliminar un estudiante
void eliminarEstudiante(Estudiante estudiantes[], int *totalEstudiantes, int id)
{
    int found = 0;
    for (int i = 0; i < *totalEstudiantes; i++)
    {
        if (estudiantes[i].id == id)
        {
            found = 1;
            for (int j = i; j < *totalEstudiantes - 1; j++)
            {
                estudiantes[j] = estudiantes[j + 1];
            }
            (*totalEstudiantes)--;
            printf("Estudiante eliminado con éxito.\n");
            break;
        }
    }
    if (!found)
    {
        printf("Estudiante con ID %d no encontrado.\n", id);
    }
}

// Función para buscar un estudiante por nombre
Estudiante *buscarEstudiantePorNombre(Estudiante estudiantes[], int totalEstudiantes, const char *nombre)
{
    for (int i = 0; i < totalEstudiantes; i++)
    {
        if (strcmp(estudiantes[i].nombre, nombre) == 0)
        {
            return &estudiantes[i];
        }
    }
    return NULL;
}

// Función para buscar un estudiante por rango de edad
Estudiante *buscarEstudiantePorEdad(Estudiante estudiantes[], int totalEstudiantes, int minEdad, int maxEdad)
{
    for (int i = 0; i < totalEstudiantes; i++)
    {
        if (estudiantes[i].edad >= minEdad && estudiantes[i].edad <= maxEdad)
        {
            return &estudiantes[i];
        }
    }
    return NULL;
}

// Función para inscribir a un estudiante en una materia
void inscribirMateria(Estudiante estudiantes[], int totalEstudiantes, const char *materia)
{
    int id;
    printf("Ingrese el ID del estudiante a inscribir en la materia '%s': ", materia);
    scanf("%d", &id);

    Estudiante *estudiante = buscarEstudiantePorNombre(estudiantes, totalEstudiantes, id);
    if (estudiante != NULL)
    {
        if (estudiante->cantidadMaterias < 100)
        {
            strcpy(estudiante->materiaInscrita[estudiante->cantidadMaterias], materia);
            estudiante->cantidadMaterias++;
            printf("Estudiante inscrito en la materia '%s' con éxito.\n", materia);
        }
        else
        {
            printf("El estudiante ya está inscrito en el máximo de materias.\n");
        }
    }
    else
    {
        printf("Estudiante no encontrado.\n");
    }
}

// Función para calcular el promedio del estudiante
void calcularPromedio(Estudiante *estudiante)
{
    if (estudiante->cantidadMaterias == 0)
    {
        printf("El estudiante no tiene materias inscritas.\n");
        return;
    }

    // Aquí se calcula el promedio basado en las calificaciones de las materias (puedes agregar una variable por calificación)
    // Como no tenemos calificaciones aún, dejaremos el promedio en 0 (puedes agregar una lógica adicional de calificación si lo deseas).
    estudiante->promedio = 0.0; // Esto lo podrías actualizar con una fórmula real
    printf("Promedio calculado: %.2f\n", estudiante->promedio);
}
