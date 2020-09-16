#include "SystemStructures.h"

void *controllerThread(void * d);
void positionPD(struct controllerData * data);
void waitForRestOfStep(struct controllerData * data, double * step);