#include<iostream>
using namespace std;
#include <string.h>
#define INF 1000000
int edge[100][100];
bool visit[100];
int Stack[100];
int n,m;
//递归深度优先搜索
void DFS(int v)
{
    cout<<v<<" ";
    visit[v]=true;
    for(int i=1; i<=n; i++)
    {
        if(!visit[i]&&edge[v][i])
        {
            DFS(i);
        }
    }
}

//非递归深度优先搜索
void NoneRecursionDFS( int v)
{
    memset(visit,false,sizeof(visit));
    cout <<v<<" " ;
    int top = 0;
    visit[v] = true ;
    Stack[top] = v ;
    while ( top != -1)
    {
        v = Stack[top] ;
        int i;
        for (i = 1 ; i <= n ; i++)
        {
            if (edge[v][i] == 1 &&!visit[i])
            {
                cout << i <<" ";

                visit[i] = true ;
                Stack[ ++top ] = i ;
                break ;
            }
        }
        if( i == (n+1))
        {
            top -- ;
        }
    }
}

//广度优先搜索
void BFS(int v)
{
    int Queue[100];
    int tail=0,head=0;
    Queue[head++]=v;
    visit[v]=true;
    while(tail!=head)
    {
        for(int i=1; i<=n; i++)
        {
            if(!visit[i]&&edge[Queue[tail]][i])
            {
                Queue[head++]=i;
                visit[i]=true;
            }
        }
        cout<<Queue[tail++]<<" ";
    }
}
int main()
{
    freopen("in.txt","r",stdin);
    cout<<"Please input the number of vertex:"<<endl;
    cin>>n;
    memset(edge,0,sizeof(edge));
    cout<<"Please input the number of edges:"<<endl;
    cin>>m;
    int start,end;
    cout<<"Please input the edges(start end):"<<endl;
    for(int i=0; i<m; i++)
    {
        cin>>start>>end;
        edge[start][end]=1;
    }
    memset(visit,false,sizeof(visit));
    DFS(1);
    cout<<endl<<"DFS has ended!"<<endl;
    NoneRecursionDFS(1);
    cout<<endl<<"NoneRecursionDFS has ended!"<<endl;
    memset(visit,false,sizeof(visit));
    BFS(1);
    cout<<endl<<"BFS has ended!"<<endl;
}
