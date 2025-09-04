#ifndef SERIAL_RUN_H
#define SERIAL_RUN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "global.h"

/**
 * Executes the serial linked list test for the given case number.
 * Runs Insert, Delete, and Member operations on a sequential linked list
 * and returns the execution time in microseconds.
 */
unsigned long test_serial_run(int case_num);

#endif // SERIAL_RUN_H
