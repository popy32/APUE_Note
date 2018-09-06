
#### 文件列表

- fork.c            验证子进程复制父进程内存空间
- forkPrint.c       fork循环打印与缓冲区之间的关系
- forkLoop.c        创建指定数目的进程
- forkOrp.c         验证孤儿进程的父进程为init进程
- forkZom.c         产生僵尸进程
- forkAvoidZom.c    避免僵尸进程的一种方法


---

#### 思考

Q: fork系统调用之后父子进程的执行顺序

A: fork后子进程创建并加入到就绪队列中等待进程调度，父子进程的执行顺序并不确定(交替执行)

> In general, we never know whether the child starts executing before the parent, or vice
versa. The order depends on the scheduling algorithm used by the kernel. (P230)

---

Q: fork返回两次的实质

A: 两次返回是在父子进程各自的内存空间中分别返回

> The only difference in the returns is that the return value in the child
is 0, whereas the return value in the parent is the process ID of the new child. (P229)

---

Q: 父进程中fork返回值大于零的设计原理

A: 子进程可以通过getppid函数获取父进程的PID，而父进程没有相关的API获取子进程的PID，因此设计父进程通过fork返回值获取子进程PID，方便父进程的管理

> The
reason the child’s process ID is returned to the parent is that a process can have more
than one child, and there is no function that allows a process to obtain the process IDs of
its children. The reason fork returns 0 to the child is that a process can have only a
single parent, and the child can always call getppid to obtain the process ID of its
parent. (Process ID 0 is reserved for use by the kernel, so it’s not possible for 0 to be the
process ID of a child.) (P229)

---

Q: 为什么fork之后而不是父进程main函数的开始

A: fork得到的子进程子进程从父进程的继承了整个进程的地址空间，包括：进程上下文、进程堆栈、内存信息、打开的文件描述符、信号控制设置、进程优先级、进程组号、当前工作目录、根目录、资源限制、控制终端等，而决定子进程运行的起点————程序计数器(PC)属于进程上下文

> The child is a copy of the parent. For example, the child gets a copy of
the parent’s data space, heap, and stack. Note that this is a copy for the child; the parent
and the child do not share these portions of memory. The parent and the child do share
the text segment, however (Section 7.6). (P229)

> Besides the open files, numerous other properties of the parent are inherited by the
child:
• Real user ID, real group ID, effective user ID, and effective group ID
• Supplementary group IDs
• Process group ID
• Session ID
• Controlling terminal
• The set-user-ID and set-group-ID flags
• Current working directory
• Root directory
• File mode creation mask
• Signal mask and dispositions
• The close-on-exec flag for any open file descriptors
• Environment
• Attached shared memory segments
• Memory mappings
• Resource limits (P233)

---

Q: PID为0、1的特殊进程

A: PID为0的进程是调度进程，通常也称为交换进程；PID为1的进程是init进程，在自举过程结束后由内核调用

> Process ID 0 is usually the scheduler process and is often known as
the swapper.Process ID 1 is usually the init process and
is invoked by the kernel at the end of the bootstrap procedure.process ID 2 is the pagedaemon. This process is responsible for
supporting the paging of the virtual memory system. (P228)

---


Q: fork循环打印结果需要注意的地方

A: 标准输出带有行缓冲，如果没有被换行符及时刷新，缓冲区的数据会复制给子进程

> The standard I/O library,
however, is buffered. Recall from Section 5.12 that standard output is line buffered if it’s
connected to a terminal device; otherwise, it’s fully buffered. When we run the
program interactively, we get only a single copy of the first printf line, because the
standard output buffer is flushed by the newline. When we redirect standard output to
a file, however, we get two copies of the printf line. In this second case, the printf
before the fork is called once, but the line remains in the buffer when fork is called.
This buffer is then copied into the child when the parent’s data space is copied to the
child. Both the parent and the child now have a standard I/O buffer with this line in it.
The second printf, right before the exit, just appends its data to the existing buffer.
When each process terminates, its copy of the buffer is finally flushed. (P231)

