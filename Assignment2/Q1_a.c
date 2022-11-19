#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sched.h>


void *countA(){
    for(long long i=1;i<=4294967296;i++){
        continue;
    }
    printf("done");
    return NULL;
}

int main(int argc , char const *argv[]){
    pthread_attr_t attr;
    pthread_t tid;
    int r;
    struct sched_param sparam;
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
    sparam.sched_priprity=1;
    pthread_attr_setschedparam(&attr,&param);
    pthread_create(&tid,&attr,&countA,NULL);
    pthread_join(tid,NULL);

    return 0;

    
}

