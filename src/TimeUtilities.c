/**
 * @file TimeUtilities.c
 * @author Nick Berezny
 * @date 13 Apr 2022
 * @brief utilities for control loop time stepping 
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "./include/Parameters.h"
#include "./include/TimeUtilities.h"

void timeStep(struct timespec * ts, struct timespec * tf, int * dt)
{
    *dt = (tf->tv_sec - ts->tv_sec)*NSEC_IN_SEC + (tf->tv_nsec - ts->tv_nsec);
    return;
}

void getTimeToSleep(struct timespec * ts, struct timespec * tf)
{
    tf->tv_nsec = ts->tv_nsec + STEP_SIZE_MS * 1000 * 1000;
    tf->tv_sec = ts->tv_sec;

    while(tf->tv_nsec > NSEC_IN_SEC)
    {
        tf->tv_nsec -= NSEC_IN_SEC;
        tf->tv_sec += 1;
    }
}

void getElapsedTime(struct timespec * ts, struct timespec * t, struct timespec * dt)
{
    dt->tv_sec = t->tv_sec - ts->tv_sec;
    dt->tv_nsec = t->tv_nsec - ts->tv_nsec;


    while(dt->tv_nsec < 0)
    {
        dt->tv_nsec += NSEC_IN_SEC;
        dt->tv_sec -= 1;
    }
}


