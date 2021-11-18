#include "scop.h"

void printMat4(t_mat4 mat)
{
    int i = 0;
    while (i < 4)
    {
        int j = 0;
        while (j < 4)
        {
            printf("%f ", mat.m[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n");
}