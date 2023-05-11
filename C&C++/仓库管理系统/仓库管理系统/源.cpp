#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 100
struct Good
{
	int id;
	char name[20];
	int cnt;
	int exist = 1;
};
Good cars[NMAX];
int top = 0;
void write();
void save();
void show();
void add();
void del();
void edit();
void quicksort();
void bubblesort();
void treeSearch();
void normalSearch();
void menu()//主菜单函数
{
	printf("*------------------------*\n");
	printf("*       仓库管理系统     *\n");
	printf("| 1.展示                 |\n");
	printf("| 2.存货                 |\n");
	printf("| 3.取货                 |\n");
	printf("| 4.修改                 |\n");
	printf("| 5.排序..1              |\n");
	printf("| 6.排序..2              |\n");
	printf("| 7.查找..1              |\n");
	printf("| 8.查找..2              |\n");
	printf("|（输入其余任意键退出）  |\n");
	printf("*------------------------*\n");
	printf("请输入以选择\n");
	int option;
	scanf("%d", &option);
	switch (option)
	{
	case 1:show();
		break;
	case 2:add();
		break;
	case 3:del();
		break;
	case 4:edit();
		break;
	case 5:quicksort();
		break;
	case 6:bubblesort();
		break;
	case 7:treeSearch();
		break;
	case 8:normalSearch();
		break;
	default:
		printf("感谢使用");
		exit(-1);
		break;
	}
	menu();
}
int main() {
	write();
	menu();
	save();
}
void write() {
	FILE* fp = fopen("good_Id_name.prn", "r+");
	for (; !feof(fp); top++)
	{
		fscanf(fp, "%d%s%d%d", &cars[top].id, cars[top].name, &cars[top].cnt, &cars[top].exist);
	}
	top -= 1;
	fclose(fp);
}
void save() {
	FILE* fp = fopen("good_Id_name.prn", "w");
	int i = 0;
	while (i < top)
	{
		fprintf(fp, "%d %s %d %d\n", cars[i].id, cars[i].name, cars[i].cnt, cars[i].exist);
	}
	fclose(fp);
}
void show() {
	printf("	次序	 编号	    名称       数量\n");
	int i = 0;
	while (i < top)
	{
		if (cars[i].exist == 1)
			printf("%10d %10d %10s %10d\n", i, cars[i].id, cars[i].name, cars[i].cnt);
		i++;
	}
}
void add() {
	printf("一次输入，名字,数量:");
	scanf("%s%d", cars[top].name, &cars[top].cnt);
	cars[top].id = top + 1;
	top++;
}
void del() {
	printf("请输入删除的次序:");
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
	Good key = cars[left];
	int myLeft = left;
	int myRight = right;
	while (myLeft != myRight) {
		while (myLeft < myRight && cars[myRight].cnt >= key.cnt) {
			myRight--;
		}
		if (myRight > myLeft) {
			cars[myLeft] = cars[myRight];
		}
		while (myLeft < myRight && cars[myLeft].cnt <= key.cnt) {
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
void bubblesort() {
	int i = 0, j = 0;
	for (i = 0; i < top; i++) {
		for (j = 0; j < top - i - 1; j++) {
			if (cars[j].cnt > cars[j + 1].cnt) {
				Good tmp = cars[j];
				cars[j] = cars[j + 1];
				cars[j + 1] = tmp;
			}
		}
	}
}
typedef struct BTNode {
	Good data;
	struct BTNode* lChild;
	struct BTNode* rChild;
}BiTNode;
void insert(BiTNode** T, Good x)
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

	if ((*T)->lChild == NULL && strcmp(x.name, (*T)->data.name) < 0)
	{
		(*T)->lChild = pInsert;
		return;
	}

	if ((*T)->rChild == NULL && strcmp(x.name, (*T)->data.name) > 0)
	{
		(*T)->rChild = pInsert;
		return;
	}

	//递归实现
	if (strcmp(x.name, (*T)->data.name) < 0)
		insert(&(*T)->lChild, x);

	if (strcmp(x.name, (*T)->data.name) > 0)
		insert(&(*T)->rChild, x);

	return;
}
void CreateBinarySearchTree(BiTNode** T)
{
	for (int i = 0; i < top; i++) {
		insert(T, cars[i]);
	}
}
void SearchValue(BiTNode* T, char* x)
{

	if (T == NULL)
	{
		return;
	}
	else
	{
		if (strcmp(x, T->data.name) < 0)
		{
			//查左子树
			SearchValue(T->lChild, x);
		}
		else if (strcmp(x, T->data.name) > 0)
		{
			//查右子树
			SearchValue(T->rChild, x);
		}
		else
		{
			//找到该值
			if (T->data.exist != 1)
			{
				printf("该员工已经被删除！\n");
				return;
			}
			printf("	 编号	    名称       数量\n");
			printf("%10d %10s %10d\n", T->data.id, T->data.name, T->data.cnt);
			return;
		}
	}
	return;
}
void treeSearch() {
	BiTNode* tree = nullptr;
	CreateBinarySearchTree(&tree);
	printf("输入要查找的key：");
	char key[20];
	scanf("%s", key);
	SearchValue(tree, key);
}
void normalSearch() {
	printf("输入要查找的key：");
	char key[20];
	scanf("%s", key);
	for (int i = 0; i < top; i++) {
		if (strcmp(key, cars[i].name) == 0) {
			//找到该值
			if (cars[i].exist != 1)
			{
				printf("被删除！\n");
				break;
			}
			printf("	 编号	    名称       数量\n");
			printf("%10d %10s %10d\n", cars[i].id, cars[i].name, cars[i].cnt);
			break;
		}
	}
}
void edit() {
	printf("输入要修改的次序：\n");
	int n;
	scanf("%d", &n);
	printf("一次输入，名字,数量:");
	scanf("%s%d", cars[n].name, &cars[n].cnt);
	printf("修改成功\n");

}