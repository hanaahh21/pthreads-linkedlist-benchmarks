//
// Created by user on 9/4/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "linked_list.h"
#include "serial.h"
#include "mutex.h"
#include "rw_lock.h"
#include "global.h"

int main() {
    // Variables to store execution times for different approaches
    unsigned long serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime;
    unsigned long rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime;

    const int N = 385;   // Number of repetitions for averaging

    /*===================
    |       case 1      |
    ====================*/
    int case_num = 1;
    FILE *fp = fopen("output/Case_1.csv","w+");     // Open CSV file for output
    fprintf(fp,"Serial, mut_t1, mut_t2, mut_t4, mut_t8, rw_t1, rw_t2, rw_t4, rw_t8\n");

    // Repeat the experiment N times to capture average runtime behavior
    for (size_t i = 0; i < N; i++) {
        serial_runtime = test_serial_run(case_num);     // Run single-threaded version
        mut_t1_runtime = test_mutex_run(case_num,1);    // Mutex with 1 thread
        mut_t2_runtime = test_mutex_run(case_num,2);    // Mutex with 2 threads
        mut_t4_runtime = test_mutex_run(case_num,4);    // Mutex with 4 threads
        mut_t8_runtime = test_mutex_run(case_num,8);    // Mutex with 8 threads
        rw_t1_runtime = test_rw_lock_run(case_num,1);   // RW Lock with 1 thread
        rw_t2_runtime = test_rw_lock_run(case_num,2);   // RW Lock with 2 threads
        rw_t4_runtime = test_rw_lock_run(case_num,4);   // RW Lock with 4 threads
        rw_t8_runtime = test_rw_lock_run(case_num,8);   // RW Lock with 8 threads

        fprintf(fp,"%lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu\n",
                serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime,
                mut_t8_runtime, rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);
    }

    fclose(fp); // Close the CSV file

    /*===================
    |       case 2      |
    ====================*/
    case_num = 2;
    fp = fopen("output/Case_2.csv","w+");
    fprintf(fp,"Serial, mut_t1, mut_t2, mut_t4, mut_t8, rw_t1, rw_t2, rw_t4, rw_t8\n");

    for (size_t i = 0; i < N; i++) {
        serial_runtime = test_serial_run(case_num);     // Run single-threaded version
        mut_t1_runtime = test_mutex_run(case_num,1);    // Mutex with 1 thread
        mut_t2_runtime = test_mutex_run(case_num,2);    // Mutex with 2 threads
        mut_t4_runtime = test_mutex_run(case_num,4);    // Mutex with 4 threads
        mut_t8_runtime = test_mutex_run(case_num,8);    // Mutex with 8 threads
        rw_t1_runtime = test_rw_lock_run(case_num,1);   // RW Lock with 1 thread
        rw_t2_runtime = test_rw_lock_run(case_num,2);   // RW Lock with 2 threads
        rw_t4_runtime = test_rw_lock_run(case_num,4);   // RW Lock with 4 threads
        rw_t8_runtime = test_rw_lock_run(case_num,8);   // RW Lock with 8 threads

        fprintf(fp,"%lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu\n",
                serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime,
                mut_t8_runtime, rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);
    }
    fclose(fp);

    /*===================
    |       case 3      |
    ====================*/
    case_num = 3;
    fp = fopen("output/Case_3.csv","w+");
    fprintf(fp,"Serial, mut_t1, mut_t2, mut_t4, mut_t8, rw_t1, rw_t2, rw_t4, rw_t8\n");

    for (size_t i = 0; i < N; i++) {
        serial_runtime = test_serial_run(case_num);    // Run single-threaded version
        mut_t1_runtime = test_mutex_run(case_num,1);    // Mutex with 1 thread
        mut_t2_runtime = test_mutex_run(case_num,2);    // Mutex with 2 threads
        mut_t4_runtime = test_mutex_run(case_num,4);    // Mutex with 4 threads
        mut_t8_runtime = test_mutex_run(case_num,8);    // Mutex with 8 threads
        rw_t1_runtime = test_rw_lock_run(case_num,1);   // RW Lock with 1 thread
        rw_t2_runtime = test_rw_lock_run(case_num,2);   // RW Lock with 2 threads
        rw_t4_runtime = test_rw_lock_run(case_num,4);   // RW Lock with 4 threads
        rw_t8_runtime = test_rw_lock_run(case_num,8);   // RW Lock with 8 threads

        fprintf(fp,"%lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu\n",
                serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime,
                mut_t8_runtime, rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);
    }
    fclose(fp);

    printf("All cases finished. CSV files saved in output/ folder.\n");
    return 0;
}
