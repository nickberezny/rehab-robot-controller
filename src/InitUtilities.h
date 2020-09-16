#include <stdbool.h>

bool initThread(pthread_attr_t * attr, struct sched_param * param, int  priority[], int numberOfThreads);
int initSock(struct sockaddr_in * serv_addr, int * listen_fd, int port);
bool initMemory(pthread_mutex_t lock[], int bufferLength);
bool initDataLog(FILE * fp, char * fileName);
void runFakeSocket(void * d);