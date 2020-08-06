# 最简单的hello word驱动程序

[TOC]

## 1 前言

​	在前面的文章中已经叙述过开发板中如何运行hello word。接下来本文将讲解如果写一个hello word 驱动程序，此次hello word[驱动程序所依赖的环境](https://blog.csdn.net/qq_43419412/article/details/107355944)已在之前的文章提到，**<font color=red>这里新手要特别注意一定要事先编译好内核，否则编译驱动时出错。</font>**

​	在写驱动前，我们需要明白一点：**<font color=blue>系统调用。</font>**简单来说就是应用层如果调用硬件设备呢？答：**应用层通过open函数调用C库（glibc）,通过swi指令发生异常陷入内核态，根据异常的原因调用处理函数sys_open,然后调用drv_open，此时就是我们的驱动程序了。**

![系统调用](C:\Users\dongkangjia\Desktop\drivers\系统调用.png)

## 2 hello word 驱动

​	在写驱动之前先提几个问题：刚才已经讲解了，系统会调用drv_open,这个驱动是我们自己写出来的，那如何告诉内核呢？

**<font color=green>1.定义一个结构体hello_drv_fops</font>**

```c
static struct file_operations hello_drv_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   hello_open,  
};

```

**<font color=green>2.把这个结构体hello_drv_fops告诉内核，通过register_chrdev函数</font>**

**<font color=green>3.谁来调用register_chrdev函数呢？驱动的入口函数hello_init</font>**

```c
/*把上述的结构体告诉内核，所以要注册*/
static int __init hello_init(void)
{

	register_chrdev(99,"hello_dev",&hello_drv_fops);/*参数依次为主设备号、设备名称、结构体*/
	return 0;
}
```

**<font color=green>4.修饰module_init(hello_init)</font>**

```c
/*修饰*/
module_init(hello_init);
```

有入口函数必然有出口函数呀！那出口函数应该是这样的，可以参考其他驱动程序。

```c
static void __exit hello_exit(void)
{

	unregister_chrdev(99,"hello_dev");/*参数依次为主设备号、设备名称*/
	return 0;
}
module_exit(hello_exit);
```

​	**<font color=red>这里我们要实现drv_open了，就是打印hello word</font>**

```c
static int hello_open(struct inode *inode, struct file *file)
{
	printk("hello word!\n");
	return 0;
}
```

​	还有一个要注意的就是要加上许可证，是一个开源许可，不然编译会出错！

```c
/*许可证*/
MODULE_LICENSE("GPL");
```

​	这样我们的驱动程序就写完了，合在一起应该是这样的：

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

static int hello_open(struct inode *inode, struct file *file)
{
	printk("hello word!\n");
	return 0;
}

static struct file_operations hello_drv_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   hello_open,  
};

/*把上述的结构体告诉内核，所以要注册*/
static int __init hello_init(void)
{

	register_chrdev(99,"hello_dev",&hello_drv_fops);/*参数依次为主设备号、设备名称、结构体*/
	return 0;
}

static void __exit hello_exit(void)
{

	unregister_chrdev(99,"hello_dev");/*参数依次为主设备号、设备名称*/
	return 0;
}

/*修饰*/
module_init(hello_init);
module_exit(hello_exit);

/*许可证*/
MODULE_LICENSE("GPL");

```

## 3 驱动程序的makefile

​	这个makefile可以参考内核中的makfile

```shell
KERN_DIR = /work/system/linux-2.6.22.6

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= arm_hello.o
```

## 4 测试程序的编写

​	测试程序就是用于打开hello驱动设备的程序，如下：

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	int fd;
	int val = 1;
	fd = open("/dev/xyz", O_RDWR);//根据自己的设备名称
	if (fd < 0)
	{
		printf("can't open!\n");
	}
	return 0;
}
```

## 5 驱动程序的测试

​	首先将刚才编写的三个文件arm_hello.c  hello_test.c  Makefile上传到虚拟机上，进行编译驱动程序。

![1](C:\Users\dongkangjia\Desktop\drivers\1.png)

​	在编译测试程序,生成hello程序

```shell
arm-linux-gcc -o hello hello_test.c
```

![2](C:\Users\dongkangjia\Desktop\drivers\2.jpg)

​	将编译好的驱动程序和测试程序通过网络文件系统拷贝到开发板子上，创建设备节点，加载驱动，运行测试程序。

```shell
mknod /dev/xyz c 99 0
insmod arm_hello.ko
./hello
```

![4](C:\Users\dongkangjia\Desktop\drivers\4.png)

**<font color=red>	这里设备节点是我们自己创建的制定的，设备号也是在驱动中写死的，那能不能自动创建设备文件，自动生成设备信息呢？答案是可以的，下一篇文章的led点灯驱动讲解，同时写完hello驱动，字符驱动设备的基础框架我们就已经清楚了，然后在慢慢学习复杂的驱动程序，一起学习，一起进步，加油！！！。</font>**