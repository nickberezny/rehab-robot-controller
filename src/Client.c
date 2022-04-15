/**
 * @file Client.c
 * @author Nick Berezny
 * @date 13 Apr 2022
 * @brief Contains client thread for sending data to TCP server during robot operation.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "./include/Parameters.h"
#include "./include/Structures.h"
#include "./include/Controller.h"
#include "./include/TimeUtilities.h"
#include "./include/Communication.h"
#include "./include/Client.h"

void * clientThread (void * d)
{
    /**
     * @brief ClientThread function to be run in POSIX thread
     * @param[in] *d : pointer to robot States structure
     */

    extern struct States *s_client;     
    extern int iter_client;
    extern char buffer[2048];

    iter_client = 0;

    while(true)
    {

        s_client = &((struct States*)d)[iter_client];
        printf("%d mutex: %d\n", iter_client, pthread_mutex_lock(&s_client->lock));
        if(iter_client == 0)
        {
            sprintf(buffer, "UI::%d", iter_client);
            printf("%d\n", *(s_client->sockfd));
            //send(*(s->sockfd), msg, strlen(msg),0);
            sendMessage(s_client->sockfd, buffer);
        }
        
        printf("%d unlock mutex: %d\n", iter_client, pthread_mutex_unlock(&s_client->lock));
        iter_client = iter_client + 1;
        if(iter_client == BUFFER_SIZE) iter_client = 0;
        
    }
    
    printf("Done Client...\n");
    //pthread_exit(NULL);
    return NULL;
}



