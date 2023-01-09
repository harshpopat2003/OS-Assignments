#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_OF_PHILOSOPHER 5
#define NUM_OF_FORKS 5

pthread_mutex_t forks[NUM_OF_FORKS];

void philosopher(void *num) {
long phil_num = (long)num ;
long fork_1 = phil_num;
long fork_2 = (phil_num + 1) % NUM_OF_PHILOSOPHER;

while (1) {
  printf("Philosopher %ld is thinking\n", phil_num);
  sleep(1);

  // Strict Ordering to Avoid Deadlock
  if (fork_1 < fork_2) {
    pthread_mutex_lock(&forks[fork_1]);
    pthread_mutex_lock(&forks[fork_2]);
  } else {
    pthread_mutex_lock(&forks[fork_2]);
    pthread_mutex_lock(&forks[fork_1]);
  }

  printf("Philosopher %ld is eating\n", phil_num);
  sleep(2);

    pthread_mutex_unlock(&forks[fork_1]);
    pthread_mutex_unlock(&forks[fork_2]);
  }
}
int main(int argc, char argv[]) {
pthread_t phil[NUM_OF_PHILOSOPHER];

for (int i = 0; i < NUM_OF_FORKS; i++) {
  pthread_mutex_init(&forks[i], NULL);
}

// Create threads for each philosopher
for (long i = 0; i < NUM_OF_PHILOSOPHER; i++) {
  pthread_create(&phil[i], NULL, philosopher,(void*)i);
}

// Joining the Threads 
for (int i = 0; i < NUM_OF_PHILOSOPHER; i++) {
  pthread_join(phil[i], NULL);
}

return 0;
}
