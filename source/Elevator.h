/**
 * @file
 * @brief File describing the elevator type and helping types
 */
#pragma once
#include "Orders.h"

/**
 * @brief @c enum Direction describes the direction the elevator is moving.
 * When idle or stopped the direction is in the last moved direction.
 * Direction value corresponds to the bit-value to set in the motor-controller to drive in that direction.
 */
typedef enum {
    DOWN = 0,
    UP = 1
} Direction;

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
    Direction direction;         //< The direction the elevator is moving, or last moved if idle
    ElevatorState elevatorState; //< The state of the elevator
    Orders orders;               //< The orders of the elevator
    DoorState doorState;         //< The state of the elevator door
    bool obstruction;
    int doorOpenTime;            //< The number of seconds the elevator door remains open
} Elevator;

/**
 * @brief Initialises the elevator
 * @param doorOpenTime Sets the number of seconds the elevator door remains open.
 * @return @c Elevator* pointer to the elevator struct which is in a consistent state.
 */
Elevator* initElevator(int doorOpenTime);

/**
 * @brief Tries to open the elevator door.
 * @param closeDoorAutomatic Indicates if the door should be closed automatically after a timeout defined in Elevator.
 * @return @c int indicating success (0) or failure (1)
 */
int openDoor(bool closeDoorAutomatic);

/**
 * @brief Closes the door. If it is already closed, this function does nothing.
 * @return @c int indicating success (0) or failure (1)
 */
int closeDoor();
int goToFloor();