#include <time.h>
#include <stddef.h>
#include "Time.h"

int timeStamp;
int timeoutSecs;
bool timerActive = false;


void timerStart(int timeoutSeconds)
{
    timerActive = true;
    timeStamp = (int)time(NULL);
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