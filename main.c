#include <stdio.h>
#include "funciones.h"

int main() {
    Libro libros[MAX_LIBROS];
    int cantidad = 0;
    int opcion;

    do {
        printf("\n--- MENU BIBLIOTECA ---\n");
        printf("1. Registrar libro\n");
        printf("2. Mostrar libros\n");
        printf("3. Buscar libro\n");
        printf("4. Actualizar estado\n");
        printf("5. Eliminar libro\n");
        printf("6. Salir\n");

        opcion = leerEnteroPositivo("Seleccione una opcion: ");

        
        if (cantidad == 0 && opcion != 1 && opcion != 6) {
            printf("  Debe registrar al menos un libro antes de usar esta opcion.\n");
            continue;
        }

        switch (opcion) {
            case 1:
                registrarLibro(libros, &cantidad, cantidad);
                break;
            case 2:
                mostrarLibros(libros, cantidad);
                break;
            case 3:
                buscarLibro(libros, cantidad);
                break;
            case 4:
                actualizarEstado(libros, cantidad);
                break;
            case 5:
                eliminarLibro(libros, &cantidad);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 6);

    return 0;
}