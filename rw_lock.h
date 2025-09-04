#ifndef RW_LOCK_H
#define RW_LOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "global.h"

/**
 * Struct to hold data for RW Lock test.
 */
typedef struct rw_lock_data {
    pthread_rwlock_t rwlock;   // Reader-writer lock
    node *head;                // Linked list head

    int thread_count;          // Number of threads
    int m;                     // Total number of operations

    // Fractions (probabilities) for each operation
    float frac_mem;            
    float frac_ins;            
    float frac_del;            

    // Exact number of operations for each type
    int max_mem_ops;           
    int max_ins_ops;           
    int max_del_ops;           

    // Operation counters (shared across threads)
    int mem_count;             
    int ins_count;             
    int del_count;             
    int total_count;           

    pthread_mutex_t counter_lock; // Protects operation counters
} rw_lock_data;

/**
 * Run RW lock experiment for given case and thread count.
 * Returns execution time in microseconds.
 */
unsigned long test_rw_lock_run(int case_num, int thread_count);

#endif
