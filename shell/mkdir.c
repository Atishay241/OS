#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char *argv[]){
    // printf("arg is %d\n",argc);
    // for(int i=0;i<argc;i++){
    //     printf("%s",argv[i])
    // }
    int flagforp = 0; // for -p no warning
    int flagforhelp = 0; //for --help
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0)
        {
            flagforp = 1;
        }
        if (strcmp(argv[i], "--help") == 0)
        {
            flagforhelp = 1;
        }
    }
    if (flagforp == 1 && flagforhelp == 1)
    {
        printf("MyShell: command not found\n");
        return 0;
    }
    else if (flagforhelp == 0 && flagforp == 0)
    {
        if(argc<2){
            printf("MyShell: command not found\n");
            return 0;
        }
        
        for(int i=1;i<argc;i++){
            int check = mkdir(argv[i], 0777);
            //checking if directory is created
            if (check!=0){
                printf(" cannot create directory %s: File exists \n", argv[i]);

            }
        
        }
    }

    
    else if (flagforp == 1)
    {
        if(argc<3){
            printf("MyShell: command not found\n");
            return 0;
        }
        for(int i=2;i<argc;i++){
            int check = mkdir(argv[i], 0777);
        }
        
    }

    else if(flagforhelp==1){
        if(argc!=2){
            printf("MyShell: command not found\n");
            return 0;
        }
        printf("Usage: mkdir [OPTION]... DIRECTORY...\nCreate the DIRECTORY(ies), if they do not already exist.\nMandatory arguments to long options are mandatory for short options too.\n -p, --parents     no error if existing, make parent directories as needed \n--help     display this help\n");
    }

    return 0;
}