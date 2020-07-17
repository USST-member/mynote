# arm开发板子运行helloword

[TOC]

## 1.uboot的编译

​	这里已经安装好了交叉编译工具链，如果自己的电脑下没有，请自行百度安装。将下载好uboot到linux下，进行解压-->打补丁-->编译-->烧写，执行以下命令完成上述四个步骤<font color=red>（不同的开发板在下载u-boot之后，进行打补丁操作）</font>,编译完成，u-boot.bin文件烧写到开发板即可。

```shell
tar -jvxf u-boot-1.1.6.tar.bz2
cd ./u-boot-1.1.6
patch -p1 < ../ u-boot-1.1.6_jz2440.patch
make   100ask24x0_config 
make CROSS_COMPILE=/work/tools/gcc-3.4.5-glibc-2.3.6/bin/arm-linux- smdk2440_config
make -j4
```

![uboot编译完成](C:\Users\dongkangjia\Desktop\笔记\jz2440系统\uboot编译完成.jpg)

## 2.linux内核的编译

​	同样，将下载好的内核包进行以下操作：解压-->打补丁-->配置内核-->编译，执行以下命令完成对应的操作。<font color=red>（执行make menuconfig时会出现配置内核的界面，根据自己的需要进行配置）</font>

```shell
tar -jvxf linux-2.6.22.6.tar.bz2
cd linux-2.6.22.6
patch -p1 < ../linux-2.6.22.6_jz2440.patch
make s3c2410_defconfig
cp config_ok .config
make menuconfig CROSS_COMPILE=/work/tools/gcc-3.4.5-glibc-2.3.6/bin/arm-linux- ARCH=arm -j4
make uImage CROSS_COMPILE=/work/tools/gcc-3.4.5-glibc-2.3.6/bin/arm-linux- ARCH=arm -j4

```

编译过程中遇到了错误是按照如下解决，如果遇到其他错误请自行解决

![编译内核出错解决办法](C:\Users\dongkangjia\Desktop\笔记\jz2440系统\编译内核出错解决办法.jpg)

​	最后编译完成。

![内核编译完成](C:\Users\dongkangjia\Desktop\笔记\jz2440系统\内核编译完成.jpg)

​	生成的uImage在下图中路径。烧写到开发板中即可。

​	![](C:\Users\dongkangjia\Desktop\笔记\jz2440系统\uImage位置.jpg)

## 3.文件系统的制作

​	一般开发板的厂商会提供文件系统，你可以自行烧写对应的文件系统，这里自己制作一个最小文件系统。制作之前应该了解最小文件系统由什么组成。<font color=red>最小根文件系统封需要5个要求：</font>

| 1    | busybox--ls、cp等命令的集合       |
| ---- | --------------------------------- |
| 2    | 两个设备：/dev/console  /dev/null |
| 3    | /etc/inittab配置文件              |
| 4    | C库                               |
| 5    | 配置指定的运行程序                |

### 3.1 制作busybox

​	busybox其实就是linux下ls、cd等一些基本命令的集合，所以要编译它进行操作。对应操作：解压-->配置-->编译-->安装，分别对应以下命令。

```shell
tar -jvxf busybox-1.7.0_patch.tar.bz2 
tar -vxf busybox-1.7.0.tar.bz2
cd busybox-1.7.0
make menuconfig CROSS_COMPILE=/work/tools/gcc-3.4.5-glibc-2.3.6/bin/arm-linux- ARCH=arm -j4
make CROSS_COMPILE=/work/tools/gcc-3.4.5-glibc-2.3.6/bin/arm-linux- ARCH=arm -j4
make CONFIG_PREFIX=/home/book/nfsroot/busybox install
```

**出现错误**

/opt/FriendlyARM/toolschain/4.4.3/arm-none-linux-gnueabi//sys-root/usr/include/linux/netfilter.h:56: error: field 'in6' has incomplete type
ipsvd/tcpudp.c: In function 'tcpudpsvd_main':
ipsvd/tcpudp.c:314: warning: ignoring return value of 'write', declared with attribute warn_unused_result
scripts/Makefile.build:192: recipe for target 'ipsvd/tcpudp.o' failed
make[1]: *** [ipsvd/tcpudp.o] Error 1
Makefile:701: recipe for target 'ipsvd' failed
make: *** [ipsvd] Error 2
make: *** Waiting for unfinished jobs....
make: *** wait: No child processes.  Stop.

解决：下载的交叉编译库中有个头文件中的 in 和 in6 类型不对，解决的方法（亲自测试）：
在 …/arm-none-linux-gnueabi/libc/usr/include/linux/netfilter.h 的开头
添加缺少的头文件：
#include <netinet/in.h>



iptunnel.c:(.text.print_tunnel+0x290): more undefined references to `__cpu_to_be16' follow
collect2: ld returned 1 exit status
Makefile:678: recipe for target 'busybox_unstripped' failed
make: *** [busybox_unstripped] Error 1

解决：在该目录下的 vim networking/libiproute/iptunnel.c 文件中加入#include <asm/byteorder.h>

最后成功编译的busybox

![busybox安装成功](C:\Users\dongkangjia\Desktop\笔记\jz2440系统\busybox安装成功.jpg)

### 3.2 创建设备文件

​	这两个设备文件可以理解为内核启动的第一个程序<font color=red>console：其实就是命令窗口</font>

```shell
mkdir dev
cd dev/
sudo mknod console c 5 1
sudo mknod null c 1 3
```

### 3.3 创建ect/inittab配置文件

```shell
mkdir etc
cd etc/
vi inittab
console::askfirst:-/bin/sh
```

### 3.4 配置C库

​	将编译器的C库拷贝到根文件系统目录下的库文件/lib中，<font color=red>是交叉编译的C库</font>

```shell
mkdir lib
cp /work/tools/gcc-3.4.5-glibc-2.3.6/arm-linux/lib/so* /work/nfs_root/lib/ -d
```

![C库1](C:\Users\dongkangjia\Desktop\笔记\jz2440系统\C库1.jpg)

![C库2](C:\Users\dongkangjia\Desktop\笔记\jz2440系统\C库2.jpg)

### 3.4制作文件系统

​	此次将文件系统制作为yaffs文件系统，下载制作工具，拷贝到linux，然后给制作工具附加执行权限，制作完毕之后烧写到开发板中即可。

```shell
sudo cp ./mkyaffs2image  /usr/local/bin
chmod +x /usr/local/bin/mkyaffs2image
mkyaffs2image nfs_root nfs_root.yaffs2
```

​	此时，开发板系统已经能正常运行。

![系统起来](C:\Users\dongkangjia\Desktop\笔记\jz2440系统\系统起来.jpg)

### 3.6 设置开发板的ip

​	此时系统已经跑起来了，为了方便接下来的操作，将自己虚拟机的文件挂载到开发板中，先配置ip，根据自己的电脑和虚拟机中，自行设置，但是一定要处于同一网络，然后让三者相互ping通即可。

```shell
ifconfig eth0 192.168.43.20
```

### 3.7 挂载网络文件系统

​	下面两个命令都可以挂载虚拟机下的文件夹，但是当进行大量传输文件到开发板时，第一种挂载会出现错误，所以建议使用第二种挂载命令。<font color=red>建议使用第二种挂载命令</font>

```shell
mount -t nfs -o nolock 192.168.43.175:/work/nfs_root /mnt
mount -t nfs -o intr,nolock,rsize=1024,wsize=1024 192.168.43.61:/work/nfs_root /mnt
```

## 4.运行helloword程序

​	首先在自己的linux下创建main.c，然后进行交叉编译生成开发板的可执行文件，放入开发板中执行。

```c
  1 #include<stdio.h>
  2 int main(int argv,char **argc)
  3 {
  4         printf("hello word");
  5         return 0;
  6 }

```

​	创建完之后，进行编译，执行结果

```shell
arm-linux-gcc -static -o a.out main.c
```

![hello运行](C:\Users\dongkangjia\Desktop\笔记\jz2440系统\hello运行.png)

