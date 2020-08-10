#include "InitUtilities.h";
#include "MathUtilities.h"
#include "SystemVariables.h"


int main(int argc, char* argv[]) 
{

	//initSock(struct sockaddr_in * serv_addr, int port) 
	//initThread

	struct sched_param param[NUM_OF_THREADS];
    pthread_attr_t attr[NUM_OF_THREADS];
    pthread_t thread[NUM_OF_THREADS];
    int priorities[NUM_OF_THREADS];

	initThread(attr, param, priorities, NUM_OF_THREADS);

	printf("STARTING\n");
	
	//initDataLog
	//initDaq

	//calculate Ad, Bd
	//Home

	//initMemory

}
