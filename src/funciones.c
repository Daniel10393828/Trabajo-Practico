#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "estudiantes.h"
#include "materias.h"

// Función para mostrar el menú principal
void mostrarMenu()
{
    printf("\n----- MENÚ PRINCIPAL -----\n");
    printf("1. Agregar Estudiante\n");
    printf("2. Listar Estudiantes\n");
    printf("3. Modificar Estudiante\n");
    printf("4. Eliminar Estudiante\n");
    printf("5. Buscar Estudiante por Nombre\n");
    printf("6. Buscar Estudiante por Edad\n");
    printf("7. Agregar Materia\n");
    printf("8. Listar Materias\n");
    printf("9. Inscribir Estudiante en Materia\n");
    printf("10. Rendir Materia\n");
    printf("11. Salir\n");
    printf("Seleccione una opción: ");
}

// Función para ordenar estudiantes por nombre (por ejemplo, usando el algoritmo de burbuja)
void ordenarEstudiantesPorNombre(Estudiante estudiantes[], int totalEstudiantes)
{
    Estudiante temp;
    for (int i = 0; i < totalEstudiantes - 1; i++)
    {
        for (int j = i + 1; j < totalEstudiantes; j++)
        {
            if (strcmp(estudiantes[i].nombre, estudiantes[j].nombre) > 0)
            {
                // Intercambiar los estudiantes
                temp = estudiantes[i];
                estudiantes[i] = estudiantes[j];
                estudiantes[j] = temp;
            }
        }
    }
}

// Función para ordenar materias por nombre
void ordenarMateriasPorNombre(Materia materias[], int totalMaterias)
{
    Materia temp;
    for (int i = 0; i < totalMaterias - 1; i++)
    {
        for (int j = i + 1; j < totalMaterias; j++)
        {
            if (strcmp(materias[i].nombre, materias[j].nombre) > 0)
            {
                // Intercambiar las materias
                temp = materias[i];
                materias[i] = materias[j];
                materias[j] = temp;
            }
        }
    }
}

// Función para cargar los estudiantes desde un archivo CSV
void cargarEstudiantesDesdeCSV(Estudiante estudiantes[], int *totalEstudiantes, const char *archivo)
{
    FILE *file = fopen(archivo, "r");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo %s.\n", archivo);
        return;
    }

    while (fscanf(file, "%d,%99[^,],%d,%f\n",
                  &estudiantes[*totalEstudiantes].id,
                  estudiantes[*totalEstudiantes].nombre,
                  &estudiantes[*totalEstudiantes].edad,
                  &estudiantes[*totalEstudiantes].promedio) != EOF)
    {
        (*totalEstudiantes)++;
    }
    fclose(file);
    printf("Estudiantes cargados desde el archivo %s.\n", archivo);
}

// Función para guardar los estudiantes en un archivo CSV
void guardarEstudiantesEnCSV(Estudiante estudiantes[], int totalEstudiantes, const char *archivo)
{
    FILE *file = fopen(archivo, "w");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo %s para guardar.\n", archivo);
        return;
    }

    for (int i = 0; i < totalEstudiantes; i++)
    {
        fprintf(file, "%d,%s,%d,%.2f\n",
                estudiantes[i].id,
                estudiantes[i].nombre,
                estudiantes[i].edad,
                estudiantes[i].promedio);
    }

    fclose(file);
    printf("Estudiantes guardados en el archivo %s.\n", archivo);
}

// Función para cargar las materias desde un archivo CSV
void cargarMateriasDesdeCSV(Materia materias[], int *totalMaterias, const char *archivo)
{
    FILE *file = fopen(archivo, "r");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo %s.\n", archivo);
        return;
    }

    while (fscanf(file, "%d,%99[^,],%d\n",
                  &materias[*totalMaterias].codigo,
                  materias[*totalMaterias].nombre,
                  &materias[*totalMaterias].cantidadCorrelativas) != EOF)
    {
        for (int i = 0; i < materias[*totalMaterias].cantidadCorrelativas; i++)
        {
            fscanf(file, "%d", &materias[*totalMaterias].correlativas[i]);
        }
        (*totalMaterias)++;
    }
    fclose(file);
    printf("Materias cargadas desde el archivo %s.\n", archivo);
}

// Función para guardar las materias en un archivo CSV
void guardarMateriasEnCSV(Materia materias[], int totalMaterias, const char *archivo)
{
    FILE *file = fopen(archivo, "w");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo %s para guardar.\n", archivo);
        return;
    }

    for (int i = 0; i < totalMaterias; i++)
    {
        fprintf(file, "%d,%s,%d",
                materias[i].codigo,
                materias[i].nombre,
                materias[i].cantidadCorrelativas);
        for (int j = 0; j < materias[i].cantidadCorrelativas; j++)
        {
            fprintf(file, ",%d", materias[i].correlativas[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Materias guardadas en el archivo %s.\n", archivo);
}

// Función para verificar si un ID de estudiante es único
int esIdUnico(Estudiante estudiantes[], int totalEstudiantes, int id)
{
    for (int i = 0; i < totalEstudiantes; i++)
    {
        if (estudiantes[i].id == id)
        {
            return 0; // El ID no es único
        }
    }
    return 1; // El ID es único
}

// Función para verificar si una materia tiene correlativas aprobadas
int verificarCorrelativas(Materia materias[], int totalMaterias, Estudiante *estudiante, const char *materia)
{
    // Buscar la materia en la lista de materias
    for (int i = 0; i < totalMaterias; i++)
    {
        if (strcmp(materias[i].nombre, materia) == 0)
        {
            // Verificar si las correlativas están aprobadas
            for (int j = 0; j < materias[i].cantidadCorrelativas; j++)
            {
                int correlativaEncontrada = 0;
                for (int k = 0; k < estudiante->cantidadMaterias; k++)
                {
                    if (strcmp(estudiante->materiaInscrita[k], materias[materias[i].correlativas[j]].nombre) == 0)
                    {
                        correlativaEncontrada = 1;
                        break;
                    }
                }
                if (!correlativaEncontrada)
                {
                    return 0; // Correlativa no aprobada
                }
            }
            return 1; // Correlativas aprobadas
        }
    }
    return 0; // Materia no encontrada
}
