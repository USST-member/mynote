# Ubuntu开机【OK】 Started LSB:automatic crash report generation卡死--已解决

【OK】 Started Disk Manager

【OK】Started Hostname Services

【OK】 Started LSB:automatic crash report generation......

<img src="https://gitee.com/dong_kj/image/raw/master/20210201234825.jpg" style="zoom:50%;" />

**解决方法**

<font color=red>ctrl+alt+delete三个按键</font>一起按下，重新启动，启动时根据自己电脑按下**esc按键**或者**shift按键**进入如下界面，选择第二个**Advanced options for ubuntu**.

![image-20210201235106560](https://gitee.com/dong_kj/image/raw/master/20210201235106.png)

​	紧接着进入如下界面：选择第二个确定

![image-20210201235225314](https://gitee.com/dong_kj/image/raw/master/20210201235225.png)

​	然后进入下面界面：选择**<font color=red>resume</font>**,确定

![image-20210202000045400](https://gitee.com/dong_kj/image/raw/master/20210202000045.png)

​	选择ok

![image-20210201235517245](https://gitee.com/dong_kj/image/raw/master/20210201235517.png)

​	随后进入成功进入图形桌面，打开终端窗口，输入以下命令，修改文件,将 **<font color=red>GRUB_CMDLINE_LINUX_DEFAULT=“quiet nomodeset”</font>**

```shell
sudo vi /etc/default/grub
```

![image-20210202000158578](https://gitee.com/dong_kj/image/raw/master/20210202000158.png)

```shell
sudo update-grub
```

