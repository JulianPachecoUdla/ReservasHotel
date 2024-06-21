#include <stdio.h>
#include "funciones.h"
#include <string.h>

void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char tipo[40];
    printf("Ingrese el tamano de habitacion que desea buscar: ");
    scanf("%s", tipo);
    printf("#\t\tTamano\t\tHotel\t\t\tPrecio\n");
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][1], tipo) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);
        }
    }
    printf("Elija el numero de habitacion que desea reservar: ");
    scanf("%d", numHabitacion);
}

void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char tipo[40];
    printf("Ingrese el hotel que desea buscar: ");
    scanf("%s", tipo);
    printf("#\t\tTamano\t\tHotel\t\t\tPrecio\n");
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][2], tipo) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);
        }
    }
    printf("Elija el numero de habitacion que desea reservar: ");
    scanf("%d", numHabitacion);
}

void realizarReserva(int numHabitacion, char habitaciones[9][3][40], char clientes[5][2][40], int reservas[10][4]) {
    char cedula[40];
    char nombre[40];
    int encontrado = 0, diasReserva;

    printf("Ingrese su nombre:\n>> ");
    scanf("%s", nombre);
    printf("Ingrese su numero de cedula:\n>> ");
    scanf("%s", cedula);

    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], "") == 0) {
            strcpy(clientes[i][0], nombre);
            strcpy(clientes[i][1], cedula);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No hay espacio para mas clientes.\n");
        return;
    }

    printf("Ingrese el numero de dias de la reserva:\n>> ");
    scanf("%d", &diasReserva);

    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == -1) {
            for (int j = 0; j < 5; j++) {
                if (strcmp(clientes[j][1], cedula) == 0) {
                    reservas[i][0] = j;
                    break;
                }
            }
            reservas[i][1] = numHabitacion; 
            reservas[i][2] = diasReserva;
            reservas[i][3] = 1; 
            printf("Reserva realizada con exito.\n");
            return;
        }
    }

    printf("No hay espacio para mas reservas.\n");
}

void buscarReservaPorCedula(int *numReserva, char clientes[][2][40], int reservas[10][4]) {
    char cedula[40];
    printf("Ingrese su numero de cedula:\n>> ");
    scanf("%s", cedula);

    for (int i = 0; i < 10; i++) {
        if (reservas[i][3] == 1) { 
            if (strcmp(clientes[reservas[i][0]][1], cedula) == 0) {
                *numReserva = i;
                return;
            }
        }
    }

    printf("Reserva no encontrada.\n");
    *numReserva = -1;
}

void imprimirReserva(int numReserva, char clientes[5][2][40], int reservas[10][4], char habitaciones[9][3][40], double precios[9]) {
    if (numReserva == -1) {
        printf("No se puede imprimir la reserva: numero de reserva invalido.\n");
        return;
    }

    int indexCliente = reservas[numReserva][0];
    int indexHabitacion = reservas[numReserva][1];
    int numDias = reservas[numReserva][2];
    int estadoReserva = reservas[numReserva][3];
    indexHabitacion--;
    const char *estado;
    if (estadoReserva == 1) {
        estado = "Reservado";
    } else {
        estado = "Pagado";
    }

    printf("=== Detalles de la Reserva ===\n");
    printf("Cliente: %s\n", clientes[indexCliente][0]); 
    printf("Cedula: %s\n", clientes[indexCliente][1]);
    printf("Habitacion: %s\n", habitaciones[indexHabitacion][0]);
    printf("Tipo: %s\n", habitaciones[indexHabitacion][1]);
    printf("Hotel: %s\n", habitaciones[indexHabitacion][2]);
    printf("Numero de dias: %d\n", numDias);
    printf("Estado: %s\n", estado);
}
void pagarReserva(int numReserva, int reservas[10][4], char habitaciones[9][3][40], double precios[9]) {
    if (numReserva == -1) {
        printf("No se puede pagar la reserva: numero de reserva invalido.\n");
        return;
    }

    int indexHabitacion = reservas[numReserva][1];
    int numDias = reservas[numReserva][2];
    double precioTotal = precios[indexHabitacion - 1] * numDias;

    printf("El costo total de su reserva es: %.2lf\n", precioTotal);
    printf("Desea pagar? (1.SI 2.NO)\n>> ");
    int opcion;
    scanf("%d", &opcion);

    if (opcion == 1) {
        reservas[numReserva][3] = 2;  
        printf("Reserva pagada con exito.\n");
    } else {
        printf("Pago cancelado.\n");
    }
}
