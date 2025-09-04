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
    pthread_rwlock_t lock;   // Read-write lock for concurrent access
    node *head;              // Pointer to the head of the linked list

    int num_threads;         // Number of concurrent threads
    int total_ops;           // Total number of operations
    float fraction_search;   // Fraction of search (Member) operations
    float fraction_insert;   // Fraction of insert operations
    float fraction_delete;   // Fraction of delete operations

    int m;
    // Number of each type of operation to perform
    int search_ops;
    int insert_ops;
    int delete_ops;

    // Counters for performed operations
    int performed_search;
    int performed_insert;
    int performed_delete;
    int performed_total;

    int thread_id;           // Thread identifier
} rw_lock_data;

/**
 * Runs the linked list test using a read-write lock.
 * @param case_id      Test case number (1,2,3)
 * @param num_threads  Number of concurrent threads to use
 * @return Execution time in microseconds
 */
unsigned long test_rw_lock_run(int case_id, int num_threads);

#endif
