# C语言图解常见排序算法

[TOC]

## 1 冒泡排序

​	冒泡排序是比较常见的一种排序，即便是初学者，也略知一二,<font color=red>**啥也不是说了，上图。**</font>

![冒泡](C:\Users\dongkangjia\Desktop\C语言实现各类排序\冒泡.gif)

​	<font color=blue>**接下来上代码，动手实践一遍才牢靠。**</font>

```c
#include<stdio.h>
#include<stdlib.h>
#define Max_array 10



/*交换函数*/
void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
	return;
}
/*冒泡排序*/
void bubble_sort(int *array)
{
	int i=0,j=0;
	for(;i<Max_array-1;i++)//注意此时是i<Max_array-1而不是i<Max_array
	{
		for(j=0;j<Max_array-i-1;j++)
		{
			if(array[j]>array[j+1])
			{
				swap(&array[j],&array[j+1]);
			}

		}
	}
	return;
}
```

## 2 选择排序

​	<font color=red>**同样，上图，理解原理、写代码。**</font>

![选择排序](C:\Users\dongkangjia\Desktop\C语言实现各类排序\选择排序.gif)



​	<font color=blue>**动手实践一遍才牢靠，一定要自己动手写一遍。**</font>

```c
#include<stdio.h>
#include<stdlib.h>
#define Max_array 10

/*交换函数*/
void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
	return;
}
/*选择排序*/
void select_insort(int *array)
{
	int i=0;
	for(;i<Max_array-1;i++)
	{
		int j=i+1;
		for(;j<Max_array;j++)
		{
			if(array[j]<array[i])
			{
				swap(&array[j],&array[i]);
			}
		}	
	}
	return;
}
```



## 3 插入排序

​		<font color=red>**同样，上图，理解原理、写代码。**</font>

![插入](C:\Users\dongkangjia\Desktop\C语言实现各类排序\插入.gif)

​	<font color=blue>**再说一遍，一定要自己动手写一遍。**</font>

```c
#include<stdio.h>
#include<stdlib.h>
#define Max_array 10
/*插入排序*/
void insert_sort(int *array)
{
	if(array==NULL)
		return;
	int i=0;
	for(i=1;i<Max_array;i++)
	{
		int j=i-1;
		int temp=array[i];//哨兵的作用
		for(;j>=0&&array[j]>=temp;j--)
		{
			array[j+1]=array[j];
		}
		array[j+1]=temp;
	}
	return;
}
```



## 4 快速排序

​	<font color=red>**同样，上图，理解原理、写代码。**</font>

![快排动图](C:\Users\dongkangjia\Desktop\C语言实现各类排序\快排动图.gif)

​		<font color=blue>**很重要，很重要，看完自己写一遍。**</font>

```c
#include<stdio.h>
#include<stdlib.h>
#define Max_array 10
/*快速排序*/
void quick_sort(int *array,int low,int high)
{
	if(array==NULL||low>=high)//判断边界条件
		return;
	int left=low,right=high;
	int temp=array[low];//哨兵，这个根据自己个人习惯选择的，不是很固定
	while(left<right)
	{
		while(left<right&&array[right]>=temp)//右边的数大于哨兵，跳过
		{
			right--;
		}
		if(left<right)//右边的数小于哨兵，换位置
		{
			array[left]=array[right];
			left++;

		}
        
		while(left<right&&array[left]<temp)//左边的数小于哨兵，跳过
		{
			left++;
		}
		if(left<right)//左边的数大于哨兵，换位置
		{
			array[right]=array[left];
			right--;
		}
	}
	array[left]=temp;
	quick_sort(array,low,left-1);
	quick_sort(array, left+1,high);
	return;
}
```



## 5 归并排序

​	<font color=red>**归并排序主要是分治的思想，理解这个原理很重要，因为他有时候不仅仅在排序上，在其他很多问题上也比较常见，把一个大的问题，分开解决。上图，理解原理、写代码。**</font>

![归并](C:\Users\dongkangjia\Desktop\C语言实现各类排序\归并.gif)

​		<font color=blue>**很重要，很重要，写完才是自己的，不要眼高手低。**</font>

```c
/*归并排序的具体的实现*/
void merger(int *array,int low,int mid,int high)
{
	int *temp=(int *)malloc(sizeof((high-low)+1)*sizeof(int));

	int left=low,right=mid+1,t=0;
    /*实现分治，把排序的结果写入动态分配空间中*/
	while(left<=mid && right<=high)
	{
		if(array[left]<=array[right])
		{
			temp[t++]=array[left++];
		}
		else
		{
			temp[t++]=array[right++];
		}
	}

	while(left<=mid)
	{
		temp[t++]=array[left++];

	}

	while(right<=high)
	{
		temp[t++]=array[right++];
	}

    /*将动态分配的值写入数组中*/
	for(;low<=high;low++)
	{
		array[low]=temp[t-(high-low)-1];
	}
	free(temp);
	return;
}

/*归并排序*/
void merger_sort(int *array,int low,int high)
{
	if(array==NULL||low>=high)
		return;
	
	int mid=(low+high)/2;
	merger_sort(array, low,mid);//进行递归，便于实现分治
	merger_sort(array, mid+1,high);
	merger(array, low, mid, high);
	
	return;
}
```





