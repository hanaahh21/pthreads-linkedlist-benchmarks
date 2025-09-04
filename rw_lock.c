#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "rw_lock.h"
#include "global.h"

// Thread function declaration
void *rw_thread_worker(void *arg);

/**
 * Executes the concurrent linked list operations using a read-write lock.
 * Supports multiple threads performing Insert, Delete, and Member operations.
 *
 * @param case_id   Test case number (1, 2, or 3)
 * @param num_threads Number of concurrent threads
 * @return          Execution time in microseconds
 */
unsigned long test_rw_lock_run(int case_id, int num_threads) {
    rw_lock_data rw_data;
    rw_data.head = NULL;         // Start with an empty list
    rw_data.m = 10000;           // Total number of operations

    // Set operation fractions based on the selected test case
    switch (case_id) {
        case 1:
            rw_data.mmem = 0.99;
            rw_data.mins = 0.005;
            rw_data.mdel = 0.005;
            break;
        case 2:
            rw_data.mmem = 0.90;
            rw_data.mins = 0.05;
            rw_data.mdel = 0.05;
            break;
        case 3:
            rw_data.mmem = 0.50;
            rw_data.mins = 0.25;
            rw_data.mdel = 0.25;
            break;
        default:
            rw_data.mmem = 0.99;
            rw_data.mins = 0.005;
            rw_data.mdel = 0.005;
            break;
    }

    rw_data.insOps = 0;
    rw_data.memOps = 0;
    rw_data.delOps = 0;
    rw_data.totOps = 0;

    // Populate the linked list with 1000 random values
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        Insert(rand() % MAX, &rw_data.head);
    }

    // Compute operation counts
    rw_data.Mem = (int)(rw_data.m * rw_data.mmem);
    rw_data.Ins = (int)(rw_data.m * rw_data.mins);
    rw_data.Del = (int)(rw_data.m * rw_data.mdel);

    // Initialize the read-write lock
    pthread_rwlock_init(&rw_data.rwlock, NULL);
    pthread_mutex_init(&rw_data.counter_lock, NULL);

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));

    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Launch threads
    for (int t = 0; t < num_threads; t++) {
        rw_data.rank = t;  // Assign thread ID
        pthread_create(&threads[t], NULL, rw_thread_worker, (void*)&rw_data);
    }

    // Wait for all threads to finish
    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    gettimeofday(&end, NULL);

    // Clean up
    pthread_rwlock_destroy(&rw_data.rwlock);
    pthread_mutex_destroy(&rw_data.counter_lock);

    free(threads);
    destructor(rw_data.head);

    // Calculate execution time in microseconds
    unsigned long exec_time = (end.tv_sec - start.tv_sec) * 1000000 + 
                               (end.tv_usec - start.tv_usec);

    printf("RW lock test completed!\n");
    return exec_time;
}

/**
 * Worker function executed by each thread.
 * Randomly performs Insert, Delete, or Member operations on the shared linked list.
 */
void *rw_thread_worker(void *arg) {
    rw_lock_data *data = (rw_lock_data*)arg;

    while (1) {
        pthread_mutex_lock(&data->counter_lock);
        if (data->totOps >= data->m) {
            pthread_mutex_unlock(&data->counter_lock);
            break; // all work done
        }
        data->totOps++; // reserve an operation slot
        pthread_mutex_unlock(&data->counter_lock);

        int val = rand() % MAX;
        int op_type = rand() % 3;

        if (op_type == 0 && data->insOps < data->Ins) {
            pthread_rwlock_wrlock(&data->rwlock);
            Insert(val, &data->head);
            pthread_rwlock_unlock(&data->rwlock);

            pthread_mutex_lock(&data->counter_lock);
            data->insOps++;
            pthread_mutex_unlock(&data->counter_lock);
        }
        else if (op_type == 1 && data->delOps < data->Del) {
            pthread_rwlock_wrlock(&data->rwlock);
            Delete(val, &data->head);
            pthread_rwlock_unlock(&data->rwlock);

            pthread_mutex_lock(&data->counter_lock);
            data->delOps++;
            pthread_mutex_unlock(&data->counter_lock);
        }
        else {
            pthread_rwlock_rdlock(&data->rwlock);
            Member(val, data->head);
            pthread_rwlock_unlock(&data->rwlock);

            pthread_mutex_lock(&data->counter_lock);
            data->memOps++;
            pthread_mutex_unlock(&data->counter_lock);
        }
    }

    return NULL;
}

