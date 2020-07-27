# 栈和队列（C语言实现）

[TOC]

## 栈的原理

​	栈的原理，我觉着通过图的解释可能更为好理解。可以想象到一个饼干盒，当手上有多余的饼干不吃的时候要把它放回去，放回去之后，最先放进去的在饼干盒底下，最后放入的在饼干盒顶部，很明显你要想拿到最底下的饼干只要，把上面的饼干一个个取出来之后才能取到最底下的。**<font color=red>所以栈的原理也是这样，只能访问栈定的元素，不能直接访问其他元素。</font>**![栈的原理图](C:\Users\dongkangjia\Desktop\栈的原理图.png)

## 栈的实现

​	参考C++中容器stack的接口函数，我们也写出相应的函数，便于操作栈这种数据结构，所以我们要实现以下几个函数，发现他们都是通过对象，调用成员函数实现的，**<font color=red>所以我们借助于结构体和函数指针实现。</font>**本文通过多文件编写形式，其中**<font color=#008000>mystack.h文件是一些成员变量的定义和函数的定义 </font>**    **<font color=blue>mystack.c文件用于函数的实现。</font>**

```
/* 参考C++容器中栈的函数接口，然后使用C语言创建对应的数据结构
 * 1.stack.push(); //往栈头添加元素
 * 2.stack.pop();      //从栈头移除第一个元素
 * 3.stack.top();      //返回栈顶元素
 * 4.stack.empty();    //判断堆栈是否为空
 * 5.stack.size();     //返回堆栈的大小
 */
```

​	首先，构建一个链表的数据结构，用于存储栈中的数据：

```c
typedef struct listnode{
    struct listnode *next;
    int val;
}listnode;
```

​	然后构建栈的结构体，其中函数指针指向具体实现操作的函数即可，在使用之前调用init函数，然后使用结构体中的函数指针即可完成栈的相关操作。

```c
typedef struct mystack{
    int (*pop)(void);//函数指针，指向对应的函数
    int (*top)(void);
    int (*empty)(void);
    int (*size)(void);
    int (*push)(int);
    listnode head;
} mystack;
```

​	首先看以下 **<font color=blue>mystack.h文件</font>**

```c
#ifndef MYSTACK_H
#define MYSTACK_H

/* 参考C++容器中栈的函数接口，然后使用C语言创建对应的数据结构
 * 1.stack.push(); //往栈头添加元素
 * 2.stack.pop();      //从栈头移除第一个元素
 * 3.stack.top();      //返回栈顶元素
 * 4.stack.empty();    //判断堆栈是否为空
 * 5.stack.size();     //返回堆栈的大小
 */
 int stack_pop(void);
 int stack_top(void);
 int stack_push(int x);
 int stack_empty(void);
 int stack_size(void);

/*链表数据节点*/
typedef struct listnode{
    struct listnode *next;
    int val;
}listnode;

typedef struct mystack{
    int (*pop)(void);
    int (*top)(void);
    int (*empty)(void);
    int (*size)(void);
    int (*push)(int);
    listnode head;
} mystack;

 mystack stack;

 int stack_init(void);

#endif // MYSTACK_H
```

​	看一下 **<font color=red>mystack.c文件</font>**

```c
#include"mystack.h"
#include<stdio.h>
#include<stdlib.h>

/*栈的初始化*/
int stack_init(void)
{
    stack.pop=stack_pop;
    stack.top=stack_top;
    stack.push=stack_push;
    stack.empty=stack_empty;
    stack.size=stack_size;
    stack.head.next=NULL;
    stack.head.val=0;


    return 0;
}

/*删除栈的首个元素*/
int stack_pop(void)
{
    if(stack.head.val==0)
    {
        printf("the stack is empty\n");
        exit(-1);
    }
    else
    {
        listnode *p=stack.head.next;
        stack.head.next=stack.head.next->next;
        free(p);
        stack.head.val--;
    }
    return 0;
}

/*返回的首个元素*/
int stack_top(void)
{
    if(stack.head.val==0)
    {
        printf("the stack is empty\n");
        exit(-1);
    }
    else
    {
        return stack.head.next->val;
    }
}
/*栈中添加元素*/
int stack_push(int x)
{
    if(stack.head.val==0)
    {
        stack.head.next=(listnode *)malloc(sizeof (listnode));
        stack.head.next->val=x;
        stack.head.next->next=NULL;
        stack.head.val++;
    }
    else
    {
        /*使用头插法向链表中插入元素*/
        listnode *p=(listnode *)malloc(sizeof (listnode));
        p->val=x;
        p->next=stack.head.next;
        stack.head.next=p;
        stack.head.val++;
    }
    return 0;
}

/* stack_empty为空时返回1，否则返回0 */
int stack_empty(void)
{
    if(stack.head.val==0)
        return 1;
    else
        return 0;
}
/*返回栈的大小*/
int stack_size(void)
{
    return stack.head.val;
}
```

## 队列的原理

​	队列，顾名思义，很好的可以理解为一个正在排队的队伍，在排队打饭，新来的人要站在队伍后面（入队），打完饭的人就离开队伍（出队），看下面这张图应该可以很好的理解，**<font color=red>队列在内核中使用还是挺频繁的，</font>**尤其是休眠唤醒，异步通知，线程什么的。

![队列的原理图](C:\Users\dongkangjia\Desktop\队列的原理图.png)

## 队列的实现

​	参考C++中容器queue的接口函数，我们也写出相应的函数，便于操作队列这种数据结构，所以我们要实现以下几个函数，发现他们都是通过对象，调用成员函数实现的，**<font color=red>所以我们借助于结构体和函数指针实现。</font>**本文通过多文件编写形式，其中**<font color=#008000>myqueue.h文件是一些成员变量的定义和函数的定义 </font>**    **<font color=blue>myqueue.c文件用于函数的实现。</font>**

```
/* 参考C++容器中栈的函数接口，然后使用C语言创建对应的数据结构
 * queue.back() 返回最后一个元素
 * queue.empty() 如果队列空则返回真
 * queue.front() 返回第一个元素
 * queue.pop() 删除第一个元素
 * queue.push() 在末尾加入一个元素
 * queue.size() 返回队列中元素的个数
 */
```

​		首先，和栈一样，构建一个链表的数据结构，用于存储队列中的数据：

```c
typedef struct listnode{
    struct listnode *next;
    int val;
}listnode;
```

​	然后构建队列的结构体，其中函数指针指向具体实现操作的函数即可，在使用之前调用init函数，然后使用结构体中的函数指针即可完成队列的相关操作。

```c
typedef struct myqueue{
    int (*back)(void);
    int (*front)(void);
    int (*pop)(void);
    int (*empty)(void);
    int (*size)(void);
    int (*push)(int);
    listnode *end; //指向队首的指针
    listnode head; //队尾的前一个节点
} myqueue;
```

​	首先看以下 **<font color=blue>myqueye.h文件</font>**

```c
#ifndef MYQUEUE_H
#define MYQUEUE_H

/* 参考C++容器中栈的函数接口，然后使用C语言创建对应的数据结构
 * queue_back 返回最后一个元素
 * queue_empty 如果队列空则返回真
 * queue_front 返回第一个元素
 * queue_pop 删除第一个元素
 * queue_push 在末尾加入一个元素
 * queue_size 返回队列中元素的个数
 */
 int queue_back(void);
 int queue_front(void);
 int queue_push(int x);
 int queue_empty(void);
 int queue_size(void);
 int queue_pop(void);



typedef struct listnode{
    struct listnode *next;
    int val;
}listnode;


typedef struct myqueue{
    int (*back)(void);
    int (*front)(void);
    int (*pop)(void);
    int (*empty)(void);
    int (*size)(void);
    int (*push)(int);
    listnode *end;
    listnode head;
} myqueue;

 myqueue queue;

 int queue_init(void);

#endif // MYQUEUE_H
```

看一下 **<font color=red>myqueue.c文件</font>**

```c
#include"myqueue.h"
#include<stdio.h>
#include<stdlib.h>


/*对队列的初始化*/
int queue_init(void)
{
    queue.pop=queue_pop;
    queue.back=queue_back;
    queue.push=queue_push;
    queue.size=queue_size;
    queue.empty=queue_empty;
    queue.front=queue_front;


    queue.head.next=NULL;
    queue.head.val=0;
    queue.end=NULL;

    return 0;
}
/*返回队尾部元素*/
int queue_back(void)
{
    if(queue.head.next==NULL)
    {
        printf("queue is empty\n");
        exit(-1);
    }
    return queue.head.next->val;
}
/*返回队首部元素*/
int queue_front(void)
{
    if(queue.head.next==NULL)
    {
        printf("queue is empty\n");
        exit(-1);
    }
    return queue.end->val;
}
/*往队列添加元素*/
int queue_push(int x)
{

    if(queue.head.next==NULL)
    {
        listnode *p=(listnode *)malloc(sizeof (listnode));
        p->val=x;
        p->next=NULL;
        queue.head.next=p;
        queue.end=p;
    }
    else
    {
        listnode *p=(listnode *)malloc(sizeof (listnode));
        p->val=x;
        p->next=queue.head.next;
        queue.head.next=p;
    }
    return 0;
}
/*队列是否为空，空返回1，不为空返回0*/
int queue_empty(void)
{
    return queue.head.val==0;
}

/*返回队列的有多少元素*/
int queue_size(void)
{
    return queue.head.val;
}

/*删除队列首个元素*/
int queue_pop(void)
{
    if(queue.head.next==NULL)
    {
        printf("queue is empty\n");
        exit(-1);
    }
    listnode *p=queue.head.next;
    while(p->next!=queue.end)
    {
        p=p->next;
    }
    queue.end=p;
    free(p->next);
    return 0;
}
```

