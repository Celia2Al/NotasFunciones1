#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

// Lee un número entero positivo desde consola
int leerEnteroPositivo(const char mensaje[]) {
    char entrada[20];
    int numero;
    while (1) {
        printf("%s", mensaje);
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%d", &numero) == 1 && numero >= 0) {
            return numero;
        } else {
            printf("Entrada invalida. Ingrese un numero entero positivo.\n");
        }
    }
}

// Revisa si un ID ya está registrado
int idExiste(Libro libros[], int n, int idBuscado) {
    for (int i = 0; i < n; i++) {
        if (libros[i].id == idBuscado) {
            return 1;
        }
    }
    return 0;
}

// Elimina el salto de línea de una cadena
void limpiarSaltoLinea(char texto[]) {
    int i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n') {
            texto[i] = '\0';
            break;
        }
        i++;
    }
}

// Compara si dos cadenas son iguales
int sonIguales(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}

// Copia una cadena en otra
void copiarTexto(char destino[], char origen[]) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

// Registro de un nuevo libro
void registrarLibro(Libro libros[], int *n, int cantidad) {
    if (*n >= MAX_LIBROS) {
        printf("Ya se alcanzo el limite de libros.\n");
        return;
    }

    Libro nuevo;
    nuevo.id = leerEnteroPositivo("Ingrese el ID del libro: ");

    if (idExiste(libros, *n, nuevo.id)) {
        printf("Ya existe un libro con ese ID.\n");
        return;
    }

    printf("Ingrese el titulo: ");
    fgets(nuevo.titulo, sizeof(nuevo.titulo), stdin);
    limpiarSaltoLinea(nuevo.titulo);

    printf("Ingrese el autor: ");
    fgets(nuevo.autor, sizeof(nuevo.autor), stdin);
    limpiarSaltoLinea(nuevo.autor);

    nuevo.anio = leerEnteroPositivo("Ingrese el anio de publicacion: ");

    char estadoIngresado[20];
    printf("Ingrese el estado (Disponible o Prestado): ");
    fgets(estadoIngresado, sizeof(estadoIngresado), stdin);
    limpiarSaltoLinea(estadoIngresado);
    copiarTexto(nuevo.estado, estadoIngresado);

    libros[*n] = nuevo;
    (*n)++;
    printf("Libro registrado con exito.\n");
}

// Mostrar todos los libros
void mostrarLibros(Libro libros[], int n) {
    printf("\n%-5s %-30s %-20s %-6s %-12s\n", "ID", "Titulo", "Autor", "Anio", "Estado");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-30s %-20s %-6d %-12s\n",
               libros[i].id, libros[i].titulo, libros[i].autor, libros[i].anio, libros[i].estado);
    }
}

// Buscar libro por ID o título
void buscarLibro(Libro libros[], int n) {
    int opcion = leerEnteroPositivo("Buscar por:\n1. ID\n2. Titulo\nSeleccione opcion: ");

    if (opcion == 1) {
        int id = leerEnteroPositivo("Ingrese ID: ");
        for (int i = 0; i < n; i++) {
            if (libros[i].id == id) {
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n",
                       libros[i].id, libros[i].titulo, libros[i].autor, libros[i].anio, libros[i].estado);
                return;
            }
        }
    } else if (opcion == 2) {
        char tituloBuscado[100];
        printf("Ingrese titulo: ");
        fgets(tituloBuscado, sizeof(tituloBuscado), stdin);
        limpiarSaltoLinea(tituloBuscado);

        for (int i = 0; i < n; i++) {
            if (sonIguales(libros[i].titulo, tituloBuscado)) {
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n",
                       libros[i].id, libros[i].titulo, libros[i].autor, libros[i].anio, libros[i].estado);
                return;
            }
        }
    }

    printf("Libro no encontrado.\n");
}

// Cambia el estado entre Disponible y Prestado
void actualizarEstado(Libro libros[], int n) {
    int id = leerEnteroPositivo("Ingrese ID del libro para cambiar el estado: ");
    for (int i = 0; i < n; i++) {
        if (libros[i].id == id) {
            if (sonIguales(libros[i].estado, "Disponible")) {
                copiarTexto(libros[i].estado, "Prestado");
            } else {
                copiarTexto(libros[i].estado, "Disponible");
            }
            printf("Estado actualizado.\n");
            return;
        }
    }
    printf("Libro no encontrado.\n");
}

// Elimina un libro por ID
void eliminarLibro(Libro libros[], int *n) {
    int id = leerEnteroPositivo("Ingrese ID del libro a eliminar: ");
    for (int i = 0; i < *n; i++) {
        if (libros[i].id == id) {
            for (int j = i; j < *n - 1; j++) {
                libros[j] = libros[j + 1];
            }
            (*n)--;
            printf("Libro eliminado.\n");
            return;
        }
    }
    printf("Libro no encontrado.\n");
}