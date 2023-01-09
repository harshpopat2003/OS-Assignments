#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

struct data_2
{
    char rondom_5_strings[5][4];
    int id_2[5];
};

int main()
{

    struct data_2 val_2;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 50; i = i + 5)
    {
        int inputfile2 = open("virtual_file", O_RDONLY);
        if (inputfile2 == -1)
        {
            return 1;
        }
        if (read(inputfile2, &val_2, sizeof(struct data_2)) == -1)
        {
            printf("Error in reading contents in P2\n");
            return 1;
        }
        printf("Successfully read the file in P2\n");
        close(inputfile2);

        for (int h = 0; h < 5; h++)
        {
            for (int j = 0; j < 4; j++)
            {
                printf("%c", val_2.rondom_5_strings[h][j]);
            }
            printf(": %d", val_2.id_2[h]);
            printf("\n");
        }

        int outputfile2 = open("virtual_file", O_WRONLY);
        if (outputfile2 == -1)
        {
            return 1;
        }

        if (write(outputfile2, &val_2.id_2[4], sizeof(int)) == -1)
        {
            printf("Error while Sending acknowledging to P1\n");
            return 1;
        }
        printf("Acknowledgment sent to P1\n");
        close(outputfile2);
    }
  clock_gettime(CLOCK_MONOTONIC, &end);
  double time_taken;
  double nano_timetaken;
  time_taken = (end.tv_sec - start.tv_sec) * 1e9;
  time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
  nano_timetaken = end.tv_nsec - start.tv_nsec;
  printf("Time Taken by p2 is %f nonoseconds without sleep \n", nano_timetaken );
  printf("Time taken by P2 is %f seconds \n", time_taken);

    return 0;
}