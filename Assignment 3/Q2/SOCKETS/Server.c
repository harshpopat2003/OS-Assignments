#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/unistd.h>

#define SOCK_PATH "echo_socket"

struct data_2{
    char five_random_strings_2[5][4];
    int id_2[5];
};

int main(void)
{
    struct data_2 val_2;
    int s, s2, t, len;
    struct sockaddr_un local, remote;

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("Bind");
        exit(1);
    }

    if (listen(s, 12) == -1) {
        perror("listen");
        exit(1);
    }
    int n;
    printf("Waiting for a connection...\n");
    t = sizeof(remote);
    if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
        perror("Accept");
        exit(1);
    }
    printf("Connected.\n");
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int i = 0; i < 50; i = i + 5){
        n = recv(s2, &val_2, sizeof(struct data_2), 0);
        if (n <= 0) {
            if (n < 0){
                perror("recv");
            }
        }
        for (int z = 0; z < 5; z++){
            for (int j = 0; j < 4; j++){
                printf("%c", val_2.five_random_strings_2[z][j]);
            }
            printf(": %d", val_2.id_2[z]);
            printf("\n");
        }
        if (send(s2, &val_2.id_2[4], sizeof(int), 0) < 0) {
            perror("send");
        }
        printf("Acknowledgment sent to client\n");
        sleep(1);
    }
    close(s2);
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