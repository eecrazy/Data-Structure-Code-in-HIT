//Prim
#define INF 99999999
const int maxn =101;
//n个点，dist[i]表示向外延伸的最短边长，map记录图信息，pre记录前去节点;
void prim(int n,int dist[maxn],int map[maxn][maxn],int pre[maxn])
{
	int i,j,k;
	int min;
	bool p[maxn];////记录该点是否属于v[A],否则属于v[B];
	//初始化
	for(i=2;i<=n;i++)
	{
		p[i]=false;
		dist[i]=map[1][i];
		pre[i]=1;
	}
	dist[1]=0;
	p[1]=true;
	//循环n-1次，每次加入一个点
	for(i=1;i<=n-1;i++)
	{
		min=INF;
		k=0;
		for(j=1;j<=n;j++)
		{
			if(!p[j]&&dist[j]<min)
			{
				min=dist[j];
				k=j;
			}
		}
		if(k==0)return ;//如果没有点可以扩展，即图不联通，返回
		p[k]=true;//将k从v[b]中除去，加入v[a];
		for(j=1;j<=n;j++)
		{
			//对于每个与k相邻的在vb中的节点j,更新到j距离最近的点及其距离;
			if(!p[j]&&map[k][j]!=INF&&dist[j]>map[k][j])
			{
				dist[j]=map[k][j];
				pre[j]=k;
			}
		}
	}
}