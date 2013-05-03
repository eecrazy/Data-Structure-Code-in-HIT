#include<iostream>
#include<stdio.h>
#define MAX 100
using namespace std;
int n,e;//顶点数和边数
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
VNode adj[MAX];//正邻接表
VNode adv[MAX];//逆邻接表

void Create()//建立有向图，正邻接表
{
    int i;
    cout<<"顶点编号从1到"<<n<<"."<<endl;
    for(i=1; i<=n; i++)
    {
        adj[i].v=i;
        adj[i].first=NULL;
    }
    for(i=1; i<=e; i++)
    {
        int a,b;
        cout<<"请输入第"<<i<<"条边:"<<endl;
        cin>>a>>b;
        if(adj[a].first==NULL)
        {
            ArcNode *p=new ArcNode;
            p->adjvex=b;
            p->next=NULL;
            adj[a].first=p;
        }
        else
        {
            ArcNode *p=adj[a].first;
            while(p->next!=NULL)
            {
                p=p->next;
            }
            ArcNode *q=new ArcNode;
            q->adjvex=b;
            q->next=NULL;
            p->next=q;
        }
    }
}
//1 2
//2 3
//3 1

void Change()//正邻接表转逆邻接表
{
    cout<<"fdfdf"<<endl;
    int i;
    for(i=1; i<=n; i++)
    {
        adv[i].v=i;
        adv[i].first=NULL;
    }
    for(i=1; i<=n; i++)
    {
        ArcNode *now=adj[i].first;
        while(now!=NULL)
        {
            if(adv[now->adjvex].first==NULL)
            {
                ArcNode *p=new ArcNode;
                p->adjvex=i;
                p->next=NULL;
                adv[now->adjvex].first=p;
            }
            else
            {
                ArcNode *p=adv[now->adjvex].first;
                while(p->next!=NULL)
                {
                    p=p->next;
                }
                ArcNode *q=new ArcNode;
                q->adjvex=i;
                q->next=NULL;
                p->next=q;
            }
            cout<<i<<" "<<now->adjvex<<endl;
            now=now->next;
        }
    }
}
void DFS(int v)//递归深度优先搜索
{
    printf("%d ",v);
    visit[v]=1;
    ArcNode *p=adv[v].first;
    while(p!=NULL)
    {
        if(!visit[p->adjvex])
            DFS(p->adjvex);
        p=p->next;
    }
}
int main()
{
    int v;
    printf("输入点的个数和边的个数：\n");
    scanf("%d%d",&n,&e);
    Create();
    Change();//正邻接表转逆邻接表
    printf("从哪个点开始搜索？\n");
    while(scanf("%d",&v)!=EOF&&v)
    {
        memset(visit,false,sizeof(visit));
        DFS(v);
        cout<<endl<<"DFS has ended."<<endl;
        printf("从哪个点开始搜索？\n");
    }
    return 0;
}
