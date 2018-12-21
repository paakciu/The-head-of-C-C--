#include<stdio.h>
#include<malloc.h>

/*遇到的问题及其分析处理：


*/
#define DataType char
#define MaxStackSize 20
#define MaxQueueSize 50
//后缀表达式求值 链式栈结构
typedef struct CTI
{
	DataType node[8];//8位的十进制数
	struct CTI * next;

}CharToInt;

//符号栈
typedef struct
{
	DataType stack[MaxStackSize];
	int top;

}Stack;

//后缀表达式队列
typedef struct
{
	DataType queue[MaxQueueSize];
	int rear;
	int front;
}Queue;

//初始化队列	时间复杂度为O(1)
void QueueInitiate(Queue *Q)
{
	Q->rear = 0;
	Q->front = 0;
}

//队列非空否 	时间复杂度为O(1)
int QueueNotEmpty(Queue Q)
{
	if (Q.rear == Q.front)
		return 0;
	else return 1;
}

//队列入队	时间复杂度为O(1)
int QueueAppend(Queue *Q, DataType x)
{
	if ((Q->rear + 1) % MaxQueueSize == Q->front)
	{
		printf("队列已经满了");
		return 0;
	}
	else
	{
		Q->queue[Q->rear] = x;
		Q->rear = (Q->rear + 1) % MaxQueueSize;
		return 1;
	}
}

//队列出队	时间复杂度为O(1)
int QueueDelete(Queue *Q, DataType *x)
{
	if (Q->rear == Q->front)
	{
		printf("队列为空！");
		return 0;
	}
	else
	{
		*x = Q->queue[Q->front];
		Q->front = (Q->front + 1) % MaxQueueSize;
		return 1;
	}
}

//顺序栈初始化	时间复杂度为O(1)
void StackInitiate(Stack *s)
{
	s->top = 0;
}

//顺序栈非空否	时间复杂度为O(1)
int StackNotEmpty(Stack s)
{
	if (s.top <= 0)
		return 0;
	else return 1;
}

//顺序栈入栈	时间复杂度为O(1)
int StackPush(Stack *s, DataType x)
{
	if (s->top >= MaxStackSize)
	{
		printf("堆栈已经满了！\n");
		return 0;
	}
	else
	{
		s->stack[s->top] = x;
		s->top++;
		return 1;
	}
}

//顺序栈出栈	时间复杂度为O(1)
int StackPop(Stack *s, DataType *d)
{
	if (s->top <= 0)
	{
		printf("堆栈已空无数据元素！\n");
		return 0;
	}
	else
	{
		s->top--;
		*d =s->stack[s->top];
		return 1;
	}
}

//取栈顶数据元素 时间复杂度为O(1)
int StackTop(Stack *s, DataType *d)
{
	if (s->top <= 0)
	{
		printf("堆栈已空无数据元素！\n");
		return 0;
	}
	else
	{
		*d = s->stack[s->top-1];
		return 1;
	}
}


//带头结点链式堆栈 CharToInt
//头结点的数据域的第一位是标志位
//初始化
void CharToIntInitiate(CharToInt **head)
{
	*head = (CharToInt*)malloc(sizeof(CharToInt));
	(*head)->next = NULL;
}

//非空否
int CharToIntNotEmpty(CharToInt *head)
{
	if (head->next == NULL)return 0;
	else return 1;
}

//字符串转换成整型
int STI(DataType c[])
{
	int i = 0;
	int x = 0;
	for (i = 0; c[i] != '\0'; i++)
	{
		x = x * 10 + c[i] - '0';
	}
	return x;
}

//把数据推入栈中并计算，但这个为区块链式表
int CharToIntPush(CharToInt *head, DataType x)
{
	CharToInt *p;
	int x1,x2,sum,n,i;
	char c[MaxQueueSize];
	if (head->next == NULL)
	{
		p = (CharToInt *)malloc(sizeof(CharToInt));
		head->node[0] = '1';
		p->node[0] = x;
		p->next = head->next;
		head->next = p;
	}
	else
	{
		if (x >= '0'&&x <= '9')//如果是数字
		{	
			if (head->node[0] != '0')//如果头结点标志位是0，就是新的节点
			{
				head->next->node[(int)(head->node[0] - '0')] = x;
				head->node[0] = head->node[0] + 1;
			}
			else //新的节点
			{
				p = (CharToInt *)malloc(sizeof(CharToInt));
				head->node[0] = '1';
				p->node[0] = x;
				p->next = head->next;
				head->next = p;
			}
		}
		else if (x == '/' || x == '*' || x == '-' || x == '+' )//读到符号位就马上运算
		{
			
			//head->next->node[(int)(head->node[0] - '0')] = '\0';
			head->node[0] = '0';
			x2 = STI(head->next->node);
			x1= STI(head->next->next->node);
			switch (x)
			{
			case'+': {
				sum = x1 + x2; break;
			}
			case'-': {
				sum = x1 - x2; break;
			}
			case '*':{
				sum = x1 * x2; break;
			 }
			case '/': {
				if (x2 == 0)
				{
					printf("除数为0出错！\n");
					return 0;
				}
				else {
					sum = x1 / x2;
					break;
				}
			}
			default:
				break;
			}
			//switch 语句结束
			p = head->next;
			head->next = p->next->next;//栈顶指向栈顶第3个区块
			free(p->next);//释放栈顶2个区块
			free(p);
			p = (CharToInt *)malloc(sizeof(CharToInt));

			//把数字转回字符串，然后放回节点中
			n = sum; i = 0;
			while (n != 0)
			{
				c[i] = n%10+'0';
				n /= 10;
				i++;
			}
			head->node[0] = i  + '0';
			for (i = i - 1,n=0; i >= 0; i--,n++)
			{
				p->node[n] = c[i];
			}
			p->node[n] = '\0';
			//p->node[0] = x;
			p->next = head->next;
			head->next = p;
		}
		else if(x==' ')//等于空格就是为了区分开数字连着数字
		{
			head->next->node[(int)(head->node[0] - '0')] = '\0';
			head->node[0] = '0';

		}
	}
	return 1;
}


//从链表第一个节点返回整型数据（仅仅用于运算至只剩一个节点）
int CharToIntGetInt(CharToInt *head)
{
	return STI(head->next->node);//理论上运算完只有一个节点，输出该节点
}