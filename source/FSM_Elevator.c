#include "FSM_Elevator.h"
#include "TimeLib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

Elevator *e;

void FSM_ElevatorInit(int doorOpenTime)
{
    e = initElevator(doorOpenTime);
}


void elevatorStateMachine()
{
    switch (e->elevatorState)
    {
        case INIT:
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            if (e->floor >= 0)
            {
                e->elevatorState = IDLE;
                fprintf(stderr, "STATE change: INIT->IDLE\n");
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            }
            break;
        case IDLE:
            e->direction = HARDWARE_MOVEMENT_STOP;
            closeDoor();
            if (e->doorState == CLOSED && hasOrders(e->orders))
            {
                e->elevatorState = MOVING;
                fprintf(stderr, "STATE change: IDLE->MOVING\n");
            }
            break;
        case MOVING:
            if (e->floor == destination(e->orders, e->floor, e->direction))
            {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                e->elevatorState = IDLE;
                fprintf(stderr, "STATE change: MOVING->IDLE\n");
                openDoor();
                orderCompleted(e->orders, e->floor);

                for (int b = 0; b<HARDWARE_NUMBER_OF_BUTTONS; b++)
                    hardware_command_order_light(e->floor, b, 0);
            }
            else if (e->floor < destination(e->orders, e->floor, e->direction))
            {
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
                e->direction = HARDWARE_MOVEMENT_UP;
            }
            else if (e->floor > destination(e->orders, e->floor, e->direction))
            {
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                e->direction = HARDWARE_MOVEMENT_DOWN;
            }
            break; 
        case STOPPED:
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            e->direction = HARDWARE_MOVEMENT_STOP;
            openDoor(); //keeps the door open if the elevator is stopped at a floor
            break;
    }
}

void event_newOrder(int floor, HardwareOrder buttonType)
{
    if (e->elevatorState == MOVING || e->elevatorState == IDLE)
    {
        addOrder(e->orders, floor, buttonType);
        hardware_command_order_light(floor, buttonType, 1);
    }
}


void event_floorSensorTriggered(int floor)
{
    e->floor = floor;
    hardware_command_floor_indicator_on(floor);
}


void event_stopButton(bool status)
{
    if (status && e->elevatorState != STOPPED)
    {
        hardware_command_stop_light(1);
        e->elevatorState = STOPPED;
        fprintf(stderr, "STATE change: ->STOPPED\n");
        clearAllOrders(e->orders);
    }
    else if (!status && e->elevatorState == STOPPED)
    {
        hardware_command_stop_light(0);
        e->elevatorState = IDLE;
        fprintf(stderr, "STATE change: STOPPED->IDLE\n");
    }
}

void event_obstruction(bool status)
{
    if (e->obstruction == status)
        return;


    e->obstruction = status;
        //used for testing!!
    for (int p1 = 0; p1<4; p1++)
    {
        for (int p2 = 0; p2<2; p2++)
        {            
            fprintf(stderr, "%d, ", e->orders[p1][p2]);
        }
        fprintf(stderr, "\n");
    }
}

int openDoor()
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

int closeDoor()
{
    if ((checkTimeout() && !e->obstruction))
    {
        hardware_command_door_open(0);
        e->doorState = CLOSED;
        return 0;
    }
    else if (e->obstruction && e->doorState == OPEN)
    {
        openDoor(); //resets the timer for closing the door
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