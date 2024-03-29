/**
 * @file 
 * @brief The state-machine of the elevator
 */
#pragma once
#include "Elevator.h"

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
 * @brief Called when a order is registered. Handles the order. Sets lights.
 */
void event_newOrder(int floor, HardwareOrder buttonType);

/**
 * @brief Called when the floor sensor is triggered. Sets info in *p_elevator and lights.
 */
void event_floorSensorTriggered(int floor);

/**
 * @brief Called to handle the stop button status.
 */
void event_stopButton(bool status);

/**
 * @brief Called to handle the obstruction status.
 */
void event_obstruction(bool status);