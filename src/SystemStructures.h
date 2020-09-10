#include "SystemVariables.h"
#include<time.h>

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