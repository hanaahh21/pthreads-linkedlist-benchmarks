#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "serial.h"
#include "global.h"

/**
 * Executes the serial linked list test for the given case number.
 * Performs a mixture of Insert, Delete, and Member operations on a linked list
 * and returns the execution time in microseconds.
 */
unsigned long test_serial_run(int case_num) {
    node* head = NULL;          // Head pointer for the linked list
    float fracMember, fracInsert, fracDelete;
    int totalOps = 10000;        // Total operations to perform

    // Choose operation fractions based on the test case
    switch (case_num) {
        case 1:
            fracMember = 0.99;
            fracInsert = 0.005;
            fracDelete = 0.005;
            break;
        case 2:
            fracMember = 0.9;
            fracInsert = 0.05;
            fracDelete = 0.05;
            break;
        case 3:
            fracMember = 0.5;
            fracInsert = 0.25;
            fracDelete = 0.25;
            break;
        default:
            fracMember = 0.99;
            fracInsert = 0.005;
            fracDelete = 0.005;
    }

    // Convert fractions into actual counts for each operation
    int targetMember = (int)(totalOps * fracMember);
    int targetInsert = (int)(totalOps * fracInsert);
    int targetDelete = (int)(totalOps * fracDelete);

    int doneMember = 0, doneInsert = 0, doneDelete = 0;
    int completedOps = 0;

    // Initial list population
    int initialSize = 1000;  // Start with 1000 random unique elements
    srand((unsigned int)time(NULL));  // Seed randomness with current time
    for (int i = 0; i < initialSize; i++) {
        Insert(rand() % MAX, &head);
    }

    // Measure start time
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    // Perform operations until all are completed
    while (completedOps < totalOps) {
        int randomValue = rand() % MAX;
        int operationType = rand() % 3;  // Randomly choose Insert, Delete, or Member

        if (operationType == 0 && doneInsert < targetInsert) {
            // Perform Insert
            Insert(randomValue, &head);
            doneInsert++;
        } 
        else if (operationType == 1 && doneDelete < targetDelete) {
            // Perform Delete
            Delete(randomValue, &head);
            doneDelete++;
        } 
        else if (doneMember < targetMember) {
            // Perform Member search
            Member(randomValue, head);
            doneMember++;
        }
        completedOps++;
    }

    // Measure end time
    gettimeofday(&endTime, NULL);
    unsigned long execTime = (endTime.tv_sec - startTime.tv_sec) * 1000000L
                           + (endTime.tv_usec - startTime.tv_usec);

    // Clean up memory
    destructor(head);
    printf("Serial execution completed!\n");

    return execTime;
}
