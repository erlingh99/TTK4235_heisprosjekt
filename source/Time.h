/**
 * @file
 * @brief A small time-library for single threaded programs. The library must be polled to alert timeouts.
 */

#pragma once
#include <stdbool.h>

int timeStamp;
int timeoutSecs;
bool timerActive;

/**
 * @brief Starts the timer by saving a timestamp and the length of the timer.
 * @param timeoutSecs The number of seconds untill the timer is finished
 */
void timerStart(int timeoutSecs);

/**
 * @brief Stops the timer. If the timer is not active this function doesn't do anything.
 */
void timerStop();

/**
 * @brief Checks if the current timer has timed out. If there is no active timer, this function returns @c False.
 */
bool checkTimeout();