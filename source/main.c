#include <stdio.h>
#include "hardware.h"
#include "EventManager.h"


int main()
{    
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    while(1)
    {
        startElevatorSoftware();
        printf("Elevator software crash!\nRestarting...");
    }    
    return 0;
}
