#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "EventManager.h"


int main()
{    
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    fprintf(stderr, "Starting...\n");
    runElevatorSoftware(); 
    return 0;
}
