#include "SystemStructures.h"
#include "SystemVariables.h"

#include "Daq.h"
#include "Time.h"

#include<stdio.h>

void *controllerThread(void * d);
void positionPD(struct controllerData * data);
void waitForRestOfStep(struct controllerData * data, double * step);