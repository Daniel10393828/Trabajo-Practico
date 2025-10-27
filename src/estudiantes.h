#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H
#include <stdbool.h>
#define NOMBRE_MAX 50

typedef struct
{
    int id;
    char nombre[NOMBRE_MAX];
    int edad;
} Estudiante;

typedef struct
{
    Estudiante *data;
    int cantidadGuardados;
    int capacidad;
    int next_id;
} Estudiantes;

// Inicializacion / Destruccion
void inicializarListaDeEstudiantes(Estudiantes *lista);
void vaciarListaDeEstudiantes(Estudiantes *lista);

// CRUD Estudiante
int altaEstudiante(Estudiantes *lista, const char *nombre, int edad);                         // Devuelve el ID asignado
bool bajaEstudiante(Estudiantes *lista, int id);                                              // Devuelve true si se borro correctamente
bool modificarEstudiante(Estudiantes *lista, int id, const char *nuevoNombre, int nuevaEdad); // Devuelve true si se modifico correctamente

// Utilidades
void listarEstudiantes(const Estudiantes *lista);
int buscarEstudiantePorNombre(const Estudiantes *lista, const char *nombre); // Devuelve la cantidad de estudiantes encontrados con el nombre dado

#endif // ESTUDIANTES_H
