#include <stdlib.h>
#include <stdio.h>
#include "Elevator.h"
#include "TimeLib.h"

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
    elevator->obstruction = false;
    elevator->orders = orders_init();
    elevator->moved = false;

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

int openDoor(Elevator *e)
{
    if(atFloor())
    {
        timerStart(e->doorOpenTime);
        hardware_command_door_open(1);
        e->doorState = OPEN;
        return 0;
    }
    return 1;
}

int closeDoor(Elevator* e)
{
    if ((checkTimeout() && !e->obstruction))
    {
        hardware_command_door_open(0);
        e->doorState = CLOSED;
        return 0;
    }
    else if (e->obstruction && e->doorState == OPEN)
    {
        openDoor(e); //resets the timer for closing the door
    }
    return 1;
}

int atFloor()
{
    for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++)
    {
        if (hardware_read_floor_sensor(f) == 1)
            return 1;
    }
    return 0;
}