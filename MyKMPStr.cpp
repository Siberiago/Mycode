//几天中断不在纠结这个bug，之后本帅来一波进一步调试完美解决了前面伪匹配的问题,原因在于前n-1个已经匹配上了，最后一个竟然不匹配了，这是十分愚蠢的，
//于是我在之后的判断已匹配成功的字符数与子串长度比较之前又加了一个判断比较最后一位字符的if语句就完事了，汗.......
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//KMP算法的实质是不用逐次的比较子串和母串的每一个字符，因为当某一部分重叠的时候，已匹配的字符串已经失去了意义，目前还不知道证明过程
//要写出部分匹配表：partial match table
//根据匹配表获取每次移动数字；
#define MAXSTR 50000
void oppostrncpy_s(char mov[20], char t[20], int n)
{
	int i, length;
	length = strlen(t);
	for (i = 0; i < n; i++)
	{
		mov[i] = t[length - n + i];
	}
	mov[i] = '\0';
}

void getmatchtable(char t[20],int matchable[20])
{
	
	int length;
	int length1;
	int i,k;
	length = strlen(t);
	char node[20];
	char forematch[20][20];
	char backmatch[20][20];
	for (i = 0; i < length; i++)
	{
		matchable[i] = 0;
	}
	int demo=0;
	int demo2;
	int m;
	for (i = 1; i < length; i++)
	{
		m = i;
		strncpy_s(node, t, i + 1);
		
		length1 = strlen(node);

		//printf_s("%s,%d\n", node, length1);
		for (k = 1; k < length1; k++)
		{
			strncpy_s(forematch[k - 1], node, k);
		}
		forematch[k][0] = '\0';
		/*for (k = 0; k < length1-1; k++)
		{
			printf_s("%s\n", forematch[k]);
		}*/
		for (k = 1; k < length1; k++)
		{
			oppostrncpy_s(backmatch[k - 1], node, k);
		}
		backmatch[k][0] = '\0';
		/*for (k = 0; k < length1-1; k++)
		{
			printf_s("%s\n", backmatch[k]);
		}*/
		for (int j = 0; j < length1-1; j++)
		{
			for (k = j; k < length1-1; k++)
			{
				
				if (strcmp(forematch[j], backmatch[k]) == 0)
				{
					demo = strlen(backmatch[k]);
					//printf_s("!!!\n");
					
				}
				
			}
			
		}
		//printf_s("demo is %d\n", demo);
		matchable[i]=demo;
		demo = 0;
	}
}
int kmpmatch(char s[MAXSTR], char t[20])
{
	int matchtable[20];
	int length1, length2;
	int spoint=0, tpoint=0;
	length1 = strlen(s);
	length2 = strlen(t);
	int flag = 0;
	getmatchtable(t, matchtable);
	while ((length1-spoint) >= (length2))
	{
		if (s[spoint] != t[tpoint])
		{
			spoint++;
			tpoint=0;
		}
		else {
			while(tpoint+1 < length2)
			{
				if (s[spoint] == t[tpoint])
				{
					spoint++;
					tpoint++;

					if (tpoint+1 == length2)
					{
						if (s[spoint] == t[tpoint]) {
							flag = 1;
							//printf_s("%d %d\n", spoint, tpoint);
							return (spoint - length2 + 2);
						}
					}
					else;
				}
				else
				{
					spoint += (tpoint - matchtable[tpoint]+1);
				}
			}

		}
		
	}
	return flag;

	

}

int main()
{
	int matchtable[20];
	char s[MAXSTR];
	char t[20];
	char x[20];
	printf_s("请输入母串(最大容量为100为)：\n");
	gets_s(s);
	printf_s("%s\n", s);


	printf_s("请输入子串(建议不要超过20位)：\n");
	gets_s(t);
	printf_s("%s\n", t);
	int length = strlen(t);


	getmatchtable(t,matchtable);
	printf_s("\n获取部分匹配表成功！\n");
	printf_s("\n打印partial match table:\n");
	for (int i = 0; i < length; i++)
	{
		printf_s("%c ", t[i]);
			
	}
	printf_s("\n");
	
	for (int i = 0; i < length; i++)
	{
		
		printf_s("%d ", matchtable[i]);
	}
	printf_s("\n");
	int flag = kmpmatch(s, t);
	printf_s("\n匹配结果如下：\n");
	if (flag)printf_s("\n匹配成功！且匹配位为%d\n", flag);
	else printf_s("\n匹配失败！\n");

	system("pause");
	return 0;

}
void givevalue(char s[MAXSTR], int n)
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
/*
int main()
{
	char s[MAXSTR];
	char t[10] = "xyz";
	int i, n;
	clock_t start, finish;
	float duration;
	printf_s("输入母串规模：\n");
	scanf_s("%d", &n);
	givevalue(s, n);
	printf_s("母串创建完毕！\n");
	printf_s("母串为：\n");
	printf_s("%s", s);
	//计算匹配时间；
	start = clock();
	i=kmpmatch(s, t);
	finish = clock();
	duration = finish - start;
	if (i)printf_s("\n匹配成功且匹配位置为%d\n", i);
	else printf_s("\n匹配失败\n");
	printf_s("\n程序运行时间为%f\n", duration);

	system("pause");
	return 0;
	








}
*/
