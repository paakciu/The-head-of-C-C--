#pragma once
#include<stdio.h>
#define Maxsize 100

//定义数据类型跟结构体
typedef char DataType;//DataType 数据应当有自己的比较大小的函数，但因为这里使用int型
typedef struct
{
	DataType list[Maxsize];
	int size;

}SeqList;

//初始化顺序表
void ListInitiate(SeqList *L)
{
	L->size = 0;
}
//求顺序表元素个数
int ListLength(SeqList *L)//传值参数比传入结构体要高效
{
	return L->size;
}

//取数据元素(从0开始)
int ListGet(SeqList *L, int index, DataType *x)
{
	if (index >= L->size || index<0)
	{
		return 0;//取元素位置index错误
	}
	*x = L->list[index];
	return 1;
}

//插入顺序表
int ListInsert(SeqList *L, DataType x)
{
	int i, flag = 0;
	DataType m;//DataType 数据应当有自己的比较大小的函数，但因为这里使用int型
			   //采用后移比较
	for (i = L->size; i >= 0; i--)
	{
		if (ListGet(L, i - 1, &m))//用m取出i-1位置的元素,如果i-1（>=0）能取出则后移或插入
			if (m>x)
			{
				L->list[i] = m;//额。。这里使用不安全的方式，跟上两句这么严谨的取值方式形成了鲜明的对比
			}
			else
			{
				flag = 1;
				L->list[i] = x;
				break;//结束循环;
			}
		else//如果m取值取完了0的数，那其实i此时为0，所以x需要插入i的位置
		{
			flag = 1;
			L->list[i] = x;
			break;//结束循环;
		}
	}
	if (flag == 1)
	{
		L->size++;
		return 1;
	}
	else return 0;
}

//删除元素，数据由x带回，并且可以缺省
int ListDelete(SeqList *L, int index, DataType *x)
{
	int i;
	if (L->size == 0)
	{
		return 0;//已经没有元素可以删除了
	}
	if (index >= L->size || index<0)
	{
		return 0;//取元素位置index错误
	}
	//先把元素带回
	if (x != NULL)*x = L->list[index];
	//循环前移删除
	for (i = index; i<L->size - 1; i++)
	{
		L->list[i] = L->list[i + 1];//前面的数用后面的数覆盖掉
	}
	L->size--;
	L->list[L->size] = 0;//为了操作安全，把最后一项置0，删除这句少一步操作
	return 1;
}

//合并函数
int ListMerge(SeqList *L1, SeqList *L2, SeqList *L3)
{
	int i;
	DataType x;
	//L3->size = L2->size + L1->size;//赋值size 决定长度
	if (L1 == NULL || L2 == NULL)
	{
		return 0;//参数有误，合并失败
	}
	for (i = 0; i < L1->size; i++)
	{
		ListGet(L1, i, &x);
		ListInsert(L3, x);// L2->list[i]
	}
	for (i = 0; i < L2->size; i++)
	{
		ListGet(L2, i, &x);
		ListInsert(L3, x);
	}

	return 1;
}