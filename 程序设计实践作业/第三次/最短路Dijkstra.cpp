//一般实现
#define INF 99999999
const int maxn=10001;
//n个点，dist[i]记录i到s的最短距离，map记录图信息，pre记录前驱结点;
void dijkstra(int n,int dist[],int map[maxn][maxn],int pre[maxn],int s)
{
	int i,j,k;
	int min;
	bool [maxn];//记录该点是否属于v[A],否则属于v[B];
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

/*
    dijkstra + heap，时间复杂度: O((n + e)log(n)).
    对于稠密图来说，仍然是dij+heap快，而且越稠密越快!
    用前向星来存图，空间复杂度为: O(m).
    更新时间: 2011.09.22
*/
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1000010;
const double EPS = 1e-10;
const long long INF = (1LL << 60) + (1LL << 61);
struct EDGE
{
    int a, b, c;
    int next;
};

int n, m, ds, dt; // n个点，m条边，ds为原点，dt为终点。
EDGE edge[maxn]; // 前向星.
int edge_num;
int first[maxn]; // 记录该点的第一条边在edge[]的下标.
bool visit[maxn]; // 判断该点的最短路是否已经求出来了.
long long ans;

struct Heap
{
    // 如果速度慢，就不要用struct，直接作为一般参数和函数.
    int heapsize;
    int heap_v[maxn]; // heap_v[i]为堆中第i个位置所存的图中的结点.
    int heap_map[maxn]; // heap_map[i]表示图中的点i在堆中的位置.
    long long heap_w[maxn]; // heap_w[i]为堆中第i个位置所存的为dist[heap_v[i]].
    void heap_swap(int i, int j)
    {
        swap(heap_w[i], heap_w[j]);
        heap_map[heap_v[i]] = j;
        heap_map[heap_v[j]] = i;
        swap(heap_v[i], heap_v[j]);
    }
    void heap_up(int i)
    {
        while (i != 1)
        {
            if (heap_w[i] < heap_w[i >> 1])
            {
                heap_swap(i, i >> 1);
                i >>= 1;
            }
            else break;
        }
    }
    void heap_down(int i)
    {
        // 注: 在dijkstra+heap没用到该函数.
        while ((i << 1) <= heapsize)
        {
            i <<= 1;
            if (i + 1 <= heapsize && heap_w[i + 1] < heap_w[i]) i++;
            if (heap_w[i] < heap_w[i >> 1])
            {
                heap_swap(i, i >> 1);
            }
            else break;
        }
    }
    void Delmin(void)
    {
        heap_swap(1, heapsize);
        heapsize--;
        heap_down(1);
    }
}hp;

void Init(void)
{
    int i, j, k;
    ans = 0;
    edge_num = 0;
    memset(visit,0,sizeof(visit));
    fill(first, first + maxn, -1);
    for (i = 1; i <= n; i++)
    {
        hp.heap_v[i] = i;
        hp.heap_map[i] = i;
        hp.heap_w[i] = INF;
    }
}

void addedge(int a, int b, int c)
{
    edge[edge_num].a = a, edge[edge_num].b = b, edge[edge_num].c = c;
    edge[edge_num].next = first[a], first[a] = edge_num++;
}

void Dijkstra_heap(void)
{
    // hp.heap_w[hp.heap_w[i]]相当于dist[i].
    int i, j, k;
    int t;
    long long temp;
    for (t = 1; t < n; t++)
    {
        i = hp.heap_v[1];
        temp = hp.heap_w[1]; // temp 相当于dist[i].
        hp.Delmin();
        visit[i] = 1;
        if (visit[dt]) break; // 说明dist[dt]已经求出.
        for (k = first[i]; k != -1; k = edge[k].next)
        {
            j = edge[k].b;
            if (!visit[j] && temp + edge[k].c < hp.heap_w[hp.heap_map[j]])
            {
                hp.heap_w[hp.heap_map[j]] = temp + edge[k].c;
                hp.heap_up(hp.heap_map[j]);
            }
        }
    }
}
int main(void)
{
    //freopen("in.txt", "r", stdin);
    int a, b, c;
    while (scanf("%d %d", &n, &m) != EOF)
    {
        Init();
        while (m--)
        {
            scanf("%d %d %d", &a, &b, &c);
            addedge(a, b, c);
          //addedge(b, a, c);无向图.
        }
        cin>>ds>>dt;
        visit[ds] = 1;
        hp.heap_w[ds] = 0;
        hp.heapsize = n;
        hp.heap_up(hp.heap_map[ds]);
        Dijkstra_heap();
        ans = hp.heap_w[hp.heap_map[dt]];
        if (ans == INF) cout << "-1" << endl;
        else cout << ans << endl;
    }
    return 0;
}
