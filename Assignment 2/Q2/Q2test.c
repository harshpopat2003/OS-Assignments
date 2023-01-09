#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define kernel_2d_memcpy 451

int main()
{
    int matrix1[4][4]={
        {21,65,12,71},
        {83,10,91,33},
        {51,47,99,55},
        {71,19,80,67}
    };

    int matrix2[4][4]={
        {69,69,69,69},
        {69,69,69,69},
        {69,69,69,69},
        {69,69,69,69}
    };

    //print matrix1
    printf("Matrix 1 is : \n");
    for(int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            printf("%d ",matrix1[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //print matrix2 before copy 
    printf("Matrix 2 before copy is : \n");
    for(int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            printf("%d ",matrix2[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int val = syscall(kernel_2d_memcpy, matrix2 , matrix1, 4, 4);

    if (val == 0) {
        printf("Matrix 2 after copy is:\n");

        for(int i=0;i<4;++i)
        {
            for(int j=0;j<4;++j)
            {
                printf("%d ",matrix2[i][j]);
            }
            printf("\n");
        } 
    }
    else{
        printf("Error in copying matrix");
    }  

    return 0;
}