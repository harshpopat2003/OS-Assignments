#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_OF_PHILOSOPHER 5
#define NUM_OF_FORKS 5

sem_t forks[NUM_OF_FORKS];

void *philosopher(void *num) {
long phil_num = (long)num;
long fork_1 = phil_num;
long fork_2 = (phil_num + 1) % NUM_OF_PHILOSOPHER;

while (1) {
printf("Philosopher %ld is thinking\n", phil_num);
//sleep(1);

//using semaphores
sem_wait(&forks[fork_1]);
sem_wait(&forks[fork_2]);

printf("Philosopher %ld is eating\n", phil_num);
sleep(1);

sem_post(&forks[fork_1]);
sem_post(&forks[fork_2]);

}
}
int main(int argc, char *argv[]) {
pthread_t phil[NUM_OF_PHILOSOPHER];

for (int i = 0; i < NUM_OF_FORKS; i++) {
sem_init(&forks[i], 0, 1);
}

// Creating threads 
for (long i = 0; i < NUM_OF_PHILOSOPHER; i++) {
pthread_create(&phil[i], NULL, philosopher, (void *)i);
}

// Joining threads
for (int i = 0; i < NUM_OF_PHILOSOPHER; i++) {
pthread_join(phil[i], NULL);
}

return 0;
}