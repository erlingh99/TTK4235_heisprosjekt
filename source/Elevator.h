/**
 * @file
 * @brief File describing the elevator type and helping types
 */
#pragma once
#include "hardware.h"
#include "Orders.h"
#include <stdbool.h>

/**
 *  @brief @c enum ElevatorState describes the state the elevator is in.
 *  Available states are INIT, IDLE, MOVING and STOPPED.
 */
typedef enum {
    INIT,
    IDLE,
    MOVING,
    STOPPED    
} ElevatorState;


/**
 *  @brief @c enum DoorState describes the state the elevator door is in.
 *  Available states are OPEN and CLOSED.
 */
typedef enum {
    OPEN,
    CLOSED
} DoorState;


/**
 * @brief @c Elevator describes the elevator. 
 */
typedef struct {
    int floor;                   //< The floor the elevator last visited
    HardwareMovement direction;  //< The direction the elevator is moving
    ElevatorState elevatorState; //< The state of the elevator
    int **orders;                //< The orders of the elevator
    DoorState doorState;         //< The state of the elevator door
    bool obstruction;            //< If there are any obstructions so the elevator door should remain open
    int doorOpenTime;            //< The number of seconds the elevator door remains open
} Elevator;

/**
 * @brief Initialises the elevator
 * @param[in] doorOpenTime Sets the number of seconds the elevator door remains open.
 * @return @c Elevator* pointer to the elevator struct.
 * @warning The returned elevator is not in a consistent state
 */
Elevator* initElevator(int doorOpenTime);

/**
 * @brief Frees the memory occupied by the elevator *e
 * @param[in, out] *e Pointer to the elevator to delete
 */
void delElevator(Elevator* e);