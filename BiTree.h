#include<stdio.h>
#include<malloc.h>

#define DataType char

//树的节点结构体
typedef struct  Node
{
	DataType data;
	struct Node* leftChild;
	struct Node* rightChild;
}BiTreeNode;
//初始化树节点
void Initiate(BiTreeNode **root,DataType x)
{
	*root = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	(*root)->leftChild = NULL;
	(*root)->rightChild = NULL;
	(*root)->data = x;

}
//左插入节点(成功返回新插入节点指针）
BiTreeNode* InsertLeftNode(BiTreeNode *curr, DataType x)
{
	BiTreeNode *s, *t;
	if (curr == NULL)return NULL;
	t = curr->leftChild;
	s = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	s->data = x;
	s->leftChild = t;
	s->rightChild = NULL;
	curr->leftChild = s;
	return curr->leftChild;
}
//右插入节点(成功返回新插入节点指针
BiTreeNode* InsertRightNode(BiTreeNode *curr, DataType x)
{
	BiTreeNode *s, *t;
	if (curr == NULL)return NULL;
	t = curr->rightChild;
	s = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	s->data = x;
	s->rightChild = t;
	s->leftChild = NULL;
	curr->rightChild = s;
	return curr->rightChild;
}
//撤销二叉树
void Destroy(BiTreeNode **root)
{
	if ((*root) != NULL && (*root)->leftChild != NULL)
		Destroy(&(*root)->leftChild);
	if ((*root) != NULL && (*root)->rightChild != NULL)
		Destroy(&(*root)->rightChild);
	free(*root);
}
//左删除节点（成功返回双亲节点
BiTreeNode* DeleteLeftTree(BiTreeNode *curr)
{
	if (curr == NULL || curr->leftChild == NULL)return NULL;
	Destroy(&curr->leftChild);
	curr->leftChild = NULL;
	return curr;
}
//右删除节点（成功返回双亲节点
BiTreeNode* DeleteRightTree(BiTreeNode *curr)
{
	if (curr == NULL || curr->rightChild == NULL)return NULL;
	Destroy(&curr->rightChild);
	curr->rightChild = NULL;
	return curr;
}

//进入堆栈的定义，这里的堆栈是为了服务二叉树的
//为二叉树服务的堆栈的结构体
typedef struct stack
{
	BiTreeNode* data;
	struct stack *next;
}BiTreeStack;
//堆栈的初始化
void StackInitiate(BiTreeStack **head)
{
	*head = (BiTreeStack*)malloc(sizeof(BiTreeStack));
	(*head)->next = NULL;
}
//堆栈非空否
int StackNotEmpty(BiTreeStack *head)
{
	if (head->next == NULL)
		return 0;
	else return 1;
}
//入栈
void StackPush(BiTreeStack *head, BiTreeNode* x)
{
	BiTreeStack *p;
	p = (BiTreeStack*)malloc(sizeof(BiTreeStack));
	p->data = x;
	p->next = head->next;
	head->next = p;
}
//出栈
int StackPop(BiTreeStack *head, BiTreeNode **d)
{
	BiTreeStack *p = head->next;
	if (p == NULL)
	{
		printf("堆栈已经空了");
		return 0;
	}
	head->next = p->next;
	*d = p->data;
	free(p);
	return 1;
}
//取栈顶元素
int StackTop(BiTreeStack* head, BiTreeNode **d)
{
	BiTreeStack* p = head->next;
	if (p == NULL)
	{
		printf("堆栈已经空了");
		return 0;
	}
	*d = p->data;
	return 0;
}
//撤销整个堆栈
void StackDestroy(BiTreeStack* head)
{
	BiTreeStack *p, *p1;
	p = head;
	while (p != NULL)
	{
		p1 = p;
		p = p->next;
		free(p1);
	}
}

//回到二叉树
//节点访问
void Visit(DataType item)
{
	printf("%c ", item);
}
//非递归方式的先序遍历
void DLR_not_digui(BiTreeNode *root, void fangwen(DataType item))
{
	BiTreeStack *BTS;
	BiTreeNode *p;
	StackInitiate(&BTS);
	StackPush(BTS, root);
	while (StackNotEmpty(BTS))
	{
		StackPop(BTS, &p);
		fangwen(p->data);
		if (p->rightChild != NULL)
			StackPush(BTS, p->rightChild);
		if (p->leftChild != NULL)
			StackPush(BTS, p->leftChild);
	}

	StackDestroy(BTS);
}

//非递归方式的中序遍历
void LDR_not_digui(BiTreeNode *root, void fangwen(DataType item))
{
	BiTreeStack *BTS;
	BiTreeNode *p=root;
	StackInitiate(&BTS);
	//StackPush(BTS, root);
	while (p!=NULL||StackNotEmpty(BTS))
	{
		while (p != NULL)
		{
			StackPush(BTS, p);
			p = p->leftChild;

		}

		if (StackNotEmpty(BTS))
		{
			StackPop(BTS, &p);
			fangwen(p->data);
			p = p->rightChild;
		}
	}
}

//递归的后序遍历
void LRD_digui(BiTreeNode *root, void fangwen(DataType item))
{
	if (root == NULL)return;
	LRD_digui(root->leftChild,fangwen);
	LRD_digui(root->rightChild,fangwen);
	fangwen(root->data);
}


//下面是队列的源码，队列为了服务层次遍历
#define MaxQueueSize 25
typedef struct queue
{
	BiTreeNode* queue[MaxQueueSize];
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
int QueueAppend(Queue *Q, BiTreeNode* x)
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
int QueueDelete(Queue *Q, BiTreeNode* *x)
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

//二叉树的层次遍历
void cengci_bianli(BiTreeNode* root, void fangwen(DataType item))
{
	Queue Q;
	BiTreeNode *p=root;

	QueueInitiate(&Q);

	if (root == NULL)
	{
		printf("该数为空\n");
		return;
	}
	QueueAppend(&Q,p);
	while (QueueNotEmpty(Q))
	{
		QueueDelete(&Q, &p);
		fangwen(p->data);
		//因为先进先出，所以先进左边
		if (p->leftChild != NULL)
		{
			QueueAppend(&Q, p->leftChild);
		}
		if (p->rightChild != NULL)
		{
			QueueAppend(&Q, p->rightChild);
		}
	}

}

//求出树的深度
int GetTreeDepth(BiTreeNode* root)
{
	int left,right,ret;

	if (root == NULL)
		return 0;
	left = GetTreeDepth(root->leftChild);
	right = GetTreeDepth(root->rightChild);
	ret = (left>right?left:right) + 1;
	return ret;
}

//修改后序遍历法，使其可以输出非叶节点和叶节点
//递归的后序遍历
//返回叶节点个数
int LRD_Ye_Node_Num(BiTreeNode *root)
{
	int left, right,ret;
	if (root == NULL)return 0;
	//如果此节点为叶节点
	if (root->leftChild == NULL && root->rightChild == NULL)
	{
		return 1;
	}
	left= LRD_Ye_Node_Num(root->leftChild);
	right= LRD_Ye_Node_Num(root->rightChild);
	ret = left + right;
	return ret;
}
//获取总的节点数
int Get_Node_Num(BiTreeNode* root)
{
	int left, right, ret;
	if (root == NULL)
		return 0;

	left = Get_Node_Num(root->leftChild);
	right = Get_Node_Num(root->rightChild);
	ret = left + right + 1;
	return ret;
}

//后来确定题目意思是输出叶节点的值，故增加函数
//后序遍历，访问叶子节点
void Get_Ye_LRD_digui(BiTreeNode *root, void fangwen(DataType item))
{
	if (root == NULL)return;
	Get_Ye_LRD_digui(root->leftChild, fangwen);
	Get_Ye_LRD_digui(root->rightChild, fangwen);
	//只有当为叶节点时才访问
	if(((root->leftChild)==NULL)&&((root->rightChild)==NULL))
	fangwen(root->data);
}
//非叶节点的输出
void Get_NotYe_LRD_digui(BiTreeNode *root, void fangwen(DataType item))
{
	if (root == NULL)return;
	Get_NotYe_LRD_digui(root->leftChild, fangwen);
	Get_NotYe_LRD_digui(root->rightChild, fangwen);
	//只有当为非叶节点时才访问
	if ((root->leftChild) != NULL || (root->rightChild) != NULL)
		fangwen(root->data);
}