#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Orders.h"

//SEGMENTATION ERROR HAPPENS SOMETIMES!!

int **orders_init()
{
    int** pp_orders = malloc(HARDWARE_NUMBER_OF_FLOORS * sizeof **pp_orders);
    if (pp_orders == NULL)
    {
        fprintf(stderr, "memory allocation failed.");
        exit(0);
    }
    
    for (int pos = 0; pos<HARDWARE_NUMBER_OF_FLOORS; pos++)
    {
        pp_orders[pos] = calloc(2, sizeof pp_orders[pos]);        
        if (pp_orders[pos] == NULL)
        {
            for (int i = 0; i<pos; i++)
                free(pp_orders[pos]);
            free(pp_orders);
            fprintf(stderr, "memory allocation failed.");
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
            list[floor][0] = 1;
            list[floor][1] = 1; //Direction does not matter
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
                fprintf(stderr, "%d", orders[floors][buttons]);
                fprintf(stderr, " has orders\n");
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