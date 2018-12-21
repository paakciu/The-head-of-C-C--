#include<stdio.h>
#include<malloc.h>

/*遇到的问题及其分析处理：


*/
typedef struct
{
	char *str;
	int len;
	int maxlen;
}String;

//字符串的初始化
void StringInitiate(String *S, int max, char *s)
{

	S->str = (char*)malloc(sizeof(char)*max);
	S->maxlen = max;
	S->len = strlen(s);
	strcpy(S->str, s);
	printf("初始化时输出：%s\n", S->str);

}

//返回字符串
char* getStr1(String *S)
{
	return S->str;
}

//字符串的插入，在S1的尾部插入S2的前n个字符
int StringInsert(String*S1, String*S2, int n)
{
	int i;
	if (n<0 || n>S2->maxlen)
	{
		printf("插入时输出：参数n不合法\n");
		return 0;
	}
	else if ((S1->len + n) > S1->maxlen)
	{
		printf("插入时输出：插入的数量太多，数组容不下\n");
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		S1->str[S1->len + i] = S2->str[i];
	}
	S1->str[S1->len + i] = '\0';
	S1->len += n;
	printf("插入时输出：%s\n", S1->str);

}

//查找字符串3在字符串1中的位置，如果找不到就在A中的m位置插入
//因为题目涉及的字符串并不含有很多重复子串，这里使用蛮力算法
int StringSearch(String *S1, String* S3,int m)
{
	int i=0,j=0;
	int flag;

	while (i < S1->len && j<S3->len)
	{
		if (S1->str[i] == S3->str[j])
		{
			i++; j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == S3->len)
	{
		flag = i - j;//找到了子串
		printf("查找中输出：找到子串位置了，在%d处\n", flag);
		return flag;
	}
	else 
	{
		flag = -1;//没找到
		if (m<0 || m>S1->maxlen)
		{
			printf("查找中输出：参数m不合法\n");
			return -11;//第一个1是没找到，第二个1表示插入失败
		}
		else if ((S1->len + m) > S1->maxlen)
		{
			printf("查找中输出：插入的数量太多，数组容不下\n");
			return -11;
		}
		for (i = S1->len; i >= m; i--) //这里i没有-1是因为要连同‘\0’符号也复制过去
		{
			S1->str[S3->len + i] = S1->str[i];
		}//所有数后移操作
		for (i = 0; i < S3->len; i++)
		{
			S1->str[m + i] = S3->str[i];
		}
		S1->len += S3->len;
		printf("查找中输出：查找不到子串后插入S1中的第%d位置中，结果为：%s\n",m,S1->str);
		//顺利插入
		return -12;//第一个1是没找到，第二个2表示顺利插入
	}

	

}