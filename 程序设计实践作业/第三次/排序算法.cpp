/*气泡排序、快速排序；插入排序、
希尔排序；选择排序、堆排序；归
并排序；基数排序*/


// 堆排序：
// 数组存储结构及操作算法的实现
#include<iostream>
using namespace std;
typedef int ElementType;
#define maxn 10000
void MaxHeap(int A[], int i, int n)
{
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest,temp;   //存储最大的下标
    if(left <= n && A[left] > A[i])
        largest = left;
    else
        largest = i;
    if(right <= n && A[right] > A[largest])
        largest = right;
    if(largest != i)
    {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        MaxHeap(A,largest,n);
    }
}
void BuildHeap(int *A, int n)
{
    int len = n; //len对堆的大小
    for(int i = n / 2; i > 0; --i)
        MaxHeap(A,i,n);
}
ElementType Max(ElementType*A)   //根即为最大元素
{
    return A[1];
}
//DeleteMax(S)：去掉S中具有最大关键字的元素。
int DeleteMax(int *A, int n)
{
    int len = n; //len对堆的大小
    int max;
    max = A[1];
    A[1] = A[n];
    len = len - 1;
    MaxHeap(A,1,len);
    return max;
}

//Update(a, i, key)：改变下标i的关键值为key.
void Update(int A[], int i, int key)
{
    A[i] = key;
    int parent = i/2;
    int temp;
    while(i>1 && A[parent]<A[i])
    {
        temp = A[i];
        A[i] = A[parent];
        A[parent] = temp;
        i = i/2;
    }
}
//Insert(S,x)：插入x到集合S。
void Insert(int A[], int n, int key)
{
    int len = n; //len对堆的大小
    len = len+1;
    A[len] = 0;

    Update(A, len, key);
}
int main()
{
    int n,a[maxn];
    cout<<"input the number of elements:";
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    BuildHeap(a,n);
    for(int i=n;i>=1;i--)
        cout<<DeleteMax(a,i)<<" ";
    cout<<endl;
}
//输入样例：
//8
//44 22 1 7 33 99 45 31


拓扑排序：
#include<iostream>
using namespace std;
#include<cstring>
#include<cstdio>
#include<stdlib.h>
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
