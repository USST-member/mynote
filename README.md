# 笔记

## 本文介绍

​	本文主要用于记录平常的学习内容和遇到的问题，方便以后的复习和查看。

## 数据库相关笔记

​	针对于前一段时间使用Qt使用数据库进行[登陆界面](https://github.com/USST-member/qt_public_demo/tree/master/log_dilog)和[本地加工参考表格](https://github.com/USST-member/qt_public_demo/tree/master/table_window_sqlite)的问题记录相关数据库的学习。数据库使用中主要用的**sqlite3**和**mysql**,但是sqlite3不支持远程登陆所以登陆界面数据库关联时使用的mysql。

### sqlite3数据库的基本命令 [帮助手册](https://doc.yonyoucloud.com/doc/wiki/project/sqlite/sqlite-intro.html)

| 基本命令                   | 命令解读                        |
| -------------------------- | ------------------------------- |
| sqlite3 student.db         | 创建一个数据库文件              |
| .help                      | 帮助命令，类似于linux下的--help |
| .quit                      | 退出                            |
| .exit                      | 退出                            |
| .tables                    | 查看数据库中的表格              |
| .schema 表名               | 显示表的字段信息                |
| pragma table_info('表名'); | 查看表的信息                    |

### sql命令

**sql命令是通用的，支持mysql、sqlite3等一些数据库，下面开始展示命令。**

在linux下安装sqlite3            `sudo apt-get install sqlite3`

查看版本及是否安装成功       `sqlite3 -version`   如果此时输出一些相关信息代表安装成功



<font color=#008000>创建一个数据库。</font>

```sqlite
sqlite3 student.db
```



<font color=#008000>在数据库中创建一个表格stu，表格为三列，分别为：整形的id、字符类型的name、整形的score。</font><font color=red>这里的整形注意不是int。</font>

```sql
create table stu(id Integer,name char,score Integer);
```



<font color=#008000>向表格stu插入三个数据，分别对应上述的id、name、score</font>

```sql
insert into stu values(001,'jack',100);
```



<font color=#008000>查看表stu的数据</font>

```sqlite
select * from stu;
```



<font color=#008000>向表格stu插入两个数据，分别对应上述的id、name，这是部分插入</font>

```sql
insert into stu (id,name) values(002,'jone');
```



<font color=#008000>查看id的字段，即为显示id那一列的信息</font>

```sql
select id from stu;
```



<font color=#008000>指定查询id=002,的那一行的值,第二行为指定两个条件查询</font>

```sql
select * from stu where id=002;
select * from stu where id=002 and name='jone';
```



<font color=#008000>指定删除表stu的一行</font>

```sql
delete from stu where id=002;
```



<font color=#008000>对表stu的某一行数据进行更新</font>

```sql
update stu set name='gcc',id=001 where score=100;
```



<font color=#008000>对表stu加入一列新的数据</font>

```sql
alter table stu add column address char;
```



<font color=#008000>**sqlite删除一列没有相关命令，采用一下方法实现**</font>

1. 创建一个新的表
2. 删除原有的表
3. 将新的表的名字改为原来表的名字

```sql
create table stu_another as select id,name,score from stu;
drop table stu;
alter table stu_another rename to stu;
```



### sqlite编程接口函数

**int  sqlite3_open(char *path,sqlite3  \* *db)**,打开sqlite3数据库。

**int   sqlite3_close(sqlite3 *db)**,关闭数据库。

**...**

使用时查找去官网查找帮助手册就好。



## mysql数据库的相关操作

mysql的相关操作和sqlite类似，在qt中均采用QSqlDatabase等相关类或者函数进行操作，也均可以使用sql语句

<font color=#008000>创建一个数据库。</font>

```mysql
create database if not exists student;
```



<font color=#008000>使用student数据库</font>

```mysql
use student;
```



<font color=#008000>创建stu表格</font>

```mysql
create table if not exists stu(id int,name char,score int);
```



| mysql命令                                | 命令解读             |
| ---------------------------------------- | -------------------- |
| mysql -u root -p                         | 登陆数据库           |
| desc student                             | 查看表的数据结构     |
| show databases                           | 显示数据库的一些信息 |
| drop database student                    | 删除数据库           |
| alter table stu modify int(20)           | 修改字段的数据类型   |
| alter table student rename [to] student1 | 修改表名             |
| alter table stu drop column address      | 删除一列             |



**<font color=red>	sqlite和mysql的选用根据需要选择，sqlite属于轻量级数据库，开源代码加一起差不错一万多行，适用于嵌入式和本地存储一些小型数据，mysql数据是中型数据库，可以远程登陆，当然还有其他数据库oracle等。</font>**

