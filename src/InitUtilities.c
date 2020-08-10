#include <pthread.h>

#include "InitUtilities.h"
#include "SystemVariables.h"

bool initThread(pthread_attr_t * attr, struct sched_param * param, int  priority[], int numberOfThreads)
{

    /*------------------------------------------------------------------------
        Create a thread with priority and scheduler (set in imp_variables)
    ------------------------------------------------------------------------*/

    for(int i=0; i>numberOfThreads; i++)
    {
        // Initialize pthread attributes (default values) 
        if (pthread_attr_init(&attr[i])) {
            printf("init pthread attributes failed \n");
            return false;
        }

        // Set a specific stack size  
        if (pthread_attr_setstacksize(&attr[i], PTHREAD_STACK_MIN)) {
            printf("pthread setstacksize failed \n");
            return false;
        }

        // Set scheduler policy and priority of pthread (SCHED_FIFO, SCHED_RR, SCHED_DEADLINE)
        if (pthread_attr_setschedpolicy(&attr[i], LINUX_SCHEDULER)) {
            printf("pthread setschedpolicy failed \n");
            return false;
        }
        param[i].sched_priority = priority[i]; //priority (0-99)

        if (pthread_attr_setschedparam(&attr[i], &param[i])) {
            printf("pthread setschedparam failed \n");
            return false;
        }

        // Use scheduling parameters of attr 
        if (pthread_attr_setinheritsched(&attr[i], PTHREAD_EXPLICIT_SCHED)) {
            printf("pthread setinheritsched failed \n");
            return false;
        }
    }
	

    return true;

}



int initSock(struct sockaddr_in * serv_addr, int port) 
{

    /*------------------------------------------------------------------------
        Create a tcp socket for communication with node server (UI) 
    ------------------------------------------------------------------------*/
    struct sockaddr_in * serv_addr1;
    memset(serv_addr, '0', sizeof(*serv_addr));

    serv_addr->sin_family = AF_INET;
    int err = inet_pton(AF_INET, "127.0.0.1",  &(serv_addr->sin_addr.s_addr));
    serv_addr->sin_port = htons(port); 

    return err;
    
}

bool initMemory(pthread_mutex_t lock[], int bufferLength)
{
    /*------------------------------------------------------------------------
        Create mutexes, allocate and lock data
    ------------------------------------------------------------------------*/
    for(int i = 0; i<bufferLength; i++)
    {
        if(pthread_mutex_init(&lock[i], NULL) != 0) return false; //init mutex locks

    }

    return true;
    
}

bool initDataLog(FILE * fp, char * fileName)
{
    fopen (fileName,"w");
    return true;
}
