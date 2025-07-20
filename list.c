#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student{
    int ID;
    char *name;
    int score;
    struct student * next;
};
struct student *input();
struct student *insert(struct student *head,struct student *p);
struct student *delete(struct student *head,int ID);
void output(struct student *head);
void updata(struct student *head,int ID,int score);
struct student *input_file();
void output_file(struct student *p);
char *scan_name(char *name);
char *scan_file_name(FILE *fp,char *name);
void freehead(struct student *head);
int main(){
    struct student *p,*head=NULL;
    int ID,score,choice,size=sizeof(struct student);
    char *name;
    printf("\n1.creat,2.Insert,3.Delete,4.update,5.Print,6.new file,7.scan file,0.exit");
    printf("\nPlease enter your choice:\n");
    scanf("%d",&choice);
    while(choice!=0){
        switch(choice){
            case 1:
                printf("\nnow your list will be deleted!\n");
                printf("if you want to qiut,please enter 0,or you can enter any interger to continue:");
                scanf("%d",&choice);
                if(choice==0)   break;
                freehead(head);
                head = input();
                break;
            case 2:              
                printf("\nPlease input your student's information:\n");
                printf("format:ID name score\n");
                scanf("%d",&ID);
                name=scan_name(name);
                scanf("%d",&score);
                p = (struct student *)malloc(size);
                p->ID=ID;
                if((p->name=(char*)malloc((strlen(name)+1)*sizeof(char)))==NULL){
                    printf("ERROR!");
                    exit(1);
                }
                strcpy(p->name,name);
                p->score=score;
                free(name);
                head=insert(head,p);
                break;
            case 3:
                printf("\nPlease input the student's ID you want to delete:\n");
                scanf("%d",&ID);
                head=delete(head,ID);
                break;
            case 4:
                printf("\nPlease enter the student's ID you want to update:\n");
                scanf("%d",&ID);
                printf("\nPlease enter the student's score you want to update:\n");
                scanf("%d",&score);
                updata(head,ID,score);
                break;
            case 5:
                output(head);
                break;
            case 6:
                if(head==NULL){
                    printf("\nthe student list is NULL!\n");
                    break;
                }
                output_file(head);
                break;
            case 7:
                freehead(head);
                head=input_file();
                break;
            default:
                break;
        }
    printf("\n1.creat,2.Insert,3.Delete,4.update,5.Print,6.new file,7.scan file,0.exit");
    printf("\nPlease enter your choice:\n");
    scanf("%d",&choice);
    }
    return 0;
}
char *scan_name(char *name){
    char ch[2]={0,0};
    do{
        ch[0]=getchar();
    }while((ch[0]==' ')||(ch[0]=='\n')||(ch[0]=='\t'));
    if((name=(char *)calloc(2,sizeof(char)))==NULL){
        printf("ERROR!");
        exit(1);
    }    
    while((ch[0]!=' ')&&(ch[0]!='\n')&&(ch[0]!='\t')){
        if((name=(char *)realloc(name,(strlen(name)+2)*sizeof(char)))==NULL){
            printf("ERROR!");
            exit(1);
        }
        strcat(name,ch);
        ch[0]=getchar();
    }
    return name;
}
char *scan_file_name(FILE *fp,char *name){
    char ch[2]={0,0};
    do{
        ch[0]=fgetc(fp);
    }while((ch[0]==' ')||(ch[0]=='\n')||(ch[0]=='\t'));
    if((name=(char *)calloc(2,sizeof(char)))==NULL){
        printf("ERROR!");
        exit(1);
    }    
    while((ch[0]!=' ')&&(ch[0]!='\n')&&(ch[0]!='\t')){
        if((name=(char *)realloc(name,(strlen(name)+2)*sizeof(char)))==NULL){
            printf("ERROR!");
            exit(1);
        }
        strcat(name,ch);
        ch[0]=fgetc(fp);
    }
    return name;
}
struct student *input(){
    struct student *p,*head=NULL;
    int ID,score;
    char *name;
    int size=sizeof(struct student);
    printf("Please input your first student's information:\n");
    printf("format:ID name score\n");
    scanf("%d",&ID);
    name=scan_name(name);
    scanf("%d",&score);
    while(ID!=0){
        p = (struct student *)malloc(size);
        p->ID=ID;
        if((p->name=(char*)malloc((strlen(name)+1)*sizeof(char)))==NULL){
            printf("ERROR!");
            exit(1);
        }
        strcpy(p->name,name);
        free(name);
        p->score=score;
        head=insert(head,p);
        printf("\nPlease input your next student's information:(enter 0 to exit)\n");
        printf("format:ID name score\n");
        scanf("%d",&ID);
        if(ID==0)   break;
        name=scan_name(name);
        scanf("%d",&score);
    }
    if(head!=NULL)  free(name);
    return head;
}
struct student *insert(struct student *head,struct student *p){
    struct student *ptr,*ptr0;
    if(head==NULL){                     //no head(new);
        p->next=head;
        head=p;
        return head;
    }
    if(head->ID>p->ID){                 //new head;
        p->next=head;
        head=p;
        return head;        
    }
    ptr0=ptr=head;
    while((ptr->next!=NULL)&&(ptr->ID<p->ID)){
        ptr0=ptr;
        ptr=ptr0->next;
    }
    if(ptr->ID==p->ID){                 //repeated ID;
        printf("\nrepeated student ID!");
    }else if(ptr->ID>p->ID){            //ptr0->p->ptr;
        p->next=ptr;
        ptr0->next=p;                   
    }else{                              //new end
        ptr->next=p;
        p->next=NULL;
    }
    return head;
}
struct student *delete(struct student *head,int ID){
    struct student *ptr,*ptr0;
    ptr=ptr0=head;
    if(head==NULL){
        printf("\nstudent clear!");
        return head;                    //no student;
    }
    while(ptr->next!=NULL&&ptr->ID!=ID){      //find ptr0 ptr==p;
        ptr0=ptr;
        ptr=ptr->next;
    }
    if(ptr->ID!=ID){                    //ptr==NULL;
        printf("\nNo such student to be delete!");
    }else if(ptr0!=ptr&&ptr->ID==ID){  //ptr0 ptr==p(...);
        ptr0->next=ptr->next;
        free(ptr);
    }else{
        head=ptr->next;
        free(ptr);
    }
    return head;
}
void output(struct student *head){
    struct student *p;
    if(head==NULL){
        printf("\nNo record!");
        return;
    }
    printf("\nID\tname\tscore");
    for(p=head;p!=NULL;p=p->next){
        printf("\n%d\t%s\t%d",p->ID,p->name,p->score);
    }
}
void updata(struct student *head,int ID,int score){
    struct student *p;
    for(p=head;p->next!=NULL;p=p->next){
        if(p->ID==ID)   break;
    }
    if(p->ID==ID){
        p->score=score;
    }else{
        printf("\nNo such student to be updated!\n");
    }
}
struct student *input_file(){
    FILE *fp;
    struct student *p,*head=NULL;
    int ID,score;
    char *file_name,*name;
    int size=sizeof(struct student);
    printf("Please enter the file's name you want to reload:(not include the ""txt"")");
    file_name=scan_name(file_name);
    if((file_name=(char *)realloc(file_name,(strlen(file_name)+5)*sizeof(char)))==NULL){
        printf("ERROR!");
        exit(1);
    }
    strcat(file_name,".txt");
    if((fp=fopen(file_name,"r"))==NULL){
        printf("\nCan not open the file! OR your list donot exist!");
        exit(1);
    }
    fscanf(fp,"ID \tname \tscore\n");
    while(!feof(fp)){
        fscanf(fp,"%d",&ID);
        name=scan_file_name(fp,name);
        fscanf(fp,"%d",&score);
        p = (struct student *)malloc(size);
        p->ID=ID;
        if((p->name=(char*)malloc((strlen(name)+1)*sizeof(char)))==NULL){
            printf("ERROR!");
            exit(1);
        }
        strcpy(p->name,name);
        free(name);
        p->score=score;
        head=insert(head,p);
    }
    fclose(fp);
    free(file_name);
    return head;
}
void output_file(struct student *p){
    FILE *fp;
    char *name;
    printf("\nPlease enter the name of your student list name to be outputed:(not include spacail patten!)\n");
    name=scan_name(name);
    if((name=(char *)realloc(name,(strlen(name)+5)*sizeof(char)))==NULL){
        printf("ERROR!");
        exit(1);
    }
    strcat(name,".txt");
    if((fp=fopen(name,"w"))==NULL){
        printf("\nCan not creat a file!");
        exit(1);
    }
    fprintf(fp,"ID \tname \tscore");
    while(p!=NULL){
        fprintf(fp,"\n%d \t%s \t %d",p->ID,p->name,p->score);
        p=p->next;
    }
    if(fclose(fp)){
        printf("\nCan not close the file!\n");
        exit(1);
    }
    printf("\nthe student list had been created!\n");
    free(name);
}
void freehead(struct student *head){
    struct student *p;
    while(head!=NULL){
        p=head->next;
        free(head);
        head=p;
    }
}