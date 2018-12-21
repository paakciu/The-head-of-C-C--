#include<stdio.h>
#include<malloc.h>

/*遇到的问题及其分析处理：


*/
//此次实验采用顺序循环队列（少用一个存储单位）
#define MaxSize 10//我名字有9个字母，空一个就是10位
typedef char DataType;
typedef struct 
{
	DataType queue[MaxSize];
	int rear;					//队尾
	int front;					//队头
}Queue;



//初始化队列
void QueueInitiate(Queue *Q)
{
	Q->rear = 0;
	Q->front = 0;

}

//入队
int QueueAppend(Queue *Q, DataType x)
{
	if ((Q->rear + 1 )% MaxSize == Q->front)
	{
		printf("队列已经满了");
		return 0;
	}
	else
	{
		Q->queue[Q->rear] = x;
		Q->rear = (Q->rear + 1) % MaxSize;
		return 1;
	}
}

//出队
int QueueDelete(Queue *Q, DataType *x)
{
	if (Q->rear == Q->front)
	{
		printf("队列为空！");
		return 0;
	}
	else
	{
		*x=Q->queue[Q->front];
		Q->front = (Q->front + 1) % MaxSize;
		return 1;
	}
}
