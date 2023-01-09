#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void makeDirectory(char fileName[1000])
{
    int chk;
    chk = mkdir(fileName, 0777);
    if (chk == -1)
    {
        perror(fileName);
    }
}

void makeDirectoryVerbose(char fileName[1000])
{
    int chk;
    chk = mkdir(fileName, 0777);
    if (chk == -1)
    {
        perror(fileName);
    }
    else
    {
        printf("mkdir: created directory '%s'\n", fileName);
    }
}

void makeDirectoryMode(char fileName[1000], int mode)
{
    int chk;
    chk = mkdir(fileName, mode);
    if (chk == -1)
    {
        perror(fileName);
    }
}

// int main(int argc, char *argv[]) 
// {
//     char cmdName[10] = "";
//     char f[10] = "";
//     char *t = strtok(argv[1], " ");
//     strcpy(cmdName, t);
//     t = strtok(NULL, " ");
//     if (t[0] == '-')
//     {
//         strcpy(f, t);
//         t = strtok(NULL, " ");
//     }
// }

int makedirchk(char *f,char *t){
    char fileName[1000] = "";
        strcpy(fileName, t);
        if (f[0] == '\0')
        {
            makeDirectory(fileName);
            return (2);
        }
        else
        {
            if (f[1] == 'v')
            {
                makeDirectoryVerbose(fileName);
                return (2);

            }
            else if (f[1] == 'm' && f[2] == '=')
            {
                if (strlen(f) < 6)
                {
                    printf("Invalid Input -- %s\n", f);
                    return 1;
                }
                if (strlen(f) == 7)
                {
                    char modeStr[5];
                    for (int i = 0; i < 4; i++)
                    {
                        modeStr[i] = f[i + 3];
                    }
                    int mode = atoi(modeStr);
                    if (mode != 400 && mode != 777 && mode != 100 && mode != 200)
                    {
                        printf("The mode '%d' entered is Invalid \n", mode);
                        return 1;
                    }
                    makeDirectoryMode(fileName, mode);
                    return (2);
                }
                else
                {
                    char modeStr[4];
                    for (int i = 0; i < 3; i++)
                    {
                        modeStr[i] = f[i + 3];
                    }
                    int mode = atoi(modeStr);
                    if (mode != 400 && mode != 777 && mode != 100 && mode != 200)
                    {
                        printf("The mode '%d' entered is invalid \n", mode);
                        return 1;
                    }
                    makeDirectoryMode(fileName, mode);
                    return (2);
                }
            }
            else
            {
                printf("Invalid Input -- %s\n", f);
                return 1;
            }
        }
        t = strtok(NULL, " ");
    }

int main(int argc, char *argv[])
{
    char cmdName[10] = "";
    char f[10] = "";
    char *t = strtok(argv[1], " ");
    strcpy(cmdName, t);
    t = strtok(NULL, " ");
    if (t[0] == '-')
    {
        strcpy(f, t);
        t = strtok(NULL, " ");
    }
    int zx;
    while (t != NULL)
    {
        zx=makedirchk(f,t);
        if(zx==2){
            break;
        }
    } 
    return 0;
}


