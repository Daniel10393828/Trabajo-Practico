#ifndef MATERIAS_H
#define MATERIAS_H

// Definición de la estructura de Materia
typedef struct
{
    char nombre[100];         // Nombre de la materia
    int codigo;               // Código único de la materia
    int correlativas[10];     // Arreglo que almacena los códigos de las materias correlativas (máximo 10 correlativas)
    int cantidadCorrelativas; // Cantidad de materias correlativas
    int aprobada;             // 0: No aprobada, 1: Aprobada
} Materia;

// Funciones para gestionar materias
void agregarMateria(Materia materias[], int *totalMaterias);
void listarMaterias(Materia materias[], int totalMaterias);
void modificarMateria(Materia materias[], int totalMaterias);
void eliminarMateria(Materia materias[], int *totalMaterias, int codigo);
Materia *buscarMateriaPorCodigo(Materia materias[], int totalMaterias, int codigo);
Materia *buscarMateriaPorNombre(Materia materias[], int totalMaterias, const char *nombre);
void inscribirEstudianteEnMateria(Estudiante estudiantes[], int totalEstudiantes, Materia materias[], int totalMaterias, int estudianteId, int materiaCodigo);
void calcularPromedioMateria(Materia *materia);

#endif // MATERIAS_H
