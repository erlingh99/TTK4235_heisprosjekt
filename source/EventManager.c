#pragma once
#include "hardware.h"
#include "FSM_Elevator.h"
#include <unistd.h>

int elevatorLoop()
{
    while (1)
    {
        event_stopButton(hardware_read_stop_signal());
        event_obstruction(hardware_read_obstruction_signal());

        for (int floorNum = 0; floorNum<HARDWARE_NUMBER_OF_FLOORS; floorNum++)
        {
            if (hardware_read_floor_sensor(floorNum))
            {
                event_floorSensorTriggered(floorNum);
            }

            for (int buttonNum = 0; buttonNum<HARDWARE_NUMBER_OF_BUTTONS; buttonNum++)
            {
                if (hardware_read_order(floorNum, buttonNum))
                {
                    event_newOrder(floorNum, buttonNum);
                }
            }
        }

        elevatorStateMachine();

        sleep(1); //1 second might be too long
    }
}


int startElevatorSoftware()
{
    FSM_ElevatorInit(3);

    elevatorLoop();
}