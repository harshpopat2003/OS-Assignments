#include <stdio.h>
#include <time.h>
#include <string.h>
//#include <sysexits.h>
#include <errno.h>

void printDate(){
    time_t gentime = time(NULL);
    if (gentime == -1){ // error handleing for time function
        // puts("The time() function failed");
        // return 1;
        perror("Error is");
        return;
    }
    struct tm *presenttime;
    char day[4], mont[4], tzone[6] , alldata[20];
    presenttime = localtime(&gentime);
    // if (presenttime == NULL){
    //     perror("Error is");
    //     return;
    // }
    //strftime(alldata, 20, "%c", presenttime); // %c is the format for the date and time  (Thu Mar  3 23:05:25 2005)
    strftime(day, sizeof(day), "%a", presenttime); // %a is for day of week
    strftime(mont, sizeof(mont), "%b", presenttime); // %b is for month
    strftime(tzone, sizeof(tzone), "%z", presenttime); // %z is for timezone
    // format like Tue Oct  4 22:48:58 IST 2022
    // check to get the time zone as written in IST 
    printf("%s %s %02d %02d:%02d:%02d IST %d\n", day, mont, presenttime->tm_mday, presenttime->tm_hour, presenttime->tm_min, presenttime->tm_sec, presenttime->tm_year + 1900);
    //printf("%02d\n",alldata);
}

void printdateformatu(){
    time_t gentime = time(NULL);
    if (gentime == -1){
        // puts("The time() function failed");
        // return 1;
        perror("Error is");
        return;
    }
    struct tm *presenttime;
    char day[4], mont[4], tzone[6];
    presenttime = gmtime(&gentime); // difference is just here gmtime() is used instead of localtime()
    // if (presenttime == NULL){
    //     perror("Error is");
    //     return;
    // }
    strftime(day, 4, "%a", presenttime); // %a is for day of week
    strftime(mont, 4, "%b", presenttime); // %b is for month
    strftime(tzone, 6, "%z", presenttime); // %z is for timezone
    printf("%s %s %02d %02d:%02d:%02d UTC %d\n", day, mont, presenttime->tm_mday, presenttime->tm_hour, presenttime->tm_min, presenttime->tm_sec, presenttime->tm_year + 1900);

}

void printdateformatR(){
    time_t gentime = time(NULL);
    if (gentime == -1){
        // puts("The time() function failed");
        // return 1;
        perror("Error is");
        return;
    }
    struct tm *presenttime;
    char day[4], mont[4], tzone[6];
    presenttime = localtime(&gentime); // difference is just here gmtime() is used instead of localtime()
    // if (presenttime == NULL){
    //     perror("Error is");
    //     return;
    // }
    strftime(day, 4, "%a", presenttime); // %a is for day of week
    strftime(mont, 4, "%b", presenttime); // %b is for month
    strftime(tzone, 6, "%z", presenttime); // %z is for timezone
    //printf(tzone);
    printf("%s, %d %s %d %02d:%02d:%02d ", day,presenttime->tm_mday, mont, presenttime->tm_year + 1900,  presenttime->tm_hour, presenttime->tm_min, presenttime->tm_sec);
    printf(tzone);
    printf("\n");
}

int main(int argc, char *argv[])
{
    char cmdName[10] = "";
    char f[10] = "";
    char *t = strtok(argv[1], " ");
    strcpy(cmdName, t);
    t = strtok(NULL, " ");
    if (t != NULL)
    {
        strcpy(f, t);    
    }
    if (strcmp(f, "") == 0)
    {
        printDate();
    }
    else if (f[1] == 'u')
    {
        printdateformatu();;
    }
    else if (f[1] == 'R')
    {
        printdateformatR();
    }
    else
    {
        printf("Invalid Input -- %s\n", f);
        return 1;
    }
    return 0;
}
