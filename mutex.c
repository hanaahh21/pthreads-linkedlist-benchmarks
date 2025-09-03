//
// Created by user on 9/4/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "mutex.h"
#include "global.h"

void *threadFunc_mtx(void* rank);


unsigned long test_mutex_run(int case_num, int thread_count){
    mutex_data thread_data;

    thread_data.head = NULL;

    //thread_data.thread_count = thread_count; // Number of threads
    thread_data.m = 10000; //Number of operations

    switch (case_num)
    {
        case 1:{
            thread_data.mmem = 0.99;
            thread_data.mins = 0.005;
            thread_data.mdel = 0.005;
            break;
        }

        case 2:{
            thread_data.mmem = 0.9;
            thread_data.mins = 0.05;
            thread_data.mdel = 0.05;
            break;
        }

        case 3:{
            thread_data.mmem = 0.5;
            thread_data.mins = 0.25;
            thread_data.mdel = 0.25;
            break;
        }

        default:{
            thread_data.mmem = 0.99;
            thread_data.mins = 0.005;
            thread_data.mdel = 0.005;
            break;
        }
    }

    thread_data.insOps = 0;
    thread_data.memOps= 0;
    thread_data.delOps = 0;
    thread_data.totOps=0;

    int n = 1000; //Number of elements in the list
    int count = 0;


    // Generate a linked list with n random numbers
    srand(time(0));
    while (count<n){
        Insert(rand()%MAX, &thread_data.head);
        count++ ;
    }

    thread_data.Mem = (int) (thread_data.m * thread_data.mmem);
    thread_data.Ins = (int)(thread_data.m * thread_data.mins);
    thread_data.Del= (int)(thread_data.m * thread_data.mdel);

    // Initializing the mutex
    pthread_mutex_init(&thread_data.mutex, NULL);

    // Generate Threads
    pthread_t *thread_handles = malloc(thread_count * sizeof(pthread_t));
    struct timeval stop;
    struct timeval start;
    gettimeofday(&start, NULL);
    //Assign work to threads
    for (int thread=0; thread < thread_count ; thread++){
        thread_data.rank = thread;
        pthread_create(&thread_handles[thread],NULL,threadFunc_mtx,(void*) &thread_data);
    }

    //printf("Hello from main thread\n");

    for (int thread=0; thread < thread_count ; thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    free(thread_handles);

    //Function call
    gettimeofday(&stop, NULL);
    pthread_mutex_destroy(&thread_data.mutex);
    unsigned long time;
    time = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    destructor(thread_data.head);
    printf("Mutex ran!\n");
    return time;
}

void *threadFunc_mtx(void * t_data){
    mutex_data* thread_data = t_data;
    long my_rank = (long) thread_data->rank;
    while (thread_data->totOps< thread_data->m){

        int rand_value = rand() % MAX;

        int op = rand() % 3;

        if (op==0 && thread_data->insOps < thread_data->Ins){
            if (thread_data->totOps<thread_data->m){
                pthread_mutex_lock(&thread_data->mutex);
                short res = Insert(rand_value, &thread_data->head);
                thread_data->insOps++;
                thread_data->totOps++;
                pthread_mutex_unlock(&thread_data->mutex);
                //printf("Thread %ld Operation %d , Insert %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);
            }

        }
        else if(op==1 && thread_data->delOps < thread_data->Del){
            if (thread_data->totOps<thread_data->m){
                pthread_mutex_lock(&thread_data->mutex);
                short res = Delete(rand_value, &thread_data->head);
                thread_data->delOps++;
                thread_data->totOps++;
                pthread_mutex_unlock(&thread_data->mutex);
                //printf("Thread %ld Operation %d , Delete %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);
            }

        }
        else if(thread_data->memOps < thread_data->Mem){
            if (thread_data->totOps<thread_data->m){
                pthread_mutex_lock(&thread_data->mutex);
                short res = Member(rand_value, thread_data->head);
                thread_data->memOps++;
                thread_data->totOps++;
                pthread_mutex_unlock(&thread_data->mutex);
                //printf("Thread %ld Operation %d , Search %d %d\n", thread_data->rank, thread_data->totOps, rand_value, res);
            }

        }
    }
}