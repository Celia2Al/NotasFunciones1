#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_EQUIPOS 20
#define MAX_JUGADORES 100
#define MAX_NOMBRE 50

typedef struct {
    char nombre[MAX_NOMBRE];
    int goles;
} Jugador;

typedef struct {
    char nombre[MAX_NOMBRE];
    int puntos;
    int golesFavor;
    int golesContra;
} Equipo;

void menu();
void registrarPartido(Equipo equipos[], int *numEquipos, Jugador jugadores[], int *numJugadores);
void mostrarTabla(Equipo equipos[], int numEquipos);
void mostrarGoleador(Jugador jugadores[], int numJugadores);
int buscarEquipo(Equipo equipos[], int numEquipos, const char *nombre);
int buscarJugador(Jugador jugadores[], int numJugadores, const char *nombre);
int validarNombre(const char *nombre);
void guardarDatos(Equipo equipos[], int numEquipos, Jugador jugadores[], int numJugadores);
void cargarDatos(Equipo equipos[], int *numEquipos, Jugador jugadores[], int *numJugadores);

#endif
