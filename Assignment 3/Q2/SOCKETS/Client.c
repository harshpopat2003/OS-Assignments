#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/unistd.h>

#define SOCK_PATH "echo_socket"


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

struct data
{
    char five_random_strings[5][4];
    int id[5];
};

int main(void)
{
    srand(time(NULL));
    int s, t, len;
    struct sockaddr_un remote;

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

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
    }

    printf("Trying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);

    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("Connect");
        exit(1);
    }

    printf("Connected.\n");
    char arr[5][4];
        for (int i = 0; i < 50; i = i + 5){
            memcpy(arr, random_strings + i, sizeof(arr));
            int array[5] = {i, i + 1, i + 2, i + 3, i + 4};
            struct data val;
            memcpy(val.five_random_strings, arr, sizeof(arr));
            memcpy(val.id, array, sizeof(array));
            printf("Going to server for reading\n");
            if (send(s, &val, sizeof(struct data), 0) == -1) {
                perror("send");
                exit(1);
            }
            printf("contents to server sent successfully !\n");
            if ((t=recv(s,  &max_id, sizeof(int), 0)) > 0) {
                printf("client has received the acknowledgment from server\n");
                printf("The maximum id is %d",max_id);
                if (max_id == (i + 4)){
                    printf("\nclient has received correct acknowledgement from server\n");
                    sleep(1);
                }
                else{
                    printf("\nclient has received wrong acknowledgement from server\n");
                    exit(1);
                }
            } 
            else {
                if (t < 0){
                    perror("recv");
                }
                else {
                    printf("Server closed connection\n");
                }
                exit(1);
            }
        }
    close(s);
    return 0;
}