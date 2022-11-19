#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sched.h>
#include <time.h>
#include <stdint.h>
#define BILLION 1000000000L

void *countA(){

    uint64_t diff;
    struct timespec start, end;
    int i;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 1; i < 4294967296; i++)
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
    for (int i = 1; i < 4294967296; i++)
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
    for (int i = 1; i < 4294967296; i++)
    {
        continue;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time = %llu nanoseconds for others for FIFO\n", (long long unsigned int)diff);
    return NULL;
}


int main(int argc , char const *argv[]){
    pthread_attr_t attr1, attr2,attr3;
    pthread_t tid1 , tid2,tid3;
    int r1,r2,r3;
    struct sched_param sparam1;
    struct sched_param sparam2;
    struct sched_param sparam3;
    
    printf("done\n");

    r1=pthread_attr_init(&attr1);
    // pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    r1=pthread_attr_setschedpolicy(&attr1, SCHED_OTHER);
    sparam1.sched_priority=3;
    r1=pthread_attr_setschedparam(&attr1,&sparam1);
    
    printf("done\n");
    
    // pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
    r2=pthread_attr_init(&attr2);
    r2=pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    sparam2.sched_priority=3;
    r2=pthread_attr_setschedparam(&attr2,&sparam2);
   

    r3=pthread_attr_init(&attr3);
    // pthread_attr_setinheritsched(&attr3, PTHREAD_EXPLICIT_SCHED);
    r3=pthread_attr_setschedpolicy(&attr3, SCHED_FIFO);
    sparam3.sched_priority=3;
    r3=pthread_attr_setschedparam(&attr3,&sparam3);

    printf("done\n");


    pthread_create(&tid1,&attr1,&countA,NULL);
    pthread_join(tid1,NULL);
    pthread_create(&tid2,&attr2,&countB,NULL);
    pthread_join(tid2,NULL);
    pthread_create(&tid3,&attr3,&countC,NULL);
    pthread_join(tid3,NULL);


    return 0;
    
}

