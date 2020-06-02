### Qt交叉编译移植arm开发板

[TOC]

## 1 环境介绍

linux             ---------------------------------------------------            Ubuntu16.04                      ------------------            [下载地址](http://releases.ubuntu.com/)

交叉编译链  ---------------------------------------------------            arm-linux-gcc-4.4.3           ------------------            [下载地址](http://www.arm9.net/download.asp)

Qt版本          ---------------------------------------------------            Qt5.13.0                              ------------------            [下载地址](http://download.qt.io/archive/qt/)

Qt源码         ----------------------------------------------------            Qt5.6.0                                ------------------            [下载地址](http://download.qt.io/archive/qt/)

tslib版本      ----------------------------------------------------            tslib1.9                                ------------------            [下载地址](https://github.com/libts/tslib/releases?after=1.10)



## 2 交叉编译链的安装

​	1.首先上传到虚拟机进行解压

```shell
 sudo tar zxvf arm-linux-gcc-4.4.3.tar.gz -C / 
```

​	2.添加环境变量

```shell
 sudo vi /etc/profile
```

​	在打开的文件中添加：export PATH=/opt/FriendlyARM/toolschain/4.4.3/bin:$PATH

​	<font color=red>注：/opt/FriendlyARM/toolschain/4.4.3/bin为交叉编译链所在路径</font>

​	3.是环境变量添加到路径

```shell
source /etc/profile
```



## 3 tslib库的安装

​	1.对源码包进行解压

```shell
tar zxvf tslib-1.9.tar.gz
```

​	2.创建tslib库的安装路径

```shell
sudo mkdir -p /usr/local/tslib
```

  3.进入解压库中配置执行以下命令<font color=red>(三步命令)</font>

```shell
  cd tslib
  
  ./autogen.sh
  
  
./configure --host=arm-linux ac_cv_func_malloc_0_nonnull=yes CC=/opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-gcc CXX=/opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-g++  -prefix=/usr/local/tslib
```

​	4.编译

```shell
make -j4
```

​	5.安装

```shell
make install
```



## 4 Qt源码的交叉编译

​	1.对Qt源码包进行解压

```shell
tar zxvf qt-everywhere-opensource-src-5.6.0.tar
```

2. 创建安装路径

   ```shell
   sudo mkdir -p /usr/local/Qt
   ```

3.配置qt-everywhere-opensource-src-5.6.0/qtbase/mkspecs/linux-arm-gnueabi-g++/qmake.conf文件

```shell
#
# qmake configuration for building with arm-linux-gnueabi-g++
#

MAKEFILE_GENERATOR      = UNIX
CONFIG                 += incremental
QMAKE_INCREMENTAL_STYLE = sublib

QMAKE_INCDIR=/usr/local/tslib/include/
      QMAKE_LIBDIR=/usr/local/tslib/lib/

include(../common/linux.conf)
include(../common/gcc-base-unix.conf)
include(../common/g++-unix.conf)

# modifications to g++.conf
QMAKE_CC                = /opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-gcc -lts
QMAKE_CXX               = /opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-g++ -lts
QMAKE_LINK              = /opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-g++ -lts
QMAKE_LINK_SHLIB        = /opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-g++ -lts

# modifications to linux.conf
QMAKE_AR                = /opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-ar cqs
QMAKE_OBJCOPY           = /opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-objcopy
QMAKE_NM                = /opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-nm -P
QMAKE_STRIP             = /opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-strip
# opengl
QMAKE_INCDIR_OPENGL_ES2 = /usr/local/opengl_lib_inc/include/khronos
QMAKE_LIBDIR_OPENGL_ES2 = /usr/local/opengl_lib_inc/libs
QMAKE_LIBS_OPENGL_ES2  += -lGLESv2 -lEGL -lGAL
QMAKE_LIBS_OPENGL_ES1       += -lGLESv1_CM -lEGL -lGAL
QMAKE_LIBS_OPENGL_ES1CL     += -lGLES_CL -lEGL -lGAL
QMAKE_INCDIR_EGL = /usr/local/opengl_lib_inc/include/khronos
QMAKE_LIBDIR_EGL = /usr/local/opengl_lib_inc/libs
QMAKE_LIBS_EGL         += -lEGL
QMAKE_LIBS_OPENVG      += -lOpenVG -lEGL -lGAL


load(qt_config)
```

​	4.在qt-everywhere-opensource-src-5.6.0/下创建qt-build.sh配置编译选项, [参数含义](https://blog.csdn.net/xi_gua_gua/article/details/53413930)

```shell
./configure  -prefix /usr/local/Qt \
  -opensource \
  -release \
  -confirm-license \
  -xplatform linux-arm-gnueabi-g++ \
  -shared \
 -verbose \
  -qt-zlib \
	-pkg-config \
	 -no-nis \
	-opengl \
  -no-gif \
  -qt-libjpeg \
  -no-opengl \
  -no-cups \
  -no-glib \
  -no-dbus \
  -no-rpath \
  -no-sse2 -no-sse3 -no-ssse3 -no-sse4.1 -no-sse4.2 \
  -no-avx  \
  -no-openssl \
	-skip qtdeclarative \
    -skip qtserialbus \
    -skip qtwebchannel \
    -skip qtlocation \
  -nomake tools \
  -qreal float \
  -qt-libpng \
  -tslib \
  -make examples \
    -I /usr/local/tslib/include \
    -L /usr/local/tslib/lib \
    -L /usr/local/opengl_lib_inc/libs \
    -I /usr/local/opengl_lib_inc/include/khronos \
```

​	5.执行qt-build.sh

```shell
sudo chmod +x qu-build.sh
sudo ./qt-build.sh
```

![1591013849(1)](C:\Users\dongkangjia\Desktop\qt交叉编译环境并且移植\1591013849(1).png) 	

6.编译、安装

```shell
sudo make -j4
sudo make install
```

![1591068736(1)](C:\Users\dongkangjia\Desktop\qt交叉编译环境并且移植\1591068736(1).jpg)

## 5 qt配置编译器

​	安装完成之后，对应的目录下已经生成相应的文件，QT在linux的安装将不再赘述，可以自行查找，主要讲一下编译完之后的配置。

​	1.首先添加编译器（g++的编译器也要添加，相同方法）

![1](C:\Users\dongkangjia\Desktop\qt交叉编译环境并且移植\1.png)

​	2.添加qmake

![2](C:\Users\dongkangjia\Desktop\qt交叉编译环境并且移植\2.jpg)

​	3.添加kits

![1591069718(1)](C:\Users\dongkangjia\Desktop\qt交叉编译环境并且移植\1591069718(1).jpg)

## 6 编译arm-qt程序

 	1 .创建项目时，选择刚才加入的编译器

![1591073677(1)](C:\Users\dongkangjia\Desktop\qt交叉编译环境并且移植\1591073677(1).jpg)

​	2.编译结果

![1591073868(1)](C:\Users\dongkangjia\Desktop\qt交叉编译环境并且移植\1591073868(1).jpg)

​	3.移植到开发板

​	可以通过文件系统或者直接拷贝进去。





（=======================================后续更新====================================）