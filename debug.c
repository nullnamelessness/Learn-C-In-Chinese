#include <io.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))){
        printf("当前工作目录: %s\n", cwd);
    }
    
    system("pause");
}
