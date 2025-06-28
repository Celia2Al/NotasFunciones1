#include <stdio.h>
#include "funciones.h"

int main() {
    Equipo equipos[MAX_EQUIPOS];
    Jugador jugadores[MAX_JUGADORES];
    int numEquipos = 0, numJugadores = 0;
    int opcion;

    cargarDatos(equipos, &numEquipos, jugadores, &numJugadores);

    do {
        menu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarPartido(equipos, &numEquipos, jugadores, &numJugadores);
                break;
            case 2:
                mostrarTabla(equipos, numEquipos);
                break;
            case 3:
                mostrarGoleador(jugadores, numJugadores);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 4);

    return 0;
}