#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define NUM_OF_PHILOSOPHERS 5

sem_t forks[NUM_OF_PHILOSOPHERS];
sem_t sauce_bowls[2];

void *philosopher(void *id) {
  int phil_id = *(int*)id;

  while (1) {
    printf("Philosopher %d is now thinking\n", phil_id);
    sleep(1);

    //One of the sauce bowls
    sem_wait(&sauce_bowls[phil_id % 2]);
    printf("Philosopher %d got sauce bowl\n", phil_id);

    //Semaphores for the forks
    sem_wait(&forks[phil_id]);
    printf("Philosopher %d got left fork\n", phil_id);
    sem_wait(&forks[(phil_id + 1) % NUM_OF_PHILOSOPHERS]);
    printf("Philosopher %d got right fork\n", phil_id);

    printf("Philosopher %d is now eating\n", phil_id);
    sleep(1);

    //Remove the forks from philospher eating 
    sem_post(&forks[phil_id]);
    printf("Philosopher %d released left fork\n", phil_id);
    sem_post(&forks[(phil_id + 1) % NUM_OF_PHILOSOPHERS]);
    printf("Philosopher %d released right fork\n", phil_id);

    // Remove the sauce bowls from philospher eating
    sem_post(&sauce_bowls[phil_id % 2]);
    printf("Philosopher %d released sauce bowl\n", phil_id);
  }

  return NULL;
}

int main() {
  int i;
  pthread_t philosophers[NUM_OF_PHILOSOPHERS];
  int philosopher_ids[NUM_OF_PHILOSOPHERS];

  //Semaphores
  for (i = 0; i < NUM_OF_PHILOSOPHERS; i++) {
    sem_init(&forks[i], 0, 1);
  }
  sem_init(&sauce_bowls[0], 0, 1);
  sem_init(&sauce_bowls[1], 0, 1);

  // Create threads
  for (i = 0; i < NUM_OF_PHILOSOPHERS; i++) {
    philosopher_ids[i] = i;
    pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
  }
  // Join threads
  for (i = 0; i < NUM_OF_PHILOSOPHERS; i++) {
    pthread_join(philosophers[i], NULL);
  }

  return 0;
}
