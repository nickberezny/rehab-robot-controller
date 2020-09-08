#include "InitUtilities.h"
#include "MathUtilities.h"
#include "SystemVariables.h"
#include "Controller.h"

int listen_fd = 0, conn_fd = 0;

struct controllerData data[BUFFER_SIZE] = {0};
pthread_mutex_t lock[BUFFER_SIZE]; 

double stepTime = STEP_NSEC;

int main(int argc, char* argv[]) 
{

	printf("STARTING...\n");
	//*stepTime = 

	//initDataLog
	//initDaq

	/***************************************************************
							INIT THREADS
	***************************************************************/

	struct sched_param param[NUM_OF_THREADS];
    pthread_attr_t attr[NUM_OF_THREADS];
    pthread_t thread[NUM_OF_THREADS];
    int priorities[NUM_OF_THREADS];

	initThread(attr, param, priorities, NUM_OF_THREADS);

	/***************************************************************
							INIT SOCKET
	***************************************************************/

	struct sockaddr_in serv_addr;
	initSock(&serv_addr, &listen_fd, PORT);
	


	//TODO****************************
	//start tcp socket
	//Get k,b,m from UI
	//calculate Ad, Bd
	//Home


	/**********************************************************************
					   Initialize Memory
	***********************************************************************/

	initMemory(lock, BUFFER_SIZE);



	
	pthread_create(&thread[0], &attr[0], controllerThread, (void *)data);
	pthread_join(thread[0], NULL);


	
    close(conn_fd);
    close(listen_fd);

	return 0;
}
