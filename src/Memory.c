/**
 * @file Memory.c
 * @author Nick Berezny
 * @date 13 Apr 2022
 * @brief functions for memory management
 *
 */


#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "./include/Parameters.h"
#include "./include/Structures.h"
#include "./include/Memory.h"

int initMutex(struct States * s)
{
    return pthread_mutex_init(&s->lock, NULL); 
}