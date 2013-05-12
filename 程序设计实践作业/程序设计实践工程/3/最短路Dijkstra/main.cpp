#include <iostream>
#include <cstdio>
using namespace std;
//一般实现
#define INF 99999999
const int maxn=10001;
int n,ans;
int dist[maxn];
int map[maxn][maxn];
int pre[maxn];
//n个点，dist[i]记录i到s的最短距离，map记录图信息，pre记录前驱结点;
void dijkstra(int s)
{
	int i,j,k;
	int min;
	bool p[maxn];//记录该点是否属于v[A],否则属于v[B];
	//初始化
	for(i=1;i<=n;i++)
	{
		p[i]=false;
		if(i!=s)
		{
			dist[i]=map[s][i];
			pre[i]=s;
		}
	}
	dist[s]=0;
	p[s]=true;
	//循环n-1次求s到其他点的最短距离
	for(i=1;i<=n-1;i++)
	{
		min=INF;
		k=0;
		for(j=1;j<=n;j++)//在v[B]中的点取一s到其距离最小的点k;
		{
			if(!p[j]&&dist[j]<min)
			{
				min=dist[j];
				k=j;
			}
		}
		if(k==0)return ;//如果没有点可以扩展，即剩余的点不可达，返回
		p[k]=true;//将k加入到v[A]中
		for(j=1;j<=n;j++)
		{
			if(!p[j]&&map[k][j]!=INF&&dist[j]>dist[k]+map[k][j])
			{
				//对于每个与k相邻的在v[B]中的点j;更新s到j的最短距离;
				dist[j]=dist[k]+map[k][j];
				pre[j]=k;
			}
		}
	}
}
int main()
{
    cout<<"请输入顶点个数:";
    cin>>n;
    cout<<"请输入距离矩阵:"<<endl;
    int num;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
        cin>>num;
        if(num==-1)num=INF;
        map[i][j]=num;
    }
    dijkstra(1);
    for(int i=1;i<=n;i++)
    cout<<dist[i]<<" ";

}

























































