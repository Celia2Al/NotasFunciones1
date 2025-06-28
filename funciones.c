#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

void menu() {
    printf("\n---- MENU ----\n");
    printf("1. Registrar partido\n");
    printf("2. Mostrar tabla de posiciones\n");
    printf("3. Mostrar goleador del torneo\n");
    printf("4. Salir\n");
}

int validarNombre(const char *nombre) {
    for (int i = 0; nombre[i]; i++) {
        if (isdigit(nombre[i])) return 0;
    }
    return 1;
}

int buscarEquipo(Equipo equipos[], int numEquipos, const char *nombre) {
    for (int i = 0; i < numEquipos; i++) {
        if (strcmp(equipos[i].nombre, nombre) == 0)
            return i;
    }
    return -1;
}

int buscarJugador(Jugador jugadores[], int numJugadores, const char *nombre) {
    for (int i = 0; i < numJugadores; i++) {
        if (strcmp(jugadores[i].nombre, nombre) == 0)
            return i;
    }
    return -1;
}

void registrarPartido(Equipo equipos[], int *numEquipos, Jugador jugadores[], int *numJugadores) {
    char eq1[MAX_NOMBRE], eq2[MAX_NOMBRE];
    int goles1, goles2;

    printf("Nombre del Equipo 1: ");
    scanf(" %[^\n]", eq1);
    if (!validarNombre(eq1)) {
        printf("Nombre inválido (contiene números).\n");
        return;
    }

    printf("Nombre del Equipo 2: ");
    scanf(" %[^\n]", eq2);
    if (!validarNombre(eq2)) {
        printf("Nombre inválido (contiene números).\n");
        return;
    }

    printf("Goles de %s: ", eq1);
    if (scanf("%d", &goles1) != 1 || goles1 < 0) {
        printf("Entrada inválida.\n");
        return;
    }

    printf("Goles de %s: ", eq2);
    if (scanf("%d", &goles2) != 1 || goles2 < 0) {
        printf("Entrada inválida.\n");
        return;
    }

    int idx1 = buscarEquipo(equipos, *numEquipos, eq1);
    if (idx1 == -1) {
        idx1 = (*numEquipos)++;
        strcpy(equipos[idx1].nombre, eq1);
        equipos[idx1].puntos = equipos[idx1].golesFavor = equipos[idx1].golesContra = 0;
    }

    int idx2 = buscarEquipo(equipos, *numEquipos, eq2);
    if (idx2 == -1) {
        idx2 = (*numEquipos)++;
        strcpy(equipos[idx2].nombre, eq2);
        equipos[idx2].puntos = equipos[idx2].golesFavor = equipos[idx2].golesContra = 0;
    }

    equipos[idx1].golesFavor += goles1;
    equipos[idx1].golesContra += goles2;
    equipos[idx2].golesFavor += goles2;
    equipos[idx2].golesContra += goles1;

    if (goles1 > goles2) equipos[idx1].puntos += 3;
    else if (goles2 > goles1) equipos[idx2].puntos += 3;
    else {
        equipos[idx1].puntos += 1;
        equipos[idx2].puntos += 1;
    }

    for (int i = 0; i < goles1; i++) {
        char nombre[MAX_NOMBRE];
        printf("Jugador %d que anotó por %s: ", i + 1, eq1);
        scanf(" %[^\n]", nombre);
        if (!validarNombre(nombre)) {
            printf("Nombre inválido (contiene números).\n");
            i--; continue;
        }
        int j = buscarJugador(jugadores, *numJugadores, nombre);
        if (j == -1) {
            j = (*numJugadores)++;
            strcpy(jugadores[j].nombre, nombre);
            jugadores[j].goles = 1;
        } else {
            jugadores[j].goles++;
        }
    }

    for (int i = 0; i < goles2; i++) {
        char nombre[MAX_NOMBRE];
        printf("Jugador %d que anotó por %s: ", i + 1, eq2);
        scanf(" %[^\n]", nombre);
        if (!validarNombre(nombre)) {
            printf("Nombre inválido (contiene números).\n");
            i--; continue;
        }
        int j = buscarJugador(jugadores, *numJugadores, nombre);
        if (j == -1) {
            j = (*numJugadores)++;
            strcpy(jugadores[j].nombre, nombre);
            jugadores[j].goles = 1;
        } else {
            jugadores[j].goles++;
        }
    }

    guardarDatos(equipos, *numEquipos, jugadores, *numJugadores);
}

void mostrarTabla(Equipo equipos[], int numEquipos) {
    printf("\n--- TABLA DE POSICIONES ---\n");
    printf("%-20s PTS GF GC\n", "Equipo");
    for (int i = 0; i < numEquipos; i++) {
        printf("%-20s %3d %2d %2d\n", equipos[i].nombre, equipos[i].puntos, equipos[i].golesFavor, equipos[i].golesContra);
    }
}

void mostrarGoleador(Jugador jugadores[], int numJugadores) {
    int maxGoles = -1;
    printf("\n--- GOLEADOR DEL TORNEO ---\n");
    for (int i = 0; i < numJugadores; i++) {
        if (jugadores[i].goles > maxGoles)
            maxGoles = jugadores[i].goles;
    }
    for (int i = 0; i < numJugadores; i++) {
        if (jugadores[i].goles == maxGoles) {
            printf("%s con %d goles\n", jugadores[i].nombre, jugadores[i].goles);
        }
    }
}

void guardarDatos(Equipo equipos[], int numEquipos, Jugador jugadores[], int numJugadores) {
    FILE *f = fopen("datos.bin", "wb");
    if (f == NULL) return;
    fwrite(&numEquipos, sizeof(int), 1, f);
    fwrite(equipos, sizeof(Equipo), numEquipos, f);
    fwrite(&numJugadores, sizeof(int), 1, f);
    fwrite(jugadores, sizeof(Jugador), numJugadores, f);
    fclose(f);
}

void cargarDatos(Equipo equipos[], int *numEquipos, Jugador jugadores[], int *numJugadores) {
    FILE *f = fopen("datos.bin", "rb");
    if (f == NULL) return;
    fread(numEquipos, sizeof(int), 1, f);
    fread(equipos, sizeof(Equipo), *numEquipos, f);
    fread(numJugadores, sizeof(int), 1, f);
    fread(jugadores, sizeof(Jugador), *numJugadores, f);
    fclose(f);
}