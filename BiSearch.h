#pragma once

#include<stdio.h>
#include<malloc.h>

typedef int KeyType;
typedef struct
{
	KeyType key;
} DataType;

typedef struct node
{
	DataType data;
	struct node *leftChild;
	struct node *rightChild;
} BiTreeNode;


//在二叉排序树root上查找数据元素item是否存在
int BiSearch(BiTreeNode *root, DataType item)

{
	BiTreeNode *p;

	if (root != NULL)
	{
		p = root;
		while (p != NULL)
		{
			if (p->data.key == item.key) 
				return 1;  //查找成功
			if (item.key > p->data.key) 
				p = p->rightChild;
			else p = p->leftChild;
		}
	}
	return 0;	//查找失败
}

int Insert(BiTreeNode **root, DataType item)
{
	BiTreeNode  *current, *parent = NULL, *p;

	current = *root;
	while (current != NULL)
	{
		if (current->data.key == item.key) return 0;//数据元素已存在
		parent = current;
		if (current->data.key < item.key)
			current = current->rightChild;
		else
			current = current->leftChild;
	}
	/*生成新结点*/
	p = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	p->data = item;
	p->leftChild = NULL;
	p->rightChild = NULL;

	if (parent == NULL) *root = p;  //树为空，新结点为根结点
	else if (item.key < parent->data.key)
		parent->leftChild = p;  //新结点为该结点的左孩子结点
	else
		parent->rightChild = p; //新结点为该结点的右孩子结点
	return 1;
}

void InTraverse(BiTreeNode *root)
/*中序遍历显示二叉排序树结点信息函数*/
{
	if (root == NULL) return;
	if (root->leftChild != NULL)
		InTraverse(root->leftChild);

	printf("%d   ", root->data.key);

	if (root->rightChild != NULL)
		InTraverse(root->rightChild);
}

int Delete(BiTreeNode **root, DataType item)
{
	BiTreeNode *p=NULL,*q=NULL;
	if (*root != NULL)
	{
		p=*root;
		while (p != NULL)
		{
			if (p->data.key == item.key)
				break; //查找成功
			q = p;//双亲节点
			if (item.key > p->data.key)
				p = p->rightChild;
			else p = p->leftChild;
		}
	}
	if (p == NULL)return 0;
	if (p->leftChild == NULL && p->rightChild == NULL)
	{
		free(p);
		return 1;//删除成功
	}
	else if (p->leftChild == NULL && p->rightChild != NULL)
	{
		if (q != NULL)//如果p是根节点，那q就为空
		{
			if (q->leftChild == p)q->leftChild = p->leftChild;
			if (q->rightChild == p)q->rightChild = p->leftChild;
		}
		free(p);
		return 1;
	}
	else if (p->leftChild != NULL && p->rightChild == NULL)
	{
		if (q != NULL)//如果p是根节点，那q就为空
		{
			if (q->leftChild == p)q->leftChild = p->rightChild;
			if (q->rightChild == p)q->rightChild = p->rightChild;
		}
		free(p);
		return 1;
	}
	else if (p->leftChild != NULL && p->rightChild != NULL)
	{
		//这个删除真的很复杂。。。不太会，交给以后的我去完善吧

		return 0;


	}
	return 0;
}