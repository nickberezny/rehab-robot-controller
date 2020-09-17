#include "SystemStructures.h"

void *controllerThread(void * d);
void positionPD(struct controllerData * data, struct controllerParameters * params);
void waitForRestOfStep(struct controllerData * data, double * step);
void admittance(struct controllerData * data, struct controllerParameters * params, double * xa, double * va);
void impedance(struct controllerData * data, struct controllerParameters * params);