#include <stdio.h>
#include <string.h>
int main(){
    char ch;
    int first=1,k;
    //scanf("%d",&k);
    for(k=1;k<=8;k++){
        ch=getchar();
        if(first==1){
            putchar(ch);
            first=0;
        }else{
            putchar('-');
            putchar(ch);
        }
    }
    return 0;
}

// #include <stdio.h>
// #include <conio.h>  // Windows专用头文件

// int main() {
//     char ch;
//     int first = 1, k;

//     for(k = 1; k <= 8; k++) {
//         ch = _getch();  // 无缓冲输入函数
//         if(first) {
//             putchar(ch);
//             first = 0;
//         } else {
//             putchar('-');
//             putchar(ch);
//         }
//         fflush(stdout);
//     }
//     return 0;
// }