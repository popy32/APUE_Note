//    Filename:     forkLoop.c
//    Description:  Create specified number of processes
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

int main() {
    int procNum = 0;
    int loopNum = 0;
    printf("enter process nums: \n");
    scanf("%d", &procNum);
    printf("enter loop nums in every process: \n");
    scanf("%d", &loopNum);
    for(int i = 1; i <= procNum; i ++) {
        pid_t pid;
        pid = fork();
        if(pid == 0) {
            for(int j = 1; j <= loopNum; j ++) {
                printf("pid:%d  print %2d\n", getpid(), j);
            }
            // 结束子进程
            exit(0);
        }
    }
    while(1) {
        // 等待子进程退出 wait为可中断睡眠
        int ret = wait(NULL);
        if(ret == -1) {
            // 被其他中断打断
            if(errno == EINTR) {
                continue;
            }
            // 处理完SIGCHLD
            break;
        }
    }
    return 0;
}
