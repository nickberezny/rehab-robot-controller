#ifndef INCLUDE_FILE
#define INCLUDE_FILE

#define LINUX_SCHEDULER SCHED_RR //cpu scheduler, choose from: SCHED_FIFO, SCHED_RR, SCHED_DEADLINE

#define MAT_EXP_ITERATIONS 15 //number of iterations for matrix exp approximation

#define NUM_OF_THREADS 1
#define PORT 6000

#define BUFFER_SIZE 10

#define NSEC_IN_SEC 1000000000.0
#define STEP_SEC 0.001 
#define STEP_NSEC (STEP_SEC*NSEC_IN_SEC)

#endif 