#include <stdio.h>
#include <stdlib.h>
#define MaxVerNum 20

int visited[MaxVerNum];

typedef char VertexType;

typedef struct ArcNode

{
    int adjvex; //该弧指向的顶点位置
    struct ArcNode * nextarc; //指向下一个表结点
    int info; //权值信息
} ArcNode; //边结点类型

typedef struct VNode
{
    VertexType data;
    int indegree;
    ArcNode * firstarc;
} VNode, Adjlist[MaxVerNum];

typedef struct
{
    Adjlist vertices; //邻接表
    int vernum, arcnum; //顶点数和边数
} ALGraph;
//查找符合的数据在数组中的下标

int LocateVer(ALGraph G, char u)
{
    int i;
    for (i=0; i < G.vernum; i++)
    {
        if (u == G.vertices[i].data)
            return i;
    }
    if (i == G.vernum)
    {
        printf("Error u!\n");
        exit(1);
    }
    return 0;
}

//建立图的邻接矩阵

void CreateALGraph(ALGraph &G)
{
    int i, j, k, w;
    char v1, v2;
    ArcNode * p;
    printf("输入顶点数和弧数: ");
    scanf("%d %d", &G.vernum, &G.arcnum);
    printf("请输入顶点!\n");
    for (i=0; i < G.vernum; i++)
    {
        printf("请输入第 %d 个顶点: \n", i);
        fflush(stdin);
        scanf("%c", &G.vertices[i].data);
        G.vertices[i].firstarc=NULL;
        G.vertices[i].indegree=0;
    }

    for (k=0; k < G.arcnum; k++)
    {
        printf("请输入弧的顶点和相应权值(v1, v2, w): \n");
        fflush(stdin);
        scanf("%c %c %d", &v1, &v2, &w);
        i=LocateVer(G, v1);
        j=LocateVer(G, v2);
        p=(ArcNode *) malloc(sizeof (ArcNode));
        p->adjvex=j;
        p->info=w;
        p->nextarc=G.vertices[i].firstarc;
        G.vertices[i].firstarc=p;
        G.vertices[j].indegree++; //vi->vj, vj入度加1
    }
    return;
}
//求图的关键路径函数

void CriticalPath(ALGraph G)
{
    int i, k, e, l;
    int * Ve, * Vl;
    ArcNode * p;
    //以下是求时间最早发生时间
    Ve=new int [G.vernum];
    Vl=new int [G.vernum];

    for (i=0; i < G.vernum; i++) //前推
        Ve[i]=0;

    for (i=0; i < G.vernum; i++)
    {
        ArcNode * p=G.vertices[i].firstarc;
        while (p != NULL)
        {
            k=p->adjvex;
            if (Ve[i] + p->info > Ve[k])
                Ve[k]=Ve[i] + p->info;
            p=p->nextarc;
        }
    }
    //以下是求最迟发生时间
    for (i=0; i < G.vernum; i++)
        Vl[i]=Ve[G.vernum - 1];
    for (i=G.vernum - 2; i >= 0; i--) //后推
    {
        p=G.vertices[i].firstarc;
        while (p != NULL)
        {
            k=p->adjvex;
            if (Vl[k] - p->info < Vl[i])
                Vl[i]=Vl[k] - p->info;
            p=p->nextarc;
        }
    }

    for (i=0; i < G.vernum; i++)
    {
        p=G.vertices[i].firstarc;
        while (p != NULL)
        {
            k=p->adjvex;
            e=Ve[i]; //最早开始时间为时间vi的最早发生时间
            l=Vl[k] - p->info; //最迟开始时间
            char tag=(e == l) ? '*' : ' '; //关键活动
            printf("(%c, %c), e = %2d, l = %2d, %c\n", G.vertices[i].data, G.vertices[k].data, e, l, tag);
            p=p->nextarc;
        }
    }
    delete [] Ve;
    delete [] Vl;
}
int main()
{
    ALGraph G;
    CreateALGraph(G);
    CriticalPath(G);
}
