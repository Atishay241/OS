#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sched.h>
#include <time.h>
#define BILLION 1000000000L

void *countA(){

    uint64_t diff;
    struct timespec start, end;
    int i;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 1; i < count; i++)
    {
        continue;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time = %llu nanoseconds for others\n", (long long unsigned int)diff);
    return NULL;
}

void *countB(){

   uint64_t diff;
    struct timespec start, end;
    int i;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 1; i < count; i++)
    {
        continue;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time = %llu nanoseconds for others RR\n", (long long unsigned int)diff);
    return NULL;
}


void *countC(){

  uint64_t diff;
    struct timespec start, end;
    int i;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 1; i < count; i++)
    {
        continue;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time = %llu nanoseconds for others for FIFO\n", (long long unsigned int)diff);
    return NULL;
}


int main(int argc , char const *argv[]){
    pthread_attr_t attr1;
    pthread_t tid1;
    int r;
    struct sched_param sparam1;
    pthread_attr_init(&attr1);
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr1, SCHED_OTHER);
    sparam.sched_priority=10;
    pthread_attr_setschedparam(&attr,&sparam1);
    pthread_create(&tid1,&attr1,&countA,NULL);
    pthread_join(tid1,NULL);


    pthread_attr_t attr2;
    pthread_t tid2;
    int r;
    struct sched_param sparam2;
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_init(&attr2);
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    sparam.sched_priority=10;
    pthread_attr_setschedparam(&attr2,&sparam2);
    pthread_create(&tid2,&attr2,&countA,NULL);
    pthread_join(tid2,NULL);


    pthread_attr_t attr3;
    pthread_t tid3;
    int r;
    struct sched_param sparam3;
    pthread_attr_init(&attr3);
    pthread_attr_setinheritsched(&attr3, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr3, SCHED_FIFO);
    sparam.sched_priority=10;
    pthread_attr_setschedparam(&attr3,&sparam3);
    pthread_create(&tid3,&attr3,&countA,NULL);
    pthread_join(tid3,NULL);


    return 0;
    
}

