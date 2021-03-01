#include <stdlib.h>
#include "Elevator.h"

Elevator* initElevator(int doorOpenTime)
{
    Elevator *elevator = malloc(sizeof(Elevator));
    if (elevator == NULL)
        return NULL;
        
    elevator->orders = malloc(sizeof(Order));
    if (elevator->orders == NULL)
    {
        free(elevator);
        return NULL;
    }
    
    elevator->elevatorState = INIT;
    elevator->floor = -1;
    elevator->doorOpenTime = doorOpenTime;
    elevator->doorState = CLOSED;
    elevator->direction = HARDWARE_MOVEMENT_DOWN;
    elevator->orders = order_init();

    return elevator;
}

void delElevator(Elevator *e)
{
    if (e != NULL)
    {
        free(e->orders);
        free(e);
    }
}