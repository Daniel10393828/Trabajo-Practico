#include <stdio.h>
#include <stdlib.h>
#include "estudiantes.h"
#include "materias.h"
#include "funciones.h"

#define MAX_ESTUDIANTES 100
#define MAX_MATERIAS 50

// Función principal
int main()
{
    Estudiante estudiantes[MAX_ESTUDIANTES];
    Materia materias[MAX_MATERIAS];
    int totalEstudiantes = 0;
    int totalMaterias = 0;
    int opcion;

    // Cargar los datos desde archivos CSV al inicio
    cargarEstudiantesDesdeCSV(estudiantes, &totalEstudiantes, "estudiantes.csv");
    cargarMateriasDesdeCSV(materias, &totalMaterias, "materias.csv");

    while (1)
    {
        mostrarMenu();
        printf("11. Rendir Materia\n"); // Nueva opción
        printf("\nIngrese una opción: ");
        if (scanf("%d", &opcion) != 1)
        {
            printf("Entrada inválida. Intente nuevamente.\n");
            while (getchar() != '\n')
                ; // Limpiar buffer
            continue;
        }
        while (getchar() != '\n')
            ; // Limpiar buffer tras leer opción

        switch (opcion)
        {
        case 1:
            agregarEstudiante(estudiantes, &totalEstudiantes);
            break;
        case 2:
            listarEstudiantes(estudiantes, totalEstudiantes);
            break;
        case 3:
            modificarEstudiante(estudiantes, totalEstudiantes);
            break;
        case 4:
        {
            int idEliminar;
            printf("Ingrese el ID del estudiante a eliminar: ");
            if (scanf("%d", &idEliminar) != 1)
            {
                printf("Entrada inválida.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            while (getchar() != '\n')
                ;
            eliminarEstudiante(estudiantes, &totalEstudiantes, idEliminar);
        }
        break;
        case 5:
        {
            char nombreBuscar[100];
            printf("Ingrese el nombre del estudiante a buscar: ");
            fgets(nombreBuscar, sizeof(nombreBuscar), stdin);
            nombreBuscar[strcspn(nombreBuscar, "\n")] = 0;
            Estudiante *estudianteEncontrado = buscarEstudiantePorNombre(estudiantes, totalEstudiantes, nombreBuscar);
            if (estudianteEncontrado != NULL)
            {
                printf("Estudiante encontrado: ID: %d | Nombre: %s | Edad: %d | Promedio: %.2f\n",
                       estudianteEncontrado->id, estudianteEncontrado->nombre, estudianteEncontrado->edad, estudianteEncontrado->promedio);
            }
            else
            {
                printf("Estudiante no encontrado.\n");
            }
        }
        break;
        case 6:
        {
            int minEdad, maxEdad;
            printf("Ingrese el rango de edad (mínimo y máximo): ");
            if (scanf("%d %d", &minEdad, &maxEdad) != 2)
            {
                printf("Entrada inválida.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            while (getchar() != '\n')
                ;
            Estudiante *estudianteEncontrado = buscarEstudiantePorEdad(estudiantes, totalEstudiantes, minEdad, maxEdad);
            if (estudianteEncontrado != NULL)
            {
                printf("Estudiante encontrado: ID: %d | Nombre: %s | Edad: %d | Promedio: %.2f\n",
                       estudianteEncontrado->id, estudianteEncontrado->nombre, estudianteEncontrado->edad, estudianteEncontrado->promedio);
            }
            else
            {
                printf("No se encontraron estudiantes en ese rango de edad.\n");
            }
        }
        break;
        case 7:
            agregarMateria(materias, &totalMaterias);
            break;
        case 8:
            listarMaterias(materias, totalMaterias);
            break;
        case 9:
        {
            int idEstudiante, codigoMateria;
            printf("Ingrese el ID del estudiante: ");
            if (scanf("%d", &idEstudiante) != 1)
            {
                printf("Entrada inválida.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            while (getchar() != '\n')
                ;
            printf("Ingrese el código de la materia: ");
            if (scanf("%d", &codigoMateria) != 1)
            {
                printf("Entrada inválida.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            while (getchar() != '\n')
                ;
            inscribirEstudianteEnMateria(estudiantes, totalEstudiantes, materias, totalMaterias, idEstudiante, codigoMateria);
        }
        break;
        case 10:
            guardarEstudiantesEnCSV(estudiantes, totalEstudiantes, "estudiantes.csv");
            guardarMateriasEnCSV(materias, totalMaterias, "materias.csv");
            printf("¡Hasta luego!\n");
            return 0;
        case 11:
        {
            int idEstudiante, codigoMateria;
            printf("Ingrese el ID del estudiante: ");
            if (scanf("%d", &idEstudiante) != 1)
            {
                printf("Entrada inválida.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            while (getchar() != '\n')
                ;
            printf("Ingrese el código de la materia a rendir: ");
            if (scanf("%d", &codigoMateria) != 1)
            {
                printf("Entrada inválida.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            while (getchar() != '\n')
                ;
            // Lógica para rendir materia
            Estudiante *estudiante = NULL;
            for (int i = 0; i < totalEstudiantes; i++)
            {
                if (estudiantes[i].id == idEstudiante)
                {
                    estudiante = &estudiantes[i];
                    break;
                }
            }
            Materia *materia = NULL;
            for (int i = 0; i < totalMaterias; i++)
            {
                if (materias[i].codigo == codigoMateria)
                {
                    materia = &materias[i];
                    break;
                }
            }
            if (estudiante && materia)
            {
                int inscrito = 0;
                for (int i = 0; i < estudiante->cantidadMaterias; i++)
                {
                    if (strcmp(estudiante->materiaInscrita[i], materia->nombre) == 0)
                    {
                        inscrito = 1;
                        break;
                    }
                }
                if (inscrito)
                {
                    materia->aprobada = 1;
                    printf("Materia '%s' rendida y aprobada para el estudiante '%s'.\n", materia->nombre, estudiante->nombre);
                }
                else
                {
                    printf("El estudiante no está inscrito en esa materia.\n");
                }
            }
            else
            {
                printf("Estudiante o materia no encontrado.\n");
            }
        }
        break;
        default:
            printf("Opción no válida. Intente nuevamente.\n");
        }
    }

    return 0;
}
