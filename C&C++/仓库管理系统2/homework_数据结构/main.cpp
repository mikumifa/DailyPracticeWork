#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct tp
{
	char name[20];
	char brand[20];
	int num;
	double price;
	int year;
	int month;
	int day;
	char sper[20];
	char tper[20];
};
tp s[10000], t[10000], x[10000], y[10000], in[10000], out[10000], no[10000], no1[10000], no2[10000];
void menu();               //主菜单函数
void write();              //创建仓库函数
void find();               //查询库存函数
void findmenu();           //查询菜单函数
void findname();           //按电器名查询
void findbrand();          //按品牌名查询
void findsper();           //按送货人查询,输出该送货人对应的入库记录。
void findtper();           //按提货人查询,输出该提货人对应的出库记录。
void findupname();         //按电器名称从小到大顺序输出所有库存,并输出排序后的电器品牌名称。
void finddownnum();        //按库存数量由高到低输出所有库存
void record();             //记录仓库函数
void takeout();            //取出仓库函数
void tongji();         //统计函数目录 
void tongji1();            //输人一个日期(年·月),统计该月每种电器的出库数目,并输出
void tongji2();            //输人一个日期(年·月),统计该月每种品牌的电器的出库数目,并输出。
void tongji3();            //统计该仓库的商品总价值(所有人库记录中入库价格X人库数量)。
void tongji4();            //计算该出库的总利润(所有出库记录(出库价格一人库价格)X出库数量)
int readkucun();           //读取库存记录文件中所有结构体的个数 
int readruku();           //读取入库记录文件中所有结构体的个数 
int readchuku();          //读取出库记录文件中所有结构体的个数 
void end();               //结束退出函数
int main()
{
	menu();
	return 0;
}
void menu()
{
	int n, l = 0;
	printf("============================================================\n");
	printf("                                                            \n");
	printf(" -----*****欢 迎 使 用 仓 库 物 资 管 理 系 统 ! *****----- \n");
	printf("                                                            \n");
	printf("============================================================\n");
	printf("                                                            \n");
	printf(" 您可以进行以下操作：                                       \n");
	printf("                                                            \n");
	printf("         1.    仓库初始化                                   \n");
	printf("                                                            \n");
	printf("         2.    查询库存                                     \n");
	printf("                                                            \n");
	printf("         3.    物资存入                                     \n");
	printf("                                                            \n");
	printf("         4.    物资取出                                     \n");
	printf("                                                            \n");
	printf("         5.    统计物资                                     \n");
	printf("                                                            \n");
	printf("         0.    退出系统                                     \n");
	printf("                                                            \n");
	printf("                                                            \n");
	printf("============================================================\n");
	printf("现在请选择您要进行的操作：（请输入操作前的数字）");
	while (scanf("%d", &n) != EOF)
	{
		switch (n)
		{
		case 1:system("CLS"); write(); break;
		case 2:system("CLS"); find(); break;
		case 3:system("CLS"); record(); break;
		case 4:system("CLS"); takeout(); break;
		case 5:system("CLS"); tongji(); break;
		case 0:system("CLS"); end(); exit(0);
		default:printf("没有此选项!\n  请重新输入!\n");
		}
	}
}
void write()
{
	FILE* fp, * fp3;
	int i, a, c = 0, n;
	fp = fopen("库存记录.txt", "w");
	fp3 = fopen("入库记录.txt", "w");
	rewind(fp);	rewind(fp3);
	printf("============================================================\n");
	printf("请输入仓库中电器信息的组数!\n        ps:相同电器但是不同品牌电器算多种！\n");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		printf("开始写入第%d组\n", i + 1);
		printf("请输入电器名称：");
		scanf("%s", s[i].name);
		printf("请输入电器品牌名称：");
		scanf("%s", s[i].brand);
		printf("请输入电器数量：");
		a = scanf("%d", &s[i].num);
		while (a != 1)
		{
			while (getchar() != '\n');   //输入非法字符后输一个删一个，直到打入回车结束循坏 
			printf("输入数量格式错误,请重新输入\n"); //  清空缓存区非法字符 
			a = scanf("%d", &s[i].num);
			if (getchar() == '\n')
			{
				break;//结束98行的循坏 
			}
		}
		while (s[i].num < 0)
		{
			printf("输入数量错误,请重新输入\n");
			a = scanf("%d", &s[i].num);
			if (a != 1)
			{
				while (getchar() != '\n');
				printf("输入数量格式错误,请重新输入\n");
				a = scanf("%d", &s[i].num);
				//
				if (getchar() == '\n')
				{
					break;
				}
			}
		}
		printf("请输入电器单价：");
		a = scanf("%lf", &s[i].price);
		while (a != 1)
		{
			while (getchar() != '\n');
			printf("输入价格格式错误,请重新输入\n");
			a = scanf("%lf", &s[i].price);
			if (getchar() == '\n')
			{
				break;
			}
		}
		while (s[i].price < 0)
		{
			printf("输入价格错误,请重新输入\n");
			a = scanf("%lf", &s[i].price);
			if (a != 1)
			{
				while (getchar() != '\n');
				printf("输入价格格式错误,请重新输入\n");
				a = scanf("%lf", &s[i].price);
				//
				if (getchar() == '\n')
				{
					break;
				}
			}
		}
		printf("请输入存货时间： <年月日之间用空格隔开>例:2016 12 01\n");
		scanf("%d%d%d", &s[i].year, &s[i].month, &s[i].day);
		printf("请输入送货人：");
		scanf("%s", s[i].sper);
	}
	fwrite(s, sizeof(tp), n, fp);
	fwrite(s, sizeof(tp), n, fp3);
	fclose(fp); fclose(fp3);
	printf("电器信息写入完成！\n请按回车键返回主界面！\n");
	getchar(); getchar();
	system("CLS");
	menu();
}
void findmenu()
{
	int n;
	printf("============================================================\n");
	printf("1. 按电器名查询\n");
	printf("2. 按品牌名查询\n");
	printf("3. 按送货人查询\n");
	printf("4. 按提货人查询\n");
	printf("5. 按电器名称由小到大顺序输出所有库存\n");
	printf("6. 按库存数量由高到低输出所有库存\n");
	printf("0. 返回主菜单\n");
	printf("现在请选择您要进行的操作：（请输入操作前的数字）");
	while (scanf("%d", &n) != EOF)
		switch (n)
		{
		case 1:system("CLS"); findname(); break;
		case 2:system("CLS"); findbrand(); break;
		case 3:system("CLS"); findsper(); break;
		case 4:system("CLS"); findtper(); break;
		case 5:system("CLS"); findupname(); break;
		case 6:system("CLS"); finddownnum(); break;
		case 0:system("CLS"); menu(); break;
		default:printf("没有此选项!\n  请重新输入!\n");
		}
}
void findname()
{
	char name[10], ch = 'y';
	int i, k, n, bn;
	bn = readkucun();
	while (ch == 'y' || ch == 'Y')
	{
		system("CLS");
		printf("============================================================\n");
		printf("请输入要查询的电器名称：\n");
		getchar();
		gets_s(name);
		k = -1;
		for (i = 0; i < bn; i++)
		{
			if (strcmp(t[i].name, name) == 0)
			{
				printf("该电器信息如下：\n");
				k = i;
				printf("电器名称：%s，电器品牌：%s，库存数量：%d，电器单价：%lf，入库时间：%d.%d.%d，送货人：%s\n", t[k].name, t[k].brand, t[k].num, t[k].price, t[k].year, t[k].month, t[k].day, t[k].sper);
			}
		}
		if (k == -1)
		{
			printf("抱歉，本仓库中无此电器！\n");
		}
		printf("\n是否继续查询？<y/n>\n");
		ch = getchar();
	};
	printf("将返回上一级菜单！\n请按回车键确认！\n");
	getchar(); getchar();
	system("CLS");
	findmenu();
}
void findbrand()
{
	char brandName[10], ch = 'y';
	int i, k, n, bn;
	bn = readkucun();
	while (ch == 'y' || ch == 'Y')
	{
		system("CLS");
		printf("============================================================\n");
		printf("请输入要查询的品牌名称：\n");
		getchar();
		gets_s(brandName);
		k = -1;
		for (i = 0; i < bn; i++)
		{
			if (strcmp(t[i].brand, brandName) == 0)
			{
				printf("该电器信息如下：\n");
				k = i;
				printf("电器名称：%s，电器品牌：%s，库存数量：%d，电器单价：%lf，入库时间：%d.%d.%d，送货人：%s\n", t[k].name, t[k].brand, t[k].num, t[k].price, t[k].year, t[k].month, t[k].day, t[k].sper);
			}
		}
		if (k == -1)
		{
			printf("抱歉，本仓库中无此电器！\n");

		}
		printf("\n是否继续查询？<y/n>\n");
		ch = getchar();
	};
	printf("将返回上一级菜单！\n请按回车键确认！\n");
	getchar(); getchar();
	system("CLS");
	findmenu();
}
void findsper()           // 按送货人查询  入库
{
	char sper[10], ch = 'y';
	int i, k, n, bn1;
	bn1 = readruku();
	FILE* fp1;
	fp1 = fopen("入库记录.txt", "rb+");
	if (fp1 == NULL)
	{
		printf("该仓库中未添加任何电器！\n");
		exit(0);
	}
	fread(&y, sizeof(tp), bn1, fp1);
	fclose(fp1);
	while (ch == 'y' || ch == 'Y')
	{
		system("CLS");
		printf("============================================================\n");
		printf("请输入要查询的送货人：\n");
		getchar();
		gets_s(sper);
		k = -1;
		for (i = 0; i < bn1; i++)
		{
			if (strcmp(y[i].sper, sper) == 0)
			{
				printf("该电器信息如下：\n");
				k = i;
				printf("电器名称：%s，电器品牌：%s，库存数量：%d，电器单价：%lf，入库时间：%d.%d.%d，送货人：%s\n", y[k].name, y[k].brand, y[k].num, y[k].price, y[k].year, y[k].month, y[k].day, y[k].sper);
			}
		}
		if (k == -1)
		{
			printf("抱歉，本仓库中无此存货人存入的电器！\n");
		}
		printf("\n是否继续查询？<y/n>\n");
		ch = getchar();
	};
	printf("将返回上一级菜单！\n请按回车键确认！\n");
	getchar(); getchar();
	system("CLS");
	findmenu();
}
void findtper()          //按提货人查询   出库
{
	char tper[10], ch = 'y';
	int i, k, n, bn2;
	bn2 = readchuku();
	FILE* fp2;
	fp2 = fopen("出库记录.txt", "rb+");
	if (fp2 == NULL)
	{
		printf("该仓库中未提出任何电器！\n");
		exit(0);
	}
	fread(&x, sizeof(tp), bn2, fp2);
	fclose(fp2);
	while (ch == 'y' || ch == 'Y')
	{
		system("CLS");
		printf("============================================================\n");
		printf("请输入要查询的提货人：\n");
		getchar();
		gets_s(tper);
		k = -1;
		for (i = 0; i < bn2; i++)
		{
			if (strcmp(x[i].tper, tper) == 0)
			{
				printf("该电器信息如下：\n");
				k = i;
				printf("电器名称：%s，电器品牌：%s，库存数量：%d，电器单价：%lf，出库时间：%d.%d.%d，提货人：%s\n", x[k].name, x[k].brand, x[k].num, x[k].price, x[k].year, x[k].month, x[k].day, x[k].tper);
			}
		}
		if (k == -1)
		{
			printf("抱歉，本仓库中无此提货人提出的电器！\n");
		}
		printf("\n是否继续查询？<y/n>\n");
		ch = getchar();
	};
	printf("将返回上一级菜单！\n请按回车键确认！\n");
	getchar(); getchar();
	system("CLS");
	findmenu();
}
void findupname()       //电器名称大小顺序输出所有库存
{
	int bn;
	bn = readkucun();
	printf("============================================================\n");
	FILE* fp;
	fp = fopen("库存记录.txt", "rb+");
	if (fp == NULL)
	{
		printf("该仓库中无库存！\n");
		exit(0);
	}
	fread(&s, sizeof(tp), bn, fp);
	int i, j, k;
	for (i = 0; i < bn - 1; i++)
	{
		for (j = 0; j < bn - 1 - i; j++)
		{
			if (k = strcmp(s[j].name, s[j + 1].name) > 0)
			{
				t[1] = s[j + 1];
				s[j + 1] = s[j];
				s[j] = t[1];
			}
		}
	}
	for (i = 0; i < bn; i++)
		printf("%d. 电器名称：%s，电器品牌：%s，库存数量：%d，电器单价：%lf，入库时间：%d.%d.%d，送货人：%s\n", i + 1, s[i].name, s[i].brand, s[i].num, s[i].price, s[i].year, s[i].month, s[i].day, s[i].sper);
	printf("\n输出完成！请按回车键返回上一级！\n");
	getchar(); getchar();
	system("CLS");
	findmenu();
}
void finddownnum()        //按库存数量由高到低输出所有库存
{
	int bn;
	bn = readkucun();
	printf("============================================================\n");
	FILE* fp;
	fp = fopen("库存记录.txt", "rb+");
	if (fp == NULL)
	{
		printf("该仓库中无库存！\n");
		exit(0);
	}
	fread(&s, sizeof(tp), bn, fp);
	int i, j;
	for (i = 0; i < bn - 1; i++)
		for (j = 0; j < bn - 1 - i; j++)
		{
			if (s[j].num < s[j + 1].num)
			{
				t[1] = s[j + 1];
				s[j + 1] = s[j];
				s[j] = t[1];
			}
		}
	for (i = 0; i < bn; i++)
		printf("%d.  电器名称：%s，电器品牌：%s，库存数量：%d，电器单价：%lf，入库时间：%d.%d.%d，存货人：%s\n", i + 1, s[i].name, s[i].brand, s[i].num, s[i].price, s[i].year, s[i].month, s[i].day, s[i].sper);
	printf("============================================================\n");
	printf("\n输出完成！请按回车键返回上一级！\n");
	getchar(); getchar();
	system("CLS");
	findmenu();
}
int readkucun()//库存记录文件中结构体的个数
{
	FILE* fb;
	int bn = 0;
	fb = fopen("库存记录.txt", "rb+");
	if (fb == NULL)
	{
		return bn;
	}
	while (!feof(fb))//判定文件是否读取完毕 , 如果返回 true 说明文件没有读取完毕 , 返回 false , 说明文件读取完毕
	{//表示没有到达末尾 
		if (fread(&no[bn], sizeof(tp), 1, fb))
			bn++;
	}
	fclose(fb);
	return bn;
}
int readruku()//入库记录文件中结构体的个数
{
	FILE* fb;
	int bn1 = 0;
	fb = fopen("入库记录.txt", "rb+");
	if (fb == NULL)
	{
		return bn1;
	}
	while (!feof(fb))
	{
		if (fread(&no1[bn1], sizeof(tp), 1, fb))
			bn1++;
	}
	fclose(fb);
	return bn1;
}
int readchuku()//出库记录文件中结构体的个数
{
	FILE* fb;
	int bn2 = 0;
	fb = fopen("出库记录.txt", "rb+");
	if (fb == NULL)
	{
		return bn2;
	}
	while (!feof(fb))
	{
		if (fread(&no2[bn2], sizeof(tp), 1, fb))
			bn2++;
	}
	fclose(fb);
	return bn2;
}
void find()
{
	int bn;
	FILE* fp;
	fp = fopen("库存记录.txt", "rb+");
	if (fp == NULL)
	{
		printf("该仓库中无库存！\n");
		exit(0);
	}
	rewind(fp);
	bn = readkucun();
	fread(&t, sizeof(tp), bn, fp);
	getchar();
	findmenu();
	fclose(fp);
}
void record()   //记录仓库函数 入库 
{
	printf("============================================================\n");
	int bn, bn1;
	struct tp jia;
	FILE* fp1, * fp;
	int i = 0, j, n = 0;
	char ch = 'y';
	printf("请输入要加入仓库的电器信息：\n");
	while (ch == 'y' || ch == 'Y')
	{
		fp1 = fopen("入库记录.txt", "ab+");
		if (fp1 == NULL)
		{
			printf("该仓库中未添加任何电器！\n");
			exit(0);
		}
		fp = fopen("库存记录.txt", "ab+");
		bn = readkucun();
		bn1 = readruku();
		printf("请输入电器名称：");
		scanf("%s", jia.name);
		printf("请输入电器品牌：");
		scanf("%s", jia.brand);
		printf("请输入电器数量：");
		scanf("%d", &jia.num);
		printf("请输入电器进货单价：");
		scanf("%lf", &jia.price);
		printf("请输入送货时间： <ps: 年月日之间用空格隔开>  例:2016 12 01\n");
		scanf("%d%d%d", &jia.year, &jia.month, &jia.day);
		printf("请输入送货人：");
		scanf("%s", jia.sper);
		fwrite(&jia, sizeof(tp), 1, fp1);
		fwrite(&jia, sizeof(tp), 1, fp);
		fclose(fp1); fclose(fp);
		printf("是否继续输入？<y/n>\n");
		getchar();
		ch = getchar();
	}
	printf("将返回上一级菜单！\n  请按回车键确认！\n");
	getchar();
	system("CLS");
	menu();
}
void takeout()     //出库
{
	struct tp chu;
	printf("==============================================================\n");
	int bn, bn2, i, j;
	char ch = 'y';
	FILE* fp, * fp2;
	bn = readkucun();
	bn2 = readchuku();
	printf("请输入要提出仓库的电器信息：\n");
	while (ch == 'y' || ch == 'Y')
	{
		int flag = 0;
		fp = fopen("库存记录.txt", "rb+");
		if (fp == NULL)
		{
			printf("无电器信息记录！\n");
			exit(0);
		}
		for (i = 0; i < bn; i++)
		{
			fread(&s[i], sizeof(tp), 1, fp);
		}
		fclose(fp);
		fp2 = fopen("出库记录.txt", "ab+");
		if (fp2 == NULL)
		{
			printf("无电器信息记录！\n");
			exit(0);
		}
		printf("请输入电器名称：");
		scanf("%s", chu.name);
		printf("请输入电器品牌：");
		scanf("%s", chu.brand);
		printf("请输入电器数量：");
		scanf("%d", &chu.num);
		printf("请输入电器出售单价：");
		scanf("%lf", &chu.price);
		printf("请输入提货时间： <ps: 年月日之间用空格隔开>  例:2016 12 01\n");
		scanf("%d%d%d", &chu.year, &chu.month, &chu.day);
		printf("请输入提货人：");
		scanf("%s", chu.tper);
		getchar();
		fwrite(&chu, sizeof(tp), 1, fp2);
		fclose(fp2);
		for (i = 0; i < bn; i++)
		{
			if ((strcmp(chu.name, s[i].name) == 0) && (strcmp(chu.brand, s[i].brand) == 0))
			{
				flag = 1;
			}
		}
		if (flag == 1)
		{
			for (i = 0; i < bn; i++)
			{
				if ((strcmp(chu.name, s[i].name) == 0) && (strcmp(chu.brand, s[i].brand) == 0))
				{
					if (chu.num <= s[i].num)
					{
						s[i].num = s[i].num - chu.num;
					}
					else
					{
						printf("库存不足！无法提出！\n");
						printf("请按回车键返回！");
						getchar();
						system("CLS");
						menu();
					}
				}
			}
			fopen("库存记录.txt", "wb+");
			for (i = 0; i < bn; i++)
			{
				fwrite(&s[i], sizeof(tp), 1, fp);
			}
			fclose(fp);
			printf("\n出库完成！ 是否继续输入？<y/n>\n");
			ch = getchar();
		}
		else
		{
			printf("此电器不存在，是否继续输入？<y/n>\n");
			ch = getchar();
		}
	}
	getchar();
	printf("将返回上一级菜单！\n 请按回车键确认！\n");
	getchar();
	system("CLS");
	menu();
}
void tongji()
{
	int n;
	system("CLS");
	printf("==============================================================\n");
	printf("1. 统计该月每种电器的出库数目\n");
	printf("2. 统计该月每种品牌的电器的出库数目\n");
	printf("3. 仓库电器总价值\n");
	printf("4. 出库电器总利润\n");
	printf("0. 返回主菜单\n");
	printf("请选择要进行的操作：（0到4）\n");
	scanf("%d", &n);
	getchar();
	while (n != 0 && n != 1 && n != 2 && n != 3 && n != 4)
	{
		printf("没有此选项!\n  请重新输入!\n");
		scanf("%d", &n);
		getchar();
	}
	switch (n)
	{
	case 1:tongji1(); break;//输人一个日期(年·月),统计该月每种电器的出库数目,并输出
	case 2:tongji2(); break;//输入一个日期(年·月),统计该月每种品牌的电器的出库数目,并输出。
	case 3:tongji3(); break;//统计该仓库的商品总价值(所有人库记录中入库价格X人库数量)。
	case 4:tongji4(); break;//计算该出库的总利润(所有出库记录(出库价格一人库价格)X出库数量)
	case 0:system("CLS"); menu(); break;
	}
}
void tongji1()//输人一个日期(年·月),统计该月每种电器的出库数目,并输出
{
	FILE* fp;
	int bn1, i, year, month, k = 0;
	bn1 = readruku();
	system("CLS");
	printf("==============================================================\n");
	fp = fopen("出库记录.txt", "rb+");
	if (fp == NULL)
	{
		printf("无电器信息记录！\n");
		exit(0);
	}
	for (i = 0; i < bn1; i++)
	{
		fread(&s, sizeof(tp), bn1, fp);
	}
	printf("请输入一个日期（年 月 如 2017 01 ）：\n");
	scanf("%d%d", &year, &month);
	for (i = 0; i < bn1; i++)
	{
		if ((s[i].year == year) && (s[i].month == month))
		{
			printf("电器名称：%s\n出库数目：%d\n", s[i].name, s[i].num);
			k++;
		}
	}
	if (k == 0)
		printf("库存记录中不存在此种电器！\n");
	fclose(fp);
	printf("统计完成，请按回车键返回！\n");
	getchar();
	getchar();
	system("CLS");
	tongji();
}
void tongji2()
{
	FILE* fp;
	int bn1, i, year, month, k = 0;
	bn1 = readruku();
	system("CLS");
	printf("==============================================================\n");
	fp = fopen("出库记录.txt", "rb+");
	if (fp == NULL)
	{
		printf("无电器信息记录！\n");
		exit(0);
	}
	for (i = 0; i < bn1; i++)
	{
		fread(&s, sizeof(tp), bn1, fp);
	}
	printf("请输入一个日期（年 月 如 2017 01）：\n");
	scanf("%d%d", &year, &month);
	for (i = 0; i < bn1; i++)
	{
		if ((s[i].year == year) && (s[i].month == month))
		{
			printf("电器名称：%s\n品牌名称：%s\n出库数目：%d\n", s[i].name, s[i].brand, s[i].num);
			k++;
		}
	}
	if (k == 0)
		printf("库存记录中不存在此种电器！\n");
	fclose(fp);
	printf("统计完成，请按回车键返回！\n");
	getchar();
	getchar();
	system("CLS");
	tongji();
}
void tongji3()
{
	FILE* fp;
	int bn1, i;
	long long int total = 0;
	bn1 = readruku();
	system("CLS");
	printf("==============================================================\n");
	fp = fopen("入库记录.txt", "rb+");
	if (fp == NULL)
	{
		printf("无电器信息记录！\n");
		exit(0);
	}
	for (i = 0; i < bn1; i++)
	{
		fread(&s[i], sizeof(tp), 1, fp);
	}
	fclose(fp);
	for (i = 0; i < bn1; i++)
	{
		total += (s[i].num * s[i].price);
	}
	printf("商品总价值为%d\n", total);
	printf("统计完成，请按回车键返回！\n");
	getchar();
	system("CLS");
	tongji();
}
void tongji4()
{
	FILE* fp1, * fp2;
	int bn, bn2, i;
	long long int money = 0;
	bn = readkucun();
	bn2 = readchuku();
	system("CLS");
	printf("==============================================================\n");
	fp1 = fopen("库存记录.txt", "rb+");
	if (fp1 == NULL)
	{
		printf("无电器信息！\n");
		exit(0);
	}
	for (i = 0; i < bn; i++)
	{
		fread(&s[i], sizeof(tp), 1, fp1);
	}
	fclose(fp1);
	fp2 = fopen("出库记录.txt", "rb+");
	if (fp2 == NULL)
	{
		printf("无电器信息！\n");
		exit(0);
	}
	for (i = 0; i < bn2; i++)
	{
		fread(&t[i], sizeof(tp), 1, fp2);
	}
	fclose(fp2);
	for (i = 0; i < bn2; i++)
	{
		money += ((t[i].price - s[i].price) * t[i].num);
	}
	printf("总利润为%d\n", money);
	printf("统计完成，请按回车键返回！\n");
	getchar();
	system("CLS");
	tongji();
}
void end()
{
	printf("==============================================================\n");
	printf("                                                              \n");
	printf("                                                              \n");
	printf("                                                              \n");
	printf("            感 谢 使 用 本 系 统 ！                           \n");
	printf("                                                              \n");
	printf("             再 见 ！                                         \n");
	printf("                                                              \n");
	printf("                                                              \n");
	printf("                                                              \n");
	printf("                                                              \n");
	printf("==============================================================\n");
}
