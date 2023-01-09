#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


void lsL(char arg[1000])
{
    DIR *thedirectory;
    struct dirent *thefile;
    struct stat thestat;
    struct passwd *tf;
    struct group *gf;
    char buf[512];
    if (strlen(arg) == 0)
    {
        arg = ".";
    }
    thedirectory = opendir(arg);
    while ((thefile = readdir(thedirectory)) != NULL)
    {
        if (thefile->d_name[0] == '.')
        {
            continue;
        }
        sprintf(buf, "%s/%s", arg, thefile->d_name);
        stat(buf, &thestat);
        switch (thestat.st_mode & S_IFMT)
        {
        case S_IFBLK:
            printf("b");
            break;
        case S_IFCHR:
            printf("c");
            break;
        case S_IFDIR:
            printf("d");
            break;
        case S_IFIFO:
            printf("p");
            break;
        case S_IFLNK:
            printf("l");
            break;
        case S_IFSOCK:
            printf("s");
            break;
        default:
            printf("-");
            break;
        }
        printf((thestat.st_mode & S_IRUSR) ? "r" : "-");
        printf((thestat.st_mode & S_IWUSR) ? "w" : "-");
        printf((thestat.st_mode & S_IXUSR) ? "x" : "-");
        printf((thestat.st_mode & S_IRGRP) ? "r" : "-");
        printf((thestat.st_mode & S_IWGRP) ? "w" : "-");
        printf((thestat.st_mode & S_IXGRP) ? "x" : "-");
        printf((thestat.st_mode & S_IROTH) ? "r" : "-");
        printf((thestat.st_mode & S_IWOTH) ? "w" : "-");
        printf((thestat.st_mode & S_IXOTH) ? "x" : "-");
        printf(" %ld", thestat.st_nlink);
        tf = getpwuid(thestat.st_uid);
        printf(" %s", tf->pw_name);
        gf = getgrgid(thestat.st_gid);
        printf(" %s", gf->gr_name);
        printf(" %zu", thestat.st_size);
        printf(" %s", thefile->d_name);
        printf(" %s", ctime(&thestat.st_mtime));
    }
    closedir(thedirectory);
}

void mainls(const char *dir,int op_a,int op_lh,int op_R,char arg[1000])
{
	//Here we will list the directory
	struct dirent *d;
	DIR *dh = opendir(dir);
	if (!dh)
	{
		if (errno = ENOENT)
		{
			//If the directory is not found
			perror("Directory doesn't exist");
		}
		else
		{
			//If the directory is not readable then throw error and exit
			perror("Unable to read directory");
		}
		exit(EXIT_FAILURE);
	}
    if (op_lh)
    {
        lsL(arg);
    }
    else if (op_R)
    {
        while ((d = readdir(dh)) != NULL)
        {
            if (d->d_name[0] == '.')
            {
                continue;
            }

            printf("%s ", d->d_name);
            //printf(". ..");
        }
    printf("\n");
    }
    // else if (op_a)
    // {
    //     while ((d = readdir(dh)) != NULL)
    //     {
    //         if (d->d_name[0] == '.')
    //         {
    //             //printf(". ..")
    //             printf(". .. %s ", d->d_name);
    //         } 
    //     }
    // }
    else
    {
        while ((d = readdir(dh)) != NULL)
        {
            if (d->d_name[0] == '.' && !op_a)
            {
                continue;
            }
            printf("%s ", d->d_name);
        }
        printf("\n");
    }
    closedir(dh);
}

int main(int argc, char *argv[])
{
    char cmdName[10] = "";
    char f[10] = "";
    char arg[1000] = "";
    if (argc > 1)
    {
        char *t = strtok(argv[1], " ");
        strcpy(cmdName, t);
        t = strtok(NULL, " ");
        if (t != NULL)
        {
            if (t[0] == '-')
            {
                strcpy(f, t);
                t = strtok(NULL, " ");
                if (t != NULL)
                {
                    strcpy(arg, t);
                }
            }
            else
            {
                strcpy(arg, t);
            }
        }
    }
    int op_a = 0, op_lh = 0 , op_R = 0;
    if (f[0] == '\0')
    {
        op_R = 1;
        //printLs(arg);
        mainls(".",op_a,op_lh,op_R,arg);
    }
    else if (f[1] == 'a')
    {
        op_a = 1;
        mainls(".",op_a,op_lh,op_R,arg);
        // printLsA(arg);
    }
    else if (f[1] == 'l')
    {
        op_lh = 1;
        mainls(".",op_a,op_lh,op_R,arg);
        // printLsL(arg);
    }
    else
    {
        printf("Not a Valid Input -- %s\n", f);
        printf("Please Enter a Valid Input\n");
        return 1;
    }

    return 0;
}

	//While the next entry is not readable we will print directory files
	// while ((d = readdir(dh)) != NULL)
	// {
	// 	//If hidden files are found we continue
	// 	if (!op_a && d->d_name[0] == '.')
	// 		continue;
	// 	//printf("%s  ", d->d_name);
	// 	if(op_lh) lsL(" ");
	// }
	// if(!op_lh)
	// printf("\n");
//}


// int main(int argc, const char *argv[])
// {
//     char cmdName[10] = "";
//     char f[10] = "";
//     char arg[1000] = "";
//     if (argc > 1)
//     {
//         char *t = strtok(argv[1], " ");
//         strcpy(cmdName, t);
//         t = strtok(NULL, " ");
//         if (t != NULL)
//         {
//             if (t[0] == '-')
//             {
//                 strcpy(f, t);
//                 t = strtok(NULL, " ");
//                 if (t != NULL)
//                 {
//                     strcpy(arg, t);
//                 }
//             }
//             else
//             {
//                 strcpy(arg, t);
//             }
//         }
//     }
//     // if (f[0] == '\0')
//     // {
//     //     lsL(arg);
//     //     return 0;
//     // }
// 	if (argc == 1)
// 	{
// 		mainls(".",0,0,1,arg);
// 	}
// 	else if (argc == 2)
// 	{
// 		if (argv[1][0] == '-')
// 		{
// 			//Checking if option is passed
// 			//Options supporting: a, l
// 			int op_a = 0, op_lh = 0 , op_R = 0;
// 			char *p = (char*)(argv[1] + 1);
// 			while(*p){
// 				if(*p == 'a') op_a = 1;
// 				else if(*p == 'l') op_lh = 1;
//                 //else if (*p == 'R') op_R = 1;
// 				else{
// 					perror("Option not available");
// 					exit(EXIT_FAILURE);
// 				}
// 				p++;
// 			}
// 			mainls(".",op_a,op_lh,op_R,arg);
// 		}
// 	}
// 	return 0;
// }
