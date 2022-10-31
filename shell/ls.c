#define _POSIX_SOURCE
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char *argv[]){

    int flagform = 0; // for -m versiion of ls
    int flagfor1 = 0; //for -1 version of ls
    
    char address[100];
    getcwd(address,100);
    struct dirent *d;
    DIR *dh = opendir(address);
	if (!dh)
	{
		if (errno == ENOENT)
		{
			perror("ls: Directory doesn't exist\n");
		}
		else
		{
			perror("ls: Unable to read directory\n");
		}
		return 0;
	}


    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-1") == 0)
        {
            flagfor1 = 1;
        }
        if (strcmp(argv[i], "-m") == 0)
        {
            flagform= 1;
        }
    }

    if (flagform == 1 && flagfor1 == 1)
    {
        printf("MyShell: command not found\n");
        return 0;
    }

    else if (flagform == 0 && flagfor1 == 0)
    {
        if(argc!=1){
            printf("MyShell: command not found\n");
            return 0;
        }
        
        while ((d = readdir(dh)) != NULL)
        {
            if (d->d_name[0] != '.')
                printf("%s   ", d->d_name);
        }
        printf("\n");
    }

    else if(flagform==1){
        if(argc!=2){
            printf("MyShell: command not found\n");
            return 0;
        }

        while ((d = readdir(dh)) != NULL)
        {
            if (d->d_name[0] != '.')
                printf("%s, ", d->d_name);
        }
        printf("\n");
    }

    else if (flagfor1 == 1)
    {
        if(argc!=2){
            printf("MyShell: command not found\n");
            return 0;
        }
        while ((d = readdir(dh)) != NULL)
        {
            if (d->d_name[0] != '.')
                printf("%s\n", d->d_name);
        }
        
    }
    
    return 0;
    
}