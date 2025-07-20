#include <stdio.h>
#include <stdlib.h>
#include "include.h"
int main(){
    int **pp,*p,n,ins_num,del_num,instru,flag=0;
    printf("Please enter the number of array you want to input:");
    scanf("%d",&n);
    if((p = (int *)calloc(n,sizeof(int)))==NULL){
        printf("ERROR!");
        exit(1);
    }
    pp=&p;
    printf("Please enter %d number to be the array:",n);
    input(p,&n);
    while(1){
        printf("[0]exxit\n[1]insert number\n[2]delete number\n");
        printf("please enter your insruction:");
        scanf("%d",&instru);
        switch(instru){
            case 0:flag=1;break;
            case 1:
                printf("Please enter the number you want to insert:");
                scanf("%d",&ins_num);
                insert(pp,&n,ins_num);
                output(p,&n);
                break;
            case 2:
                printf("Please enter the number you want to delete:");
                scanf("%d",&del_num);
                remov(pp,&n,del_num);
                output(p,&n);
                break;
            default:printf("error instruction!\n");break;
        }
        if(flag==1)
            break;
    }
    free(p);
    return 0;
}
