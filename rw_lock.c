#include "rw_lock.h"

static void *threadFunc_rw(void *arg);

unsigned long test_rw_lock_run(int case_num, int thread_count) {
    rw_lock_data data;
    data.head = NULL;
    data.thread_count = thread_count;
    data.m = 10000; // Total operations

    // Set workload mix based on case
    switch (case_num) {
        case 1: data.frac_mem = 0.99; data.frac_ins = 0.005; data.frac_del = 0.005; break;
        case 2: data.frac_mem = 0.90; data.frac_ins = 0.05;  data.frac_del = 0.05;  break;
        case 3: data.frac_mem = 0.50; data.frac_ins = 0.25;  data.frac_del = 0.25;  break;
        default:data.frac_mem = 0.99; data.frac_ins = 0.005; data.frac_del = 0.005; break;
    }

    // Compute max operations per type
    data.max_mem_ops = (int)(data.m * data.frac_mem);
    data.max_ins_ops = (int)(data.m * data.frac_ins);
    data.max_del_ops = (int)(data.m * data.frac_del);

    // Initialize counters
    data.mem_count = 0;
    data.ins_count = 0;
    data.del_count = 0;
    data.total_count = 0;

    // Initialize sync primitives
    pthread_rwlock_init(&data.rwlock, NULL);
    pthread_mutex_init(&data.counter_lock, NULL);

    int n = 1000; //Number of elements in the list

    
    // Build initial linked list
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        Insert(rand() % MAX, &data.head);
    }

    // Launch threads
    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));
    struct timeval start, stop;
    gettimeofday(&start, NULL);

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], NULL, threadFunc_rw, &data);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&stop, NULL);

    // Cleanup
    pthread_rwlock_destroy(&data.rwlock);
    pthread_mutex_destroy(&data.counter_lock);
    destructor(data.head);
    free(threads);

    unsigned long elapsed = (stop.tv_sec - start.tv_sec) * 1000000L +
                            (stop.tv_usec - start.tv_usec);
    printf("RW Lock case %d with %d threads took %lu us\n",
           case_num, thread_count, elapsed);
    return elapsed;
}

static void *threadFunc_rw(void *arg) {
    rw_lock_data *data = (rw_lock_data *)arg;

    while (1) {
        int op;
        int rand_value = rand() % MAX;

        pthread_mutex_lock(&data->counter_lock);
        if (data->total_count >= data->m) {
            pthread_mutex_unlock(&data->counter_lock);
            break;
        }

        // Randomly pick operation (but ensure limits not exceeded)
        if (data->ins_count < data->max_ins_ops) {
            op = 0; // Insert
            data->ins_count++;
        } else if (data->del_count < data->max_del_ops) {
            op = 1; // Delete
            data->del_count++;
        } else {
            op = 2; // Member
            data->mem_count++;
        }
        data->total_count++;
        pthread_mutex_unlock(&data->counter_lock);

        // Perform operation under proper lock
        if (op == 0) { // Insert
            pthread_rwlock_wrlock(&data->rwlock);
            Insert(rand_value, &data->head);
            pthread_rwlock_unlock(&data->rwlock);
        } else if (op == 1) { // Delete
            pthread_rwlock_wrlock(&data->rwlock);
            Delete(rand_value, &data->head);
            pthread_rwlock_unlock(&data->rwlock);
        } else { // Member
            pthread_rwlock_rdlock(&data->rwlock);
            Member(rand_value, data->head);
            pthread_rwlock_unlock(&data->rwlock);
        }
    }

    return NULL;
}
