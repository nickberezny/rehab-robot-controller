/**
 * @file Log.c
 * @author Nick Berezny
 * @date 13 Apr 2022
 * @brief Contains function to initialize log folder and the logging thread
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

void * logThread (void * d)
{
    /**
     * @brief logThread function to be run in POSIX thread
     * @param[in] *d : pointer to robot States structure
     */

    printf("Starting Log...\n");

    extern struct States *s_log;    
    extern int iter_log;
    extern struct LogData *logData;
    extern quitThreads;
    iter_log = 0;

    while(!quitThreads)
    {
        s_log = &((struct States*)d)[iter_log];
        pthread_mutex_lock(&s_log->lock);
        iter_log= iter_log + 1;
        if(iter_log== BUFFER_SIZE) iter_log = 0;

        fprintf (logData->fp,"%d, %d, %.8f,%.8f, %.8f,%.8f, %.8f, %.8f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.6f, %.4f\n", s_log->t_start.tv_sec, s_log->t_start.tv_nsec, s_log->x, s_log->dx, s_log->xv, s_log->dxv, s_log->ddxv, s_log->x0, s_log->cmd, s_log->Fext,s_log->emg1,s_log->emg2,s_log->emg3,s_log->emg4, s_log->Fraw, s_log->gonio);
        pthread_mutex_unlock(&s_log->lock);
    }
    
    printf("Done Log...\n");
    //pthread_exit(NULL);
    return NULL;
}



void initFolder(struct tm * timeinfo, char * folder)
{
    /**
     * @brief initialize full folder path + name for log file
     * @param[in] timeinfo time structure to add to filename
     * @param[in] folder desired folder path
     */

    char * data_file_name;
    data_file_name = asctime(timeinfo);
    int en = strlen(data_file_name);
    data_file_name[en-1] = '_';

    
    strcat(folder, data_file_name);

    for(int i; i < strlen(folder) - 1; i++)
    {
        if (folder[i] == ' ') 
            folder[i]='_';
        if (folder[i] == ':')
            folder[i]='-';
    }

    mkdir(folder,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    
}


void initLog(char * filename, struct LogData *logData, char * folder)
{
    /**
     * @brief open log file and write header
     * @param[in] filename desired filenmae
     * @param[in] *s pointer to robot States
     * @param[in] timeinfo time structure to add to filename
     * 
     */
    
    strcat(folder, filename);
    printf("%s\n", folder);

    strcpy(logData->filepath, folder);
    logData->fp = fopen(folder,"w");

    //file header
    fprintf(logData->fp,"t(s),t(nsec),x,dx,xv,dxv,ddxv,x0,cmd,Fext,emg1,emg2,emg3,emg4,Fraw,Gonio\n");
    fclose(logData->fp);

    printf("%s\n", folder); 

}


