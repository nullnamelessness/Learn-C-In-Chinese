//虚指针转化二级数组和二级指针，遇到段错误

// #include <stdio.h>
// int main(){
//     void *pv;
//     char arrc[3][8]={"we","are","family!"};
//     char **ppc;
//     pv=arrc;
//     ppc=pv;
//     printf("%p %p %c",ppc,*ppc,**(ppc));
//     return 0;
// }

#include <stdio.h>
int main(){
    int a[][2][3][4]={{{1,2.3,4},{1,2,3,4},{1,2,3}}};
    printf("%d",(int)sizeof(a));
    return 0;
}