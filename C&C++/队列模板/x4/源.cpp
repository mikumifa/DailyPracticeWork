
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 20
#define INFINITE 9999
#define VRType int
#define InfoType int
#define VertexType int


typedef struct QueueNode
{
	VertexType data;
	struct QueueNode* next;
}QNode;

typedef struct Queue
{
	QNode* head;
	QNode* tail;

	//size_t size;
}Queue;
void QueueInit(Queue* pq)
{
	pq->head = pq->tail = NULL;
}
void QueueDestory(Queue* pq)
{
	QNode* cur = pq->head;
	while (cur)
	{
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}

	pq->head = pq->tail = NULL;
}

void QueuePush(Queue* pq, VertexType x)
{
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	newnode->data = x;
	newnode->next = NULL;

	if (pq->tail == NULL)
	{
		pq->head = pq->tail = newnode;
	}
	else
	{
		pq->tail->next = newnode;
		pq->tail = newnode;
	}
}

void QueuePop(Queue* pq)
{

	if (pq->head->next == NULL)
	{
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else
	{
		QNode* next = pq->head->next;
		free(pq->head);
		pq->head = next;
	}
}

bool QueueEmpty(Queue* pq)
{
	return pq->head == NULL;
}

size_t QueueSize(Queue* pq)
{
	QNode* cur = pq->head;
	size_t size = 0;
	while (cur)
	{
		size++;
		cur = cur->next;
	}

	return size;
}

VertexType QueueFront(Queue* pq)
{

	return pq->head->data;
}

VertexType QueueBack(Queue* pq)
{

	return pq->tail->data;
}
typedef enum GraphKind
{
	DG = 1,
	DN = 2,
	UDG = 3,
	UDN = 4

} GraphKind;
typedef struct ArcCell
{
	VRType adj;
	InfoType* info;
} AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct MGraph // 图
{
	bool bVisited1[MAX_VERTEX_NUM];
	VertexType vexs[MAX_VERTEX_NUM];
	int degree[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum;
	int arcnum;
	GraphKind kind;
} MGraph;

int LocateVex(MGraph* G, VertexType v);
void CreateDN(MGraph* G);
void CreateDG(MGraph* G);
void CreateUDN(MGraph* G);
void CreateUDG(MGraph* G);
void CreateGraph(MGraph* G);
int LocateVex(MGraph* G, VertexType v)
{
	int i, j;
	for (i = 0; i < G->vexnum; i++)
	{
		if (G->vexs[i] == v)
		{
			return i;
		}
	}
	return -1;
}
void CreateUDG(MGraph* G)
{
	scanf("%d%d", &(G->vexnum), &(G->arcnum));
	int i, j;
	for (i = 0; i < G->vexnum; i++)
	{
		scanf("%d", &(G->vexs[i]));
		G->degree[i] = 0;
	}

	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].adj = 0;
			G->arcs[i][j].info = NULL;
		}
	}

	for (i = 0; i < G->arcnum; i++)
	{
		VertexType v1, v2;
		scanf("%d%d", &v1, &v2);

		int n = LocateVex(G, v1);
		int m = LocateVex(G, v2);
		G->degree[n]++;
		G->degree[m]++;
		G->arcs[n][m].adj = 1;
		G->arcs[m][n].adj = 1;
	}
	G->kind = UDG;
	printf("UDG has been created successfully.\n");
}

void CreateDG(MGraph* G)
{
	scanf("%d%d", &(G->vexnum), &(G->arcnum));
	int i, j;
	for (i = 0; i < G->vexnum; i++)
	{
		scanf("%d", &(G->vexs[i]));
		G->degree[i] = 0;
	}

	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].adj = 0;
			G->arcs[i][j].info = NULL;
		}
	}

	for (i = 0; i < G->arcnum; i++)
	{
		VertexType v1, v2;
		scanf("%d%d", &v1, &v2);

		int n = LocateVex(G, v1);
		int m = LocateVex(G, v2);
		G->degree[n]++;
		G->degree[m]++;
		G->arcs[n][m].adj = 1;
	}

	G->kind = DG;
	printf("DG has been created successfully.\n");
}

void CreateUDN(MGraph* G)
{
	int i, j;
	scanf("%d%d", &(G->vexnum), &(G->arcnum));

	for (i = 0; i < G->vexnum; i++)
	{
		scanf("%d", &(G->vexs[i]));
		G->degree[i] = 0;
	}

	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].adj = INFINITE;
			G->arcs[i][j].info = NULL;
		}
	}

	for (i = 0; i < G->arcnum; i++)
	{
		VertexType v1, v2;
		InfoType w;
		scanf("%d%d%d", &v1, &v2, &w);
		int n = LocateVex(G, v1);
		int m = LocateVex(G, v2);
		G->degree[n]++;
		G->degree[m]++;
		G->arcs[n][m].adj = w;
		G->arcs[m][n].adj = w;
	}

	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			if (i == j)
			{
				G->arcs[i][j].adj = 0;
			}
		}
	}

	G->kind = UDN;
	printf("UDN has been created successfully.\n");
}

void CreateDN(MGraph* G)
{
	int i, j;
	scanf("%d,%d", &(G->vexnum), &(G->arcnum));

	for (i = 0; i < G->vexnum; i++)
	{
		scanf("%d", &(G->vexs[i]));
		G->degree[i] = 0;
	}

	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].adj = INFINITE;
			G->arcs[i][j].info = NULL;
		}
	}

	for (i = 0; i < G->arcnum; i++)
	{
		VertexType v1, v2;
		InfoType w;
		scanf("%d%d%d", &v1, &v2, &w);

		int n = LocateVex(G, v1);
		int m = LocateVex(G, v2);
		G->degree[n]++;
		G->degree[m]++;
		G->arcs[n][m].adj = w;
	}

	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			if (i == j)
			{
				G->arcs[i][j].adj = 0;
			}
		}
	}

	G->kind = DN;
	printf("DN has been created successfully.\n");
}

void CreateGraph(MGraph* G)
{

	int k;
	scanf("%d", &k);
	switch (k)
	{
	case 1:
		CreateDG(G);
		break;

	case 2:
		CreateDN(G);
		break;

	case 3:
		CreateUDG(G);
		break;

	case 4:
		CreateUDN(G);
		break;

	default:
		break;
	}
}

void BFSTraverse(MGraph* G) {
	int i, j;
	printf("BFS traverse:");
	Queue Q;
	QueueInit(&Q);
	for (i = 0; i < G->vexnum; i++)
	{
		G->bVisited1[i] = false;
	}
	for (i = 0; i < G->vexnum; i++)
	{
		if (!G->bVisited1[i])
		{
			printf(" %d", G->vexs[i]);
			G->bVisited1[i] = true;
			QueuePush(&Q, G->vexs[i]);

			while (!QueueEmpty(&Q))
			{

				VertexType from = QueueFront(&Q);
				QueuePop(&Q);
				for (j = 0; j < G->vexnum; j++)
				{
					if (G->arcs[from][j].adj != INFINITE && !G->bVisited1[j])
					{
						printf(" %d", G->vexs[j]);
						G->bVisited1[j] = true;
						QueuePush(&Q, G->vexs[j]);
					}
				}
			}
		}
	}
	printf("\n");
}
int FirstAdjVex(MGraph* G, int v)

{
	int i, j;
	for (i = 0; i < G->vexnum; i++)
	{
		if (G->arcs[v][i].adj != 0)
		{
			return i;
		}
	}
	return -1;
}

int NextAdjVex(MGraph* G, int v, int w)
{
	int i, j;
	for (i = w + 1; i < G->vexnum; i++)
	{
		if (G->arcs[v][i].adj)
		{
			return i;
		}
	}
	return -1;
}

void DFS(MGraph* G, int v)
{
	G->bVisited1[v] = true;
	printf(" %d", G->vexs[v]);
	int w;
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
	{

		if (!G->bVisited1[w])
		{
			DFS(G, w);
		}
	}
}

void DFSTraverse(MGraph* G)
{
	int i, j;
	printf("DFS traverse:");
	for (i = 0; i < G->vexnum; i++)
	{
		G->bVisited1[i] = false;
	}

	for (i = 0; i < G->vexnum; i++)
	{
		if (!G->bVisited1[i])
		{
			DFS(G, i);
		}
	}
	printf("\n");
}
void DegreePrint(MGraph* G) {
	int i, j;
	printf("The degree of each vertex:");
	for (i = 0; i < G->vexnum; i++) {
		printf("%d:%d", G->vexs[i], G->degree[i]);
		if (i != G->vexnum - 1)
			printf(",");
	}
	printf("\n");
}
int main()
{

	MGraph G;
	CreateGraph(&G);
	DFSTraverse(&G);
	BFSTraverse(&G);
	DegreePrint(&G);
	return 0;
}
