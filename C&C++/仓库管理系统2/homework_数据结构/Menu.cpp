#include"Menu.h"
#include"Function.h"
#define MAXN 100000
People team[MAXN];
int top;
void Menu()
{
	loadData(team, &top);
	int i;
loop:
	//增加数据、显示数据、删除数据、修改数据、两种排序、两种查找功能。
	printf("\n");
	printf("	         ！！！！！！欢迎！！！！！！\n");
	printf("	                 职工管理系统\n");
	printf("\n");
	printf("	*================================================*\n");
	printf("	|. . . . . . . . . . . . . . . . . . . . . . . . |\n");
	printf("	|. . . . . . . . . . . . . . . . . . .*. . . * . |\n");
	printf("	|      [ ①增加职工信息         ]        *       |\n");
	printf("	|      [ ②输出通讯费年度计划表 ]   *        *   |\n");
	printf("	|      [ ③输出该公司通讯费年度总预算费用 ] *   *|\n");
	printf("	|      [ ④输出该公司通讯费年度平均预算费用 ]    |\n");
	printf("	|      [ ⑤输出年度费用最高、最低的员工。 ]      |\n");
	printf("	|      [ 0 键退出]                               |\n");
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
		increase(team, &top);
		goto loop;
		break;
	case 2:
		show(team, &top);
		goto loop;
		break;
	case 3:
		sum(team, &top);
		goto loop;
		break;
	case 4:
		average(team, &top);
		goto loop;
		break;
	case 5:
		minAndMax(team, &top);
		goto loop;
		break;

	default:
		system("cls");
		printf("请输入正确的指令~\n");
		system("pause");  //运行暂停
		break;

	}
	saveData(team, &top);
}
