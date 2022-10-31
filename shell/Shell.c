#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include<pthread.h>      
#include<fcntl.h>
#include<signal.h>

pid_t pid;
char commandPath[200];
#define clear() printf("\033[H\033[J")  // ANSI SEQUENCE
char split[100][100];
int count=0;


void parsed(char *cmd){
    count=0;
    char *first= strtok(cmd," ");
    while(first!=NULL){
        strcpy(split[count++],first);
        first=strtok(NULL," ");
    }

}

void* sys1(){
    char arg[100];
    char concat[100];
    strcpy(arg,commandPath);
    strcat(arg,"/./mkdir");
    
    for(int i=1;i<count-1;i++){
        sprintf(concat," %s",split[i]);
        strcat(arg,concat);
    }
    // printf("%s\n",arg);
    system(arg);
    return NULL;

}


void* sys2(){
    char arg[100];
    char concat[100];
    strcpy(arg,commandPath);
    strcat(arg,"/./rm");
    
    for(int i=1;i<count-1;i++){
        sprintf(concat," %s",split[i]);
        strcat(arg,concat);
    }
    // printf("%s\n",arg);
    system(arg);
    return NULL;

}

void* sys3(){
    char arg[100];
    char concat[100];
    strcpy(arg,commandPath);
    strcat(arg,"/./cat");
    
    for(int i=1;i<count-1;i++){
        sprintf(concat," %s",split[i]);
        strcat(arg,concat);
    }
    // printf("%s\n",arg);
    system(arg);
    return NULL;

}

void* sys4(){
    char arg[100];
    char concat[100];
    strcpy(arg,commandPath);
    strcat(arg,"/./ls");
    
    for(int i=1;i<count-1;i++){
        sprintf(concat," %s",split[i]);
        strcat(arg,concat);
    }
    // printf("%s\n",arg);
    system(arg);
    return NULL;

}

void* sys5(){
    char arg[100];
    char concat[100];
    strcpy(arg,commandPath);
    strcat(arg,"/./date");
    
    for(int i=1;i<count-1;i++){
        sprintf(concat," %s",split[i]);
        strcat(arg,concat);
    }
    // printf("%s\n",arg);
    system(arg);
    return NULL;

}

int main() {
    clear();
    char userinput[200];
    getcwd(commandPath, sizeof(commandPath));  // PATH OF CURRENT WORKING DIRECTORY
    char *username = getlogin(); // Get username
    // printf("%sabcdshell",username);
    if (username == NULL)
        return EXIT_FAILURE;

    int a=1;

    while(a){
        char address[200];
        int flag=0;      // Flag for detemine if pthread is used or  not
        getcwd(address, sizeof(address));
        printf("%s@MyShell:~$",username);
        gets(userinput);         // Taking user input
        if(strlen(userinput)==0) continue;
        if(strcmp(userinput,"exit")==0){
            a=0;
            return 0;
        }
        if(strcmp(userinput,"clear")==0){
            clear();
            continue;
        }
        char cpy[200];
        strcpy(cpy,userinput);

        parsed(cpy);

        char *command= strtok(userinput, " ");


        if(strcmp(split[count-1],"&t")==0) flag=1;

       
        if (strcmp(command, "pwd") == 0){  
                char array[2000][2000];
                int idx=0;
                // strcpy(array[idx++],command);
                while(command != NULL){
                    strcpy(array[idx++],command);
                    command = strtok(NULL," ");
                }
                
                if(strcmp(array[1],"-n")==0){
                    for (int i = 2; i < idx; i++){
                        printf("%s ", array[i]);
                    }
                }
                if(idx>2){
                        printf("MyShell: command not found\n");
                    }
                else if(idx==2){
                    if(strcmp(array[1],"-P")!=0 && strcmp(array[1],"-L")!=0){
                        printf("MyShell: command not found\n");
                    }
                    else{
                        char currentaddress[100];
                        puts(getcwd(currentaddress, sizeof(currentaddress)));
                        
                    }
                }
                else{
                    char currentaddress[100];
                    puts(getcwd(currentaddress, sizeof(currentaddress)));
                    }
        }

       
        else if (strcmp(command, "echo") == 0){  
            
                char array[2000][2000];
                int idx=0;
                // strcpy(array[idx++],command);
                while(command != NULL){
                    strcpy(array[idx++],command);
                    command = strtok(NULL," ");
                }
                
                if(strcmp(array[1],"-n")==0){
                    for (int i = 2; i < idx; i++){
                        printf("%s ", array[i]);
                    }
                }

                else if(strcmp(array[1],"--help")==0){
                    if(idx>2){
                        printf("MyShell: command not found\n");
                        continue;
                    }
                    
                    printf("Echo the STRING(s) to standard output.\n-n do not output the trailing newline\n--help display this help and exit\n");

                }

                else{
                    for(int i=1;i<idx;i++){
                        printf("%s ",array[i]);
                    }
                    printf("\n");
                }
                continue;

        }

        else if (strcmp(command, "cd") == 0){  
                char array[100][100];
                int idx=0;
                int r=0;
                // strcpy(array[idx++],command);
                while(command != NULL){
                    strcpy(array[idx++],command);
                    command = strtok(NULL," ");
                }
                if(strcmp(array[1],".")==0){
                    printf("MyShell: command not found\n");

                }
                else if(strcmp(array[1],"..")==0){
                    if(idx>2){
                        printf("MyShell: command not found\n");
                        continue;
                    }
                    
                    chdir("..");
                }

                else if(strcmp(array[1],"/")==0){
                    if(idx>2){
                        printf("MyShell: command not found\n");
                        continue;
                    }
                
                    chdir("/");
                }

                else{
                    char pwd[100];
                    getcwd(pwd,100);
                    strcat(pwd,"/");
                    strcat(pwd,array[1]);
                    r=chdir(pwd);
                }

                if(r==-1){
                    printf("-bash: cd: %s: No such file or directory\n",array[1]);
                }
                
                continue;


        }



        else if(strcmp(command,"mkdir")==0){
            if(flag){
                
                pthread_t thread;
                pthread_create(&thread,NULL,&sys1,NULL);
                // printf("hgjkl\n");
                pthread_join(thread,NULL);

                continue;
            }


            char *argv[20];
            char arg1[200];
            strcpy(arg1, commandPath);
            strcat(arg1, "/mkdir");
            int idx=0;
            for (int i = 0; i < 10; i++)
                argv[i] = (char *)malloc(100 * sizeof(char));
            
            strcpy(argv[idx++], arg1);
            while(command != NULL){

                if (strcmp(command, "mkdir") == 0){
                    command = strtok(NULL, " ");
                    continue;
                }
                    strcpy(argv[idx++],command);
                    command = strtok(NULL," ");
                }


            argv[idx++] = NULL;

            pid = fork();
            if(pid==-1){
                printf("Process failed\n");
            }
            if (pid == 0)
            {
                execv(argv[0], argv);
                
            }
            
            else
            {
                wait(NULL);
                
            }


        }



        else if(strcmp(command,"rm")==0){

            if(flag){
                
                pthread_t thread;
                pthread_create(&thread,NULL,&sys2,NULL);
                // printf("hgjkl\n");
                pthread_join(thread,NULL);

                continue;
            }

            char *argv[20];
            int idx=0;
            char arg1[200];
            strcpy(arg1, commandPath);
            strcat(arg1, "/rm");
            for (int i = 0; i < 10; i++)
                argv[i] = (char *)malloc(100 * sizeof(char));
            
            strcpy(argv[idx++], arg1);
            while(command != NULL){

                if (strcmp(command, "rm") == 0){
                    command = strtok(NULL, " ");
                    continue;
                }
                    strcpy(argv[idx++],command);
                    command = strtok(NULL," ");
                }


            argv[idx++] = NULL;

            pid = fork();
            if(pid==-1){
                printf("Process failed\n");
            }
            if (pid == 0)
            {
                execv(argv[0], argv);
                
            }
            
            else
            {
                wait(NULL);
                
            }


        }



        else if(strcmp(command,"cat")==0){
            
            if(flag){
                
                pthread_t thread;
                pthread_create(&thread,NULL,&sys3,NULL);
                // printf("hgjkl\n");
                pthread_join(thread,NULL);

                continue;
            }

            char *argv[20];
            int idx=0;
            char arg1[200];
            strcpy(arg1, commandPath);
            strcat(arg1, "/cat");
            for (int i = 0; i < 10; i++)
                argv[i] = (char *)malloc(100 * sizeof(char));
            
            strcpy(argv[idx++], arg1);
            while(command != NULL){

                if (strcmp(command, "cat") == 0){
                    command = strtok(NULL, " ");
                    continue;
                }
                    strcpy(argv[idx++],command);
                    command = strtok(NULL," ");
                }


            argv[idx++] = NULL;

            pid = fork();
            if(pid==-1){
                printf("Process failed");
            }
            if (pid == 0)
            {
                execv(argv[0], argv);
                
            }
            
            else
            {
                wait(NULL);
                
            }
        }


        


        else if(strcmp(command,"ls")==0){
            if(flag){
                
                pthread_t thread;
                pthread_create(&thread,NULL,&sys4,NULL);
                // printf("hgjkl\n");
                pthread_join(thread,NULL);

                continue;
            }

            char *argv[20];
            int idx=0;
            char arg1[200];
            strcpy(arg1, commandPath);
            strcat(arg1, "/ls");
            for (int i = 0; i < 10; i++)
                argv[i] = (char *)malloc(100 * sizeof(char));
            
            strcpy(argv[idx++], arg1);
            while(command != NULL){

                if (strcmp(command, "ls") == 0){
                    command = strtok(NULL, " ");
                    continue;
                }
                    strcpy(argv[idx++],command);
                    command = strtok(NULL," ");
                }


            argv[idx++] = NULL;

            pid = fork();
            if(pid==-1){
                printf("Process failed");
            }
            if (pid == 0)
            {
                execv(argv[0], argv);
                
            }
            
            else
            {
                wait(NULL);
                
            }


        }



        else if(strcmp(command,"date")==0){
            if(flag){
                
                pthread_t thread;
                pthread_create(&thread,NULL,&sys5,NULL);
                // printf("hgjkl\n");
                pthread_join(thread,NULL);

                continue;
            }

            char *argv[20];
            int idx=0;
            char arg1[200];
            strcpy(arg1, commandPath);
            strcat(arg1, "/date");
            for (int i = 0; i < 10; i++)
                argv[i] = (char *)malloc(100 * sizeof(char));
            
            strcpy(argv[idx++], arg1);
            while(command != NULL){

                if (strcmp(command, "date") == 0){
                    command = strtok(NULL, " ");
                    continue;
                }
                    strcpy(argv[idx++],command);
                    command = strtok(NULL," ");
                }


            argv[idx++] = NULL;

            pid = fork();
            if(pid==-1){
                printf("Process failed");
            }
            if (pid == 0)
            {
                execv(argv[0], argv);
                
            }
            
            else
            {
                wait(NULL);
                
            }


        }



    else{
        printf("MyShell: command not found\n");
    }




        
    }
    

    



    return 0;
}