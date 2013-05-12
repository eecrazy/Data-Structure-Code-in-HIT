#include <cstdio>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

#define maxn 100005
struct node
{
    int data;
    bool visit;
} array1[maxn];
void init()
{
    for (int i = 0; i < maxn; i++)
        array1[i].visit = false;
}
int h(int a)
{
    return a % maxn;
}
void insert(int a)
{
    int b = h(a);
    while (array1[b].visit)
    {
        b++;
        if(b>=maxn)
            b=b%maxn;
    }
    array1[b].data = a;
    array1[b].visit = true;
}
bool search(int a)
{
    int b = h(a);
    while (1)
    {
        if (array1[b].visit == false)
        {
            b++;
            if(b>=maxn)
                b=b%maxn;
            continue;
        }
        else
        {
            if (array1[b].data != a)
            {
                b++;
                if(b>=maxn)
                    b=b%maxn;
                continue;
            }
            else
                return true;
        }
    }
}
int main()
{
    freopen("in.txt", "r", stdin);
    clock_t start, finish;
    double duration;
    init();
    int a;
    int arr[maxn], i = 0;;
    for(i=0;i<100000;i++)
    {
        scanf("%d",&arr[i]);
    }
    for (int j = 0; j < i; j++)
    {
        insert(arr[j]);
    }
    start = clock();
    int num=0;
    for (int j = 0; j < i; j++)
    {
        if (search(arr[j]))
        num++;
    }
    printf("搜索到%d个数据\n",num);
    finish = clock();
    duration =(double)(finish - start) / CLOCKS_PER_SEC;
    printf("内散列搜索用时 %f seconds\n", duration );
}
