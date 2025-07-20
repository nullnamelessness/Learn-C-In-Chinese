//数组指针

#include<stdio.h>
int main (){
    int b[3] = {11,22,33};
    int a[2] = {1,2};
    int c[4] = {44,55,66,77};
    int (*ptr)[] = &a;
    int *pi[3] = {b,a,c};
    int *(*pd)[] = &pi;
    int d[2][3]={{1,2},{3,4}};
    int(*pdd)[2][3]=&d;
    int *p = a;
    int **pp = pi;
    // int **pp = d;
    // printf("d[0][0] = %d \t&d = %p \tpp = %p \t*pp = %p \t**pp = %d\n",d[0][0],&d,pp,*pp,**pp);
    printf("&d = %p \td = %p \t*(d+1) = %p\t *(*(d+1)+1) = %d\n",&d,d,*(d+1),*(*(d+1)+1));
    printf("&a = %p \t&b = %p \t&c = %p \tptr = %p \tp = %p",&a,&b,&c,ptr,p);
    printf("\npi = %p \t*pi = %p \t**pi = %d \tpd = %p \t*pd = %p \t**pd = %p \t***pd = %d\n",pi,*pi,**pi,pd,*pd,**pd,***pd);
    printf("pdd = %p \t*pdd = %p \t**pdd = %p \t***pdd = %d",pdd,*pdd,**pdd,*(**pdd));
    // printf("\n%p \t%d \t%d\n",*ptr,**ptr,*p);
    // printf("%d",(*ptr)[1]);
}
