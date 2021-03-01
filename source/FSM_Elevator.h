/**
 * @file 
 * @brief The state-machine of the elevator
 */

#pragma once
#include "Orders.h"
#include "Elevator.h"
#include "hardware.h"


/**
 * @brief Initialises the state machine
 * @warning Must be called before the state machine is used.
 */
void FSM_ElevatorInit();


/**
 * @brief The elevator state machine that controls the elevator.
 */
void elevatorStateMachine();

/**
 * @brief Called when a new order is registered. Handles the new order. Sets lights.
 */
void event_newOrder(order);

/**
 * @brief Called when the floor sensor is triggered. Sets info in elevator and lights.
 */
void event_floorSensorTriggered(int floor);

/**
 * @brief Called when the stop button status changes. Handles the event.
 */
void event_stopButton(bool status);

/**
 * @brief Called when the obstuction sensor is triggered. Handles the event.
 */
void event_obstruction(bool status);

/**
 * @brief Tries to open the elevator door.
 * @return @c int indicating success (0) or failure (1)
 */
int openDoor();

/**
 * @brief Closes the door. If it is already closed, this function does nothing.
 * @return @c int indicating success (0) or failure (1)
 */
int closeDoor();