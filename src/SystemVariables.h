#ifndef INCLUDE_FILE
#define INCLUDE_FILE

#define NSEC_IN_SEC 1000000000.0
#define STEP_NSEC 1000000.0 //control step time (1ms)
#define LINUX_SCHEDULER SCHED_RR //cpu scheduler, choose from: SCHED_FIFO, SCHED_RR, SCHED_DEADLINE

#define MAT_EXP_ITERATIONS 15 //number of iterations for matrix exp approximation

#define NUM_OF_THREADS 3


#endif 