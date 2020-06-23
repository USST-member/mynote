# Qt之多线程编程笔记

[TOC]

## 1 程序、进程、线程的相关概念

​	什么是程序？什么是进程？什么是线程？程序和进程有什么关系？线程和进程之间的关系？

​	程序是计算机存储系统中的数据文件，源代码程序：文本文件，描述程序行为和功能；可执行程序：二进制文件，直接加载并且执行。

​	进程的广义概念：程序关于某一个数据几个的一次运行活动；狭义概念：程序被加载到内存中执行后得到的进程。

​	线程的概念：进程内的一个执行单元，操作系统中一个可调度的实体，进程中相对独立的一个控制流序列，执行时的现场数据和其调度的所需信息。

**程序和进程的关系：**程序时硬盘中静态文件--存储系统中的一段二进制表示；进程时内存中动态的运行实体：数据段、代码段、PC指针等；一个程序可能对应多个线程--一个程序多次运行，每次运行产生一个进程；一个进程可能包含多个程序--一个程序依赖多个其他动态库。

**进程和线程的关系：**进程中可以存在多个线程共享进程资源；线程是被调度的执行单元，而进程不是调度单元，线程不能脱离进程单独存在，只能依赖于进程运行；线程由生命周期，有诞生和死亡，任意线程都可以创建其他新的线程。

​	**当代操作系统中，资源分配的基本单位是进程，而CPU调度执行的基本单位时线程，进程中多个线程并行执行，共享进程资源。**

## 2 Qt中多线程的使用（QThread）

### 2.1 类中函数简介

​	Qt中通过QThread直接支持多线程，Qt中的线程以对象的形式被创建和使用，每一个线程对应着一个QThread对象。

| **类中所使用到的基本函数** | **函数功能**                           |
| -------------------------- | -------------------------------------- |
| void run()                 | 线程体函数，用于定义线程功能（执行流） |
| void start()               | 启动函数，将线程入口地址设置为run函数  |
| void terminate()           | 强制结束线程（不推荐使用）             |

### 2.2 线程的生命周期

![线程生命周期](C:\Users\dongkangjia\Desktop\笔记\线程生命周期.png)

​	在工程开发中terminate()是进制使用的，此函数会使得操作系统暴力终止线程，而不会考虑数据完整性、资源释放等问题。那如何优雅的终止线程呢？在线程类中增加标志量stop(volatile bool),通过stop的值判断是否需要从run()函数返回。

### 2.3 多线程并发代码示例

```c++
#include <iostream>
#include <QApplication>
#include<QDebug>
#include<QThread>

class q1 : public QThread
{
protected:
    void run()
    {
        qDebug()<<this->objectName()<<"begin()";
        for(int i=0;i<10;i++)
        {
            qDebug()<<i;
        }
        qDebug()<<this->objectName()<<"end()";
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    q1 i,j;
    i.setObjectName("i");
    j.setObjectName("j");
    i.start();
    j.start();
    return a.exec();
}
```

## 3 多线程间的同步

### 3.1 同步的相关概念

**同步的概念：**在特殊情况下，控制多线程间的相对执行顺序（QThread类直接支持线程间的同步wait()）wait()函数停止当前线程的执行，等待目标线程的执行结束。	

​	***线程间总是完全独立，毫无依赖的吗？***

​	在特殊情况下，多线程的执行在时序上存在依赖，如吃饭这件事，煮饭、炒菜、吃，这三件事情并发执行的话存在一个时许的问题，也就是吃必须要等待煮饭和炒菜都完成了，才能吃。

![多线程同步的问题](C:\Users\dongkangjia\Desktop\笔记\多线程同步的问题.png)

### 3.2 同步的代码展示

```c++
#include <iostream>
#include <QApplication>
#include<QDebug>
#include<QThread>

class q1 : public QThread
{
protected:
    void run()
    {
        qDebug()<<this->objectName()<<"begin()";
        for(int i=0;i<10;i++)
        {
            qDebug()<<i;
        }
        qDebug()<<this->objectName()<<"end()";
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    q1 i,j;
    i.setObjectName("i");
    j.setObjectName("j");
    i.start();
    i.wait();
    j.start();
    return a.exec();
}
```



## 4 多线程间的互斥

### 4.1 互斥的相关概念

​	多线程除了在时序上可能产生依赖，在其他方面是否也可能产生依赖呢？

**临界资源：**每次只允许一个线程进行访问（读/写）的资源。

**多线程间的互斥：**多个线程在同一时刻都需要访问临界资源。

​	如何保证多线程并发执行的时候，只有一个线程访问临界资源呢？

​	生活中的例子：红绿灯中间的区域可以理解为临界资源，前后方向和左右方向的车辆可以理解为两个线程，都需要经过公共区域，红绿灯起到了一个信号，让哪一个车过，QT中使用QMutex来充当这个信号，保护临界资源。

**线程锁QMutex**

| QMutex中的成员函数 | 功能                                                         |
| ------------------ | ------------------------------------------------------------ |
| void lock()        | 当锁空闲时，获取锁并继续执行；当锁被获取时，阻塞并等待锁释放 |
| void unlock()      | 释放锁                                                       |

​	用于保护临界资源，线程只有获取锁之后才能访问临界资源，锁被其他线程获取时，当前线程进入等待状态，同一把锁的获取和释放必须在同一个线程中成对出现，如果QMutex在调用unlock（）时处于空闲状态，那么程序的行为是未定义的。

### 4.2 线程的死锁概念

​	程序有多少临界资源？需要多少把线程锁？

**死锁：**线程间相互等待临界资源，而造成彼此无法继续执行。

​		——系统中存在多个临界资源但临界资源不可抢占。

​		——线程需要多个临界资源才能继续执行。

**死锁的避免：**对所有的临界资源都分配一个唯一的序号，对应的线程锁也分配唯一的序号，系统中每一个线程按照严格递增的次序请求资源。



### 4.3 多线程的信号量

**信号量：**信号量是特殊的线程锁，信号量允许N个线程同时访问临界资源，信号量允许N个线程同时访问临界资源，Qt中直接支持信号量（QSemaphore）

```c++
QSemaphore sem(1);
sem.acquire();
//do something
sem.release;
```

​	QSemaphore对应中维护了一个整型值，acquire()使得该值减1，release()使得该值加1,当该值为0时，acquire()函数将阻塞当前线程。

### 4.4 互斥的代码展示

​	如果不加锁的话，运行会出错；

```c++
#include <iostream>
#include <QApplication>
#include<QDebug>
#include<QThread>
#include<QMutex>
#include<QSemaphore>

static QString str;
static QMutex lock;
static QSemaphore sem(1);

class q1 : public QThread
{
protected:
    void run()
    {
        qDebug()<<this->objectName()<<"begin()";
        while(true)
        {
            lock.lock();//sem.acquire();
            str.append("1");
            lock.unlock();//sem.release;
            sleep(1);
            qDebug()<<str;
        }
        qDebug()<<this->objectName()<<"end()";
    }
};
class q2 : public QThread
{
protected:
    void run()
    {
        qDebug()<<this->objectName()<<"begin()";
        while(true)
        {
            lock.lock();//sem.acquire();
            str.clear();
            lock.unlock();//sem.release;
            sleep(1);
        }
        qDebug()<<this->objectName()<<"end()";
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    q1 i;
    q2 j;
    q2 k;
    i.setObjectName("i");
    j.setObjectName("j");
    k.setObjectName("k");
    k.start();
    i.start();
    j.start();
    return a.exec();
}
```



## 5 多线程中的信号与槽

### 5.1 线程对象依附性问题

​	通过信号可以知道线程的状态，操作系统通过整形标识管理进程和线程，进程拥有全局唯一的ID值（PID），线程有进程内唯一的ID值（TID)。QThread中的关键静态成员函数currentThread()获取进程号，currentThreadId()获取线程值。

​	默认情况下，对象依附于自身被创建的线程，槽函数在其所依附的线程中被调用执行。Qobject::moveToThread用于改变对象的线程依附性，使得对象的槽函数在依附的函数中调用执行。

​	**线程中的事件循环：**QThread类中提供的exec()函数用于开启线程的事件循环，只有时间循环开启，槽函数才能在信号发送后调用。事件循环结束前，exec()后的语句无法执行,quit()和exit()函数用于结束事件循环。事务性操作、间断性IO操作等可以开启线程的事件循环，每次操作通过发送信号的方式使得槽函数在线程中执行。

### 5.2 信号与槽的连接方式

​	connect()函数是5个参数，但是平时使用时只是用4个参数，是因为有一个默认参数，且如果一个槽函数两次连接两次，当接收到信号时，槽函数就会执行两次。

| 槽函数连接方式                           | 功能解读                                                     |
| ---------------------------------------- | ------------------------------------------------------------ |
| Qt::DirectConnection(立即调用)           | 直接在发送信号的线程中调用槽函数，等价于槽函数的实时调用。   |
| Qt::QueuedConnection（异步调用）         | 信号发送至目标线程的事件队列，由目标线程处理当前线程继续向下执行。 |
| Qt::BlockingQueuedConnection（同步调用） | 信号发送至目标线程的事件队列，由目标线程处理当前线程等待槽函数返回，之后继续向下执行。目标线程与当前线程必须不同。 |
| Qt::AutoConnection（默认连接）           | 根据对象的依附性判断是直接调用还是异步调用。                 |
| Qt::UniqueConnection（单一连接）         | 功能与默认连接相同，自动确定连接类型，但是同一个信号与同一个槽函数之间只有一个选择。 |

### 5.3 线程对象的生命周期

​	QThread对象的生命周期与对应的线程生命周期是否一致？

**多线程设计的原则：**线程对象生命周期>对应的线程生命周期、

**同步型线程设计：**线程对象主动等待线程生命周期结束后才销毁。

——同时支持在栈空间和堆空间中创建线程对象

——对象销毁时确保线程生命周期结束

——在析构函数中调用wait()函数，强制等到线程运行结束

——线程生命周期相对较短的情形

**异步型线程设计：**线程生命周期结束时通知销毁线程对象。

——只能在堆中创建线程对象没有任何实际意义

——线程对象不能被外界主动销毁

——在run（）函数中最后调用deleteLater()函数，线程函数中的申请销毁线程对象

——线程生命周期不可控，需要长时间运行于后台的情形

### 5.4 另一种创建线程的方式

通过继承的的方式实现多线程没有任何实际意义，那如何灵活的指定一个线程对象的线程入口？

​	<font color=#008000>在类中定义一个槽函数作为线程入口函数</font>

​	<font color=#008000>在类中定义一个QThread成员对象m_thread</font>

​	<font color=#008000>改变当前对象的线程依附性到m_thread</font>

​	<font color=#008000>连接m_thread的start()信号到入口函数。</font>



**GUI系统设计原则：**所有界面逐渐的操作都只能在主线程中完成，因此主线程也叫做UI线程。子线程如何对界面组件进行更新？

​	<font color=#008000>在子线程中定义界面组件的更新信号</font>

​	<font color=#008000>在主窗口类中定义更新界面组件的槽函数</font>

​	<font color=#008000>使用异步方式连接更新信号到槽函数</font>

​	<font color=#008000>子线程通过发射信号的方式更新界面组件，所有的界面组件对象只能依附于主线程</font>