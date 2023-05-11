#include <stdio.h>
#define MAX_NUM 100
#define MAX_LEN 1024
int nowStrNum = 0;
char strs[MAX_NUM][MAX_LEN] = {};

void system(const char* string);
void SubString(char s[], int pos, int n, char sub[]) {
	for (int i = 0; i < n; i++) {
		sub[i] = s[i + pos];
	}
	sub[n + 1] = '\0';
}
void printAllStr()
{
	for (int i = 0; i < nowStrNum; i++)
		printf("第%d个: %s\n", i + 1, strs[i]);
	printf("\n");
}
int strlen(char s[])
{
	for (int i = 0; i < MAX_LEN; i++)
	{
		if (s[i] == '\0')
			return i;
	}
	return -1;
}
int strcmp(const char* str1, const char* str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
		{
			return 0;
		}
		str1++;
		str2++;
	}
	return *str1 - *str2;
}
void Insert(char s[], int pos, char t[])
{
	int s_len = strlen(s);
	int t_len = strlen(t);
	char lastPart[MAX_LEN];
	for (int i = pos; i < s_len + 1; i++)
	{
		lastPart[i - pos] = s[i];
	}
	int last_len = strlen(lastPart);
	for (int i = 0; i < t_len; i++)
	{
		s[i + pos] = t[i];
	}
	for (int i = 0; i < last_len; i++)
	{
		s[i + pos + t_len] = lastPart[i];
	}
}

int main()
{
	int i;
	system("chcp 65001");
	//scanf("%s", strs[0]);
	//scanf("%s", strs[1]);
	//Insert(strs[0], 3, strs[1]);
	//printf("%s:%s", strs[0], strs[1]);
loop:
	printf("\n");
	printf("	         ！！！！！！欢迎！！！！！！\n");
	printf("	             字符串计算器\n");
	printf("\n");
	printf("	*================================================*\n");
	printf("	|. . . . . . . . . . . . . . . . . . . . . . . . |\n");
	printf("	|. . . . . . . . . . . . . . . . . . .*. . . * . |\n");
	printf("	|              [ 1. 输入字符串 ]        *       |\n");
	printf("	|              [ 2. 显示字符串 ]   *        *   |\n");
	printf("	|              [ 3. 求串长 ] *   ／ì、     *|\n");
	printf("	|              [ 4. 串连接 ]   （゜, 。フ   |\n");
	printf("	|              [ 5. 串比较 ]     1、 -ヽ    |\n");
	printf("	|              [ 6. 串复制 ]     (●ˇ∀ˇ●)  |\n");
	printf("	|              [ 7. 串插入 ]     (*^_^*)     |\n");
	printf("	|              [ 8. 求子串 ]  ( •̀ ω •́ )   |\n");
	printf("	|              [ 0.退出程序]   * じしf_,)ノ |\n");
	printf("	|. . ∩__∩. . . . . . . . . . . . . . . . . . . |\n");
	printf("	|. .( o w o) . . . . . . . . . . . . . . . . . . |\n");
	printf("	*___/ ぅ[欢迎]___________________________________*\n");
	printf("\n");
	printf("请输入指令：");
	scanf("%d", &i);
	printf("\n");
	switch (i)
	{
	case 1:
		scanf("%s", strs[nowStrNum++]);
		goto loop;
		break;
	case 2:
		printAllStr();
		goto loop;
		break;
	case 3:
	{
		// ModifyInfo(L);
		printAllStr();
		printf(" 输入一个数:要求字符串的编号:");
		int s;
		scanf("%d", &s);
		printf("长度为：%d\n", strlen(strs[s - 1]));
		goto loop;
		break;
	}
	case 4:
	{
		printAllStr();
		printf(" 输入2个数分别是,2个字符串的编号，结果会让第二个接到第一个后面：\n");
		int s, t;
		scanf("%d%d", &s, &t);
		Insert(strs[s - 1], strlen(strs[s - 1]), strs[t - 1]);
		printf("插入结果如下：\n");
		printAllStr();
		goto loop;
		break;
	}

	case 5:
	{
		printAllStr();
		printf(" 输入2个数分别是,2个字符串的编号，结果是第一个和第二个的比较结果：\n");
		int s, t;
		scanf("%d%d", &s, &t);
		if (strcmp(strs[s - 1], strs[t - 1]) > 0)

			printf("结果为前者大于后者\n");
		else if (strcmp(strs[s - 1], strs[t - 1]) == 0)
			printf("结果为前者等于后者\n");
		else
			printf("结果为前者小于后者\n");
		goto loop;
		break;
	}
	case 6:
	{
		printAllStr();
		printf(" 选择想要复制的串的编号：\n");
		int s;
		scanf("%d", &s);
		Insert(strs[nowStrNum++], 0, strs[s - 1]);
		printAllStr();
		goto loop;
		break;
	}
	case 7:
	{
		printAllStr();
		printf(" 输入三个数分别是,被插入字符串的编号，插入的位置，插入的字符串:");
		int s, pos, t;
		scanf("%d%d%d", &s, &pos, &t);
		Insert(strs[s - 1], pos, strs[t - 1]);
		printf("插入结果如下：\n");
		printAllStr();
		goto loop;
		break;
	}
	case 8:
	{
		printAllStr();
		printf(" 输入三个数分别是,想要求的字符串的编号，子串开始位置，子串的长度:");
		int i; int pos, n;
		char subStr[MAX_LEN];
		scanf("%d%d%d", &i, &pos, &n);
		SubString(strs[i - 1], pos, n, subStr);
		printf("子串为：%s", subStr);
		goto loop;
		break;
	}
	case 0:
	{

		break;
	}
	default:
		printf("请输入正确的指令~\n");
		system("pause"); // 运行暂停
		goto loop;
		break;
	}
}

void system(const char* string)
{
}
