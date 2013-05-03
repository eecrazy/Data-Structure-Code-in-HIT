#include <iostream>
using namespace std;
#define maxsize 100
#define ElemType int
struct spacestr
{
    ElemType data;
    int  next;
} ;  /*结点类型*/
spacestr  SPACE[maxsize];/*存储池*/
typedef  int  position,Cursor;
Cursor  avail;
position head;
void Initialize()
{
    int j;
    /*  依次链接池中结点*/
    for (j=0; j<maxsize-1; j++ )
        SPACE[j].next=j+1;
    /*  最后一个结点指针域为空*/
    SPACE[j].next=-1;
    /*  标识线性表*/
    avail=0;
    head=0;
}
//可用空间的分配操作
Cursor GetNode() //q=new spacestr;
{
    Cursor p;
    if (SPACE[avail].next ==-1)
        p=-1;
    else
    {
        p= SPACE[avail].next;
        SPACE[avail].next =SPACE[ p ].next;
    }
    return p;
}
//可用空间的回收操作
void FreeNode(Cursor q)
{
    SPACE [q].next =SPACE[avail].next ;
    SPACE[avail].next=q ;
}
//插入操作
void  Insert(ElemType x,position p,spacestr *SPACE)
{
    position  q;
    q=GetNode();
    SPACE[q].data=x;
    SPACE[q].next=SPACE[p].next;
    SPACE[p].next=q;
}
//删除操作
void Delete(position p,spacestr *SPACE)
{
    position q;
    if(SPACE[p].next !=-1)
    {
        q = SPACE[p].next;
        SPACE[p].next = SPACE[q].next ;
        FreeNode(q);
    }
}
int main()
{
    Initialize();
    for(int i=0;i<20;i++)
    Insert(i,19-i,SPACE);
    return 0;
}
