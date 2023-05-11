#include"Function.h"
int statusMoney(char* key) {
	if (strcmp(key, "副经理") == 0)
		return 1500;
	if (strcmp(key, "采购部") == 0)
		return 1000;
	if (strcmp(key, "销售部") == 0)
		return 2000;
	if (strcmp(key, "商品生产") == 0)
		return 600;
	if (strcmp(key, "技术研发") == 0)
		return 200;
	if (strcmp(key, "服务部") == 0)
		return 1800;
	if (strcmp(key, "业务总监") == 0)
		return 1200;
	if (strcmp(key, "总经理") == 0)
		return 2500;
	return 1000;
}
int calMoney(People p) {
	return p.workTime * statusMoney(p.status);
}
void loadData(People team[], int* top) {
	FILE* fp = fopen("data.prn", "r+");
	if (!fp)
	{
		printf("打开文件失败！\n");
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%d%d", team[*top].id, team[*top].name, team[*top].status, &team[*top].workTime, &team[*top].hava);
		if (team[*top].id[0] != 'A')
			break;
		//printf("%s %s %s %d\n", team[*top].id, team[*top].name, team[*top].status, team[*top].workTime);
		(*top)++;
	}
	fclose(fp);
}
void saveData(People team[], int* top) {
	FILE* fp = fopen("data.prn", "w");
	if (!fp)
	{
		printf("打开文件失败！\n");
	}
	for (int i = 0; i < *top; i++)
	{
		fprintf(fp, "%s %s %s %d %d\n", team[i].id, team[i].name, team[i].status, team[i].workTime, team[i].hava);
	}
	fclose(fp);
}
void increase(People team[], int* top) {
	People temp;
	int id = *top + 1;
	char t[20] = { 'A' };
	strcpy(temp.id, t);
	printf("请输入添加的员工的名字:");
	scanf("%s", &temp.name);

	int chosen;
loop:
	printf("请选择添加的员工的职业(1.副经理，2.采购部，3.销售部，4.商品生产，5.技术研发，6.服务部，7.业务总监，8.总经理):\n");
	scanf("%d", &chosen);
	switch (chosen)
	{
	case 1:strcpy(temp.status, "副经理"); break;
	case 2:strcpy(temp.status, "采购部"); break;
	case 3:strcpy(temp.status, "销售部"); break;
	case 4:strcpy(temp.status, "商品生产"); break;
	case 5:strcpy(temp.status, "技术研发"); break;
	case 6:strcpy(temp.status, "服务部"); break;
	case 7:strcpy(temp.status, "业务总监"); break;
	case 8:strcpy(temp.status, "总经理"); break;
	default:
		goto loop;
		break;
	}
	printf("请输入添加的员工的预计报销总时间:");
	scanf("%d", &temp.workTime);
	temp.hava = 1;
	team[(*top)++] = temp;
	printf("成功添加的第%d员工,ID为%s！！！\n", *top, team[*top - 1].id);
}
void updateValue(People team[], int top) {
	for (int i = 0; i < top; i++) {
		team[i].statuesMoney = statusMoney(team[i].status);
		team[i].yearValue = team[i].statuesMoney * team[i].workTime;
	}
}
void show(People team[], int* top) {
	updateValue(team, *top);
	printf("员工编号\t姓名\t  岗位类别\t岗位标准\t预计报销总时间\t年度费用\n");
	for (int i = 0; i < *top; i++)
		if (team[i].hava == 1)
			printf("%s          %s       %s         %d         %d             %d\n", team[i].id, team[i].name, team[i].status, team[i].statuesMoney, team[i].workTime, team[i].yearValue);
}

void sum(People team[], int* top) {
	long long int sum = 0;
	for (int i = 0; i < *top; i++) {
		team[i].statuesMoney = statusMoney(team[i].status);
		team[i].yearValue = team[i].statuesMoney * team[i].workTime;
		sum += team[i].yearValue;
	}
	printf("该公司通讯费年度总预算费用:%lld\n", sum);
}
void average(People team[], int* top) {
	long long int sum = 0;
	for (int i = 0; i < *top; i++) {
		team[i].statuesMoney = statusMoney(team[i].status);
		team[i].yearValue = team[i].statuesMoney * team[i].workTime;
		sum += team[i].yearValue;
	}
	printf("该公司通讯费年度平均预算费用:%lld\n", sum / (*top));
}
void minAndMax(People team[], int* top) {
	int min = -1; int max = -1;
	int minN = 0; int maxN = 0;
	for (int i = 0; i < *top; i++) {
		team[i].statuesMoney = statusMoney(team[i].status);
		team[i].yearValue = team[i].statuesMoney * team[i].workTime;
		if (i == 0 || min > team[i].yearValue)
			min = team[i].yearValue, minN = i;
		if (i == 0 || max < team[i].yearValue)
			max = team[i].yearValue, maxN = i;
	}
	int i = minN;
	printf("最小的员工编号\t姓名\t  岗位类别\t岗位标准\t预计报销总时间\t年度费用\n");
	printf("%s          %s       %s         %d         %d             %d\n", team[i].id, team[i].name, team[i].status, team[i].statuesMoney, team[i].workTime, team[i].yearValue);
	i = maxN;
	printf("最大的员工编号\t姓名\t  岗位类别\t岗位标准\t预计报销总时间\t年度费用\n");
	printf("%s          %s       %s         %d         %d             %d\n", team[i].id, team[i].name, team[i].status, team[i].statuesMoney, team[i].workTime, team[i].yearValue);

}