// 拓扑排序：
#include <iostream>
using namespace std;
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#define X 1001
int n=6;
int g[6][6]= {0,1,1,0,0,0,//对角线上都是0.
              0,0,0,1,0,0,
              0,0,0,1,1,0,
              0,0,0,0,0,1,
              0,0,0,0,0,1,
              0,0,0,0,0,0
             };
int count[X];
void Topsort()
{
    int i,top=-1;
    memset(count,0,sizeof(count));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(g[i][j]!=0)
                count[j]++;
        }
    }
    for(i=0; i<n; i++)
        if(count[i]==0)
            top=i;
    if(top==-1)
    {
        printf("0 degree stack is empty,there are cycles in graph\n");
        return ;
    }
    for(i=0; i<n; i++)
    {
        int j=top;
        top=count[j];
        printf("%d",j+1);
        if(i!=n-1)printf("->");
        for(int k=0; k<n; k++)
            if(g[j][k])
            {
                count[k]--;
                if(count[k]==0)
                {
                    count[k]=top;
                    top=k;
                }
            }
    }
}
void topsort()//队列实现，直观易于理解
{
    memset(count,0,sizeof(count));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(g[i][j]!=0)
                count[j]++;
        }
    }
    int flag[X];
    int queue[X];  /*队列*/
    int head=0,tail=0,v,k=0;
    memset(flag,0,sizeof(flag));
    for(int i=0; i<n; i++)  /*先将所有入度为0的顶点进队*/
        if(count[i]==0 && flag[i]==0)
        {
            queue[tail++]=i;
            flag[i]=1;
        }
    if(tail==0)
    {
        printf("0 degree stack is empty,there are cycles in graph\n");
        return ;
    }
    while (head<tail)             /*当队列不空时*/
    {
        v=queue[head++];  /*队首元出队*/
        printf("%d",v+1);
        k++;                  /*计数器加1*/
        if(k!=n)printf("-->");
        for(int i=0; i<n; i++)
        {
            if(g[v][i]&&!flag[i]&&--count[i]==0)
            {
                queue[tail++]=i;
                flag[i]=1;
            }
        }
    }
}
int main()
{
    topsort();
    return 0;
}
