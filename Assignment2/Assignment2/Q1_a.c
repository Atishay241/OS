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

long long unsigned int t1;
long long unsigned int t2;
long long unsigned int t3;

struct sched_param sparam1;
struct sched_param sparam2;
struct sched_param sparam3;



void *countA(){

    uint64_t diff;
    struct timespec start, end;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (long long int i = 1; i <= 4294967296; i++)
    {
        continue;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time = %llu nanoseconds for others\n", (long long unsigned int)diff);
    t1=(long long unsigned int)diff;
    
    return NULL;
}

void *countB(){

   uint64_t diff;
    struct timespec start, end;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (long long int i = 1; i <= 4294967296; i++)
    {
        continue;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time = %llu nanoseconds for RR\n", (long long unsigned int)diff);
    t2=(long long unsigned int)diff;
    return NULL;
}


void *countC(){

  uint64_t diff;
    struct timespec start, end;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (long long int i = 1; i <= 4294967296; i++)
    {
        continue;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time = %llu nanoseconds for FIFO\n", (long long unsigned int)diff);
    t3=(long long unsigned int)diff;
    return NULL;
}


int main(int argc , char const *argv[]){
    pthread_attr_t attr1, attr2,attr3;
    pthread_t tid1 , tid2,tid3;
    int r1,r2,r3,prio=5;
 

    r1=pthread_attr_init(&attr1);
    r1=pthread_attr_setschedpolicy(&attr1, SCHED_OTHER);
    r1=pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);

    // r1= pthread_attr_setinheritsched(&attr1,PTHREAD_EXPLICIT_SCHED);

    
    
    r2=pthread_attr_init(&attr2);
    r2=pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    r2=pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    

    r3=pthread_attr_init(&attr3);
    r3=pthread_attr_setschedpolicy(&attr3, SCHED_FIFO);
    r3=pthread_attr_setinheritsched(&attr3, PTHREAD_EXPLICIT_SCHED);


    FILE *ptr;
    ptr= fopen("a.data","a");
    for(int i=0;i<10;i++){
        
        r1=pthread_attr_getschedparam(&attr1,&sparam1);
        sparam1.sched_priority=0;
        r1=pthread_attr_setschedparam(&attr1,&sparam1);
        pthread_create(&tid1,&attr1,&countA,NULL);

        r2=pthread_attr_getschedparam(&attr2,&sparam2);
        sparam2.sched_priority=prio;
        r2=pthread_attr_setschedparam(&attr2,&sparam2);
        pthread_create(&tid2,&attr2,&countB,NULL);

        r3=pthread_attr_getschedparam(&attr3,&sparam3);
        sparam3.sched_priority=prio;
        r3=pthread_attr_setschedparam(&attr3,&sparam3);
        pthread_create(&tid3,&attr3,&countC,NULL);

        printf("priority is %d: \n",prio);
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        pthread_join(tid3,NULL);
        printf("\n");
        
        fprintf(ptr,"Priority-%d %llu %llu %llu\n",prio,t1,t2,t3);
        prio+=5;

    }

    fclose(ptr);

    return 0;
    
}

