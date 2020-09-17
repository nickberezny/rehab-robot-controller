#include <time.h>
#include "SystemVariables.h"
#include "Time.h"

void waitForTime(struct timespec * stepTime, struct timespec * currTime, double * totalTime)
{

	/*------------------------------------------------------------------------
    Calculate remaining time in control step given sampling rate
	------------------------------------------------------------------------*/

    if(*totalTime - stepTime->tv_nsec <= 0) return;

    if(currTime->tv_nsec + *totalTime - stepTime->tv_nsec > NSEC_IN_SEC)
    {
    	currTime->tv_sec += 1;
    	currTime->tv_nsec += *totalTime - stepTime->tv_nsec - NSEC_IN_SEC; 
    }else
    {
        currTime->tv_nsec += *totalTime - stepTime->tv_nsec;
    }

    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, currTime, NULL);

    return;

}

void getStepTime(struct timespec * start, struct timespec * end, struct timespec * step)
{

	/*------------------------------------------------------------------------
	    Calculate delta time between start and end time
	        step time = end - start
	------------------------------------------------------------------------*/

    step->tv_sec = 0;
    step->tv_nsec = 0;

    if(end->tv_nsec > start->tv_nsec && end->tv_sec >= start->tv_sec)
    {
        step->tv_sec = end->tv_sec - start->tv_sec;
        step->tv_nsec = end->tv_nsec - start->tv_nsec;
    }
    else if(end->tv_nsec == start->tv_nsec && end->tv_sec > start->tv_sec)
    {
        step->tv_sec = end->tv_sec - start->tv_sec;
        step->tv_nsec = end->tv_nsec - start->tv_nsec;
    }
    else if(end->tv_nsec < start->tv_nsec && end->tv_sec > start->tv_sec)
    {
        step->tv_sec = end->tv_sec - start->tv_sec - 1;
        step->tv_nsec = NSEC_IN_SEC - start->tv_nsec + end->tv_nsec;
    }


	return;
}

void getTime(struct timespec * timePtr)
{
    //clock_gettime(CLOCK_MONOTONIC, timePtr);
    return;
}