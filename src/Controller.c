#include<stdio.h>
#include "SystemStructures.h"
#include "SystemVariables.h"
#include "Daq.h"
#include "Time.h"
#include "Controller.h"


extern struct controllerData * contData; 
//extern struct controllerParameters
extern double stepTime;

void *controllerThread(void * d)
{
	//SETUP
	

	while(1)
	{
		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			contData = &((struct controllerData*)d)[i];

			getTime(&contData->startTime); //get initial time

			//read values
			readValues(&contData->daq);

			//do calcs
			//positionPD(data);

			//write values?
			writeValues(&contData->daq);

			//wait
			waitForRestOfStep(contData, &stepTime);
			

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

void positionPD(struct controllerData * data, struct controllerParameters * params)
{

/*------------------------------------------------------------------------
    Position controller (move to xdes)
        command = P*(xdes-x) + D*(vdes - d)
------------------------------------------------------------------------*/

	data->cmd = params->P*(data->xdes - data->xk) + params->D*(data->vdes - data->vk);

}

void admittance(struct controllerData * data, struct controllerParameters * params, double * xa, double * va)
{
	/*------------------------------------------------------------------------
    	Admittance control - go to position given force and desired impedance 
        Xa = Ad * X + Bd * F
        command = P*(x) + D*(va)
	------------------------------------------------------------------------*/

    data->xa = data->xdes - ( params->Ad[0]*(data->xdes - *xa) + params->Ad[1]*(data->vdes - *va) + params->Bd[0] * (data->fk) );
    
    if(data->xa < 0.0) data->xa = 0.0;
    if(data->xa > params->x_end) data->xa = params->x_end;

    data->va = data->vdes - ( params->Ad[2]*(data->xdes - *xa) + params->Ad[3]*(data->vdes - *va) + params->Bd[1] * (data->fk) );
    
    data->cmd = params->P*(data->xa - data->xk) + params->D*(- data->vk);

    *xa = data->xa;
    *va = data->va;
}

void impedance(struct controllerData * data, struct controllerParameters * params)
{
	data->cmd = params->K*(data->xk - data->xdes) + params->B*(data->vk - data->vdes);
}
