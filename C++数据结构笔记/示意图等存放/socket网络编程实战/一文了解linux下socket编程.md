# 一文了解linux下socket编程

[TOC]

## 1 网络编程的相关简述

### 1.1 引言

​	本文主要讲述网络编程中套接字socket网络编程在linux下的使用，同时对其中的udp和tcp通信协议进行简单概述，不对通信协议做出详细的叙述，主要讲述如何使用、实现网络通信。下面是本文参考的一些文章连接：

https://www.cnblogs.com/fundebug/p/differences-of-tcp-and-udp.html

https://blog.csdn.net/qq_36171645/article/details/88907970

百问网的文档（没找到其中的参考链接，如有侵权请联系我删除）

### 1.2 Tcp和Udp简介

​	<font color=blue>**TCP向它的应用程序提供了面向连接的服务。**</font>这种服务包括了应用层报文向目的地的确保传递和流量控制（即发送方/接收方速率匹配）。这种服务包括了应用层报文划分为短报文，并提供拥塞控制机制，因此当网络拥塞时源抑制其传输速率。<font color=blue>**UDP协议向它的应用程序提供无连接服务。**</font>这是一种不提供不必要服务的服务，没有可靠性，没有流量控制，也没有拥塞控制。

|          | TCP                                                          | UDP                                                          |
| -------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 是否连接 | 面向连接（发送数据前需要建立连接）                           | 无连接（发送数据无需连接）                                   |
| 是否丢包 | 实现了数据传输时各种控制功能，可以进行丢包的重发控制，还可以对次序乱掉的分包进行顺序控制 | 不会进行丢包重试，也不会纠正到达的顺序                       |
| 模式     | 流模式（面向字节流）                                         | 数据报模式（面向报文）                                       |
| 对应关系 | 一对一                                                       | 支持一对一，一对多，多对一和多对多的交互通信                 |
| 头部开销 | 最小20字节                                                   | 只有8字节                                                    |
| 可靠性   | 全双工非常可靠、无差错、不丢失、不重复、且按序到达           | 不保证可靠交付，不保证顺序到达                               |
| 拥塞控制 | 有控制                                                       | 有拥塞控制，因此网络出现拥塞不会使源主机的发送速率降低（对实时应用很有用，如IP电话，实时视频会议等） |
| 资源要求 | TCP程序结构较复杂，较多                                      | UDP程序结构简单，少                                          |

### 1.3 TCP三次握手和四次挥手

​	TCP是全双工通信，且相对稳定可靠，就是因为有建立连接机制和超时重传机制，而双方建立连接的过程就涉及到三次握手，一提到三次握手自然就想到四次挥手，同时这个东西经常在面试问到，所以简单提一下。

![三次握手](C:\Users\dongkangjia\Desktop\socket网络编程实战\三次握手.jpg)

**第一次握手**：Client将标志位SYN置为1，随机产生一个值seq=J，并将该数据包发送给Server，Client进入SYN_SENT状态，等待Server确认。
**第二次握手**：Server收到数据包后由标志位SYN=1知道Client请求建立连接，Server将标志位SYN和ACK都置为1，ack (number )=J+1，随机产生一个值seq=K，并将该数据包发送给Client以确认连接请求，Server进入SYN_RCVD状态。
**第三次握手**：Client收到确认后，检查ack是否为J+1，ACK是否为1，如果正确则将标志位ACK置为1，ack=K+1，并将该数据包发送给Server，Server检查ack是否为K+1，ACK是否为1，如果正确则连接建立成功，Client和Server进入ESTABLISHED状态，完成三次握手，随后Client与Server之间可以开始传输数据了。

![四次分手](C:\Users\dongkangjia\Desktop\socket网络编程实战\四次分手.jpg)

 **第一次挥手**：Client发送一个FIN，用来关闭Client到Server的数据传送。
 **第二次挥手**：Server收到FIN后，发送一个ACK给Client，确认序号为收到序号+1。
 **第三次挥手**：Server发送一个FIN，用来关闭Server到Client的数据传送。
 **第四次挥手**：Client收到FIN后，接着发送一个ACK给Server，确认序号为收到序号+1。

### 1.4 网络编程函数接口

​	下面对linux下网络编程的相关函数进行简单介绍，之后的程序，许多函数用到。

| 函数                                                         | 作用                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| int socket(int domain, int type,int protocol);               | 创建一个套接字                                               |
| int bind(int sockfd, struct sockaddr \*my_addr, int addrlen); | 从函数用于将地址绑定到一个套接字                             |
| int listen(int sockfd,int backlog);                          | 此函数宣告服务器可以接受连接请求                             |
| int accept(int sockfd, struct sockaddr \*addr,int \*addrlen); | 服务器使用此函数获得连接请求，并且建立连接                   |
| int connect(int sockfd, struct sockaddr \* serv_addr,int addrlen); | connect函数是客户端用来同服务端连接的                        |
| ssize_t send(int sockfd, const void \*buf, size_t len, int flags); | 客户或者服务器应用程序都用send函数来向TCP连接的另一端发送数据 |
| ssize_t recv(int sockfd, void \*buf, size_t len, int flags); | 客户或者服务器应用程序都用recv函数从TCP连接的另一端接收数据  |
| ssize_t recvfrom(int sockfd, void \*buf, size_t len, int flags, | 通常用于无连接套接字，因为此函数可以获得发送者的地址         |
| ssize_t sendto(int sockfd, const void \*buf, size_t len, int flags,const struct sockaddr \*dest_addr, socklen_t addrlen); | sendto和send相似，区别在于sendto允许在无连接的套接字上指定一个目标地址。 |

## 2.socket之TCP实战

​	![tcp编程](C:\Users\dongkangjia\Desktop\socket网络编程实战\tcp编程.png)

<font color=red>**TCP服务端程序。**</font>

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#define SERVER_PORT 8180
#define C_QUEUE     10 


int main(int argc, char **argv)
{
    char buf[512];
    int len;
    int duty_socket;
    int customer_socket;
    struct sockaddr_in socket_server_addr;
    struct sockaddr_in socket_client_addr;
    int ret;
    int addr_len;

    signal(SIGCHLD, SIG_IGN);
	
	/* 服务器端开始建立socket描述符 */
    duty_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (duty_socket == -1)
    {
        printf("socket error");
        return -1;
    }
    
	/* 服务器端填充 sockaddr_in结构 */
    socket_server_addr.sin_family   = AF_INET;
	/*端口号转换为网络字节序*/
    socket_server_addr.sin_port     = htons(SERVER_PORT);
	/*接收本机所有网口的数据*/
    socket_server_addr.sin_addr.s_addr  = INADDR_ANY;
    memset(socket_server_addr.sin_zero, 0, 8);
    
	/* 捆绑sockfd描述符 */
    ret = bind(duty_socket, (const struct sockaddr *)&socket_server_addr, sizeof(struct sockaddr));
    if (ret == -1)
    {
        printf("bind error!\n");
        return -1;
    }
    ret = listen(duty_socket, C_QUEUE);
    if (ret == -1)
    {
        printf("listen error!\n");
        return -1;
    }
    
    while (1)
    {
        addr_len = sizeof(struct sockaddr);
				/* 服务器阻塞,直到客户程序建立连接 */
        customer_socket = accept(duty_socket, (struct sockaddr *)&socket_client_addr, &addr_len);
        if (customer_socket != -1)
        {
			/*inet_ntoa的作用是将一个32位Ipv4地址转换为相应的点分十进制数串*/
            printf("Get connect from %s\n", inet_ntoa(socket_client_addr.sin_addr));
        }
        if (!fork())
        {
            while (1)
            {
                memset(buf, 512, 0);
				/*接收数据*/
                len = recv(customer_socket, buf, sizeof(buf), 0);
                buf[len] = '\0';
                if (len <= 0)
                {
                    close(customer_socket);
                    return -1;
                }
                else
               {
                    printf("Get connect from %s, Msg is %s\n", inet_ntoa(socket_client_addr.sin_addr), buf);
                }
            }
        }
    }
    
    close(duty_socket);
    return 0;
}
```

<font color=red>**TCP客户端程序。**</font>

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8180


int main(int argc, char **argv)
{
    unsigned char buf[512];
    int len;
    struct sockaddr_in socket_server_addr;
    int ret;
    int addr_len;
    int client_socket;

    
    if (argc != 2)
    {
        printf("Usage:\n");
        printf("%s <server_ip>\n", argv[0]);
        return -1;
    }
    
    /* 客户程序开始建立 sockfd描述符 */
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        printf("socket error");
        return -1;
    }
    
	/* 客户程序填充服务端的资料 */
    socket_server_addr.sin_family   = AF_INET;
	/*主机字节序转换为网络字节序*/
    socket_server_addr.sin_port     = htons(SERVER_PORT);
    if (inet_aton(argv[1], &socket_server_addr.sin_addr) == 0)
    {
        printf("invalid server ip\n");
        return -1;
    }
    memset(socket_server_addr.sin_zero, 0, 8);
    /* 客户程序发起连接请求 */
   ret = connect(client_socket, (const struct sockaddr *)&socket_server_addr, sizeof(struct sockaddr));
    if (ret == -1)
    {
        printf("connect error!\n");
        return -1;
    }
    
    while (1)
    {
        if (fgets(buf, sizeof(buf), stdin))
        {
            len = send(client_socket, buf, strlen(buf), 0);
            if (len <= 0)
            {
                close(client_socket);
                return -1;
            }
        }
    }
    
    close(client_socket);
    return 0;
}
```



## 3.socket之udp实战

![udp编程](C:\Users\dongkangjia\Desktop\socket网络编程实战\udp编程.png)

<font color=red>**UDP服务端程序。**</font>

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
/*服务器端口为8180*/
#define SERVER_PORT 8180

int main(int argc, char **argv)
{
    unsigned char buf[512];
    int len;
    int duty_socket;
    int customer_socket;
    struct sockaddr_in socket_server_addr;
    struct sockaddr_in socket_client_addr;
    int ret;
    int addr_len;

	/*创建数据报套接字*/
    duty_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (duty_socket == -1)
    {
        printf("socket error");
        return -1;
   }
    
	/* 服务器端填充 sockaddr_in结构 */
    socket_server_addr.sin_family   = AF_INET;
   socket_server_addr.sin_port     = htons(SERVER_PORT);
    socket_server_addr.sin_addr.s_addr  = INADDR_ANY;
    memset(socket_server_addr.sin_zero, 0, 8);
   
	/*绑定套接字*/
    ret = bind(duty_socket, (const struct sockaddr *)&socket_server_addr, sizeof(struct sockaddr));
   if (ret == -1)
    {
        printf("bind error!\n");
        return -1;
    }

    
    while (1)
    {
        addr_len = sizeof(struct sockaddr);
		  /* 接收客户端数据报，返回的为接收到的字节数 */ 
        len = recvfrom(duty_socket, buf, sizeof(buf), 0, (struct sockaddr *)&socket_client_addr, &addr_len);
        if (len > 0)
        {
            buf[len] = '\0';
            printf("Get Msg from %s : %s\n", inet_ntoa(socket_client_addr.sin_addr), buf);
        }
    }
    
   close(duty_socket);
   return 0;
}
```

<font color=red>**UDP客户端程序。**</font>

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8180

int main(int argc, char **argv)
{
    unsigned char buf[512];
    int len;
    struct sockaddr_in socket_server_addr;
    int ret;
    int addr_len;
    int client_socket;
    
    if (argc != 2)
    {
        printf("Usage:\n");
        printf("%s <server_ip>\n", argv[0]);
        return -1;
    }
/*创建套接字*/
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1)
    {
        printf("socket error");
        return -1;
    }
    
	/* 填充服务端的资料 */
    socket_server_addr.sin_family   = AF_INET;
    socket_server_addr.sin_port     = htons(SERVER_PORT);
    if (inet_aton(argv[1], &socket_server_addr.sin_addr) == 0)
    {
       printf("invalid server ip\n");
        return -1;
    }
    memset(socket_server_addr.sin_zero, 0, 8);
   
    
    while (1)
    {
        if (fgets(buf, sizeof(buf), stdin))
       {
			/*向服务器端发送数据报*/
            addr_len = sizeof(struct sockaddr);
            len = sendto(client_socket, buf, sizeof(buf), 0, (struct sockaddr *)&socket_server_addr, addr_len);
            if (len <= 0)
           {
                close(client_socket);
               return -1;
            }
       }
    }
    
   close(client_socket);
    return 0;
}
```

