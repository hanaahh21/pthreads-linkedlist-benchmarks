//
// Created by user on 9/4/2025.
//

#ifndef PTHREADS_LINKEDLIST_BENCHMARKS_MUTEX_H
#define PTHREADS_LINKEDLIST_BENCHMARKS_MUTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "global.h"

struct mutex_data
{
    pthread_mutex_t mutex;
    node *head;

    int thread_count; // Number of threads
    int m; //Number of operations
    float mmem;
    float mins;
    float mdel;

    // Fractions of each operation
    int Mem,Ins,Del;

    int insOps;
    int memOps;
    int delOps;
    int totOps;

    int rank;
};
typedef struct mutex_data mutex_data;

unsigned long test_mutex_run(int case_num, int thread_count);

#endif //PTHREADS_LINKEDLIST_BENCHMARKS_MUTEX_H
