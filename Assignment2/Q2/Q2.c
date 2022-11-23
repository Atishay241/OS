#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define SYS_kernel_2d_memcpy 451

int main(int argc, char **argv)
{
	float matrix1[2][2] = {{5.1,2.1},{3.7,4.99}};
	float matrix2[2][2];

	printf("\nInitial Matrix1: \n");
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			printf("%f ",matrix1[i][j]);
		}
		printf("\n");
	}
	printf("\nInitial Matrix2: \n");
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			printf("%f ",matrix2[i][j]);
		}
		printf("\n");
}

	
	printf("\n\nMaking system call with matrix1 and matrix2\n");
	long res =  syscall(SYS_kernel_2d_memcpy, (float *)matrix1 , (float *)matrix2);
	
	printf("System call returned %ld.\n",res);
	perror("Console Output");

	printf("Matrix 2 : -After system call\n");

	for(int i =0 ;i<2 ;i++){
		for(int j=0 ; j<2;j++){
			printf("%f ",matrix2[i][j]);
		}
		printf("\n");
	}
	return res;
}
