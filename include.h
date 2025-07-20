#include <stdio.h>
#include <stdlib.h>
void sort(int *ptr,int *num);
void input(int *ptr,int *num);
void output(int *ptr,int *num);
void swap(int *p,int*q);
void delete(int *ptr,int *num);
void remov(int **pptr,int *num,int n);
void insert(int **pptr,int *num,int n);
void sort(int *ptr,int *num){
    for(int i=0;i<*num;i++){
        for(int j=i+1;j<*num;j++){
            if(ptr[i]>ptr[j]){
                swap(&ptr[i],&ptr[j]);
            }
        }
    }
    delete (ptr,num);
}
void swap(int *p,int*q){
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}
void input(int *ptr,int *num){
    for(int i=0;i<*num;i++){
        scanf("%d",&ptr[i]);
    }
    sort(ptr,num);
}
void output(int *ptr,int *num){
    for(int j=0;j<*num;j++){
        printf("%d",ptr[j]);
        if(j<*num-1)
            printf("\t");
    }
    printf("\n%d\n",*num);
}
void delete(int *ptr,int *num){
    for(int i=0;i<*num-1;){
            if(ptr[i]==ptr[i+1]){
                for(int j=i+1;j<*num;j++){
                    ptr[j]=ptr[j+1];
                }
                (*num)--;
            }else{
                i++;
            }
    }
}
void insert(int **pptr,int *num,int n){
    int flag=0;
    for(int i=0;i<*num;i++){
        if((*pptr)[i]>n){
            (*num)++;
            if((*pptr = (int *)realloc(*pptr,(*num)*sizeof(int)))==NULL){
                printf("ERROR!");
                exit(1);
            }
            for(int j=*num-2;j>=i;j--){
                (*pptr)[j+1]=(*pptr)[j];
            }
            (*pptr)[i]=n;
            flag=1;
            break;
        }else if((*pptr)[i]==n){
            flag=-1;
            break;
        }
    }
    if(flag==-1)
        printf("repeated number to be insert!\n");
    else if(flag==0){
        (*num)++;
        if((*pptr = (int *)realloc(*pptr,(*num)*sizeof(int)))==NULL){
            printf("ERROR!");
            exit(1);
        }
        (*pptr)[*num-1]=n;        
    }
}
void remov(int **pptr,int *num,int n){
    int flag=0;
    for(int i=0;i<*num;i++){
        if((*pptr)[i]==n){
            for(int j=i;j<*num-1;j++){
                (*pptr)[j]=(*pptr)[j+1];
            }
            (*num)--;
            if((*pptr = (int *)realloc(*pptr,(*num)*sizeof(int)))==NULL){
                printf("ERROR!");
                exit(1);
            }
            flag=1;
            break;
        }
    }
    if(flag==0)
        printf("No such number to be delete!\n");
}