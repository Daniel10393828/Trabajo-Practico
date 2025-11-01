#include <stdio.h>
#include <string.h>
#include "materias.h"
#include "estudiantes.h"

// Función para agregar una nueva materia
void agregarMateria(Materia materias[], int *totalMaterias)
{
    Materia nuevaMateria;

    printf("Ingrese el nombre de la materia: ");
    getchar(); // Para consumir el salto de línea residual
    fgets(nuevaMateria.nombre, sizeof(nuevaMateria.nombre), stdin);
    nuevaMateria.nombre[strcspn(nuevaMateria.nombre, "\n")] = 0; // Eliminar salto de línea

    printf("Ingrese el código de la materia: ");
    scanf("%d", &nuevaMateria.codigo);

    printf("Ingrese la cantidad de correlativas: ");
    scanf("%d", &nuevaMateria.cantidadCorrelativas);

    for (int i = 0; i < nuevaMateria.cantidadCorrelativas; i++)
    {
        printf("Ingrese el código de la correlativa %d: ", i + 1);
        scanf("%d", &nuevaMateria.correlativas[i]);
    }

    // Inicialmente no está aprobada
    nuevaMateria.aprobada = 0;

    // Agregar la nueva materia al arreglo
    materias[*totalMaterias] = nuevaMateria;
    (*totalMaterias)++;
    printf("Materia '%s' agregada con éxito.\n", nuevaMateria.nombre);
}

// Función para listar todas las materias
void listarMaterias(Materia materias[], int totalMaterias)
{
    if (totalMaterias == 0)
    {
        printf("No hay materias registradas.\n");
        return;
    }

    printf("\nLista de Materias:\n");
    for (int i = 0; i < totalMaterias; i++)
    {
        printf("Código: %d | Nombre: %s | Correlativas: ", materias[i].codigo, materias[i].nombre);
        for (int j = 0; j < materias[i].cantidadCorrelativas; j++)
        {
            printf("%d ", materias[i].correlativas[j]);
        }
        printf("\n");
    }
}

// Función para modificar los datos de una materia
void modificarMateria(Materia materias[], int totalMaterias)
{
    int codigo;
    printf("Ingrese el código de la materia a modificar: ");
    scanf("%d", &codigo);

    Materia *materia = buscarMateriaPorCodigo(materias, totalMaterias, codigo);
    if (materia != NULL)
    {
        printf("Modificar nombre de la materia (actual: %s): ", materia->nombre);
        getchar(); // Para consumir el salto de línea residual
        fgets(materia->nombre, sizeof(materia->nombre), stdin);
        materia->nombre[strcspn(materia->nombre, "\n")] = 0; // Eliminar salto de línea

        printf("Modificar cantidad de correlativas (actual: %d): ", materia->cantidadCorrelativas);
        scanf("%d", &materia->cantidadCorrelativas);

        for (int i = 0; i < materia->cantidadCorrelativas; i++)
        {
            printf("Ingrese el código de la correlativa %d: ", i + 1);
            scanf("%d", &materia->correlativas[i]);
        }

        printf("Materia modificada con éxito.\n");
    }
    else
    {
        printf("Materia con código %d no encontrada.\n", codigo);
    }
}

// Función para eliminar una materia
void eliminarMateria(Materia materias[], int *totalMaterias, int codigo)
{
    int found = 0;
    for (int i = 0; i < *totalMaterias; i++)
    {
        if (materias[i].codigo == codigo)
        {
            found = 1;
            for (int j = i; j < *totalMaterias - 1; j++)
            {
                materias[j] = materias[j + 1];
            }
            (*totalMaterias)--;
            printf("Materia con código %d eliminada con éxito.\n", codigo);
            break;
        }
    }
    if (!found)
    {
        printf("Materia con código %d no encontrada.\n", codigo);
    }
}

// Función para buscar una materia por su código
Materia *buscarMateriaPorCodigo(Materia materias[], int totalMaterias, int codigo)
{
    for (int i = 0; i < totalMaterias; i++)
    {
        if (materias[i].codigo == codigo)
        {
            return &materias[i];
        }
    }
    return NULL;
}

// Función para buscar una materia por nombre
Materia *buscarMateriaPorNombre(Materia materias[], int totalMaterias, const char *nombre)
{
    for (int i = 0; i < totalMaterias; i++)
    {
        if (strcmp(materias[i].nombre, nombre) == 0)
        {
            return &materias[i];
        }
    }
    return NULL;
}

// Función para inscribir a un estudiante en una materia
void inscribirEstudianteEnMateria(Estudiante estudiantes[], int totalEstudiantes, Materia materias[], int totalMaterias, int estudianteId, int materiaCodigo)
{
    Estudiante *estudiante = buscarEstudiantePorNombre(estudiantes, totalEstudiantes, estudianteId);
    Materia *materia = buscarMateriaPorCodigo(materias, totalMaterias, materiaCodigo);

    if (estudiante != NULL && materia != NULL)
    {
        if (verificarCorrelativas(materias, totalMaterias, estudiante, materia->nombre))
        {
            if (estudiante->cantidadMaterias < 100)
            {
                strcpy(estudiante->materiaInscrita[estudiante->cantidadMaterias], materia->nombre);
                estudiante->cantidadMaterias++;
                printf("Estudiante inscripto con éxito en la materia '%s'.\n", materia->nombre);
            }
            else
            {
                printf("El estudiante ya ha alcanzado el límite de materias inscritas.\n");
            }
        }
        else
        {
            printf("El estudiante no cumple con las correlativas necesarias para inscribirse en '%s'.\n", materia->nombre);
        }
    }
    else
    {
        printf("Estudiante o materia no encontrado.\n");
    }
}
