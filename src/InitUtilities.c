#include <pthread.h>

#include "InitUtilities.h"
#include "SystemVariables.h"

bool initThread(pthread_attr_t * attr, struct sched_param * param, int priority)
{

    /*------------------------------------------------------------------------
        Create a thread with priority and scheduler (set in imp_variables)
    ------------------------------------------------------------------------*/

	// Initialize pthread attributes (default values) 
    if (pthread_attr_init(attr)) {
        printf("init pthread attributes failed \n");
        return false;
    }

    // Set a specific stack size  
    if (pthread_attr_setstacksize(attr, PTHREAD_STACK_MIN)) {
        printf("pthread setstacksize failed \n");
        return false;
    }

    // Set scheduler policy and priority of pthread (SCHED_FIFO, SCHED_RR, SCHED_DEADLINE)
    if (pthread_attr_setschedpolicy(attr, LINUX_SCHEDULER)) {
        printf("pthread setschedpolicy failed \n");
        return false;
    }
    param->sched_priority = priority; //priority (0-99)

    if (pthread_attr_setschedparam(attr, param)) {
        printf("pthread setschedparam failed \n");
        return false;
    }

    // Use scheduling parameters of attr 
    if (pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED)) {
        printf("pthread setinheritsched failed \n");
        return false;
    }

    return true;

}

bool init_sock(struct socket_data * sock) 
{

/*------------------------------------------------------------------------
    Create a tcp socket for communication with node server (UI) 
------------------------------------------------------------------------*/
    
    sock->opt = 1;
    
    sock->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    setsockopt(sock->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &(sock->opt), sizeof(sock->opt));
    sock->address.sin_family = AF_INET;
    sock->address.sin_port = htons( GAME_PORT );
    inet_pton(AF_INET, "127.0.0.1", &sock->address.sin_addr);

    bind(sock->server_fd, (struct sockaddr *)&(sock->address), sizeof(sock->address));
    listen(sock->server_fd, 3);

    
    return true;
}