#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "estudiantes.h"
#include "materias.h"

// Función para mostrar un menú de opciones al usuario
void mostrarMenu();

// Función para ordenar estudiantes por nombre (puedes usar cualquier algoritmo de ordenamiento)
void ordenarEstudiantesPorNombre(Estudiante estudiantes[], int totalEstudiantes);

// Función para ordenar materias por nombre
void ordenarMateriasPorNombre(Materia materias[], int totalMaterias);

// Función para cargar datos de estudiantes desde un archivo CSV (persistencia)
void cargarEstudiantesDesdeCSV(Estudiante estudiantes[], int *totalEstudiantes, const char *archivo)
// Función para guardar estudiantes en un archivo CSV
void guardarEstudiantesEnCSV(Estudiante estudiantes[], int totalEstudiantes, const char *archivo);

// Función para cargar datos de materias desde un archivo CSV (persistencia)
void cargarMateriasDesdeCSV(Materia materias[], int *totalMaterias, const char *archivo);

// Función para guardar materias en un archivo CSV
void guardarMateriasEnCSV(Materia materias[], int totalMaterias, const char *archivo);

// Función para validar si un ID de estudiante es único
int esIdUnico(Estudiante estudiantes[], int totalEstudiantes, int id);

// Función para verificar si una materia tiene correlativas aprobadas antes de inscribir al estudiante
int verificarCorrelativas(Materia materias[], int totalMaterias, Estudiante *estudiante, const char *materia);

// Función para realizar búsqueda binaria de estudiantes (en caso de que utilices un array ordenado)
Estudiante *buscarEstudianteBinario(Estudiante estudiantes[], int totalEstudiantes, int id);

#endif // FUNCIONES_H
