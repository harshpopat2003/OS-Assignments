#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void removeFile(char fileName[1000])
{
    char cmd[32] = { 0 };
    int ret = 0;
    sprintf(cmd, "rm %s", fileName);
    ret = system(cmd);
    if (ret != 0){
        perror(fileName);
    }
    //  if (remove(filename)=! 0)
    // {
    //     perror(fileName);
    // }
    // owners implenetation
    // if (unlink(fileName) != 0)
    // {
    //     perror(fileName);
    // }
}

void removeFileD(char fileName[1000])
{
    char cmd[32] = { 0 };
    int ret = 0;
    sprintf(cmd, "rmdir %s", fileName);
    ret = system(cmd);
    if (ret != 0){
        perror(fileName);
    }
    //  implenetation firsttime
    // if (rmdir(fileName) != 0)
    // {
    //     perror(fileName);
    // }
}

void removeFileV(char fileName[1000])
{
    if (unlink(fileName) == 0)
    {
        printf("rm: removing file, '%s'\n", fileName);
    }
    else
    {
        perror(fileName);
    }
}

int main(int argc, char *argv[])
{
    char command[10] = "";
    char f[10] = "";
    char *t = strtok(argv[1], " ");
    strcpy(command, t);
    t = strtok(NULL, " ");
    if (t[0] == '-')
    {
        strcpy(f, t);
        t = strtok(NULL, " ");
    }
    while (t != NULL)
    {
        char fileName[1000] = "";
        strcpy(fileName, t);
        if (f[0] == '\0')
        {
            removeFile(fileName);
        }
        else if (f[1] == 'd')
        {
            removeFileD(fileName);
        }
        else if (f[1] == 'v')
        {
            removeFileV(fileName);
        }
        else
        {
            printf("Invalid Input -- %s\n", f);
            return 1;
        }
        t = strtok(NULL, " ");
    }
    return 0;
}

