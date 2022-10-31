#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char *argv[]){

    int flagforn = 0; // for -n version of cat
    int flagforE= 0; //for -e version of cat

    FILE *file;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
        {
            flagforn = 1;
        }
        if (strcmp(argv[i], "-e") == 0)
        {
            flagforE = 1;
        }
    }

    if (flagforn == 1 && flagforE == 1)
    {
        printf("MyShell: command not found\n");
        return 0;
    }



    else if (flagforn == 0 && flagforE == 0)
    {
        if(argc<2){
            printf("MyShell: command not found\n");
            return 0;
        }
        
        for(int i=1;i<argc;i++){

            DIR* dir = opendir(argv[i]);
            if(dir) {printf("cat: %s: Is a directory\n",argv[i]);
                    continue;}
            
            file = fopen(argv[i],"r");

            if(file==NULL) printf("cat: %s: No such file or directory\n",argv[i]);
            else{
                char read[500];

                while (fgets(read, 100, file) != NULL){
                    printf("%s", read);
                }

                fclose(file);
            }

            }
        
        }
    

    
    else if (flagforn == 1)
    {
        if(argc<3){
            printf("MyShell: command not found\n");
            return 0;
        }
        for(int i=2;i<argc;i++){
            
            DIR* dir = opendir(argv[i]);
            if(dir) {printf("cat: %s: Is a directory\n",argv[i]);
                    continue;}
            file = fopen(argv[i],"r");

            if(file==NULL) printf("cat: %s: No such file or directory\n",argv[i]);
            else{
                char read[500];
                int c=1;
                while (fgets(read, 100, file) != NULL){
                    printf("%d %s", c,read);
                    c++;
                }

                fclose(file);
            }

            }
        }
        
    

    else if(flagforE==1){
        if(argc<3){
            printf("MyShell: command not found\n");
            return 0;
        }
        for(int i=2;i<argc;i++){
            
            DIR* dir = opendir(argv[i]);
            if(dir) {printf("cat: %s: Is a directory\n",argv[i]);
                    continue;}

            file = fopen(argv[i],"r");
            

            if(file==NULL) printf("cat: %s: No such file or directory\n",argv[i]);
            else{
                char read[500];
                
                while (fgets(read, 100, file) != NULL){
                    read[strcspn(read,"\n")]='\0';
                    printf("%s$\n",read);
   
                    
                }
                
                fclose(file);
            }

            }

    }

    return 0;
}