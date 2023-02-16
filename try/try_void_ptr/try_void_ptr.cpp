#include<stdio.h>

int main(int argc,char *argv[])
{
    int a = 2;
    double b = 2.0;
    void *c;                   //定义void *
    int *p = &a;
    c = p;                    //将int * 转成void *，
    double *q = (double *)c;  //将void *转成double *
    printf("%.f\n",*q);

    return 0;
}