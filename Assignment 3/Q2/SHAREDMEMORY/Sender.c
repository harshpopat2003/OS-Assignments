#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define SHM_SIZE 50   // size of shared memory in bytes

char *rand_string(char *str, size_t size)
{
    const char str_set[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t n = 0; n < size; n++)
    {
        int key = rand() % (int)(sizeof str_set - 1);
        str[n] = str_set[key];
    }
    str[size] = '\0';
    return str;
}

int main() {

  char random_strings[50][4];
    int max_id;
    for (int i = 0; i < 50; i++)
    {
        char si[4];
        char *temp = rand_string(si, 3);
        for (int j = 0; j < 4; j++)
        {
            random_strings[i][j] = temp[j];
        }
    }
    printf("Generated random strings\n");
    printf("Waiting for the reciever to connect...\n");
    // //print the random strings
    // for (int i = 0; i < 50; i++)
    // {
    //     printf("%s\n", random_strings[i]);
    // }


  // creating a key for the shared memory
  key_t key = ftok("shmfile", 65);

  // creating the shared memory
  int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);

  // attaching the shared memory to going to address space
  char* str = (char*) shmat(shmid, NULL, 0);

  //random strings and store them in the shared memory
  srand(time(0));
  for (int i = 0; i < 50; i++) {
    for (int j =0; j<3;j++){
        str[i*3+j]=random_strings[i][j];
    }
    str[i*3+3]='\0';
  }

    for (int i = 0; i < 50; i=i+5)
    {
      printf("Sending data to P2\n");
        for (int j = 0; j < 5; j++)
        {
            printf("%s ", random_strings[i+j]);
        }
        printf("\n");
        sleep(1);
        printf("Recieved Acknowlwdge from P2\n");
        printf("Maximum ID recieved from P2: %d\n",i+5);
    }
    
//printf("Data written in memory: %s", str);
  // detach the shared memory
  shmdt(str);

  return 0;
}