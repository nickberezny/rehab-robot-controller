#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sched.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>

#include "Interface.h"

#include "InitUtilities.h"
#include "MathUtilities.h"
#include "SystemVariables.h"
#include "Controller.h"
#include "Logger.h"


const bool logData = false;

int listen_fd = 0, conn_fd = 0;
FILE logFile;

struct controllerData data[BUFFER_SIZE] = {0};
struct controllerParameters params; 
pthread_mutex_t lock[BUFFER_SIZE]; 

double stepTime = STEP_NSEC;



int main(int argc, char* argv[]) 
{
	printf("STARTING...\n");
	if(!logData) printf("Warning: not logging data...\n");
	
	/***************************************************************
							OPEN UI
	***************************************************************/

	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	
	printf("Time: %f\n", params.time);
	//wait for input from UI





	//initDaq

	/***************************************************************
							INIT Data Log
	***************************************************************/
	if(logData)
	{
		openLogFile(&logFile);

		double freq = NSEC_IN_SEC/STEP_NSEC;
		char freq_buff[50];
		
		sprintf(freq_buff, "Controller Frequency: %.2f kHz", freq);
	}
	

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


	if(logData) fclose(&logFile);
    close(conn_fd);
    close(listen_fd);

	return 0;
}
