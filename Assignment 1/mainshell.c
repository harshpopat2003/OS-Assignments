#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>
#include <sys/wait.h>

char allcomands[100][100]={"cd","echo","pwd","exit","ls","cat","date","rm","mkdir"};
int nextln;

void cdP(char **input_array)
{
    char cwd_inputnew[1024];

    if (input_array[2] != NULL)
    {

        strcpy(cwd_inputnew, input_array[2]);
        char *pt = strtok(cwd_inputnew, "\n");
        char buff[PATH_MAX];
        char *res = realpath(pt, buff);
        if (!res)
        {
            perror("REALPATH ERROR OCCURED ");
        }
        else
        {
            int value23 = chdir(res);
            printf("physical source directory : %s\n", buff);
            printf("%s\n", res);
            if (value23 != 0)
            {
                perror("ERROR IN THE COMMAND ENTERED - ");
            }
            else
            {
                char cwd5[200];
                char *cwd35 = getcwd(cwd5, sizeof(cwd5));
            }
        }
    }
    else
    {
        int value2 = chdir(getenv("HOME"));
        if (value2 != 0)
        {
            perror("ERROR IN THE COMMAND ENTERED - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
}

void cdL(char **input_array)
{
    if (input_array[2] != NULL)
    {
        char cwd_inputnew[1024];
        strcpy(cwd_inputnew, input_array[2]);
        char *pt = strtok(cwd_inputnew, "\n");
        int id = chdir(pt);
        if (id != 0)
        {
            perror("ERROR IN -L COMMAND - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
    else
    {
        int value2 = chdir(getenv("HOME"));
        if (value2 != 0)
        {
            perror("ERROR IN THE COMMAND ENTERED - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
}

void cd(char **input_array) 
{
    int fs1 = INT_MAX;
    int fs2 = INT_MAX;
    int fs3 = INT_MAX;
    int fs4 = INT_MAX;
    int fs5 = INT_MAX;
    int fs6 = INT_MAX;
    int fs7 = INT_MAX;

    char cwd_inputnew1[1024];

    if (input_array[1] != NULL)
    {

        strcpy(cwd_inputnew1, input_array[1]);
        fs1 = strcmp(cwd_inputnew1, "~");
        fs2 = strcmp(cwd_inputnew1, "--");
        fs3 = strcmp(cwd_inputnew1, "-");
        fs4 = strcmp(cwd_inputnew1, "-P");
        fs5 = strcmp(cwd_inputnew1, "-L");
        fs6 = strcmp(cwd_inputnew1, "--help");
    }
    else
    {
        fs7 = 0;
    }
    if (fs3 == 0)
    {
        int f3 = chdir("..");
        if (f3 != 0)
        {
            perror("ERROR IN THE COMMAND ENTERED - ");
        }
        else
        {
            char cwd2[200];
            char *cwd32 = getcwd(cwd2, sizeof(cwd2));
            printf("%s", cwd32);
        }
    }
    else if (fs4 == 0)
    {
        cdP(input_array);
    }
    else if (fs6 == 0)
    {
        printf("%s", "This command is used to change the directory to the given input");
    }
    else if (fs5 == 0)
    {
        cdL(input_array);
    }
    else if (fs1 == 0 || fs2 == 0 || fs7 == 0)
    {
        int f127 = chdir(getenv("HOME"));
        if (f127 != 0)
        {
            perror("ERROR IN THE COMMAND ENTERED - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
    else
    {
        char *pt = strtok(cwd_inputnew1, "\n");
        int value = chdir(pt);
        if (value != 0)
        {
            perror("ERROR IN ALLCOMMANDS - ");
        }
        else
        {
            char cwd[200];
            char *cwd3 = getcwd(cwd, sizeof(cwd));
            printf("%s", cwd3);
        }
    }
}

void pwdforP()
{
    char narr[1024];
    char *cwd69 = getcwd(narr, sizeof(narr));
    printf("%s", cwd69);
}

void pwdforL()
{
    char buff[PATH_MAX];
    char narr[1024];
    char *res = realpath(narr, buff);
    char *cwd = getcwd(narr, sizeof(narr));
    printf("%s", cwd);
}

void pwd(char **input_array)
{
    int newf = 0;
    char cwd_input[10];
    char arr[1024];
    int forP = INT_MAX;
    int forh = INT_MAX;
    int forL= INT_MAX;

    if (input_array[1] != NULL)
    {
        strcpy(cwd_input, input_array[1]);
        newf = 1;
    }

    char *cwd = getcwd(arr, sizeof(arr));
    if (cwd == NULL)
    {
        perror("Error:");
    }
    else
    {
        if (newf == 1)
        {
            forP = strcmp(cwd_input, "-P");
            forh = strcmp(cwd_input, "--help");
            forL = strcmp(cwd_input, "-L");
            if (forh == 0)
            {
                printf("%s", "This command prints the current working directory");
                exit;
            }
            else if (forL == 0)
            {
                pwdforL();
            }
            else if (forP == 0)
            {
                pwdforP();
            }  
        }
        else
        {
            printf("%s", cwd);
        }
    }
}

void echoforE(char **input_array, int size)
{
    int i = 2;
    while (i < size)
    {
        if (input_array[i] == NULL)
        {
            break;
        }
        else
        {
            printf("%s ", input_array[i]);
            i++;
        }
    }
}

void echoforn(char **input_array, int size)
{
    int i = 2;
    while (i < size)
    {
        if (input_array[i] == NULL)
        {
            break;
        }
        else
        {
            printf("%s ", input_array[i]);
            i++;
        }
    }
}

void echo(char **input_array, int size)
{
    int forn = INT_MAX;
    int forE = INT_MAX;
    int forh = INT_MAX;
    char echo_input[10];
    if (input_array[1] != NULL)
    {
        strcpy(echo_input, input_array[1]);
        forn = strcmp(echo_input, "-n");
        forE = strcmp(echo_input, "-E");
        forh = strcmp(echo_input, "--help");
    }
    else
    {
        return;
    }
    if (forn == 0)
    {
        nextln = 1;
        echoforn(input_array, size);
    }
    else if (forE == 0)
    {
        echoforE(input_array, size);
    }
    else if (forh == 0)
    {
        printf("%s", "This command is used to print the given input which is written after  the echo command");
    }
    else
    {
        for (int i = 1; i < size; ++i)
        {
            if (input_array[i] != NULL)
            {
                printf("%s ", input_array[i]);
            }
        }
    }
}

int shellmain(){
    nextln = 0;

        char command[1024];
        printf("(artixlinux@localhost) $ ");

        scanf("%[^\n]%*c", command);

        if (command[0] != 0)
        {
            int size = 0;
            //char func[10];
            int fn_no = -1;
            char new_command[1024];
            char **input_array = (char **)malloc(500 * sizeof(char *));

            strcpy(new_command, command);
            // if (counter > 999)
            // {
            //     counter = 0;
            // }

            char *t = strtok(command, " ");

            while (t != NULL)
            {
                input_array[size] = (char *)malloc(500 * sizeof(char));
                strcpy(input_array[size], t);
                t = strtok(NULL, " ");
                size++;
            }

            int i = 0;
            while (i < 10)
            {
                int ctr = 0;

                int f = 0;

                while (allcomands[i][ctr] != '\0' && input_array[0][ctr] != '\0')
                {
                    if (allcomands[i][ctr] != input_array[0][ctr])
                    {
                        f = 1;
                        break;
                    }
                    ctr++;
                }

                if (allcomands[i][ctr] != '\0' || input_array[0][ctr] != '\0')
                {
                    f = 1;
                }

                if (f != 1)
                {
                    fn_no = i;
                    break;
                }
                i++;
            }

            if (fn_no == 0)
            {
                cd(input_array);
            }
            else if (fn_no == 1)
            {
                echo(input_array, size);
            }
            else if (fn_no == 2)
            {
                pwd(input_array);
            }
            else if (fn_no == 3)
            {
                printf("SHELL TERMINATED\n");
                printf("THANK YOU !!\n");
                return(0);
            }

            else if (fn_no == 4)
            {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./ls", new_command, NULL};
                    execvp("./ls", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (fn_no == 5)
            {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./cat", new_command, NULL};
                    execvp("./cat", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (fn_no == 6)
            {
                pid_t id;

                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./date", new_command, NULL};
                    execvp("./date", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (fn_no == 7)
            {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./rm", new_command, NULL};
                    execvp("./rm", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else if (fn_no == 8)
            {
                pid_t id;
                int stat;
                if ((id = fork()) == 0)
                {
                    char *args[] = {"./mkdir", new_command, NULL};
                    execvp("./mkdir", args);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&stat);
                }
            }
            else
            {
                printf("%s", "Error: Command not found\n");
            }
            if (nextln == 0)
            {
                printf("%s\n", "");
            }
        }
        else
        {
            printf("%s\n", "PLEASE RUN AGAIN,THERE WAS NO INPUT PROVIDED");
        }
}

int main(){
    system("clear");
    //printf("WELOME TO SHELL USER\n");
    printf("*******************************SHELL*******************************\n");
    printf("\n");
    char cwd[100];
    int t;
    while(1)
    {
        t=shellmain();
        if (t==0)
        {
            break;
        }
    }
    return 0;
}
