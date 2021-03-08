/**
 * @file
 * @brief controls and stores which orders to be executed
 */
#pragma once
#include "hardware.h"

/**
 * @brief intializes the list of orders
 * @return A pointer to the made 2D array
 */
int **orders_init();


/**
 * @brief Add orders to orderlist a 4X2-matrix where either is up or down
 * @param[in, out] orderList the 2D array to store the order in
 * @param[in] floor the floor the order is associated with
 * @param[in] buttonType The button type that created the order
 */
void addOrder(int **orderList, int floor, HardwareOrder buttonType);

/**
 * @brief clear all orders if stop signal is high
 * @param[in] orderList Double pointer to the elevator's orderlist
 */
void clearAllOrders(int **orderList);

/**
 * @brief checks if the order on top of the orderlist is excuted
 * @param[in, out] orderList Double pointer to the elevator's orderlist
 * @param[in] floor The floor which the order directed the elevator to
 */
void orderCompleted(int **orderList, int floor);

/**
 * @brief Find the next destination for the elevator 
 * @param[in] orderList Double pointer to the elevators orderlist
 * @param[in] currentFloor The floor the elevator is at currently
 * @param[in] dir The direction the elevator is already moving
 * @return @c int representing the destination floor 
 */
int destination(int **orderList, int currentFloor, HardwareMovement dir);

/**
 * @brief Checks if there are more orders.
 * @param[in] orderList Double pointer to the elevator's orderlist
 * @return 1 if there exists active orders, 0 otherwise.
 */
int hasOrders(int **orderlist);

/**
 * @brief Finds the first order above @p floor in direction UP.
 * @param[in] orderList Double pointer to the elevator's orderlist
 * @return floor number of the first order above in upwards direction, -1 if no orders exist.
 */
int checkUp(int** orderList, int floor);

/**
 * @brief Finds the first order below @p floor in direction DOWN.
 * @param[in] orderList Double pointer to the elevator's orderlist
 * @return floor number of the first order below in downwards direction, -1 if no orders exist.
 */
int checkDown(int** orderList, int floor);