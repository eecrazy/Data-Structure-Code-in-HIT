#include <iostream>
using namespace std;
#include <cstdio>
struct node
{
    int data;
    node *lchild,*rchild;
};
node *CreatTree() //按先序输入建立二叉树
{
    node *T;
    int e;
    cin>>e;
    if(e==0)
    {
        T=NULL;
    }
    else
    {
        T=new node;
        T->data=e;
        T->lchild=CreatTree();
        T->rchild=CreatTree();
    }
    return T;
}

node* Findd(node* T,int x)
{
    if(T!=NULL)
    {
        if((T->data)==x)
            return T;
        else
        {
            return Findd(T->lchild,x);
            return Findd(T->rchild,x);
        }

    }
}
int Search(node *T,int x,int n)
{
    node *cur=Findd(T,x);
    cur=cur->lchild;
    for(int i=0; i<n-1; i++)
    {
        cur=cur->rchild;
    }
    return cur->data;
}
int height(node *T)
{
    int count=0;
    while(T!=NULL)
    {
        T=T->lchild;
        count++;
    }
    return count;
}
void inorder(node *T)
{
    if(T==NULL)
        cout<<"0 ";
    if(T!=NULL)
    {
        cout<<T->data<<" ";
        inorder(T->lchild);
        inorder(T->rchild);
    }
}
int main()
{
    node *T;
    cout<<"按先序输入建立二叉树："<<endl;
    T=CreatTree();
    //inorder(T);
    cout<<"2的第三个孩子为："<<endl;
    cout<<Search(T,2,3)<<endl;
    cout<<"树高为："<<endl;
    cout<<height(T);
    return 0;
}
//1 2 6 0 7 0 8 0 0 3 0 4 0 5 0 0 0
