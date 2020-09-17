#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <sys/mman.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "SystemVariables.h"
#include "SystemStructures.h"
#include "InitUtilities.h"

void runFakeSocket(void * d)
{
    //char str = (char)d;

    printf("FakeSocket is running ...\n");
    
    int f_listen_fd = 0, f_conn_fd = 0;

    struct sockaddr_in f_serv_addr;
    initSock(&f_serv_addr, &f_listen_fd, PORT);
    
    //start tcp socket
    bind(f_listen_fd, (struct sockaddr*)&f_serv_addr, sizeof(f_serv_addr)); 
    listen(f_listen_fd, 100);

    f_conn_fd = accept(f_listen_fd, (struct sockaddr*)NULL, NULL);

    char str[] = "Hi";

    send(f_conn_fd, str, strlen(str), 0);

    close(f_conn_fd);
    close(f_listen_fd);
    

    return;


}

bool initThread(pthread_attr_t * attr, struct sched_param * param, int  priority[], int numberOfThreads)
{

    /*------------------------------------------------------------------------
        Create a thread with priority and scheduler (set in imp_variables)
    ------------------------------------------------------------------------*/

    for(int i=0; i<numberOfThreads; i++)
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
        param[i].sched_priority = 98; //priority (0-99)

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



int initSock(struct sockaddr_in * serv_addr, int * listen_fd, int port) 
{

    /*------------------------------------------------------------------------
        Create a tcp socket for communication with node server (UI) 
    ------------------------------------------------------------------------*/
    struct sockaddr_in * serv_addr1;
    *listen_fd = socket(AF_INET, SOCK_STREAM, 0);

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
    
    if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
       printf("mlockall failed: %m\n");
       return false;
    }
    
    return true;
    
}


bool initDataLog(FILE * fp, char * fileName)
{
    fopen (fileName,"w");
    return true;
}
