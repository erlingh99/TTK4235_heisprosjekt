#include <time.h>
#include "Time.h"

time_t timeStamp;
int timeoutSecs;
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