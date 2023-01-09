#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <stdint.h>
#include <sched.h>

int main(int argc, char* argv[]){
    int process1;
    int process2;
    int process3;
    double time_spent1;
    double time_spent2;
    double time_spent3;
    struct timespec start1, end1;
    process1 = fork();
    clock_gettime(CLOCK_MONOTONIC, &start1);
    if (process1 == 0){
        int f = getpid();
        struct sched_param param;
        param.sched_priority = 0;
        sched_setscheduler(f, SCHED_OTHER, &param);
        //printf("1->%d\n", sched_getscheduler(f)); 
        char *arg1[2];
        arg1[0] = "./bashsc1.sh";
        arg1[1] = NULL;
        execvp(arg1[0], arg1);    
    }
    else{
        process2 = fork();
        struct timespec start2, end2;
        clock_gettime(CLOCK_MONOTONIC, &start2);
        if (process2 == 0){
            int g = getpid();
            struct sched_param param2;
            param2.sched_priority = 1;
            sched_setscheduler(g, SCHED_RR, &param2);
            char *arg2[2];
            arg2[0] = "./bashsc2.sh";
            arg2[1] = NULL;
            execvp(arg2[0], arg2);
        }
        else{
            process3 = fork();
            struct timespec start3, end3;
            clock_gettime(CLOCK_MONOTONIC, &start3);
            if (process3 == 0){
                int h = getpid();
                struct sched_param param3;
                param3.sched_priority = 2;
                sched_setscheduler(h, SCHED_FIFO, &param3);
                char *arg3[2];
                arg3[0] = "./bashsc3.sh";
                arg3[1] = NULL;
                execvp(arg3[0], arg3);
            }
            else{
                pid_t wpid;
                int sts;
                for (int i = 0; i < 3; i++){
                    wpid = wait(&sts);
                    if ((int) wpid == (int) process1){
                        clock_gettime(CLOCK_MONOTONIC, &end1);
                        time_spent1 = (end1.tv_sec - start1.tv_sec) + (end1.tv_nsec - start1.tv_nsec) / 1000000000.0;
                        //printf("Time spent for process 1: %f", time_spent1);
                    }
                    else if ((int) wpid == (int) process2){
                        clock_gettime(CLOCK_MONOTONIC, &end2);
                        time_spent2 = (end2.tv_sec - start2.tv_sec) + (end2.tv_nsec - start2.tv_nsec) / 1000000000.0;
                        //printf("Time spent for process 2: %f", time_spent2);
                    }
                    else if ((int) wpid == (int) process3){
                        clock_gettime(CLOCK_MONOTONIC, &end3);
                        time_spent3 = (end3.tv_sec - start3.tv_sec) + (end3.tv_nsec - start3.tv_nsec) / 1000000000.0;
                        //printf("Time spent for process 3: %f", time_spent3);
                    }
                }
                printf("Time spent for process 1: %f\n", time_spent1);
                printf("Time spent for process 2: %f\n", time_spent2);
                printf("Time spent for process 3: %f\n", time_spent3);

                // wait(NULL);
                // clock_gettime(CLOCK_MONOTONIC, &end3);
                // time_spent3 = (end3.tv_sec - start3.tv_sec) + (end3.tv_nsec - start3.tv_nsec) / 1000000000.0;
                // printf("Time spent by process 3: %f", time_spent3);
                // wait(NULL);
                // clock_gettime(CLOCK_MONOTONIC, &end2);
                // time_spent2 = (end2.tv_sec - start2.tv_sec) + (end2.tv_nsec - start2.tv_nsec) / 1000000000.0;
                // printf("Time spent by process 2: %f", time_spent2);
                // wait(NULL);
                // clock_gettime(CLOCK_MONOTONIC, &end1);
                // time_spent1 = (end1.tv_sec - start1.tv_sec) + (end1.tv_nsec - start1.tv_nsec) / 1000000000.0;
                // printf("Time spent by process 1: %f", time_spent1);
            }
        }
    }

    return 0;
}