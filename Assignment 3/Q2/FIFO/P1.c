#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

char *generate_random_string(char *str, size_t size){
    char alpha_select[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int n = 0; n < size; n++){
        int index = rand() % (int)(sizeof alpha_select - 1);
        str[n] = alpha_select[index];
    }
    str[size] = '\0';
    return str;
}

struct data
{
    char random_5_strings[5][4];
    int id[5];
};


int main(){
    char gen_rand_str[50][4];
    int max_id;
    srand(time(NULL));
    for (int i = 0; i < 50; i++){
        char s[4];
        char *temp = generate_random_string(s, 3);
        for (int j = 0; j < 4; j++){
            gen_rand_str[i][j] = temp[j];
        }
    }
    printf("Sucessfully Generated random strings");

    if (mkfifo("virtual_file", 0666) == -1){
        if (errno != EEXIST){
            printf("Unable to create fifo file\n");
        }
    }

    char arr[5][4];

    for (int i = 0; i < 50; i = i + 5)
    {
        memcpy(arr, gen_rand_str + i, sizeof(arr));
        int array[5] = {i, i + 1, i + 2, i + 3, i + 4};
        struct data val;
        memcpy(val.random_5_strings, arr, sizeof(arr));
        memcpy(val.id, array, sizeof(array));
        printf("Going to P2 for reading\n");
        int outputfile1 = open("virtual_file", O_WRONLY);
        if (outputfile1 == -1)
        {
            return 1;
        }
        if (write(outputfile1, &val, sizeof(struct data)) == -1)
        {
            printf("Error while writing to P2\n");
            return 1;
        }
        printf("Contents to file written successfully !\n");
        close(outputfile1);
        sleep(1);

        int inputfile1 = open("virtual_file", O_RDONLY);
        if (inputfile1 == -1)
        {
            return 1;
        }

        if (read(inputfile1, &max_id, sizeof(int)) == -1)
        {
            printf("P1 is unable to read from P2\n");
            return 2;
        }
        close(inputfile1);

        printf("The maximum id is %d",max_id);

        if (max_id == (i + 4))
        {
            printf("\nP1 has received correct acknowledgement from P2\n");
        }
        else
        {
            printf("\nP1 has received wrong acknowledgement from P2\n");
            return 1;
        }
    }

}