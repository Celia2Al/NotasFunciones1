#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_LIBROS 10

typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[15]; // Disponible o Prestado
} Libro;

void registrarLibro(Libro libros[], int *n ,int cantidad); 
void mostrarLibros(Libro libros[], int n);
void buscarLibro(Libro libros[], int n);
void actualizarEstado(Libro libros[], int n);
void eliminarLibro(Libro libros[], int *n);

int leerEnteroPositivo(const char mensaje[]);

#endif

