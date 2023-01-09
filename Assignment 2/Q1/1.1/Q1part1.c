#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void countsA(){
    for (long i = 1; i < 4294967296; i++) {
        }
    }
void countsB(){
    for (long i = 1; i < 4294967296; i++) {
        }
    }
void countsC(){
    for (long i = 1; i < 4294967296; i++) {
        }
    }

//create threads and calculate the time taken to evecute each function

void *countA(void *arg){
    printf("Starting Thread A\n");
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    countsA();
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time taken to execute countA: %f\n", time_spent);
    }
void *countB(void *arg){
    printf("Starting Thread B\n");
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    countsB();
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time taken to execute countB: %f\n", time_spent);
    }
void *countC(void *arg){
    printf("Starting Thread C\n");
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    countsC();
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time taken to execute countC: %f\n", time_spent);
    }

// void *countA(void *arg){
//     printf("Starting Thread A\n");
//     clock_t start = clock();
//     countsA();
//     clock_t end = clock();
//     double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
//     printf("Time taken to execute countA: %f\n", time_spent);
//     return NULL;
//     }
// void *countB(void *arg){
//     printf("Starting Thread B\n");
//     clock_t start = clock();
//     countsB();
//     clock_t end = clock();
//     double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
//     printf("Time taken to execute countB: %f\n", time_spent);
//     return NULL;
//     }
// void *countC(void *arg){
//     printf("Starting Thread C\n");
//     clock_t start = clock();
//     countsC();
//     clock_t end = clock();
//     double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
//     printf("Time taken to execute countC: %f\n", time_spent);
//     return NULL;
//     }

int main(int argc, char *argv[]){
    pthread_t threadA, threadB, threadC;
    int policy;
    int priority;
    int ret;
    pthread_attr_t attrA;
    pthread_attr_t attrB;
    pthread_attr_t attrC;
    struct sched_param param;
    
    //set the policies and priorities of each thread
    param.sched_priority = 0;
    pthread_attr_init(&attrA);
    pthread_attr_setinheritsched(&attrA, PTHREAD_EXPLICIT_SCHED);
    ret = pthread_attr_setschedpolicy(&attrA, SCHED_OTHER);
    if (ret != 0) {
        perror("pthread_attr_setschedpolicy");
        exit(EXIT_FAILURE);
        }
    ret = pthread_attr_setschedparam(&attrA, &param);
    if (ret != 0) {
        perror("pthread_attr_setschedparam");
        exit(EXIT_FAILURE);
        }
    
    
    param.sched_priority = 2;
    pthread_attr_init(&attrB);
    pthread_attr_setinheritsched(&attrB,PTHREAD_EXPLICIT_SCHED);
    ret = pthread_attr_setschedpolicy(&attrB, SCHED_RR);
    if (ret != 0) {
        perror("pthread_attr_setschedpolicy");
        exit(EXIT_FAILURE);
        }
    ret = pthread_attr_setschedparam(&attrB, &param);
    if (ret != 0) {
        perror("pthread_attr_setschedparam");
        exit(EXIT_FAILURE);
        }

    
    
    param.sched_priority = 3;
    pthread_attr_init(&attrC);
    pthread_attr_setinheritsched(&attrC, PTHREAD_EXPLICIT_SCHED);
    ret = pthread_attr_setschedpolicy(&attrC, SCHED_FIFO);
    if (ret != 0) {
        perror("pthread_attr_setschedpolicy");
        exit(EXIT_FAILURE);
        }
    ret = pthread_attr_setschedparam(&attrC, &param);
    if (ret != 0) {
        perror("pthread_attr_setschedparam");
        exit(EXIT_FAILURE);
        }


    //create threads
    ret = pthread_create(&threadA, &attrA, countA, NULL);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
        }
    ret = pthread_create(&threadB, NULL, countB, NULL);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
        }
    ret = pthread_create(&threadC, NULL, countC, NULL);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
        }
    //wait for threads to finish
    ret = pthread_join(threadA, NULL);
    if (ret != 0) {
        perror("pthread_join");
        exit(EXIT_FAILURE);
        }
    ret = pthread_join(threadB, NULL);
    if (ret != 0) {
        perror("pthread_join");
        exit(EXIT_FAILURE);
        }
    ret = pthread_join(threadC, NULL);
    if (ret != 0) {
        perror("pthread_join");
        exit(EXIT_FAILURE);
        }
    return 0;
    }
