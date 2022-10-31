#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]){
    char month[12][20] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    char week[7][20]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    int flagforu = 0; // for -u version of date
    int flagforR= 0; //for -R version of date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-u") == 0)
        {
            flagforu = 1;
        }
        if (strcmp(argv[i], "-R") == 0)
        {
            flagforR = 1;
        }
    }

    if (flagforu == 1 && flagforR == 1)
    {
        printf("MyShell: command not found\n");
        return 0;
    }



    else if (flagforu == 0 && flagforR == 0)
    {
        if(argc!=1){
            printf("MyShell: command not found\n");
            return 0;
        }

        printf("%s %s %d %02d:%02d:%02d IST %d\n",week[tm->tm_wday], month[tm->tm_mon],tm->tm_mday, tm->tm_hour,tm->tm_min, tm->tm_sec,1900+tm->tm_year);
        
        }
    

    
    else if (flagforu== 1)
    {
        if(argc!=2){
            printf("MyShell: command not found\n");
            return 0;
        }
        struct tm *gmt=gmtime(&t);

        printf("%s %s %d %02d:%02d:%02d UTC %d\n",week[gmt->tm_wday], month[gmt->tm_mon],gmt->tm_mday, gmt->tm_hour,gmt->tm_min, gmt->tm_sec,1900+gmt->tm_year);
        
    }
        
    

    else if(flagforR==1){
        if(argc!=2){
            printf("MyShell: command not found\n");
            return 0;
        }
        printf("%s, %d %s %d %02d:%02d:%02d +0530\n",week[tm->tm_wday],tm->tm_mday,month[tm->tm_mon] ,1900+tm->tm_year, tm->tm_hour,tm->tm_min, tm->tm_sec);

    return 0;
}

}