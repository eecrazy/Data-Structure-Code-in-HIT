#include <iostream>
using namespace std;
#define maxsize 100
struct node
{
    int data;
    int  next;
} ;  /*结点类型*/
node  space[maxsize];
int avail;int head;
void Initialize()
{
    int j;
    /*  依次链接池中结点*/
    for (j=0; j<maxsize-1; j++ )
        space[j].next=j+1;
    /*  最后一个结点指针域为空*/
    space[j].next=-1;
    /*  标识线性表*/
    avail=0;
    head=0;
}
//可用空间的分配操作
int GetNode() //q=new node;
{
    int p;
    if (space[avail].next ==-1)
        p=-1;
    else
    {
        p= space[avail].next;
        space[avail].next =space[ p ].next;
    }
    return p;
}
//可用空间的回收操作
void FreeNode(int q)
{
    space [q].next =space[avail].next ;
    space[avail].next=q ;
}
//插入操作
void  Insert(int x,int p,node *space)
{
    int  q;
    q=GetNode();
    space[q].data=x;
    space[q].next=space[p].next;
    space[p].next=q;
}
//删除操作
void Delete(int p,node *space)
{
    int q;
    if(space[p].next !=-1)
    {
        q = space[p].next;
        space[p].next = space[q].next ;
        FreeNode(q);
    }
}
int main()
{
    Initialize();
    for(int i=0;i<20;i++)
    Insert(i,19-i,space);
    return 0;
}
