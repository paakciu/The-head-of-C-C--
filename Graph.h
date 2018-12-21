/*实验题目：图的建立、遍历及其应用
设图结点的元素类型为char，建立一个不少于8个顶点的带权无向图G，实现以下图的各种基本操作的程序：
① 用邻接矩阵作为储结构存储图G并输出该邻接矩阵；
② 用邻接链表作为储结构存储图G并输出该邻接链表；
③ 按DFS算法输出图G中顶点的遍历序列；
④ 按BFS算法输出图G中顶点的遍历序列；
⑤ 按Prime或者Kruskal算法从某个指定的顶点出发输出图G的最小生成树；
⑥ 主函数通过函数调用实现以上各项操作。
*/

#include "顺序表"
#include <stdio.h>
#include <malloc.h>
#define MaxVertices 20
#define MaxWeight 255
typedef char DataType;


//图的邻接矩阵 天生带权值、单向边，比较容易表示
typedef struct linjiejuzhentu
{
	顺序表 Vertices;//顶点顺序表
	int edge[MaxVertices][MaxVertices];//存放变的邻接矩阵
	int numOfEdges;		//边的条数
}AdjMGraph;

//初始化n个顶点的邻接矩阵
void Initiate(AdjMGraph *G,int n)
{
	//参数表
	int j,i;
	ListInitiate(&G->Vertices); //顺序表初始化
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)G->edge[i][j]=0;
			else G->edge[i][j]=MaxWeight;
		}
	}
	G->numOfEdges=0;
}

//插入顶点
void InsertVertex(AdjMGraph *G, DataType vertex)
{
    ListInsert(&G->Vertices, G->Vertices.size, vertex);//在顺序表后面
}

//插入边   要不要加个双向边标志位呢，标记----------------------------------------------------------------------------------------
void InsertEdge(AdjMGraph *G, int v1, int v2, int weight)
//在图中增加一条有向边,无向图要增加2条
{
    if(v1 < 0 || v1 >= G->Vertices.size || v2 < 0 || v2 >= G->Vertices.size||v1==v2)
    {   	
		printf("参数v1或v2越界出错!\n");
		return;
	}
	G->edge[v1][v2] = weight;
    G->numOfEdges++;
}

//删除边  要不要加个双向边标志位呢，标记----------------------------------------------------------------------------------------
void DeleteEdge(AdjMGraph *G, int v1, int v2)
//在图中取消一条有向边，无向图要删除2条
{
	if(v1 < 0 || v1 > G->Vertices.size || v2 < 0 ||  v2 > G->Vertices.size || v1 == v2)
	{   
		printf("参数v1或v2越界出错!\n");	
		return;   
	}
	if(G->edge[v1][v2] == MaxWeight || v1 == v2) //这里的一句v1==v2是不是可以不要呢？
	{   
		printf("该边不存在!\n"); 	
		return;   
	}
	G->edge[v1][v2] = MaxWeight;
	G->numOfEdges--;
}

//取第一个邻接顶点
int GetFirstVex(AdjMGraph G, int v)
//在图G中寻找序号为v的顶点的第一个邻接顶点
//如果这样的顶点存在，则返回该邻接顶点的序号，否则返回-1
{
	int col;

	if(v < 0 || v >= G.Vertices.size)
	{
	    printf("参数v1越界出错!\n");
	    return -1;
	}
	for(col = 0; col < G.Vertices.size; col++)
	{
	    if(G.edge[v][col] > 0 &&G.edge[v][col] < MaxWeight) 
			return col;
	}
	return -1;
}

//取下一个邻接顶点 当v2为-1时，功能就是取第一个邻接顶点
int GetNextVex(AdjMGraph G, int v1, int v2)
//在图中寻找V1顶点的邻接顶点V2的下一个邻接顶点
//如果这样的邻接顶点存在，则返回该邻接顶点的序号，否则返回-1
{
	int col;
	if(v1 < 0 || v1 > G.Vertices.size || v2 < 0 || v2 > G.Vertices.size)
	{    
		printf("参数v1或v2越界出错!\n");    
		return -1;	
	}
	for(col = v2+1; col <= G.Vertices.size; col++)
	{
	    if(G.edge[v1][col] > 0 && G.edge[v1][col] < MaxWeight) 
			return col;
	}
	return -1;
}


//邻接表

//邻接边单链表的结点---邻接表的边
typedef struct Node
{
	int dest;	            //邻接边的弧头顶点序号
	int cost;				//权值
	struct Node *next;
} Edge;

//顶点的信息
typedef struct
{
	DataType data;	//顶点数据元素
	int source;		//邻接边的弧尾顶点序号
	Edge *adj;		//邻接边的头指针
} AdjLHeight;	 

//图的邻接表
typedef struct
{
    AdjLHeight a[MaxVertices];		//邻接表数组
    int numOfVerts;					//顶点个数
    int numOfEdges;					//边个数
} AdjLGraph;				

//邻接表初始化
void AdjInitiate(AdjLGraph * G)
{
	int i;
	G->numOfEdges=0;
	G->numOfVerts=0;
	for(i=0;i<MaxVertices;i++)
	{
		G->a[i].source = i;
		G->a[i].adj=NULL;
	}
}

//插入顶点
//在图G中的第i个位置插入顶点数据元素vertex
void InsertVertex(AdjLGraph * G, int i, DataType vertex)
{
	if(i>=0&&i<MaxVertices)
	{
		G->a[i].data=vertex;
		G->numOfVerts++;
	}
	else
		printf("顶点越界!\n");
}

//在图G中加入边<v1,v2> weight 带权图的权值
void InsertEdge(AdjLGraph* G, int v1, int v2, int weight)
{
	Edge* p;
	if(v1<0||v1>G->numOfVerts||v2<0||v2>G->numOfVerts)
	{
		printf("参数v1或v2出错!");
		return ;
	}
	p=(Edge* )malloc(sizeof(Edge));
	p->dest=v2;
	p->next=G->a[v1].adj;
	p->cost=weight;     //边的权值
	G->a[v1].adj=p;
	G->numOfEdges++;
}

void DeleteEdge(AdjLGraph *G, int v1, int v2)
{
	Edge * curr;
	Edge * pre;
	if(v1<0||v1>=G->numOfVerts||v2<0||v2>=G->numOfVerts)
	{	printf("参数v1或v2出错!");
		return ; 		}
	pre = NULL;
	curr = G->a[v1].adj;
	while(curr!=NULL&&curr->dest!=v2)
	{	pre=curr;
		curr=curr->next;		}
	//邻接边<v1,v2>是单链表的第一个节点
	if(curr!=NULL&&curr->dest==v2&&pre==NULL)
	{	G->a[v1].adj=curr->next;
		free(curr);
		G->numOfEdges--;	}
	//邻接边<v1,v2>不是单链表的第一个节点
	else if(curr!=NULL&&curr->dest==v2&&pre!=NULL)
	      {	pre->next=curr->next;
		free(curr);
		G->numOfEdges--;}
	else  printf("边<v1,v2>不存在!");
}

//取图G中顶点v的第一个邻接顶点
int GetFirstVex(AdjLGraph G, int v)
{
	Edge * p;
	if(v<0||v>G.numOfVerts)
	{
		printf("顶点越界!");
		return -1;

	}
	p=G.a[v].adj;
	if(p!=NULL) return p->dest;
	else return -1;
}

int GetNextVex(AdjLGraph G, int v1, int v2)
//在图中寻找V1顶点的邻接顶点V2的下一个邻接顶点
{
	Edge * p;
	if(v1<0||v1>G.numOfVerts||v2<0||v2>G.numOfVerts)
	{
		printf("参数V1或V2越界!");
		return -1;
	}
	p=G.a[v1].adj;
	while(p!=NULL)
	{
		 if(p->dest!=v2)
			p=p->next; 		
		else break;
	}
	if(p!=NULL&& p->next!=NULL) 	return p->next->dest;
	else return -1;
}

void AdjDestroy(AdjLGraph* G)
{//撤销G中所有单链表占用的存储空间
	int i;
	Edge* p,*q;
	for(i=0;i<G->numOfVerts;i++)
	{
		p=G->a[i].adj;
		while(p!=NULL)
		{
			q=p->next;
			free(p);
			p=q;
		}
	}
}
	
//邻接矩阵结构的连通图G以v为起始顶点，数组visited[]标记相应顶点是否已经访问过
void DepthFSearch(AdjMWGraph G, int v, int visited[], void Visit(DataType item))
{
	int w;
	Visit(G.Vertices.list[v]);	
	visited[v] = 1;	
	w = GetFirstVex(G, v);						while(w != -1)
	{
	      //递归访问以W为起点的图
	      if(! visited[w]) 
                  DepthFSearch(G, w, visited, Visit); 	
	      w = GetNextVex(G, v, w);
	}
}

//非连通图的深度优先遍历
void DepthFirstSearch(AdjMWGraph G, void Visit(DataType item))
{
	int i;
	int *visited = (int *)malloc(sizeof(int)*G.Vertices.size);
 
	for(i = 0; i < G.Vertices.size; i++)
	      visited[i] = 0;
 
	for(i = 0; i < G.Vertices.size; i++)
	      if(! visited[i]) 
	            DepthFSearch(G, i, visited, Visit);
 
	free(visited);
}

#include "SeqQueue.h" //队列是为了服务广度遍历的
//广度遍历
void BroadFSearch(AdjMWGraph G, int v, int visited[], 
      void Visit(DataType item))
{
	DataType u, w;
	SeqCQueue queue; 
	Visit(G.Vertices.list[v]);	
	visited[v] = 1;					 
	QueueInitiate(&queue);	
	QueueAppend(&queue, v);						
	while(QueueNotEmpty(queue))
	{
		QueueDelete(&queue, &u);
	    w = GetFirstVex(G, u);	
	    while(w != -1)					
		{
			if(!visited[w])								
			{
				Visit(G.Vertices.list[w]);	
				visited[w] = 1;							
				QueueAppend(&queue, w);					
			}
			w = GetNextVex(G, u, w);					
		}
	}
}

void BroadFirstSearch(AdjMWGraph G, void Visit(DataType item))
{
	int i;
	int *visited = (int *)malloc(sizeof(int)*G.Vertices.size);
 
	for(i = 0; i < G.Vertices.size; i++)
	      visited[i] = 0;
 
	for(i = 0; i < G.Vertices.size; i++)
	      if(! visited[i]) 
	            BroadFSearch(G, i, visited, Visit);
 
	free(visited);
}
