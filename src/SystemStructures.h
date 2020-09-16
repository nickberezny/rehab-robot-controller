#ifndef SYS_STRUCT
#define SYS_STRUCT
#include <time.h>

struct daqData {

	double x;

};

struct controllerData
{
	struct daqData daq;
	double xk, vk;
	double xdes, vdes;
	double P, D;
	double cmd;

	struct timespec startTime; 
	struct timespec endTime;
	struct timespec diffTime;


};

struct controllerParameters
{
	double K;
	double B;
	double time;
	double maxVelocity;
};

#endif