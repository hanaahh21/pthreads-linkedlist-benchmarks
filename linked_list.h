//
// Created by user on 9/4/2025.
//

#ifndef PTHREADS_LINKEDLIST_BENCHMARKS_LINKED_LIST_H
#define PTHREADS_LINKEDLIST_BENCHMARKS_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node {
    int data;
    struct node * next;
    pthread_mutex_t mutex;
};

typedef struct node node;

void destructor(node* head_p);
int Member(int value, node *head_p);
int Insert(int value, node **head_p);
int Delete(int value, node **head_p);
void Print(node * head_p);


#endif //PTHREADS_LINKEDLIST_BENCHMARKS_LINKED_LIST_H
