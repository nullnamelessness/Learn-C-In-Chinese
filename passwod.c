#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
typedef struct {
    long int pid;
    char website[81];
    char username[81];
    char password[81];
} usrpassword;
char *read_file_name();
void encrypt(char *);
void decrypt(char *);
void creat();
long int load(FILE *);
long int *query(FILE *,long int *,char *,int);
FILE *update(FILE *);
long int *find_same_elements(long int *,long int,long int *,long int,long int *);
void insert(FILE *);
FILE *delete(FILE *);
void swap(FILE *,long int,long int);
void print_element(FILE *,long int,int);
void print_all(FILE *,int);
char *save(FILE *,char *);
void save_old_file(FILE *,char *);
void save_new_file(FILE *,char *);
void rename_new_file(FILE *,char *,char *);
void fcpy(FILE *,FILE *);
FILE *remove_element(FILE *,long int);
void ge_password();
int main(){
    FILE *fp=NULL,*fptr=NULL;
    int choice,choose,size=sizeof(usrpassword);
    long int i,pid,nu,nu1,nu2,*result,*result1,*result2,*num=&nu,*num1=&nu1,*num2=&nu2;
    char *file_name=NULL,website[81],username[81],password[81];
    usrpassword *usr;
    fptr=fopen("tmp.dat","wb");
    fclose(fptr);
    fptr=NULL;
    printf("1.creat,2.load,3.query,4.update,5.insert,6.endless insert,7.delete,8.Print,9.save file,10.suggest a password,0.exit");
    printf("\nPlease enter your choice:");
    scanf("%d",&choice);
    while(choice!=0){
        switch(choice){
            case 1:
                creat();
                if((fp=fopen("tmp.dat","rb+"))==NULL){
                    printf("\nERROR\n");
                    system("pause");
                    exit(1);
                }
                break;
            case 2:
                if(fp!=NULL){
                    if(fclose(fp)){
                        printf("\nERROR\n");
                        system("pause");
                        exit(2);
                    }
                    fp=NULL;
                }
                printf("\nPlease enter the file's name you want to load:");
                if(file_name!=NULL) free(file_name);
                file_name=read_file_name();
                file_name=(char *)realloc(file_name,(strlen(file_name)+5)*sizeof(char));
                strcat(file_name,".dat");
                if((fp=fopen(file_name,"rb"))==NULL){
                    printf("\ncannot open the file OR the file not exsit!");
                    system("pause");
                    exit(3);
                }
                if((fptr=fopen("tmp.dat","wb+"))==NULL){
                    printf("\ncannot open the file OR the file not exsit!\n");
                    system("pause");
                    exit(4);
                }
                fcpy(fptr,fp);
                if(fclose(fp)){
                        printf("\nERROR\n");
                        system("pause");
                        exit(5);
                }
                fp=NULL;
                if(fclose(fptr)){
                        printf("\nERROR\n");
                        system("pause");
                        exit(6);
                }
                fptr=NULL;
                if((fp=fopen("tmp.dat","rb+"))==NULL){
                    printf("\ncannot open the tmp.dat file OR the file not exsit!\n");
                    system("pause");
                    exit(7);
                }
                break;
            case 3:
            case 712:
                printf("\n0.search pid,1.search website,2.search username,3.search password\n");
                printf("12.search website and username,23,search username and password,13.search website and password\n");
                scanf("%d",&choose);
                switch(choose){
                    case 0:
                        printf("\nPlease enter your search pid:");
                        scanf("%ld",&pid);
                        usr=(usrpassword *)calloc(1,size);
                        fseek(fp,pid*size,SEEK_SET);
                        fread(usr,size,1,fp);
                        printf("\nPID\twebsite\t\t\t\t\t\tusername\t\t\t\tpassword");
                        print_element(fp,pid,choice);
                        free(usr);
                        break;
                    case 1:
                        printf("\nPlease enter your search website:");
                        scanf("%s",website);
                        result=query(fp,num,website,choose-1);
                        break;
                    case 2:
                        printf("\nPlease enter your search username:");
                        scanf("%s",username);
                        result=query(fp,num,username,choose-1);
                        break;
                    case 3:
                        printf("\nPlease enter your search password:");
                        scanf("%s",password);
                        if(choice==712) encrypt(password);
                        result=query(fp,num,password,choose-1);
                        break;
                    case 12:
                        printf("\nPlease enter your search website:");
                        scanf("%s",website);
                        result1=query(fp,num1,website,0);
                        printf("\nPlease enter your search username:");
                        scanf("%s",username);
                        result2=query(fp,num2,username,1);
                        break;
                    case 23:
                        printf("\nPlease enter your search username:");
                        scanf("%s",username);
                        result1=query(fp,num1,username,1);
                        printf("\nPlease enter your search password:");
                        scanf("%s",password);
                        if(choice==712) encrypt(password);
                        result2=query(fp,num2,password,2);
                        break;
                    case 13:
                        printf("\nPlease enter your search website:");
                        scanf("%s",website);
                        result1=query(fp,num1,website,0);
                        printf("\nPlease enter your search password:");
                        scanf("%s",password);
                        if(choice==712) encrypt(password);
                        result2=query(fp,num2,password,2);
                        break;
                    default:
                        printf("\nERROR CODE!");
                        break;
                }
                if((choose<=3)&&(choose>=1)){
                    usr=(usrpassword *)calloc(1,size);
                    printf("\nPID\twebsite\t\t\t\t\t\tusername\t\t\t\tpassword");
                    for(i=0;i<=nu;i++){
                        print_element(fp,result[i],choice);
                    }
                    free(result);
                    free(usr);
                }
                if((choose==12)||(choose==23)||(choose==13)){
                    result=find_same_elements(result1,nu1,result2,nu2,num);
                    usr=(usrpassword *)calloc(1,size);
                    printf("\nPID\twebsite\t\t\t\t\t\tusername\t\t\t\tpassword");
                    for(i=0;i<=nu;i++){
                        print_element(fp,result[i],choice);
                    }
                    free(result);
                    free(result1);
                    free(result2);
                    free(usr);
                }
                break;
            case 4:
                fp=update(fp);
                break;
            case 5:
                usr=(usrpassword *)calloc(1,size);
                printf("\nPlease enter your website:");
                scanf("%s",usr->website);
                printf("\nPlease enter your username:");
                scanf("%s",usr->username);
                printf("\nPlease enter your password:");
                scanf("%s",usr->password);
                encrypt(usr->password);
                usr->pid=load(fp);
                fseek(fp,0L,SEEK_END);
                fwrite(usr,size,1,fp);
                insert(fp);
                free(usr);
                break;
            case 6:
                usr=(usrpassword *)calloc(1,size);
                printf("\nPlease enter your website(enter 0 to exit insert):");
                scanf("%s",usr->website);
                while(strcmp(usr->website,"0")!=0){
                    printf("\nPlease enter your username:");
                    scanf("%s",usr->username);
                    printf("\nPlease enter your password:");
                    scanf("%s",usr->password);
                    encrypt(usr->password);
                    usr->pid=load(fp);
                    fseek(fp,0L,SEEK_END);
                    fwrite(usr,size,1,fp);
                    insert(fp);
                    printf("\nPlease enter your website(enter 0 to exit insert):");
                    scanf("%s",usr->website);
                }
                free(usr);
                break;
            case 7:
                fp=delete(fp);
                break;
            case 8:
            case 831:
                print_all(fp,choice);
                break;
            case 9:
                file_name=save(fp,file_name);
                fp=NULL;
                fptr=NULL;
                if((fp=fopen("tmp.dat","rb+"))==NULL){
                    printf("\nERROR\n");
                    system("pause");
                    exit(111);
                }
                break;
                case 10:
                    ge_password();
            default: 
                break;
        }
    printf("\n1.creat,2.load,3.query,4.update,5.insert,6.endless insert,7.delete,8.Print,9.save file,10.suggest a password,0.exit");
    printf("\nPlease enter your choice:");
    scanf("%d",&choice);
    }
    if(fp!=NULL){
        if(fclose(fp)){
            printf("\nERROR\n");
            system("pause");
            exit(5);
        }
        fp=NULL;
    }
    if(fptr!=NULL){
        if(fclose(fptr)){
            printf("\nERROR\n");
            system("pause");
            exit(6);
        }
        fptr=NULL;
    }
    if(file_name!=NULL)  free(file_name);
    if(remove("tmp.dat")==EOF){
        printf("\nERROR!can NOT delete tmp.dat\n");
        system("pause");
        exit(8);
    }
    return 0;
}
void ge_password(){
    int num,a[94]={0};
    char ch;
    srand((unsigned int)time(NULL));
    num=rand()%10+17;
    printf("\nyour password is %d bit:\n",num-1);
    for(int i=0;i<num-1;i++){
        do{
            ch=(char)(rand()%94+33);
            if(a[ch-33]==0){
                a[ch-33]=1;
                break;
            }
        }while(1);
        putchar(ch);
    }
}
void fcpy(FILE *fptr,FILE *fp){
    usrpassword *usr;
    int size=sizeof(usrpassword);
    long int i=0;
    usr=(usrpassword *)calloc(1,size);
    rewind(fp);
    rewind(fptr);
    while(fread(usr,size,1,fp)==1){
        fwrite(usr,size,1,fptr);
        i++;
    }
    free(usr);
}
char *read_file_name(){
    char *name;
    char ch[2]={0,0};
    do{
    ch[0]=getchar();
    }while((ch[0]==' ')||(ch[0]=='\n')||(ch[0]=='\t'));
    if((name=(char *)calloc(2,sizeof(char)))==NULL){
        printf("\nERROR!");
        exit(9);
    }    
    while((ch[0]!=' ')&&(ch[0]!='\n')&&(ch[0]!='\t')){
        if((name=(char *)realloc(name,(strlen(name)+2)*sizeof(char)))==NULL){
            printf("\nERROR!");
            exit(10);
        }
        strcat(name,ch);
        ch[0]=getchar();
    }
    return name;
}
void encrypt(char *strs){
    int i;
    for(i=0;i<(int)strlen(strs);i++){
        if(i%2==0)
            strs[i]=0XF0^strs[i];
        else
            strs[i]=0X0F^strs[i];
    }
}
void decrypt(char *strs){
    int i;
    for(i=0;i<(int)strlen(strs);i++){
        if(i%2==0)
            strs[i]=0XF0^strs[i];
        else
            strs[i]=0X0F^strs[i];
    }
}
void creat(){
    usrpassword *usr;
    FILE *fp;
    long int i=0;
    char strs[81];
    int size=sizeof(usrpassword);
    usr=(usrpassword *)calloc(1,size);
    if((fp=fopen("tmp.dat","wb+"))==NULL){
        printf("\nERROR\n");
        system("pause");
        exit(11);
    }
    printf("\nPlease enter your website:");
    scanf("%s",strs);
    while(strcmp(strs,"0")!=0){
        strcpy(usr->website,strs);
        printf("\nPlease enter your username:");
        scanf("%s",usr->username);
        printf("\nPlease enter your password:");
        scanf("%s",usr->password);
        encrypt(usr->password);
        usr->pid=i;
        fseek(fp,i*size,SEEK_SET);
        fwrite(usr,size,1,fp);
        i++;
        insert(fp);
        printf("\nPlease enter your website(enter 0 to qiut creat list):");
        scanf("%s",strs);
    }
    if(fclose(fp)){
        printf("\nERROR\n");
        system("pause");
        exit(12);
    }
    free(usr);
}
long int load(FILE *fp){
    long int length,begin,end;
    int size=sizeof(usrpassword);
    fseek(fp,0L,SEEK_SET);
    begin=ftell(fp);
    fseek(fp,0L,SEEK_END);
    end=ftell(fp);
    length=(end-begin)/size;
    return length;
}
long int *query(FILE *fp,long int *num,char *ptr,int choice){ //choice:   0:website  1.username   2.password
    long int *result=NULL,i,size=sizeof(usrpassword),length=load(fp);
    usrpassword *usr;
    usr=(usrpassword *)calloc(1,size);
    *num=0;
    switch(choice){
        case 0:
            for(i=0;i<length;i++){
                fseek(fp,i*size,SEEK_SET);
                fread(usr,size,1,fp);
                if(strcmp(usr->website,ptr)==0){
                    if(result==NULL){
                        result=(long int *)calloc(1,sizeof(long int));
                        result[*num]=usr->pid;
                        (*num)++;
                    }else{
                        result=(long int *)realloc(result,(*num+1)*sizeof(long int));
                        result[*num]=usr->pid;
                        (*num)++;
                    }
                }
            }
            (*num)--;
            break;
        case 1:
            for(i=0;i<length;i++){
                fseek(fp,i*size,SEEK_SET);
                fread(usr,size,1,fp);
                if(strcmp(usr->username,ptr)==0){
                    if(result==NULL){
                        result=(long int *)calloc(1,sizeof(long int));
                        result[*num]=usr->pid;
                        (*num)++;
                    }else{
                        result=(long int *)realloc(result,(*num+1)*sizeof(long int));
                        result[*num]=usr->pid;
                        (*num)++;
                    }
                }
            }
            (*num)--;
            break;
        case 2:
            for(i=0;i<length;i++){
                fseek(fp,i*size,SEEK_SET);
                fread(usr,size,1,fp);
                if(strcmp(usr->password,ptr)==0){
                    if(result==NULL){
                        result=(long int *)calloc(1,sizeof(long int));
                        result[*num]=usr->pid;
                        (*num)++;
                    }else{
                        result=(long int *)realloc(result,(*num+1)*sizeof(long int));
                        result[*num]=usr->pid;
                        (*num)++;
                    }
                }
            }
            (*num)--;
            break;
        default:
            break;
    }
    free(usr);
    return result;
}
FILE *update(FILE *fp){
    int choice,size=sizeof(usrpassword);
    long int *num,*num1,*num2,nu,nu1,nu2,pid,*result=NULL,*result1,*result2;
    char *change;
    usrpassword *usr;
    num=&nu;
    num1=&nu1;
    num2=&nu2;
    usr=(usrpassword *)calloc(1,size);
    printf("\n1.use pid to update,2.use website and username to update:");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            printf("\nPlease enter the pid you want to update:");
            scanf("%ld",&pid);
            fseek(fp,pid*size,SEEK_SET);
            fread(usr,size,1,fp);
            printf("\nPlease enter the changed website(enter . to not change website):");
            change=read_file_name();
            if(strcmp(change,".")==0){
            }else{
                strcpy(usr->website,change);
            }
            free(change);
            printf("\nPlease enter the changed username(enter . to not change username):");
            change=read_file_name();
            if(strcmp(change,".")==0){
            }else{
                strcpy(usr->username,change);
            }
            free(change);
            printf("\nPlease enter the changed password(enter . to not change password):");
            change=read_file_name();
            if(strcmp(change,".")==0){
            }else{
                encrypt(change);
                strcpy(usr->password,change);
            }           
            free(change);
            fseek(fp,pid*size,SEEK_SET);
            fwrite(usr,size,1,fp);
            fp=remove_element(fp,pid);
            fseek(fp,0L,SEEK_END);
            fwrite(usr,size,1,fp);
            insert(fp);
            break;
        case 2:
            printf("\nPlease enter the website you want to update:");
            change=read_file_name();
            result1=query(fp,num1,change,0);
            free(change);
            printf("\nPlease enter the username you want to update:");
            change=read_file_name();
            result2=query(fp,num2,change,1);
            free(change);
            result=find_same_elements(result1,nu1,result2,nu2,num);
            if(nu>0){
                printf("\nfind too much result!,Please sure the result only one!");
            }else{
                pid=result[0];
                fseek(fp,pid*size,SEEK_SET);
                fread(usr,size,1,fp);
                printf("\nPlease enter the changed website(enter . to not change website):");
                change=read_file_name();
                if(strcmp(change,".")==0){
                }else{
                    strcpy(usr->website,change);
                }
                free(change);
                printf("\nPlease enter the changed username(enter . to not change username):");
                change=read_file_name();
                if(strcmp(change,".")==0){
                }else{
                    strcpy(usr->username,change);
                }
                free(change);
                printf("\nPlease enter the changed password(enter . to not change password):");
                change=read_file_name();
                if(strcmp(change,".")==0){
                }else{
                    encrypt(change);
                    strcpy(usr->password,change);
                }
                free(change);
                fseek(fp,pid*size,SEEK_SET);
                fwrite(usr,size,1,fp);
                fp=remove_element(fp,pid);
                fseek(fp,0L,SEEK_END);
                fwrite(usr,size,1,fp);
                insert(fp);
            }
            free(result);
            free(result1);
            free(result2);
            break;
        default:
            break;
    }
    free(usr);
    return fp;
}
long int *find_same_elements(long int *result1,long int nu1,long int *result2,long int nu2,long int *num){
    long int i,j,*result=NULL;
    *num=0;
    for(i=0;i<=nu1;i++){
        for(j=0;(j<=((nu2<result1[i])?nu2:result1[i]))&&(result2[j]<=result1[i]);j++){
            if(result2[j]==result1[i]){
                if(result==NULL){
                    result=(long int *)calloc(1,sizeof(long int));
                    result[*num]=result1[i];
                    (*num)++;
                }else{
                    result=(long int *)realloc(result,(*num+1)*sizeof(long int));
                    result[*num]=result1[i];
                    (*num)++;
                }
                break;
            }
        }
    }
    (*num)--;
    return result;
}
void insert(FILE *fp){
    usrpassword *usr1,*usr2;
    long int i,length=load(fp);
    int size=sizeof(usrpassword);
    usr1=(usrpassword *)calloc(1,size);
    usr2=(usrpassword *)calloc(1,size);
    fseek(fp,-size,SEEK_END);
    fread(usr2,size,1,fp);
    for(i=0;i<length-1;i++){
        fseek(fp,i*size,SEEK_SET);
        fread(usr1,size,1,fp);
        if(strcmp(usr1->website,usr2->website)>0){
            while(i<length-1){
                swap(fp,i,length-1);
                i++;
            }
            break;
        }
    }
    free(usr1);
    free(usr2);
}
void swap(FILE *fp,long int i,long int j){
    usrpassword *tmp1,*tmp2;
    int size=sizeof(usrpassword);
    tmp1=(usrpassword *)calloc(1,size);
    tmp2=(usrpassword *)calloc(1,size);
    fseek(fp,i*size,SEEK_SET);
    fread(tmp1,size,1,fp);
    fseek(fp,j*size,SEEK_SET);
    fread(tmp2,size,1,fp);
    tmp1->pid=j;
    tmp2->pid=i;
    fseek(fp,i*size,SEEK_SET);
    fwrite(tmp2,size,1,fp);
    fseek(fp,j*size,SEEK_SET);
    fwrite(tmp1,size,1,fp);
    free(tmp1);
    free(tmp2);
}
FILE *delete(FILE * fp){
    long int pid,i=0;
    int count=0,flag=0,chioce,size=sizeof(usrpassword);
    usrpassword *usr,*usr1,*usr2;
    char password[81];
    usr=(usrpassword *)calloc(1,size);
    usr1=(usrpassword *)calloc(1,size);
    usr2=(usrpassword *)calloc(1,size);
    printf("\nselect your delete mode:");
    printf("\n1.delete specific website and username and password");
    printf("\n2.delete specific pid");
    printf("\n3.delete specific website");
    printf("\n4.delete specific user");
    printf("\nany other number to cancle delete\n");
    scanf("%d",&chioce);
    switch(chioce){
        case 1:
            printf("\nPlease enter the website you want to delete:");
            scanf("%s",usr1->website);
            printf("\nPlease enter the username you want to delete:");
            scanf("%s",usr1->username);
            printf("\nPlease enter the password you want to delete:");
            scanf("%s",usr1->password);
            encrypt(usr1->password);
            while(i<load(fp)){
                fseek(fp,i*size,SEEK_SET);
                fread(usr2,size,1,fp);
                if((strcmp(usr2->website,usr1->website)==0)&&(strcmp(usr2->username,usr1->username)==0)){
                    if(strcmp(usr2->password,usr1->password)==0){
                        fp=remove_element(fp,i);
                        flag=1;
                        count=1;
                    }else{
                        flag=-1;
                    }
                }
                if(flag==-1) break;
                if(!count){
                    i++;
                }else{
                    count=0;
                }
            }
            if(flag==0) printf("\nno such log!\n");
            else if(flag==-1)   printf("\npassword erroe!you have no right to delete the account!\n");
            else printf("\ndelete success!\n");
            break;
        case 2:
            printf("\nPlease enter the pid you want to delete:");
            scanf("%ld",&pid);
            fseek(fp,pid*size,SEEK_SET);
            fread(usr,size,1,fp);
            printf("\nthe accout's website you want delete is %s",usr->website);
            printf("\nthe accout's username you want delete is %s",usr->username);
            printf("\nPlease enter the password you want to delete:");
            scanf("%s",password);
            encrypt(password);
            if((strcmp(usr->password,password)==0)&&(pid<(load(fp)))){
                fp=remove_element(fp,pid);
                flag=1;
            }else{
                flag=-1;
            }
            if(flag==0) printf("\nno such log!\n");
            else if(flag==-1)   printf("\npassword erroe!you have no right to delete the account!\n");
            else printf("\ndelete success!\n");
            break;
        case 3:
            printf("\nPlease enter the website you want to delete:");
            scanf("%s",usr2->website);
            fseek(fp,0L,SEEK_SET);
            while(fread(usr1,size,1,fp)==1){
                if(strcmp(usr1->website,usr2->website)==0){
                    printf("\nthe accout's username you want delete is %s",usr1->username);
                    printf("\nPlease enter the password you want to delete:");
                    scanf("%s",usr2->password);
                    encrypt(usr2->password);
                    if(strcmp(usr1->password,usr2->password)==0){
                        fp=remove_element(fp,i);
                        flag=1;
                        count=1;
                    }else{
                        flag=-1;
                    }
                }
                if(flag==-1) break;
                if(!count){
                    i++;
                }else{
                    count=0;
                }
                fseek(fp,i*size,SEEK_SET);
            }
            if(flag==0) printf("\nno such log!\n");
            else if(flag==-1)   printf("\npassword erroe!you have no right to delete the account!\n");
            else printf("\ndelete success!\n");
            break;
        case 4:
            printf("\nPlease enter the usr you want to delete:");
            scanf("%s",usr2->username);
            fseek(fp,0L,SEEK_SET);
            while(fread(usr1,size,1,fp)==1){
                if(strcmp(usr1->username,usr2->username)==0){
                    printf("\nthe accout's website you want delete is %s",usr1->website);
                    printf("\nPlease enter the password you want to delete:");
                    scanf("%s",usr2->password);
                    encrypt(usr2->password);
                    if(strcmp(usr1->password,usr2->password)==0){
                        fp=remove_element(fp,i);
                        flag=1;
                        count=1;
                    }else{
                        flag=-1;
                    }
                }
                if(flag==-1) break;
                if(!count){
                    i++;
                }else{
                    count=0;
                }
                fseek(fp,i*size,SEEK_SET);
            }
            if(flag==0) printf("\nno such log!\n");
            else if(flag==-1)   printf("\npassword erroe!you have no right to delete the account!\n");
            else printf("\ndelete success!\n");
            break;
        default:
            break;
    }
    free(usr);
    free(usr1);
    free(usr2);
    return fp;
}
FILE *remove_element(FILE *fp,long int index){
    usrpassword *usr;
    FILE *fptr=NULL;
    int size=sizeof(usrpassword);
    long int i=0,j=0;
    if((fptr=fopen("temp.dat","wb+"))==NULL){
        printf("\nERROR\n");
        system("pause");
        exit(13);
    }
    usr=(usrpassword *)calloc(1,size);
    rewind(fp);
    rewind(fptr);
    while(fread(usr,size,1,fp)==1){
        if(i!=index){
            usr->pid=j;
            fwrite(usr,size,1,fptr);
            j++;
        }
        i++;
    }
    if(fclose(fp)){
        printf("\nERROR\n");
        system("pause");
        exit(14);
    }
    fp=NULL;
    if(fclose(fptr)){
        printf("\nERROR\n");
        system("pause");
        exit(14);
    }
    fptr=NULL;
    if(remove("tmp.dat")==EOF){
        printf("\nERROR\n");
        system("pause");
        exit(15);
    }
    if(rename("temp.dat","tmp.dat")==EOF){
        printf("\nERROR\n");
        system("pause");
        exit(15);
    }
    if((fp=fopen("tmp.dat","rb+"))==NULL){
        printf("\nERROR\n");
        system("pause");
        exit(14);
    }
    free(usr);
    return fp;
}
void print_element(FILE *fp,long int pid,int choice){
    usrpassword *usr;
    int size=sizeof(usrpassword);
    usr=(usrpassword *)calloc(1,size);
    fseek(fp,pid*size,SEEK_SET);
    fread(usr,size,1,fp);
    if(choice==712){
        encrypt(usr->password);
    }
    printf("\n%-5ld%-50s%-35s%-25s",usr->pid,usr->website,usr->username,usr->password);
    free(usr);
}
void print_all(FILE *fp,int choice){
    long int pid,length=load(fp);
    int size=sizeof(usrpassword);
    usrpassword *usr;
    usr=(usrpassword *)calloc(1,size);
    printf("\nPID\twebsite\t\t\t\t\t\tusername\t\t\t\tpassword");
    for(pid=0;pid<length;pid++){
        fseek(fp,pid*size,SEEK_SET);
        fread(usr,size,1,fp);
        if(choice==831){
            encrypt(usr->password);
        }
        printf("\n%-5ld%-50s%-35s%-25s",usr->pid,usr->website,usr->username,usr->password);  //120 pixle
    }
    free(usr);
}
char *save(FILE *fp,char *file_name){
    FILE *fptr;
    char *name;
    int choice;
    if(file_name==NULL){
        printf("\nPlease enter new file name:");
        name=read_file_name();
        name=(char *)realloc(name,(strlen(name)+5)*sizeof(char));
        strcat(name,".dat");
        save_new_file(fp,name);
        if((fp=fopen(name,"rb"))==NULL){
            printf("\nERROR\n");
            system("pause");
            exit(111);
        }
        if((fptr=fopen("tmp.dat","wb"))==NULL){
            printf("\nERROR\n");
            system("pause");
            exit(111);
        }
    }else{
        printf("\nif you want to rename,please enter 0(enter any other number to cancel rename):");
        scanf("%d",&choice);
        switch(choice){
            case 0:
                printf("\nPlease enter new file name:");
                name=read_file_name();
                name=(char *)realloc(name,(strlen(name)+5)*sizeof(char));
                strcat(name,".dat");
                rename_new_file(fp,name,file_name);
                if((fp=fopen(name,"rb"))==NULL){
                    printf("\nERROR\n");
                    system("pause");
                    exit(111);
                }
                if((fptr=fopen("tmp.dat","wb"))==NULL){
                    printf("\nERROR\n");
                    system("pause");
                    exit(111);
                }
                break;
            default:
                name=(char *)calloc(1,strlen(file_name)+1);
                strcpy(name,file_name);
                save_old_file(fp,file_name);
                if((fp=fopen(file_name,"rb"))==NULL){
                    printf("\nERROR\n");
                    system("pause");
                    exit(111);
                }
                if((fptr=fopen("tmp.dat","wb"))==NULL){
                    printf("\nERROR\n");
                    system("pause");
                    exit(111);
                }
                break;
        }
    }
    fcpy(fptr,fp);
    if(fclose(fp)){
        printf("\nERROR\n");
        system("pause");
        exit(111);
    }
    if(fclose(fptr)){
        printf("\nERROR\n");
        system("pause");
        exit(111);
    }
    free(file_name);
    return name;
}
void save_old_file(FILE *fp,char *name){                //save old file
    if(fclose(fp)){
        printf("\ncan not close the file!");
        system("pause");
        exit(16);
    }
    if(remove(name)==EOF){
        printf("\nERROR\n");
        system("pause");
        exit(17);
    }
    if(rename("tmp.dat",name)==EOF){
        printf("\nERROR\n");
        system("pause");
        exit(18);
    }
}
void save_new_file(FILE *fp,char *name){                //save created list
    if(fclose(fp)){
        printf("\ncan not close the file!\n");
        system("pause");
        exit(19);
    }
    if(rename("tmp.dat",name)==EOF){
        printf("\nERROR\n");
        system("pause");
        exit(20);
    }
}
void rename_new_file(FILE *fp,char *name,char *file_name){              //rename old file
    if(fclose(fp)){
        printf("\nERRORcan not close the file!\n");
        system("pause");
        exit(21);
    }
    if(remove(file_name)==EOF){
        printf("\nERROR\n");
        system("pause");
        exit(22);
    }
    if(rename("tmp.dat",name)==EOF){
        printf("\nERROR\n");
        system("pause");
        exit(23);
    }
}