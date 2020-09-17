#ifndef SYS_STRUCT
#define SYS_STRUCT
#include <time.h>

#define CONTROLLER_DATA_ELEMENTS 13
#define CONTROLLER_PARAMETERS_ELEMENTS 10

struct daqData {

	double x;

};

struct controllerData
{
	struct daqData daq;
	double xk, vk, fk;
	double xdes, vdes;
	double xa, va;
	double cmd;

	struct timespec startTime; 
	struct timespec endTime;
	struct timespec diffTime;


};

struct controllerParameters
{
	double K, B, M;
	double *Ad, *Bd;
	double P, D;
	double time;
	double maxVelocity;
	double x_end;
};

#endif