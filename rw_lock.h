#ifndef RW_LOCK_MODULE_H
#define RW_LOCK_MODULE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "global.h"

/**
 * Structure to store data needed for the read-write lock test.
 * Includes the linked list head, operation counters, 
 * fractions of operations, and the pthread read-write lock.
 */
typedef struct {
    pthread_rwlock_t rwlock;// Read-write lock for concurrent access
    pthread_mutex_t counter_lock; // New: protect counters

    node *head;              // Pointer to the head of the linked list

    int num_threads;         // Number of concurrent threads
    int totOps;           // Total number of operations
    float mmem;   // Fraction of search (Member) operations
    float mins;   // Fraction of insert operations
    float mdel;   // Fraction of delete operations

    // Counters for performed operations
    int memOps;
    int insOps;
    int delOps;

    // Number of each type of operation to perform
    int Mem;
    int Ins;
    int Del;
    int m;

    int rank;           // Thread identifier
} rw_lock_data;

/**
 * Runs the linked list test using a read-write lock.
 * @param case_id      Test case number (1,2,3)
 * @param num_threads  Number of concurrent threads to use
 * @return Execution time in microseconds
 */
unsigned long test_rw_lock_run(int case_id, int num_threads);

#endif
