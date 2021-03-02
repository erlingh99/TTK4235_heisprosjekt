#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Orders.h"


int **orders_init()
{
    int** pp_orders = (int**)malloc(HARDWARE_NUMBER_OF_FLOORS*sizeof(int*));
    for (int pos = 0; pos<HARDWARE_NUMBER_OF_FLOORS; pos++)
        pp_orders[pos] = (int*)malloc(2*sizeof(int));

    fprintf(stderr, "init orders done\n");
    return pp_orders;
}

void addOrder(int **list, int floor, HardwareOrder buttonType) //doesnt work for some reason
{
    switch (buttonType)
    {
        case HARDWARE_ORDER_INSIDE:
            list[floor][0] = 1;
            list[floor][1] = 1; //Dir does not matter
            fprintf(stderr, "order inside %d \n", floor);
            break;
        case HARDWARE_ORDER_UP:
            list[floor][1] = 1;
            fprintf(stderr, "order up %d \n", list[floor][1]);
            break;
        case HARDWARE_ORDER_DOWN:
            list[floor][0] = 1;
            fprintf(stderr, "order down %d \n", list[floor][1]);
            break;
    }
}

int destination(int **orders, int floor, HardwareMovement dir)
{
    fprintf(stderr, "finding dest \n");
    int dest;
    switch (dir)
    {
        case HARDWARE_MOVEMENT_UP:
            dest = checkUp(orders, floor);
            if (dest == -1)
                dest = checkDown(orders, HARDWARE_NUMBER_OF_FLOORS);
            if (dest == -1)
                dest = checkUp(orders, 0);
            break;
            
        case HARDWARE_MOVEMENT_DOWN:
            dest = checkDown(orders, floor);
            if (dest == -1)
                dest = checkUp(orders, 0);
            if (dest == -1)
                dest = checkDown(orders, HARDWARE_NUMBER_OF_FLOORS);
            break;
            
        default:
            dest = checkUp(orders, 0);
            if (dest == -1)
                dest = checkDown(orders, HARDWARE_NUMBER_OF_FLOORS);
            break;            
    }
    fprintf(stderr, "dest found: %d \n", dest);
    return dest;
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

int hasOrders(int **orders)
{
    for(int floors = 0; floors < HARDWARE_NUMBER_OF_FLOORS; floors++)
    {
        for(int buttons = 0; buttons < 2; buttons++)
        {
            if(orders[floors][buttons] != 0)
            {
                fprintf(stderr, "has orders");
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