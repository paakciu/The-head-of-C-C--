//#include <stdio.h>
#include <math.h>

//typedef int DataType;

//这个数据结构类型是为了像<int，String>这样的<key,data>数据，用key找到data，或者用key排序
typedef   int   KeyType;
typedef struct
{
	KeyType key;
	//InfoType otherinfo;
}DataType;

//#define MAXSIZE 20
//这个暂时用不到，但是有参考价值，留着
//typedef struct{
//	DataType d[MAXSIZE];
//	int length;
//}SqList;


//用直接插入法对a[m]--a[n-1]排序
void InsertSort(DataType a[], int m, int n)
{
	int i, j;
	DataType temp;
	for (i = m; i<n - 1; i++)
	{
		temp = a[i + 1];//先暂存ai+1
						//已排好序的部分，大于ai+1的元素依次后移一个位置		
		for (j = i; j > m - 1 && temp.key <a[j].key; j--)
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}
}
//用希尔排序法对元素a[m]--a[n-1]排序，d[0]--d[numOfD-1]为希尔增量值
//希尔排序d的选择：初始d=n/2, d=d/2直到d=1为止
void ShellSort(DataType a[], int m, int n)
{
	DataType temp;
	int i, j, k, l, span;
	int *d, numOfD = 0;
	//这里待会实验一下把0改成m
	int num = n - m;
	for (i = num; i > 1; i /= 2)
		numOfD++;
	d = (int*)malloc(sizeof(int)*numOfD);
	for (i = 0; i < numOfD; i++)
	{
		d[i] = num/2;
		num /= 2;
		if (d[i] == 1)break;
	}

	//
	for (l = 0; l < numOfD; l++)	       //共numOfD次循环
	{
		span = d[l];		      //取本次的增量值
		for (k = 0; k < span; k++)	      //共span个小组
		{
			//组内是直接插入排序，区别是每次不是增1而是增span
			for (i = k; i + span < n; i = i + span)
			{
				temp = a[i + span];
				j = i;
				//这里可以试一下把0换成m
				while (j >=m && temp.key < a[j].key)
				{
					a[j + span] = a[j];
					j = j - span;
				}
				a[j + span] = temp;
			}
		}
	}


	free(d);
}

//稳定直接选择排序
void SelectSort_Stable(DataType a[], int n)
{
	int i, j, small,k;
	DataType temp;
	for(i = 0; i < n-1; i++)				
	{
		small = i;	 							//设第i个数据元素关键字最小
		for(j = i+1; j < n; j++)				//寻找关键字最小的数据元素
		  if(a[j].key < a[small].key) 
			  small=j;  //记住最小元素的下标

		if(small != i)		//当最小元素的下标不为i时交换位置
		{
			temp = a[small];
			//i及i之后，small之前的所有元素都往后移一位
			for (k = small-1; k >= i; k--)
			{
				a[k + 1] = a[k];
			}
			a[i] = temp;;
		}
	}
}


//快速排序
void QuickSort(DataType a[],int low, int high)
{
	int i=low,j=high-1;
	DataType temp=a[low];	
	while(i<j)
	{
		while(i < j && temp.key <= a[j].key)
			j--; //在数组的右端扫描
		if(i < j)
		{
		 	a[i] = a[j];
			i++;
		}
		while(i < j && a[i].key < temp.key) 
			i++; //在数组的左端扫描
		if(i < j)
		{
			a[j] = a[i];
			j--;
		}
	}
	
	a[i]=temp;
	if(low<i) 
		QuickSort(a,low,i);
	if(i<high) 
		QuickSort(a,j+1,high);
}



//void AjustHeap (DataType a[], int n, int h)
// // 调整下标为h的根元素,成为最大堆,n为堆的元素个数
// {
//	int i, j, flag;
//	DataType temp;
// 	i = h;			// i为要建堆的二叉树根结点下标
//	j = 2*i+1;			// j为i的左孩子结点的下标
//	temp = a[i];
//	flag = 0;
// 	//沿左右孩子中值较大者重复向下筛选
//	while(j < n && flag != 1)
//	{	//寻找左右孩子结点中的较大者,j为其下标
//		if( j+1 < n &&  a[j].key < a[j+1].key) j++;
// 		if(temp.key > a[j].key)			//a[i].key>a[j].key
//			flag=1;				//标记结束筛选条件
//		else					//否则把a[j]上移
//		{
//			a[i] = a[j];
//			i = j;
//			j = 2*i+1;
//		}
//	}
//	a[i] = temp;				//把最初的a[i]赋予最后的a[j]
//}
////初始化创建最大堆算法如下：
//void CreatHeap(DataType a[], int n)	
//{
//	int i;
// 
//	for(i = (n-2)/2; i >= 0; i--)	
//		AjustHeap(a, n, i);
//}
////堆排序算法如下：
//void HeapSort(DataType a[], int n)
//{
//	int i;
//	DataType temp;   
//	CreatHeap(a, n);		//初始化创建最大堆 
//	for(i = n-1; i > 0; i--)		//当前最大堆个数每次递减1
//	{	 //把堆顶a[0]元素和当前最大堆的最后一个元素交换
//                        temp = a[0];
//		a[0] = a[i];
//		a[i] = temp; 
//		AjustHeap(a, i, 0);	//调整根结点满足最大堆
//	}
//}
////冒泡排序
//Void BubbleSort(DataType a[],int n)
//{
//	int i, j, flag =1;
//	DataType temp;
//		
//	for(i = 1;i < n && flag == 1; i++)
//	{ //flag标记一趟冒泡如果没有交换，则已经排好序，提前结束循环
//	  	flag = 0;
//	  	for(j = 0;j < n  - i; j++)
//	 	{	
//			if(a[j].key>a[j+1].key)
//			{
//				flag = 1;
//				temp = a[j];
//				a[j] = a[j+1] ；
//				a[j+1] = temp;
//	  		}
//		}
//	}
//}

//
//
//一次二路归并排序算法如下：
//void Merge(DataType a[], int n, DataType swap[], int k)
////k为有序子数组的长度，一次二路归并排序后的有序子序列存于数组swap中
//{
//	int m = 0, u1,l2,i,j,u2;
//	int l1 = 0;				//第一个有序子数组下界为0
//	while( l1+k <= n-1 )
//	{
//		l2 = l1 + k;			//计算第二个有序子数组下界
//		u1 = l2 - 1;			//计算第一个有序子数组上界
//		u2 = (l2+k-1 <= n-1)? l2+k-1: n-1;       //计算第二个有序子数组上界
//							//两个有序子数组合并
//		for(i = l1, j = l2; i <= u1 && j <= u2; m++)	
//		{
//			if(a[i].key <= a[j].key)
//			{
//				swap[m] = a[i];
//				i++;
//			}
//			else
//			{
//				swap[m]=a[j];
//				j++;
//			}
//		}
//    //子数组2已归并完，将子数组1中剩余的元素存放到数组swap中
//		while(i <= u1)
//		{
//			swap[m] = a[i];
//			m++;
//			i++;
//		}
//		while(j <= u2)
//		{
//			swap[m] = a[j];
//			m++;
//			j++;
//		}
//		l1=u2+1;
//	}//将原始数组中只够一组的数据元素顺序存放到数组swap中
//	for(i=l1;i<n;i++,m++)
//		swap[m]=a[i];
//	}
//
//Void MergeSort(DataType a[ ], int n)
//{
//	int i, k=1;
//	DataType *swap;
//	swap=(DataType*i) malloc(sizeof(DataType)*n)
//	while(k<n)
//	{
//		Merge(a,n,swap,k);
//		for(i=0;i<n;i++)
//		{
//			a[i]=swap[i];
//		}
//		k=2*k;
//	}
//	free(swap);
//}
//
////基于链式队列的基数排序算法如下：
//#include "LinQueue.h"
//void RadixSort(DataType a[], int n, int m, int d)
////对数据元素a[0]--a[n-1]进行关键码为m位d进制整型数值的基数排序
////桶采用链式队列结构
//{
//	int i, j, k, power = 1;
//	LinQueue *tub；
//	tub = (LinQueue *) malloc(sizeof(LinQueue)*d);
// 
//	//进行m次排序
//	for(i = 0; i < m; i++)
//	{
//		if(i == 0) power = 1;
//		else power = power *d;
//	//将数据元素按关键码第k位的大小放到相应的队列中
//	for(j = 0; j < n; j++)
//	{
//		k = a[j].key /power - (a[j].key /(power * d)) * d;
//		tub[k].Append(a[j]);
//	}
//	//顺序回收各队列中的数据元素
//	for(j = 0, k = 0; j < d; j++)
//		while(tub[j].NotEmpty())
//		a[k++] = tub[j].Delete();
//	}
//}
