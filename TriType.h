#include<stdio.h>
#include<malloc.h>

/*遇到的问题及其分析处理：


*/
#define elemtype int
//三元组元素
typedef struct
{
	int i;		//行号
	int j;		//列号
	elemtype d;	//元素值
}DataType;

typedef struct
{
	int id;		//行数
	int jd;		//列数
	int td;		//非零元素个数
}TriType;

//三元组的初始化
void TriTypeInitiate(TriType *tt,int i,int j)
{
	tt->id = i;
	tt->jd = j;
	tt->td = 0;
}
//设定矩阵值
int setDataType(TriType *tt, DataType *dt, int i, int j, int d)
{
	if (d != 0) tt->td++;
	if (i > tt->id || j > tt->jd || i < 0 || j < 0)
	{
		printf("输入的数据有误\n");
		return 0;
	}
	dt->i = i;
	dt->j = j;
	dt->d = d;
	return 1;
}

//打印矩阵
int printData(TriType tt, DataType dt[])
{
	int n = tt.td;
	int i,j,t;
	int flag=0;

	//行优先，行循环
	for (i = 1; i <= tt.id; i++)
	{

		//然后再到列遍历
		for (j = 1; j <= tt.jd; j++)
		{
			flag = 0;
			//询问三元表是否含该位元素
			for (t = 0; t < n; t++)
			{
				if (dt[t].i == i && dt[t].j == j)
				{
					flag = dt[t].d;
					break;
				}
			}
			printf("%d\t", flag);
		}

		printf("\n");
	}
	return 1;
}

//矩阵相加
int addData(TriType Att, DataType Adt[], TriType Btt, DataType Bdt[], TriType* Ctt, DataType(* Cdt)[])
{


	int n1 = Att.td,n2=Btt.td;
	int i, j, t,index=0;
	int flag = 0;
	int id = Att.id, jd = Att.jd;//因为AB的行列数都是一样的，所以挑A就行
	if (Att.id != Btt.id || Att.jd != Btt.jd)
	{
		return 0;//行列数不一样，就不相加了
	}
	Ctt->id = id;
	Ctt->jd = jd;
	Ctt->td = 0;//先置零，然后后面每插入一个就自动加1
	//行优先，行循环
	for (i = 1; i <= id; i++)
	{

		//然后再到列遍历
		for (j = 1; j <= jd; j++)
		{
			flag = 0;
			//询问A矩阵的三元表是否含该位元素
			for (t = 0; t < n1; t++)
			{
				if (Adt[t].i == i && Adt[t].j == j)
				{
					flag += Adt[t].d;
					break;
				}
			}
			//询问B矩阵的三元表是否含该位元素
			for (t = 0; t < n2; t++)
			{
				if (Bdt[t].i == i && Bdt[t].j == j)
				{
					flag += Bdt[t].d;
					break;
				}
			}

			//printf("%d\t", flag);
			if (flag != 0)
			{
				setDataType(Ctt,&((*Cdt)[index++]),i,j,flag);
			}
		}

		//printf("\n");
	}
}

//矩阵转置
int Transition(TriType* tt, DataType(*dt)[])
{
	int ij;
	int i, j, d;//交换媒子
	int n,flag,t;
	//交换控制表
	ij = tt->id;
	tt->id = tt->jd;
	tt->jd = ij;

	//交换表
	for (n = 0; n < tt->td; n++)
	{
		flag = 0;
		//询问三元表是否含该位元素
		for (t = n; t < tt->td; t++)
		{
			if ((*dt)[t].i == (*dt)[n].j && (*dt)[t].j == (*dt)[n].j)
			{
				flag = (*dt)[t].d;
				(*dt)[t].d = (*dt)[n].d;
				(*dt)[n].d = flag;
				break;
			}
		}
		i = (*dt)[n].i;
		(*dt)[n].i = (*dt)[n].j;
		(*dt)[n].j = i;

	}


	return 1;

}