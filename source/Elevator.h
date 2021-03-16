/**
 * @file
 * @brief File describing the elevator type and helping types
 */
#pragma once
#include "hardware.h"
#include <stdbool.h>

#define doorTime 3

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
    HardwareMovement direction;  //< The direction the elevator is moving or last moved
    ElevatorState elevatorState; //< The state of the elevator
    int **orders;                //< The orders of the elevator
    DoorState doorState;         //< The state of the elevator door
    bool obstruction;            //< If there are any obstructions so the elevator door should remain open
    int doorOpenTime;            //< The number of seconds the elevator door remains open
    bool moved;                  //< indicates if the elevator has moved since last stopped
} Elevator;

/**
 * @brief Initialises the elevator
 * @return @c Elevator* pointer to the elevator struct.
 * @warning The returned elevator is not in a consistent state
 */
Elevator* initElevator();

/**
 * @brief Frees the memory occupied by the elevator pointed to by @p p_elevator
 * @param[in, out] p_elevator Pointer to the elevator to delete
 */
void delElevator(Elevator* p_elevator);

/**
 * @brief Tries to open the door of elevator pointed to by @p p_elevator.
 * @param[in, out] p_elevator Pointer to the elevator which door shall be opened
 * @return @c int indicating success (0) or failure (1)
 */
int openDoor(Elevator* p_elevator);

/**
 * @brief Closes the door of elevator pointed to by @p p_elevator. If it is already closed, this function does nothing.
 * @param[in, out] p_elevator Pointer to the elevator which door shall be closed
 * @return @c int indicating success (0) or failure (1)
 */
int closeDoor(Elevator* p_elevator);


/**
 * @brief Checks if the elevator is at a floor.
 * @return 1 if yes, 0 if not
 */
int atFloor();