/**
 * @file 
 * @brief The state-machine of the elevator
 */

#pragma once
#include "Elevator.h"
#include "hardware.h"


static Elevator* e;


/**
 * @brief Initialises the state machine
 * @warning Must be called before the state machine is used.
 */
void init();


/**
 * @brief The elevator state machine that controls the elevator.
 */
void elevatorStateMachine();

/**
 * @brief Called when a new order is registered. Handles the new order. Sets lights.
 */
void event_newOrder(Order newOrder);

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