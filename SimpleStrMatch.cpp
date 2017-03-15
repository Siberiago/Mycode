#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<string.h>
#define MAX 50000
int norstring(char s[MAX], char t[10])
{
	int i, k,flag;
	int lengths = strlen(s);
	int lengtht = strlen(t);
	for (i = 0; i < (lengths + 1 - lengtht); i++)
	{
		flag = 1;
		for(k = 0; k < lengtht; k++)
		{
			if (s[i + k] != t[k])
			{
				flag = 0;
				
			}
		}
		if (flag) return i+1; 
	}
	return flag;
	
}
void givevalue(char s[MAX], int n)
{
	int i, ran;
	for (i = 0; i < (n - 3); i++)
	{
		ran = rand() % (118 - 97 + 1) + 97;
		s[i] = ((char*)(&ran))[0];

	}
	s[n - 3] = 'x';
	s[n - 2] = 'y';
	s[n - 1] = 'z';
	s[n] = '\0';
}
int main()
{
	char s[MAX];
	char t[10]="xyz";
	int i,n;
	clock_t start, over;
	float duration;
	printf_s("输入母串规模：\n");
	scanf_s("%d", &n);
	givevalue(s, n);
	printf_s("母串创建完毕！\n");
	printf_s("母串为：\n");
	printf_s("%s", s);
	/*
	printf_s("input string t:\n");
	gets_s(s);
	printf_s("input string s:\n");
	gets_s(t);*/
	start = clock();
	i = norstring(s, t);
	over = clock();
	duration = over - start;
	if (i)printf_s("\n匹配成功且匹配位置为%d\n", i);
	else printf_s("\n匹配失败\n");
	printf_s("\n程序运行时间为%f\n", duration);

	system("pause");
	return 0;
}
