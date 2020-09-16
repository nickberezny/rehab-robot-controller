#include<stdio.h>
#include "SystemStructures.h"
#include "SystemVariables.h"
#include "Daq.h"
#include "Time.h"
#include "Controller.h"


extern struct controllerData * data; 
extern double stepTime;

void *controllerThread(void * d)
{
	//SETUP
	

	while(1)
	{
		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			data = &((struct controllerData*)d)[i];

			getTime(&data->startTime); //get initial time

			//read values
			readValues(&data->daq);

			//do calcs
			positionPD(data);

			//write values?
			writeValues(&data->daq);

			//wait
			waitForRestOfStep(data, &stepTime);
			

		}

		break;
	}
}

void waitForRestOfStep(struct controllerData * data, double * step)
{
	getTime(&data->endTime);
	getStepTime(&data->startTime, &data->endTime, &data->diffTime);

	//printf("start: %ld,%ld\n",data->startTime.tv_sec,data->startTime.tv_nsec);
	//printf("step: %ld,%ld\n",data->stepTime.tv_sec, data->stepTime.tv_nsec);
	waitForTime(&data->diffTime, &data->endTime, step);
}

void positionPD(struct controllerData * data)
{

/*------------------------------------------------------------------------
    Position controller (move to xdes)
        command = P*(xdes-x) + D*(vdes - d)
------------------------------------------------------------------------*/

	data->cmd = data->P*(data->xdes - data->xk) + data->D*(data->vdes - data->vk);
    
	return;
}
