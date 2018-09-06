//    Filename:     fork.c
//    Description:  fork api in apue
//    Version:      1.0.0(2018/9/6 15:28:19)
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

int main() {
    pid_t pid;
    printf("before fork: pid = %d\n", getpid());
    
    int a = 10;
    pid = fork();

    if(pid == -1) {
        perror("fork error");
        return -1;
    }

    // 子进程复制了父进程的整个地址空间
    if(0 == pid) {
        // a == 11
        a ++;
        printf("child %d: ppid = %d, a = %d\n", getpid(), getppid(), a);
    }

    if(pid > 0) {
        // a == 9
        a --;
        printf("parent %d: a = %d\n", getpid(), a);
        wait(NULL);
    }

    return 0;
}
