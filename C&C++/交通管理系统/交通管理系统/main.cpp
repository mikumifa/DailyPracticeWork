#include<stdio.h>
#include<Windows.h>
//交通管理系统，统计车辆的位置和速度
#define NMAX 100
struct Car
{
	int id;
	int speed;
	int pos;
	int exist = 1;
};
Car cars[NMAX];
int top = 0;
void write();
void save();
void show();
void add();
void del();
void quicksort();
void selectsort();
void binarySearch();
void normalSearch();
void edit();
void showMenu() {
	printf("============================================================\n");
	printf("         -----       交通管理系统                     ----- \n");
	printf("                                                            \n");
	printf("                                                            \n");
	printf("                                                            \n");
	printf("         1.    从文件中加载数据\n");
	printf("\n");
	printf("         2.    显示所有车辆\n");
	printf(" \n");
	printf("         3.    添加车辆\n");
	printf("\n");
	printf("         4.    删除车辆\n");
	printf(" \n");
	printf("         5.    按照位置排序（快排） \n");
	printf(" \n");
	printf("         6.    按照位置排序（选择排序）\n");
	printf(" \n");
	printf("         7.    二叉树搜索 \n");
	printf(" \n");
	printf("         8.    顺序查找 \n");
	printf(" \n");
	printf("         8.    修改车辆 \n");
	printf(" \n");
	printf("         0.    退出系统                                     \n");
	printf("                                                            \n");
	printf("                                                            \n");
	printf("============================================================\n");
	printf("现在请选择您要进行的操作：（请输入操作前的数字）");
}
void menu()
{
	int n, l = 0;
	showMenu();
	while (scanf("%d", &n) != EOF)
	{
		switch (n)
		{
		case 1:system("CLS"); write(); break;
		case 2:system("CLS"); show(); break;
		case 3:system("CLS"); add(); break;
		case 4:system("CLS"); del(); break;
		case 5:system("CLS"); quicksort(); break;
		case 6:system("CLS"); selectsort(); break;
		case 7:system("CLS"); binarySearch(); break;
		case 8:system("CLS"); normalSearch(); break;
		case 9:system("CLS"); edit(); break;

		case 0:system("CLS"); save(); exit(0);
		default:printf("没有此选项!\n  请重新输入!\n");
		}
		showMenu();
	}
}
int main() {
	menu();
}

void write() {
	FILE* fp = fopen("car_speed_pos.prn", "r+");
	if (!fp)
	{
		printf("打开文件失败！\n");
		exit(-1);
	}
	for (; !feof(fp); top++)
	{
		fscanf(fp, "%d%d%d%d", &cars[top].id, &cars[top].speed, &cars[top].pos, &cars[top].exist);
	}
	top--;
	fclose(fp);
}
void show() {
	printf("	次序	 编号	    速度       位置\n");
	for (int i = 0; i < top; i++)
		if (cars[i].exist == 1)
			printf("%10d %10d %10d %10d\n", i, cars[i].id, cars[i].speed, cars[i].pos);
}
void add() {
	printf("一次输入，速度,位置:");
	scanf("%d%d", &cars[top].speed, &cars[top].pos);
	cars[top].id = top + 1;
	top++;
}
void edit() {
	printf("输入修改的次序：");
	int x;
	scanf("%d", &x);
	printf("一次输入，速度,位置:");
	scanf("%d%d", &cars[x].speed, &cars[x].pos);
	printf("修改完成\n");
}
void del() {
	printf("请输入删除的车辆的次序:");
	int id;
	scanf("%d", &id);
	if (id >= top || cars[id].exist != 1)
	{
		printf("输入的不存在，退出\n");
		return;
	}
	cars[id].exist = 0;
	printf("删除成功，退出\n");
}
void quick(int left, int right) {
	if (right <= left)
		return;
	Car key = cars[left];
	int myLeft = left;
	int myRight = right;
	while (myLeft != myRight) {
		while (myLeft < myRight && cars[myRight].pos >= key.pos) {
			myRight--;
		}
		if (myRight > myLeft) {
			cars[myLeft] = cars[myRight];
		}
		while (myLeft < myRight && cars[myLeft].pos <= key.pos) {
			myLeft++;
		}
		if (myLeft < myRight) {
			cars[myRight] = cars[myLeft];
		}
	}
	cars[myLeft] = key;
	quick(left, myLeft - 1);
	quick(myLeft + 1, right);
}
void quicksort() {
	quick(0, top - 1);
}
int findMin(int left) {
	int index = 0;
	for (int i = left; i < top; i++) {
		if (i == left || cars[index].pos > cars[i].pos) {
			index = i;
		}
	}
	return index;
}
void selectsort() {
	for (int i = 0; i < top; i++) {
		int m = findMin(i);
		Car t = cars[m];
		cars[m] = cars[i];
		cars[i] = t;
	}
}
typedef struct BTNode {
	Car data;
	struct BTNode* lChild;
	struct BTNode* rChild;
}BiTNode;
void insert(BiTNode** T, Car x)
{
	//这里创建一个要插入的节点
	BiTNode* pInsert = (BiTNode*)malloc(sizeof(BiTNode));
	pInsert->data = x;
	pInsert->lChild = NULL;
	pInsert->rChild = NULL;

	if ((*T) == NULL)
	{
		*T = pInsert;
		return;
	}

	if ((*T)->lChild == NULL && x.id < (*T)->data.id)
	{
		(*T)->lChild = pInsert;
		return;
	}

	if ((*T)->rChild == NULL && x.id > (*T)->data.id)
	{
		(*T)->rChild = pInsert;
		return;
	}

	//递归实现
	if (x.id < (*T)->data.id)
		insert(&(*T)->lChild, x);

	if (x.id > (*T)->data.id)
		insert(&(*T)->rChild, x);

	return;
}
void CreateBinarySearchTree(BiTNode** T)
{
	for (int i = 0; i < top; i++) {
		insert(T, cars[i]);
	}
}
void SearchValue(BiTNode* T, int x)
{

	if (T == NULL)
	{
		return;
	}
	else
	{
		if (x < T->data.id)
		{
			SearchValue(T->lChild, x);
		}
		else if (x > T->data.id)
		{
			SearchValue(T->rChild, x);
		}
		else
		{
			if (T->data.exist != 1)
			{
				printf("已经被删除！\n");
				return;
			}
			printf("      编号	   速度       位置\n");
			printf("%10d %10d %10d\n", T->data.id, T->data.speed, T->data.pos);
			return;
		}
	}
	return;
}
void treeSearch(int key) {
	BiTNode* tree = nullptr;
	CreateBinarySearchTree(&tree);
	SearchValue(tree, key);
}
void binarySearch() {

	printf("输入要查找的key：");
	int key;
	scanf("%d", &key);
	treeSearch(key);

}
void normalSearch() {
	printf("输入要查找的key：");
	int key;
	scanf("%d", &key);
	for (int i = 0; i < top; i++) {
		if (cars[i].id == key)
		{
			if (cars[i].exist != 1) {
				printf("已经被删除！\n");
				return;
			}
			printf("      编号	   速度       位置\n");
			printf("%10d %10d %10d\n", cars[i].id, cars[i].speed, cars[i].pos);
			return;
		}
	}
}
void save() {
	FILE* fp = fopen("car_speed_pos.prn", "w");
	if (!fp)
	{
		printf("打开文件失败！\n");
		exit(-1);
	}
	for (int i = 0; i < top; i++)
	{
		fprintf(fp, "%d %d %d %d\n", cars[i].id, cars[i].speed, cars[i].pos, cars[i].exist);
	}
	fclose(fp);
}