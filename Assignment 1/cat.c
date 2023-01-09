#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

//extern int errno;

void pfile(char *fileName){
    int file = open(fileName, O_RDONLY);
    char ch;
    int sz;
    while ((sz = read(file, &ch, 1))){
        if (sz < 0){
            perror("read");
            return;
        }
        size_t w = write(STDIN_FILENO, &ch, 1);
        if (w < 0){
            if (errno != EINTR){
                perror("write");
                return;
            }
        }
    }
}

void printthefile(char fileName[1000]){
    int file = open(fileName, O_RDONLY);
    if (file ==-1){
        perror("File Not Present Error");
        return;
    }
    pfile(fileName);
    // char ch;
    // int sz;
    // while ((sz = read(file, &ch, 1))){
    //     if (sz < 0){
    //         perror("read");
    //         return;
    //     }
    //     size_t w = write(STDIN_FILENO, &ch, 1);
    //     if (w < 0){
    //         if (errno != EINTR){
    //             perror("write");
    //             return;
    //         }
    //     }
    // }
    if (close(file) < 0){
        perror("close");
        return;
    }
    return;
}

// void printthefileE(char fileName[1000]){
//     {
//     int file = open(fileName, O_RDONLY);
//     if (file == -1)
//     {
//         perror("File Not Present Error");
//         return;
//     }
//     char ch;
//     int sz;
//     while ((sz = read(file, &ch, 1)))
//     {
//         if (sz < 0)
//         {
//             perror("read");
//             return;
//         }
//         if (ch == '\n')
//         {
//             char c = '$';
//             size_t w = write(STDIN_FILENO, &c, 1);
//             if (w < 0)
//             {
//                 if (errno != EINTR)
//                 {
//                     perror("write");
//                     return;
//                 }
//             }
//         }
//         write(STDIN_FILENO, &ch, 1);
//     }
//     if (close(file) < 0)
//     {
//         perror("close");
//         return;
//     }
//     return;
//     }
// }

void printthefileE(char fileName[1000])
{
    int file = open(fileName, O_RDONLY);
    if (file == -1)
    {
        perror("The Inputed File Not Present Error");
        return;
    }
    char ch;
    int sz;
    while ((sz = read(file, &ch, 1)))
    {
        if (sz < 0)
        {
            perror("Reading the file Error");
            return;
        }
        if (ch == '\n')
        {
            char c = '$';
            size_t w = write(STDIN_FILENO, &c, 1);
            if (w < 0)
            {
                if (errno != EINTR)
                {
                    perror("Writing the file Error");
                    return;
                }
            }
        }
        write(STDIN_FILENO, &ch, 1);
    }
    if (close(file) < 0)
    {
        perror("Closing file Error");
        return;
    }
    return;
}

int main(int argc, char *argv[])
{
    char cmdName[10] = "";
    char f[10] = "";
    char fileName[1000] = "";
    char *t = strtok(argv[1], " ");
    strcpy(cmdName, t);
    t = strtok(NULL, " ");
    if (t[0] == '-')
    {
        strcpy(f, t);
        t = strtok(NULL, " ");
    }
    while (t != NULL)
    {
        strcpy(fileName, t);
        if (strcmp(f, "") == 0)
        {
            printthefile(fileName);
        }
        else if (f[1] == 'E')
        {
            printthefileE(fileName);
        }
        // else if (f[1] == 'T')
        // {
        //     printFileTab(fileName);
        // }
        else
        {
            printf("Not a Valid Input -- %s\n", f);
            printf("Please Enter a Valid Input\n");
            return 1;
        }
        t = strtok(NULL, " ");
    }
    return 0;
}