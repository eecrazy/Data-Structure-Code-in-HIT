#include <iostream>
#include <stdio.h>
#define maxn 100005
using namespace std;
int n;
struct node
{
    int data;
    node *next;
};
struct Node
{
    int v;
    node *first;
};
Node array[maxn];

void init()
{
    for (int i = 0; i < maxn; i++)
    {
        array[i].v = -1;
        array[i].first = NULL;
    }
}
int h(int a)
{
    return a % maxn;
}
void insert(int b)
{
    int a = h(b);
    if (array[a].v == -1)
    {
        array[a].v = b;
    }
    else if (array[a].first == NULL)
    {
        node *p = new node;
        p->data = b;
        p->next = NULL;
        array[a].first = p;
    }
    else
    {
        node *p = array[a].first;
        while (p->next != NULL)
        {
            p = p->next;
        }
        node *q = new node;
        q->data = b;
        q->next = NULL;
        p->next = q;
    }
}
bool search(int b)
{
    int a = h(b);
    if (array[a].v == -1)
    {
        return false;
    }
    else if(array[a].v==b)
    {
        return true;
    }
    else if (array[a].first == NULL)
    {
        return false;
    }
    else
    {
        node *p = array[a].first;
        while (p->next != NULL)
        {
            if(p->data==b)
                return true;
            p = p->next;
        }
        if(p==NULL)
            return false;
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
    printf("带溢出表的内散列搜索用时 %f seconds\n", duration );
}
