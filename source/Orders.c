
#pragma once
#include "stdlib.h"
#include <stdbool.h>
#include "Orders.h"
#include "hardware.h"

int **orders_init()
{
    int orders[HARDWARE_NUMBER_OF_FLOORS][2]; //2 as in the 2 possible ways of ordering the elevator, up/down
    return orders;
}


void addOrder(int **list, int floor, HardwareOrder buttonType)
{
    switch (buttonType)
    {
        case HARDWARE_ORDER_INSIDE:
            list[floor][0] = 1;
            list[floor][1] = 1; //Dir does not matter
            break;
        case HARDWARE_ORDER_UP:
            list[floor][1] = 1;
            break;
        case HARDWARE_ORDER_DOWN:
            list[floor][0] = 1;
            break;
    }
}

int destination(int **orders, int floor, HardwareMovement dir)
{
    switch (dir)
    {
        case HARDWARE_MOVEMENT_UP:
            int dest = checkUp(orders, floor);
            if (dest == -1)
                dest = checkDown(orders, HARDWARE_NUMBER_OF_FLOORS);
            if (dest == -1)
                dest = checkUp(orders, 0);
            return dest;
            
        case HARDWARE_MOVEMENT_DOWN:
            int dest = checkDown(orders, floor);
            if (dest == -1)
                dest = checkUp(orders, 0);
            if (dest == -1)
                dest = checkDown(orders, HARDWARE_NUMBER_OF_FLOORS);
            return dest;
            
        default:
            int dest = checkUp(orders, 0);
            if (dest == -1)
                dest = checkDown(orders, HARDWARE_NUMBER_OF_FLOORS);
            return dest;            
    }
}

int checkDown(int **orders, int floor)
{
    for (int fl = floor; fl>=0 ; fl--)
    {
        if (orders[fl][0] == 1)
            return fl;
        
    }
    return -1;
}

int checkUp(int **orders, int floor)
{
    for (int fl = floor; fl<HARDWARE_NUMBER_OF_FLOORS; fl++)
    {
        if (orders[fl][1] == 1)
        {
            return fl; 
        }
    }
    return -1;
}

void clearAllOrders(int **orders)
{
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++)
    {
        for (int b = 0; b < 2; b++)
        {
            orders[f][b] = 0;
        }
    }
}

int hasOrders(int **orderlist)
{
    for(int floors = 0; floors < HARDWARE_NUMBER_OF_FLOORS; floors++)
    {
        for(int buttons = 0; buttons < 2; buttons++)
        {
            if(orderList[floors][buttons] != 0)
            {
                return 1;
            }
        }
    }
    return 0;    
}

void orderCompleted(int **orderList, int floor)
{
    orderList[floor][0] = 0;
    orderList[floor][1] = 0; //everyone on the floor boards the elevator regardless of dir
}