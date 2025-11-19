#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H

// Definición de la estructura de estudiante
typedef struct {
    int id;                        // ID único del estudiante
    char nombre[100];              // Nombre del estudiante
    int edad;                      // Edad del estudiante
    char materiaInscrita[100][50]; // Materias en las que está inscrito (máximo 100 materias)
    int cantidadMaterias;          // Cantidad de materias en las que está inscrito
    float promedio;                // Promedio del estudiante
} Estudiante;

// Funciones para gestionar estudiantes
void agregarEstudiante(Estudiante estudiantes[], int *totalEstudiantes);
void listarEstudiantes(Estudiante estudiantes[], int totalEstudiantes);
void modificarEstudiante(Estudiante estudiantes[], int totalEstudiantes);
void eliminarEstudiante(Estudiante estudiantes[], int *totalEstudiantes, int id);
Estudiante* buscarEstudiantePorNombre(Estudiante estudiantes[], int totalEstudiantes, const char* nombre);
Estudiante* buscarEstudiantePorEdad(Estudiante estudiantes[], int totalEstudiantes, int minEdad, int maxEdad);
void inscribirMateria(Estudiante estudiantes[], int totalEstudiantes, const char* materia);
void calcularPromedio(Estudiante *estudiante);

#endif // ESTUDIANTES_H
