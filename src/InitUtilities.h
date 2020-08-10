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


bool initThread(pthread_attr_t * attr, struct sched_param * param, int  priority[], int numberOfThreads);
int initSock(struct sockaddr_in *serv_addr, int port);
bool initMemory(pthread_mutex_t lock[], int bufferLength);
bool initDataLog(FILE * fp, char * fileName);