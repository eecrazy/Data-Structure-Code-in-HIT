#include <iostream>
#include<cstdio>
#include<string.h>
using namespace std;
#define X 105
#define INF 1000000
int d[X][X];     /* 距离向量*/
int p[X][X];    /* 路径向量*/
int g[X][X];
int n,num,sum;
void floyd()
{
    int i,j,k;
    for (i=0; i<n; i++)       /*初始化*/
        for (j=0; j<n; j++)
        {
            d[i][j]=g[i][j];
            if (i!=j && d[i][j]<INF) p[i][j]=i;
            else p[i][j]=-1;
        }
            for (i=0; i<n; i++)
            for (j=0; j<n; j++) /*递推求解每一对顶点间的最短距离*/
            for (k=0; k<n; k++)
                if (d[i][j]>(g[i][k]+g[k][j]))
                {
                    d[i][j]=g[i][k]+g[k][j];
                    p[i][j]=k;
                }
            for (i=0; i<n; i++)
            for (j=0; j<n; j++) /*递推求解每一对顶点间的最短距离*/
            for (k=0; k<n; k++)
                if (d[i][j]>(d[i][k]+d[k][j]))
                {
                    d[i][j]=d[i][k]+d[k][j];
                }
}
int main()
{
    cout<<"输入顶点个数：";
    while(scanf("%d",&n)!=EOF,n)
    {
        cout<<"输入距离矩阵:"<<endl;
        memset(g,0,sizeof(g));
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                cin>>num;
                if(num==-1)num=INF;
                g[i][j]=num;
            }
        memset(d,0,sizeof(d));
        memset(p,0,sizeof(p));
        floyd();
        for (int i=0; i<n; i++)       /*初始化*/
        {
            for (int j=0; j<n; j++)
            {
                cout<<d[i][j]<<" ";
            }
            cout<<endl;
        }
    }
}
