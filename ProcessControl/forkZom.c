//    Filename:     forkZom.c
//    Description:  make a zoobie processes
//    Version:      1.0.0(2018/9/2 18:57:19)
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
output:
    ubuntu@VM-227-108-ubuntu:~$ ps -ef | grep defunc | grep -v grep
    ubuntu    3409  3408  0 19:39 pts/0    00:00:00 [a.out] <defunct>
*/

int main() {
    pid_t pid;
    pid = fork();
    if(pid == -1) {
        perror("fork error");
        return -1;
    }

    if(0 == pid) {
        printf("pid = %d ppid = %d\n", getpid(), getppid());
        // 子进程调用exit() 直到父进程处理子进程退出的状态才完全退出
        exit(0);
    }

    if(pid > 0) {
        // 父进程打呼噜时不管子进程死活
        sleep(10);
        printf("parent %d exit\n", getpid());
        exit(0);
    }
    return 0;
}