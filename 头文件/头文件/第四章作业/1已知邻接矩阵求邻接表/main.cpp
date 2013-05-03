#include<iostream>
#include<stdio.h>
#define MAX 100
using namespace std;

//样例邻接矩阵
int map[5][5]=
{
    {0,1,1,0,0},
    {0,0,0,1,0},
    {0,0,0,0,1},
    {0,0,0,0,0},
    {0,0,0,0,0}
};

int n=5,e=4;//顶点数和边数
bool visit[MAX];//是否访问
struct ArcNode//邻接点定义
{
    int adjvex;
    ArcNode *next;
};
struct VNode//出发点定义
{
    int v;
    ArcNode *first;
};
VNode adj[MAX];//邻接表

void Create()//将邻接矩阵转化为邻接表
{
    int i,j;
    for(i=1; i<=n; i++)
    {
        adj[i].v=i;
        adj[i].first=NULL;
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(map[i][j]==0)
                continue;
            if(adj[i+1].first==NULL)
            {
                ArcNode *p=new ArcNode;
                p->adjvex=(j+1);
                p->next=NULL;
                adj[i+1].first=p;
            }
            else
            {
                ArcNode *p=adj[i+1].first;
                while(p->next!=NULL)
                {
                    p=p->next;
                }
                ArcNode *q=new ArcNode;
                q->adjvex=(j+1);
                q->next=NULL;
                p->next=q;
            }
        }
    }
}
void DFS(int v)//递归深度优先搜索
{
    printf("%d ",v);
    visit[v]=1;
    ArcNode *p=adj[v].first;
    while(p!=NULL)
    {
        if(!visit[p->adjvex])
            DFS(p->adjvex);
        p=p->next;
    }
}

void None_DFS(int v)//非递归深度优先搜索
{
    int Queue[MAX];
    int front=1;
    Queue[front]=v;
    cout<<v<<" ";
    visit[v]=true;
    while(front>0)
    {
        ArcNode *p=adj[Queue[front]].first;
        if(p==NULL)
        {
            front--;
            continue;
        }
        int flag=0;//判断是否能继续往下搜
        while(p!=NULL)
        {
            if(!visit[p->adjvex])
            {
                cout<<p->adjvex<<" ";
                Queue[++front]=p->adjvex;
                visit[p->adjvex]=true;
                flag=1;
                break;
            }
            else
                p=p->next;
        }
        if(flag==0)front--;
    }
}
void BFS(int v)//广度优先搜索
{
    int Queue[MAX];
    int front=1;
    int tail=1;
    Queue[front++]=v;
    cout<<v<<" ";
    visit[v]=true;
    while(tail<front)
    {
        ArcNode *p=adj[Queue[tail]].first;
        while(p!=NULL)
        {
            if(!visit[p->adjvex])
            {
                cout<<p->adjvex<<" ";
                Queue[front++]=p->adjvex;
                visit[p->adjvex]=true;
                p=p->next;
            }
            else
                p=p->next;
        }
        tail++;
    }
}
int main()
{
    int v;
    Create();
    cout<<"已将邻接矩阵转化为邻接表."<<endl;
    printf("从哪个点开始搜索？\n");
    while(scanf("%d",&v)!=EOF&&v)
    {
        memset(visit,false,sizeof(visit));
        BFS(v);
        cout<<endl<<"BFS has ended."<<endl;
        memset(visit,false,sizeof(visit));
        DFS(v);
        cout<<endl<<"DFS has ended."<<endl;
        memset(visit,false,sizeof(visit));
        None_DFS(v);
        cout<<endl<<"非递归DFS has ended."<<endl;
        printf("从哪个点开始搜索？\n");
    }
    return 0;
}
