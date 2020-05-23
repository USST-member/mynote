# arm移植qt之opencv交叉环境的搭建

[TOC]

## 1. 前提准备

### 1.1 环境

​	首先交叉编译肯定在linux下进行的，系统我使用的是ubuntu16.04，opencv的版本opecv3.4.1,交叉编译链是arm-cortex_a9-eabi-4.7-eglibc-2.18（根据你自己需要移植的板子确定交叉编译工具），cmake3.5.1版本。

### 1.2 交叉编译链的安装

​	自行下载所需交叉编译工具链，我这里的是arm-cortex_a9-eabi-4.7-eglibc-2.18.tar.gz已经下载好并且拷贝到ubuntu下的/opt/。

```shell
tar zxvf arm-cortex_a9-eabi-4.7-eglibc-2.18.tar.gz
```

​	设置环境变量

```shell
vim /etc/profile
```

​	在打开的文件中加入下面这句话 export PATH=/opt/arm-cortex_a9_eabi-4.7-eglibc-2.18/bin:$PATH![1](C:\Users\dongkangjia\Desktop\arm移植qt之opencv的搭建\1.png)

​	使用如下命令是添加的环境变量生效

```shell
source /etc/profile
```

### 1.3 cmake的安装

​	首先确定自己的linux下有没有安装cmake

```shell
cmake --version
```

​	如果没有安装，通过以下命令进行安装。

```shell
sudo apt-get install cmake cmake-qt-gui
```

![2](C:\Users\dongkangjia\Desktop\arm移植qt之opencv的搭建\2.jpg)

### 1.4 opencv3.4.1的相关配置

​	[opencv下载地址](https://www.opencv.org/releases.html): https://www.opencv.org/releases.html

​	下载完之后上传到ubuntu下解压（解压的路径根据需要自行设置），放置之后编译出错对解压之后的文件进行更改opencv-3.4.1/3rdparty/libpng/pngpriv.h，大概在130行左右，左侧原先，右侧改动。

![3](C:\Users\dongkangjia\Desktop\arm移植qt之opencv的搭建\3.jpg)

​	在解压之后的文件夹下创建两个目录build,cv_install.<font color=red>（和3rdparty是同级目录）</font>

```shell
mkdir bulid cv_install
```

## 2 opencv的交叉编译

### 2.1 cmake项目的配置

​	进入刚才创建的build目录，执行cmake-gui.进入以下界面，其中步骤1是解压之后的opencv目录，步骤2是解压之后创建的builid目录，步骤3进行勾选，步骤4点击configure.

```shell
cmake-gui
```

![4](C:\Users\dongkangjia\Desktop\arm移植qt之opencv的搭建\4.jpg)

之后进入下面步骤1，2，3与下图相对应。

![5](C:\Users\dongkangjia\Desktop\arm移植qt之opencv的搭建\5.jpg)

​	随后进入下图示步骤，步骤1写linux,步骤2是刚才安装交叉编译链所在目录opt/arm-cortex_a9-eabi-4.7-eglibc-2.18/bin目录下的gcc编译器，步骤3也是这个目录下的g++编译器，步骤4是安装的编译器目录，步骤5和6一样进行选择，然后点击finish.

![6](C:\Users\dongkangjia\Desktop\arm移植qt之opencv的搭建\6.jpg)

对以下四个个选项进行配置：配置完之后点击generate.

| CMAKE_CONFIGURATION_TYPES | Release                                                      |
| ------------------------- | ------------------------------------------------------------ |
| CMAKE_INSTALL_PREFIX      | 在解压目录下的cv_install目录<font color=red>（自己选择好）</font> |
| BUILD_JPEG                | 勾选                                                         |
| BUILD_PNG                 | 勾选                                                         |

![7](C:\Users\dongkangjia\Desktop\arm移植qt之opencv的搭建\7.jpg)

### 2.2 对opencv库编译

​	关闭cmake界面，在build目录下输入make命令,-j4根据你的电脑配置编译加快速度，等待编译完成。

```shell
make -j4
```

![8](C:\Users\dongkangjia\Desktop\arm移植qt之opencv的搭建\8.jpg)

​	进入cv_install目录下查看编译结果，接下来就可以在Qt中使用了。

![9](C:\Users\dongkangjia\Desktop\arm移植qt之opencv的搭建\9.png)