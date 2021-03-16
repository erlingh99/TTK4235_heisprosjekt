#include "FSM_Elevator.h"
#include "Orders.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

Elevator *p_elevator;

void FSM_ElevatorInit()
{
    p_elevator = initElevator();
}

void elevatorStateMachine()
{
    switch (p_elevator->elevatorState)
    {
        case INIT:
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            if (atFloor())
            {
                p_elevator->elevatorState = IDLE;
                fprintf(stderr, "STATE change: INIT->IDLE\n");
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            }
            break;
        case IDLE:
            closeDoor(p_elevator);
            if (p_elevator->doorState == CLOSED && hasOrders(p_elevator->orders))
            {
                p_elevator->elevatorState = MOVING;                
                fprintf(stderr, "STATE change: IDLE->MOVING\n");
            }
            break;
        case MOVING:
        { //curly braces to define scope of currOrder
            int currOrder = findDestination(p_elevator->orders, p_elevator->floor, p_elevator->direction);

            if (currOrder < 0 || currOrder >= HARDWARE_NUMBER_OF_FLOORS)
                exit(0);
            
            if ((p_elevator->floor == currOrder) && atFloor())
            {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                p_elevator->elevatorState = IDLE;
                fprintf(stderr, "STATE change: MOVING->IDLE\n");
                openDoor(p_elevator);
                orderCompleted(p_elevator->orders, p_elevator->floor);

                for (int b = 0; b<HARDWARE_NUMBER_OF_BUTTONS; b++)
                    hardware_command_order_light(p_elevator->floor, b, 0);
            }
            else if (p_elevator->floor < currOrder)
            {
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
                p_elevator->direction = HARDWARE_MOVEMENT_UP;
            }
            else if (p_elevator->floor > currOrder)
            {
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                p_elevator->direction = HARDWARE_MOVEMENT_DOWN;
            }
            else if (p_elevator->floor == currOrder && !p_elevator->moved)
            {                
                //Stopped between floors and having order back to prev floor: Revert last driven direction
                if (p_elevator->direction == HARDWARE_MOVEMENT_UP)
                {
                    hardware_command_movement(HARDWARE_MOVEMENT_DOWN); //opposite dir
                    p_elevator->direction = HARDWARE_MOVEMENT_DOWN;
                }
                else
                {
                    hardware_command_movement(HARDWARE_MOVEMENT_UP);                                            
                    p_elevator->direction = HARDWARE_MOVEMENT_UP;
                }
            }
            p_elevator->moved = true;
            break;
        }
        case STOPPED:
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            if (atFloor())
                openDoor(p_elevator);
            p_elevator->moved = false;
            break;
    }
}

void event_newOrder(int floor, HardwareOrder buttonType)
{
    if (p_elevator->elevatorState == MOVING || p_elevator->elevatorState == IDLE)
    {
        addOrder(p_elevator->orders, floor, buttonType);
        hardware_command_order_light(floor, buttonType, 1);
    }
}

void event_floorSensorTriggered(int floor)
{
    p_elevator->floor = floor;
    hardware_command_floor_indicator_on(floor);
}

void event_stopButton(bool status)
{
    if (status && p_elevator->elevatorState == INIT)
    {
        fprintf(stderr, "Aborting initialisation. Program terminated \n"); //could also ignore, but is a nice "safety measure" IRL
        delElevator(p_elevator);
        exit(1);
    }


    if (status && p_elevator->elevatorState != STOPPED)
    {
        hardware_command_stop_light(1);
        p_elevator->elevatorState = STOPPED;
        fprintf(stderr, "STATE change: ->STOPPED\n");
        clearAllOrders(p_elevator->orders);
        //clear lights
        for (int f = 0; f<HARDWARE_NUMBER_OF_FLOORS; f++)
        {
            for (int b = 0; b<HARDWARE_NUMBER_OF_BUTTONS; b++)
                hardware_command_order_light(f, b, 0);
        }
    }
    else if (!status && p_elevator->elevatorState == STOPPED)
    {
        hardware_command_stop_light(0);
        p_elevator->elevatorState = IDLE;
        fprintf(stderr, "STATE change: STOPPED->IDLE\n");
    }
}

void event_obstruction(bool status)
{
    p_elevator->obstruction = status;
}