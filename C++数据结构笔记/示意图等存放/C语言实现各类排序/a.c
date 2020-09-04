#include<stdio.h>
#include<stdlib.h>

#define Max_array 10

void print_array(int *array)
{
	int i=0;
	for(;i<Max_array;i++)
	{
		printf("array[%d]=%d\n",i,array[i]);
	}
	return;
}


/*快速排序*/

void quick_sort(int *array,int low,int high)
{
	if(array==NULL||low>=high)
		return;
	int left=low,right=high;
	int temp=array[low];
	while(left<right)
	{
		while(left<right&&array[right]>=temp)
		{
			right--;
		}
		if(left<right)
		{
			array[left]=array[right];
			left++;
		}
		while(left<right&&array[left]<temp)
		{
			left++;
		}
		if(left<right)
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



/*归并排序的具体的实现*/
void merger(int *array,int low,int mid,int high)
{
	int *temp=(int *)malloc(sizeof((high-low)+1)*sizeof(int));

	int left=low,right=mid+1,t=0;
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

	for(;low<=high;low++)
	{
		array[low]=temp[t-(high-low)-1];
		printf("low=%d,high=%d,t=%d,t-(high-low)=%d\n",low,high,t,t-(high-low)-1);
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
	merger_sort(array, low,mid);
	merger_sort(array, mid+1,high);
	merger(array, low, mid, high);
	
	return;
}




/*插入排序*/

void insert_sort(int *array)
{
	if(array==NULL)
		return;
	int i=0;
	for(i=1;i<Max_array;i++)
	{
		int j=i-1;
		int temp=array[i];
		for(;j>=0&&array[j]>=temp;j--)
		{
			array[j+1]=array[j];
		}
		array[j+1]=temp;
	}
	return;
}

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
	for(;i<Max_array-1;i++)
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


int main(int argc,char **argv)
{
	int array[Max_array]={2,10,1,5,3,56,6,4,342,3};
	//quick_sort(array,0,Max_array-1);
	//merger_sort(array,0,Max_array-1);
	//insert_sort(array);
	//select_insort(array);
	bubble_sort(array);
	printf("----------------------------------\n");
	print_array(array);
	printf("++++++++++++++++++++++++++++++++++\n");
	return 0;
}
