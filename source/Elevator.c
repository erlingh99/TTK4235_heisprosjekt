#include <stdlib.h>
#include <stdio.h>
#include "Orders.h"
#include "Elevator.h"
#include "TimeLib.h"

Elevator* initElevator()
{
    Elevator *elevator = (Elevator*)malloc(sizeof(Elevator));
    if (elevator == NULL)
    {
        fprintf(stderr, "elevator memory allocation failed");
        exit(0);
    }
    
    elevator->elevatorState = INIT;
    elevator->floor = -1;
    elevator->doorOpenTime = doorTime;
    elevator->doorState = CLOSED;
    elevator->direction = HARDWARE_MOVEMENT_DOWN;
    elevator->obstruction = false;
    elevator->orders = orders_init();
    elevator->moved = false;

    fprintf(stderr, "elevator init done\n");

    return elevator;
}

void delElevator(Elevator *p_elevator)
{
    if (p_elevator != NULL)
    {
        for (int i = 0; i<HARDWARE_NUMBER_OF_FLOORS; i++)
            free((p_elevator->orders)[i]);
        free(p_elevator);
    }
}

int openDoor(Elevator *p_elevator)
{
    if(atFloor())
    {
        timerStart(p_elevator->doorOpenTime);
        hardware_command_door_open(1);
        p_elevator->doorState = OPEN;
        return 0;
    }
    return 1;
}

int closeDoor(Elevator* p_elevator)
{
    if ((checkTimeout() && !p_elevator->obstruction))
    {
        hardware_command_door_open(0);
        p_elevator->doorState = CLOSED;
        return 0;
    }
    else if (p_elevator->obstruction && p_elevator->doorState == OPEN)
    {
        openDoor(p_elevator); //resets the timer for closing the door
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