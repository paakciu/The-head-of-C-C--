#include<stdio.h>
#include<malloc.h>

/*遇到的问题及其分析处理：
	在main函数中首先使用的是PloyNode PN
	但是发现在插入函数PNInsert中，插入新的首元节点会非常难处理
	于是我修改了链表的初始化 并且在初始化的时候才产生内存区域


*/
//此次实验采用循环链表
typedef struct node
{
	float coef;			//系数域
	int exp;			//指数域
	struct node *next;	//指针域
}PloyNode;

//初始化单链表,并给第一个节点赋值
void PNInitiate(PloyNode **h, float a, int n)
{
	*h= (PloyNode*)malloc(sizeof(PloyNode)); //把头指针指向一块空的内存区域，因为main函数中的是函数指针
	(*h)->coef = a;
	(*h)->exp = n;
	(*h)->next = *h;//指向自己完成一个循环单链表
}

//插入数据元素，并整理排序，合并同类项
int PNInsert(PloyNode **h, float a, int n)
{
	/*废弃代码，先放着，调试可能有需要*/
	//while(p->next!=h) p=p->next;
	//p->coef=a;
	//p->exp=n;
	//p->next=(PloyNode*)malloc(sizeof(PloyNode)); //生成新的节点，并且末节点的next指向新节点
	//p=p->next ;//指针指向新节点
	//p->next=h;//把新节点的next指到头节点，维护循环单链表

	PloyNode *p = (*h), *p1;
	if (*h == NULL)return 0;

	//头节点
	if ((*h)->exp>n)//这里要插在头节点位置
	{
		p1 = (PloyNode*)malloc(sizeof(PloyNode));
		p1->next = (*h);					//新节点指向原头节点
		while (p->next != (*h)) p = p->next; //取得尾节点
		p->next = p1;//尾节点指向新节点，完成维护循环单链表
		(*h) = p1;//让新节点成为头节点
			   //赋值
		(*h)->coef = a;
		(*h)->exp = n;
		return 1;
	}
	//此处应该找到指数项>= n的,处理除头节点以外的节点
	while (p->next != (*h) && (p->next->exp<n)) p = p->next;
	if (p->next->exp == n)
	{
		p->next->coef += a; //合并同类项
		return 1;//完成操作，不需要申请新节点，返回函数即可
	}
	else
	{
		p1 = (PloyNode*)malloc(sizeof(PloyNode));//不管他是到了尾节点（新节点指数最大）还是找到了合适的位置
		p1->next = p->next;  //新节点指向下个节点
		p->next = p1;			//原节点指向新节点	//维护好循环链表
								//赋值
		p1->coef = a;
		p1->exp = n;
	}

	return 1;
}

//求数据元素的个数，返回-1为出错
int PNlength(PloyNode *h)
{
	PloyNode *p = h;
	int j = 1;
	if (h == NULL)return -1;//若返回-1则出错
	if (h->coef==0.0)return 0;//如果系数域为0，那么此元素在多项式中等于不存在，那么我可以认为头节点是初始化后的状态
	while (p->next != h)
	{
		p = p->next;
		j++;//这段话执行一次就代表有一个元素，没有执行过也至少有头节点一个元素
	}
	return j;
}

//取数据元素(由a，n带回数据)
int PNGet(PloyNode *h, int i, float *a, int *n)
{
	int j = 0;
	PloyNode *p = h;

	if (h == NULL)return 0;
	if (i<0 || i>PNlength(h))return 0;
	while (j<i)
	{
		p = p->next;
		j++;
	}
	*a = p->coef;
	*n = p->exp;
	return 0;
}

//删除元素
int PNDelete(PloyNode *h, int i, float *a, int *n)
{
	int j = 0;
	PloyNode *p = h;
	PloyNode * q=p;
	if (h == NULL)return 0;
	if (i<0 || i>PNlength(h))return 0;
	while (j<i)
	{
		q = p;
		p = p->next;
		j++;
	}
	*a = p->coef;
	*n = p->exp;
	q->next = p->next;
	free(p);
	return 1;
}