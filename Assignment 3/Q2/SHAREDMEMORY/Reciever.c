#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define SHM_SIZE 50   // size of shared memory in bytes

int main() {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  // create a key for the shared memory
  key_t key = ftok("shmfile", 65);

  // get the shared memory
  int shmid = shmget(key, SHM_SIZE, 0666);

  // attach the shared memory to the receiver's address space
  char* str = (char*) shmat(shmid, NULL, 0);

  printf("Waiting for P1 to send data\n");
  printf("Data received from P1:\n");
  // print the strings
  for (int i = 0; i < 50; i++) {
      if (i%5==0){
          printf("Data received from P1:\n");
          printf("Maximum id recieved : %d\n",i+5);
          printf("Sending Acknowledgement to P1\n");
          sleep(1);
      }
      for (int j =0; j<3;j++){
        printf("%c",str[i*3+j]);
      }
      printf("\n");

      
  }
  printf("Sending Acknowledgement to P1\n");
  printf("Got all data from P1\n");
  clock_gettime(CLOCK_MONOTONIC, &end);
  double time_taken;
  double nano_timetaken;
  time_taken = (end.tv_sec - start.tv_sec) * 1e9;
  time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
  nano_timetaken = end.tv_nsec - start.tv_nsec;
  printf("Time Taken by p2 is %f nonoseconds without sleep \n", nano_timetaken );
  printf("Time taken by P2 is %f seconds \n", time_taken);


  // detach the shared memory
  shmdt(str);

  // remove the shared memory
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}