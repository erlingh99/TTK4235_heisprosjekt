#include <stdlib.h>
#include <stdio.h>
#include "Elevator.h"

Elevator* initElevator(int doorOpenTime)
{
    Elevator *elevator = (Elevator*)malloc(sizeof(Elevator));
    if (elevator == NULL)
    {
        fprintf(stderr, "elevator memory allocation failed");
        exit(0);
    }
    
    elevator->elevatorState = INIT;
    elevator->floor = -1;
    elevator->doorOpenTime = doorOpenTime;
    elevator->doorState = CLOSED;
    elevator->direction = HARDWARE_MOVEMENT_DOWN;
    elevator->orders = orders_init();

    fprintf(stderr, "elevator init done\n");

    return elevator;
}

void delElevator(Elevator *e)
{
    if (e != NULL)
    {
        for (int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++)
            free((e->orders)[i]);
        free(e);
    }
}