// 并查集的表示与等价分类
#include<iostream>
#include<algorithm>
using namespace std;
int rank[101];
int v[101];
void make_set(int x)//初始化
{
    v[x]=x;
    rank[x]=0;
}
int find_set(int x)//路径压缩
{
    if(v[x]!=x) v[x]=find_set(v[x]);
    return v[x];
}
void Union(int x,int y)//根据rank合并两棵树
{
    if(rank[x]>rank[y])
        v[y]=x;
    else if(rank[x]<rank[y])
        v[x]=y;
    else if(rank[x]==rank[y])
    {
        v[x]=y;
        rank[y]++;
    }
}
struct Edge//边定义
{
    int x,y,w;
} e[1001];
bool cmp(Edge e1,Edge e2)
{
    if(e1.w<e2.w) return true;
    else return false;
}
int main()
{
    int n,m,s1,s2;
    int i,j,ans;//ans为最小权值和
    cout<<"请输入顶点数和边数:"<<endl;
    cin>>n>>m;//输入顶点数和边数
    for(i=0; i<m; i++)
    {
        cout<<"请输入m条边的起点终点和权值:"<<endl;
        cin>>e[i].x>>e[i].y>>e[i].w;//输入m条边，包括权值
    }
    sort(e,e+m,cmp);//按边权从小到大排序
    for(i=1; i<=n; i++)//初始化
    make_set(i);

    ans=0;//计数器
    for(i=0; i<m; i++)
    {
        s1=find_set(e[i].x);
        s2=find_set(e[i].y);
        if(s1!=s2)
        {
            ans+=e[i].w;
            Union(s1,s2);
        }
    }
    cout<<"最小权为:"<<ans<<endl;
    return 0;
}
