#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<math.h>
#include<time.h>
#include<stdint.h>
#define BILLION 1000000000

static void* countA(void* arg){
	struct timespec st,end;
	long long int i=0;
	clock_gettime(CLOCK_MONOTONIC,&st);
	for(i=0;i<pow(2,32);i++){
		
	}
	clock_gettime(CLOCK_MONOTONIC,&end);
	uint64_t diff=(end.tv_sec-st.tv_sec);
	long double d=(long double)(end.tv_nsec-st.tv_nsec)/BILLION;
	printf("Time elapsed OTHER : %Lf \n",(long long unsigned int)diff+d);
}

static void* countB(void* arg){
	struct timespec st,end;
	long long int i=0;
	clock_gettime(CLOCK_MONOTONIC,&st);
	for(i=0;i<pow(2,32);i++){
		
	}
	clock_gettime(CLOCK_MONOTONIC,&end);
	uint64_t diff=(end.tv_sec-st.tv_sec);
	long double d=(long double)(end.tv_nsec-st.tv_nsec)/BILLION;
	printf("Time elapsed RR : %Lf \n",(long long unsigned int)diff+d);
}

static void* countC(void* arg){
	struct timespec st,end;
	long long int i=0;
	clock_gettime(CLOCK_MONOTONIC,&st);
	for(i=0;i<pow(2,32);i++){
		
	}
	clock_gettime(CLOCK_MONOTONIC,&end);
	uint64_t diff=(end.tv_sec-st.tv_sec);
	long double d=(long double)(end.tv_nsec-st.tv_nsec)/BILLION;
	printf("Time elapsed FIFO : %Lf \n",(long long unsigned int)diff+d);
}

int main(int argc,char* argv[]){
	pthread_t ThrA;
	pthread_t ThrB;
	pthread_t ThrC;
	pthread_attr_t attr1;
	int s;
	s=pthread_attr_init(&attr1);
	if(s!=0){
		errno=s;
		perror("pthread_attr_init");
		exit(EXIT_FAILURE);
	}


	s=pthread_attr_setschedpolicy(&attr1,SCHED_OTHER);	
	if(s!=0){
		errno=s;
		perror("pthread_attr_schedpolicy");
		exit(EXIT_FAILURE);
	}
	pthread_attr_setinheritsched(&attr1,PTHREAD_EXPLICIT_SCHED);
	struct sched_param schedParamA;
	schedParamA.sched_priority=0;
	s=pthread_attr_setschedparam(&attr1,&schedParamA);
	s=pthread_create(&ThrA,&attr1,&countA,(void*)"thr1 ");
	//pthread_join(ThrA,NULL);

	pthread_attr_t attr2;
	s=pthread_attr_init(&attr2);
	s=pthread_attr_setschedpolicy(&attr2,SCHED_RR);
	if(s!=0){
		errno=s;
		perror("pthread_attr_schedpolicy");
		exit(EXIT_FAILURE);
	}
	//attrp2=&attr2;
	pthread_attr_setinheritsched(&attr2,PTHREAD_EXPLICIT_SCHED);
	struct sched_param schedParamB;
	schedParamB.sched_priority=1;
	s=pthread_attr_setschedparam(&attr2,&schedParamB);
	s=pthread_create(&ThrB,&attr2,&countB,(void*)"thr2 ");
	//pthread_join(ThrB,NULL);

	pthread_attr_t attr3;
	s=pthread_attr_init(&attr3);
	s=pthread_attr_setschedpolicy(&attr3,SCHED_FIFO);
	if(s!=0){
		errno=s;
		perror("pthread_attr_setinheritsched");
		exit(EXIT_FAILURE);
	}
	//attrp3=&attr3;
	pthread_attr_setinheritsched(&attr3,PTHREAD_EXPLICIT_SCHED);
	struct sched_param schedParamC;
	schedParamC.sched_priority=1;
	s=pthread_attr_setschedparam(&attr3,&schedParamC);
	s=pthread_create(&ThrC,&attr3,&countC,(void*)"thr3 ");
	//pthread_join(ThrC,NULL);

	if(s!=0){
		errno=s;
		perror("pthread_attr_setschedparam");
		exit(EXIT_FAILURE);
	}
	if(s!=0){
		errno=s;
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	if(s!=0){
		errno=s;
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	pthread_join(ThrC,NULL);
	pthread_join(ThrB,NULL);
	pthread_join(ThrA,NULL);
	return 0;
}
