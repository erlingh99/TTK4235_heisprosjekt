#include <time.h>
#include <stddef.h>
#include "TimeLib.h"

time_t timeStamp = 0;
int timeoutSecs = 0;
bool timerActive = false;


void timerStart(int timeoutSeconds)
{
    timerActive = true;
    timeStamp = time(NULL);
    timeoutSecs = timeoutSeconds;
}


void timerStop()
{
    timerActive = false;
}

bool checkTimeout()
{
    if (timeStamp + timeoutSecs < time(NULL) && timerActive)
    {
        timerActive = false;
        return true;
    }
    return false;
}