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
    // printf("arg is %d\n",argc);
    // for(int i=0;i<argc;i++){
    //     printf("%s",argv[i])
    // }
    int flagfori = 0; // for -i versiion of rm
    int flagford = 0; //for -d version of rm
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            flagfori = 1;
        }
        if (strcmp(argv[i], "-d") == 0)
        {
            flagford= 1;
        }
    }
    if (flagford == 1 && flagfori == 1)
    {
        printf("MyShell: command not found\n");
        return 0;
    }

    else if (flagfori == 0 && flagford == 0)
    {
        if(argc<2){
            printf("MyShell: command not found\n");
            return 0;
        }
        
        for(int i=1;i<argc;i++){
            
            // char path[100];
            // getcwd(path,100);
            // printf("%s",path);
            // strcat(path,"/mkdir");
            DIR* dir = opendir(argv[i]);
            
            if (ENOENT == errno) {
                printf("rm: %s: No such file or directory\n",argv[i]);
                continue;
            }

            int check = unlink(argv[i]);
            //checking if directory is created
            if (check!=0){
                printf("rm: %s : is a directory\n",argv[i]);

            }
        
        }
    }

    else if(flagford==1){
        if(argc<3){
            printf("MyShell: command not found\n");
            return 0;
        }

        for(int i=2;i<argc;i++){

            DIR* dir = opendir(argv[i]);
            
            if (ENOENT == errno) {
                printf("rm: %s: No such file or directory\n",argv[i]);
                continue;
            }

            int check = remove(argv[i]);

            if (check!=0){
                printf("rm: %s : Directory not empty\n",argv[i]);

            }

        }


    }

    else if (flagfori == 1)
    {
        if(argc<3){
            printf("MyShell: command not found\n");
            return 0;
        }
        for(int i=2;i<argc;i++){
            DIR* dir = opendir(argv[i]);
            
            if (ENOENT == errno) {
                printf("rm: %s: No such file or directory\n",argv[i]);
                continue;
            }
            char boolean[10];
            printf("remove %s? y/n ",argv[i]);
            // fgets(boolean,10,stdin);
            scanf("%s",boolean);
            
            if(strcmp(boolean,"y")==0){
                int check= unlink(argv[i]);
                
                if (check!=0){
                printf("rm: %s : is a directory\n",argv[i]);
                }

            }

        }
        
    }
    
    return 0;
    
}




