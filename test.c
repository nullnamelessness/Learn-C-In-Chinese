// #include<stdio.h>
// double func1(int n);
// double func2(int n);

// double func1(int n){
//     if(n>=2)
//         return (func1(n-1) + func2(n-1));
//     else return 2.0;
// }
// double func2(int n){
//     if(n>=2)
//         return func1(n-1);
//     else return 1.0;
// }
// int main(){
//     int N;
//     double sum =0,y,x;
//     scanf("%d",&N);
//     for(int i =1;i<=N;i++){
//         x = func1(i);
//         y = func2(i);
//         sum = sum + x/y;
//     }
//     printf("%.2lf",sum);
//     return 0;
// }

// #include<stdio.h>
// #include<math.h>
// double fun(int i){
//     if(i>=2)return i*fun(i-1);
//     else return 1;
// }
// double func(double x,int i){
//     return pow(x,i)/fun(i);
// }
// int main(){
//     int i =0;
//     double x,y,sum = 0;
//     scanf("%lf",&x);
//     do {
//         y = func(x,i);
//         sum = sum + y;
//         i++;
//     }while(y>=0.00001);
//     printf("%.4lf",sum);
// }

// #include <stdio.h>
// int is_perfect(int n){
//     int sum=0,count=0;
//     for(int i = 1;i<=n-1;i++){
//         if(n%i==0){
//             sum =sum + i;
//             count++;
//         }
//     }
//     if(sum == n)return count;
//     else return 0;
// }
// int main(){
//     int m,n,i,j,y,count=0,flag=0;
//     scanf("%d %d",&m,&n);
//     for(i=m;i<=n;i++){
//         count = 0;
//         y = is_perfect(i);
//         if(y){
//             flag = 1;
//             printf("%d = ",i);
//             for(j = 1;count<y-1;j++){
//                 if(i%j==0){
//                     count++;
//                     printf("%d + ",j);
//                 }
//             }
//             printf("%d\n",i/2);
//         }
//     }
//     if(flag==0)printf("None\n");
// }

// #include<stdio.h>
// int main(){
//     int N,line,clon;
//     scanf("%d",&N);
//     line = N;
//     clon = N;
//     for(int i = 1;i<=line;i++){
//         for(int j =1;j<=i;j++){
//             printf("%d*%d = %-4d",j,i,i*j);
//         }
//         printf("\n");
//     }
// }

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int (*func(int))(int,int);
int (*gfunc(int))(int,int);
int add(int,int);
int sub(int,int);
int mul(int,int);
int div_int(int,int);
int judge(int (*(*pf)(int))(int,int));
int main(){
    int ch=0,(*(*pf)(int))(int,int),result;
    scanf("%d",&ch);
    srand((unsigned int)time(NULL));
    if(ch){
        printf("guess add or sub?\n");
        pf=func;
    }
    else{
        printf("guess mul or div?\n");
        pf=gfunc;
    }
    result=judge(pf);
    printf("%d",result);
    return 0;
}
int (*func(int n))(int x,int y){
    int (*addp)(int,int),(*subp)(int,int);
    addp=add;
    subp=&sub;
    if(n){
        printf("rand(1)%%2 is  !0,add!are u right?\n");
        return addp;
    }
    else{
        printf("rand(1)%%2 is  0,sub!are u right??\n");
        return subp;
    }
}
int (*gfunc(int n))(int x,int y){
    int (*mulp)(int,int),(*divp)(int,int);
    mulp=mul;
    divp=&div_int;
    if(n){
        printf("rand(1)%%2 is  !0,mul!are u right?\n");
        return mulp;
    }
    else{
        printf("rand(1)%%2 is  0,div!are u right?\n");
        return divp;
    }
}
int add(int x,int y){
    printf("rand(2) is %d,rand(3) is %d\n",x,y);
    printf("%d + %d = ",x,y);
    return x+y;
}
int sub(int x,int y){
    printf("rand(2) is %d,rand(3) is %d\n",x,y);
    printf("%d - %d = ",x,y);
    return x-y;
}
int mul(int x,int y){
    printf("rand(2) is %d,rand(3) is %d\n",x,y);
    printf("%d * %d = ",x,y);
    return x*y;
}
int div_int(int x,int y){
    if(!y){
        printf("rand(3) is 0,cannot div,rerandoming...\n");
        y=rand()%100+1;
    }
    printf("rand(2) is %d,rand(3) is %d\n",x,y);
    printf("%d / %d = ",x,y);
    return x/y;
}
int judge(int (*(*pf)(int))(int,int)){
    return pf(rand()%2)(rand()%101,rand()%101);
}