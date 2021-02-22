#include<stdio.h> 

typedef enum {STANS, KJORE_OPP, KJORE_NED, INIT, IDLE} State;

int heisFSM()
{
    State heisEnum = INIT;
    while (1)
    {
        switch (heisEnum)
        {
            case STANS:
                clearOrders();
                break;
            case KJORE_OPP:
                //blabla
            case KJORE_NED:
                //blabla 
            case INIT:
                findFloor();
                heisEnum = IDLE;
                break;
            case IDLE:
                getNewOrder();
                //sette opp/ned
        }
    }
    return 0;
}

