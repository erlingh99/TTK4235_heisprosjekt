/**
 * @file
 * @brief The eventmanager reacts to events and delegates
 */

#pragma once
#include "hardware.h"

/**
 * @brief Polls all the hardware and delegates the responses to appropriate modules.
 * Calls the elevatormanager at the end of every loop
 */
int elevatorLoop();


/**
 * @brief initialises all software and calls the program execution loop
 */
int startElevatorSoftware();