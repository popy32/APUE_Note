//    Filename:     forkPrint.c
//    Description:  fork and std i/o buffer
//    Version:      1.0.0(2018/9/6 16:07:09)
//    Author:       Pan Lin <740502708@qq.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
将循环拆开来看 并且假设主进程的PID为k1
第一次fork:
    两个进程k1和k2

第一次printf:
    k1和k2均往缓冲区写入"-"

第二次fork:
    k1继续产生k3 而k2产生k4
    k3, k4的缓冲区里复制k1k2的数据(参考README里的Q/A)
    此时每个进程的缓冲区都含有一个"-"

第二次printf:
    k1, k2, k3, k4均往缓冲区写入"-"
    此时每个进程的缓冲区都含有两个"-"

main函数调用return 0等同于exit()
exit()作为标准库函数会执行收尾工作(刷新缓冲区等)和系统调用_exit()

因此最后输出8个"-"
*/

int main() {
    for(int i = 0; i < 2; i ++) {
        fork();
        printf("-");
    }
    return 0;
}
