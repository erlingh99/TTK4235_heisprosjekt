#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Orders.h"


int **orders_init()
{
    int** pp_orders = malloc(HARDWARE_NUMBER_OF_FLOORS * sizeof **pp_orders);
    if (pp_orders == NULL)
    {   //error handling
        fprintf(stderr, "memory allocation failed.");
        exit(0);
    }
    
    for (int pos = 0; pos<HARDWARE_NUMBER_OF_FLOORS; pos++)
    {
        pp_orders[pos] = calloc(2, sizeof pp_orders[pos]);        
        if (pp_orders[pos] == NULL) 
        {   //error handling
            fprintf(stderr, "memory allocation failed.");
            for (int i = 0; i<pos; i++)
                free(pp_orders[pos]);
            free(pp_orders);
            exit(0);
        }
    }
    fprintf(stderr, "init orders done\n");
    return pp_orders;
}

void addOrder(int **list, int floor, HardwareOrder buttonType)
{
    switch (buttonType)
    {
        case HARDWARE_ORDER_INSIDE:            
            if (!(list[floor][0] && list[floor][1]))
                fprintf(stderr, "new order at floor %d, type inside \n", floor);
            list[floor][0] = 1;
            list[floor][1] = 1; //Direction does not matter            
            break;
        case HARDWARE_ORDER_UP:
            if (!list[floor][1])
                fprintf(stderr, "new order at floor %d, type up \n", floor);
            list[floor][1] = 1;
            break;

        case HARDWARE_ORDER_DOWN:
            if (!list[floor][0])
                fprintf(stderr, "new order at floor %d, type down \n", floor);
            list[floor][0] = 1;            
            break;
    }
}

int destination(int **orders, int floor, HardwareMovement dir)
{
    //fprintf(stderr, "finding dest \n");
    int dest;
    switch (dir)
    {
        case HARDWARE_MOVEMENT_UP:
            dest = checkUp(orders, floor);
            if (dest == -1)
                dest = checkDown(orders, HARDWARE_NUMBER_OF_FLOORS-1);
            if (dest == -1)
                dest = checkUp(orders, 0);
            break;
            
        case HARDWARE_MOVEMENT_DOWN:
            dest = checkDown(orders, floor);
            if (dest == -1)
                dest = checkUp(orders, 0);
            if (dest == -1)
                dest = checkDown(orders, HARDWARE_NUMBER_OF_FLOORS-1);
            break;
            
        default:
            dest = checkUp(orders, 0);
            if (dest == -1)
                dest = checkDown(orders, HARDWARE_NUMBER_OF_FLOORS-1);
            break;            
    }
    if (dest == -1)
        fprintf(stderr, "dest found negative error");

    //fprintf(stderr, "dest found: %d \n", dest);
    return dest;
}

int checkDown(int **orders, int floor)
{
    //fprintf(stderr, "Check down \n");
    for (int fl = floor; fl>=0 ; fl--)
    {
        if (orders[fl][0] == 1)
            return fl;
        
    }
    return -1;
}

int checkUp(int **orders, int floor)
{
    //fprintf(stderr, "Check up\n");
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
    fprintf(stderr, "All orders cleared\n");
}

int hasOrders(int **orders)
{
    for(int floors = 0; floors < HARDWARE_NUMBER_OF_FLOORS; floors++)
    {
        for(int buttons = 0; buttons < 2; buttons++)
        {
            if(orders[floors][buttons] != 0)
            {
                //fprintf(stderr, "Has order floor %d\n", orders[floors][buttons]);
                return 1;
            }
        }
    }
    return 0;    
}

void orderCompleted(int **orderList, int floor)
{
    fprintf(stderr, "clearing order floor %d\n", floor);
    orderList[floor][0] = 0;
    orderList[floor][1] = 0; //everyone on the floor boards the elevator regardless of dir
}