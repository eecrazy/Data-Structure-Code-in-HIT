#include <iostream>
#include <stack>
using namespace std;
#include <cstdio>
typedef struct node
{
    int data;
    int ltag,rtag; //左右标志
    node *lchild,*rchild;
};//线索二叉树的结点类型
node *pre=NULL; //全局量
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
        T->ltag=1;          //初始化时指针标志均为0
        T->rtag=1;
        T->lchild=CreatTree();
        T->rchild=CreatTree();
    }
    return T;
}

//将二叉树按中序线索化的算法
void Inordering(node* p)
{
    //将二叉树p中序线索化
    if(p)  //p非空时,当前访问结点是*p
    {
        Inordering(p->lchild); //左子树线索化
        //以下直至右子树线索化之前相当于遍历算法中访问结点的操作
        p->ltag=(p->lchild)?1:0; //左指针非空时左标志为1
        //(即0),否则为0(即1)
        p->rtag=(p->rchild)?1:0;
        if(pre)  //若*p的前趋*pre存在
        {
            if(pre->rtag==0) //若*p的前趋右标志为线索
                pre->rchild=p; //令*pre的右线索指向中序后继
            if(p->ltag==0) //*p的左标志为线索
                p->lchild=pre; //令*p的左线索指向中序前趋
        } // 完成处理*pre的线索
        pre=p; //令pre是下一访问结点的中序前趋
        Inordering(p->rchild); //右子树线索化
    }
}
//在中序线索二叉树中求中序后继结点,时间复杂度不超过树的高度h,即O(h)
node *InorderSuccessor(node *p)
{
    //在中序线索树中找结点*p的中序后继,设p非空
    node *q;
    if (p->rtag==0) //*p的右子树为空
        return p->rchild; //返回右线索所指的中序后继
    else
    {
        q=p->rchild; //从*p的右孩子开始查找
        while (q->ltag==1)
            q=q->lchild; //左子树非空时,沿左链往下查找
        return q; //当q的左子树为空时,它就是最左下结点
    } //end if
}

//中序线索二叉树中求中序前趋结点,时间复杂度不超过树的高度h,即O(h)
node *Inorderpre(node *p)
{
    //在中序线索树中找结点*p的中序前趋,设p非空
    node *q;
    if (p->ltag==0) //*p的左子树为空
        return p->lchild; //返回左线索所指的中序前趋
    else
    {
        q=p->lchild; //从*p的左孩子开始查找
        while (q->rtag==1)
            q=q->rchild; //右子树非空时,沿右链往下查找
        return q; //当q的右子树为空时,它就是最右下结点
    }
}

//遍历中序线索二叉树
void TraverseInorderThrTree(node* p)
{
    if(p) //树非空
    {
        while(p->ltag==1)
            p=p->lchild; //从根往下找最左下结点,即中序序列的开始结点
        do
        {
            printf("%d ",p->data); //访问结点
            p=InorderSuccessor(p); //找*p的中序后继

        }
        while(p);
    }
    cout<<endl;
}

//前序线索化
void PreOrderThreading(node* p)
{
    stack<node* >nodeTypeStack;
    node* a[1000];
    int b=0;
    node* current;
    current=p;
    while((current!=NULL)||!nodeTypeStack.empty())
    {
        if(current!=NULL)
        {
            cout<<current->data<<" ";
            a[b++]=current;
            nodeTypeStack.push(current);
            current=current->lchild;
        }
        else
        {
            current=nodeTypeStack.top();
            nodeTypeStack.pop();
            current=current->rchild;
        }
    }
    cout<<endl;
    if(a[0]->rchild==NULL)
    a[0]->rchild=a[1],a[0]->rtag=0;
    for(int i=1;i<b-1;i++)
    {
        if(a[i]->lchild==NULL)
        {
            a[i]->ltag=0,a[i]->lchild=a[i-1];
        }
        if(a[i]->rchild==NULL)
        {
            a[i]->rtag=0,a[i]->rchild=a[i+1];
        }
    }
}
//在前序线索二叉树中求前序后继结点,时间复杂度不超过树的高度h,即O(h)
node *PreorderSuccessor(node *p)
{
    //在中序线索树中找结点*p的中序后继,设p非空
    node *q;
    if (p->rtag==0) //*p的右子树为空
        return p->rchild; //返回右线索所指的前序后继
    else
    {
        if(p->ltag==1)
            return p->lchild;
        else
        {
            return p->rchild;
        }
    }
}
//遍历前序线索二叉树
void TraversePreorderThrTree(node* p)
{
    if(p) //树非空
    {
        do
        {
            printf("%d ",p->data); //访问结点
            p=PreorderSuccessor(p); //找*p的前序后继
        }
        while(p);
    }
    cout<<endl;
}
void Traverse(node* p)
{
    if(p) //树非空
    {
            printf("%d ",p->data); //访问结点
           if(p->lchild)
           Traverse(p->lchild);
           if(p->rchild)
           Traverse(p->rchild);
    }
}

//后序线索化
void PostOrderThreading(node* p)
{
    node* a[1000];
    int b=0;
    stack<node*>nodeTypeStack;
    stack<int> IntStack;
    node* current;
    current=p;
    int v=0;
    if(current!=NULL)
    {
        nodeTypeStack.push(current);
        IntStack.push(1);
        current=current->lchild;
        while(!nodeTypeStack.empty())
        {
            if(current!=NULL && v==0)
            {
                nodeTypeStack.push(current);
                IntStack.push(1);
                current=current->lchild;
            }
            else
            {
                current=nodeTypeStack.top();
                nodeTypeStack.pop();
                v=IntStack.top();
                IntStack.pop();
                if(v==1)
                {
                    nodeTypeStack.push(current);
                    IntStack.push(2);
                    current=current->rchild;
                    v=0;
                }
                else
                    a[b++]=current;
            }
        }
    }
    if(a[0]->rchild==NULL)
    a[0]->rchild=a[1],a[0]->rtag=0;
    for(int i=1;i<b-1;i++)
    {
        if(a[i]->lchild==NULL)
        {
            a[i]->ltag=0,a[i]->lchild=a[i-1];
        }
        if(a[i]->rchild==NULL)
        {
            a[i]->rtag=0,a[i]->rchild=a[i+1];
        }
    }
}
//在后序线索二叉树中求后序后继结点：未完成
node *PostorderSuccessor(node *p)
{
    //在中序线索树中找结点*p的后序后继,设p非空
    node *q;
    if (p->rtag==0) //*p的右子树为空
        return p->rchild; //返回右线索所指的后序后继
    else//？？？？
    {
        if(p->ltag==1)
            return p->lchild;
        else
        {
            return p->rchild;
        }
    }
}
//遍历后序线索二叉树:已完成
void TraversePostorderThrTree(node* p)
{
//    if(p) //树非空
//    {
//        while(p->ltag==1)
//            p=p->lchild; //从根往下找最左下结点,即中序序列的开始结点
//        do
//        {
//            printf("%d ",p->data); //访问结点
//            p=InorderSuccessor(p); //找*p的中序后继
//
//        }
//        while(p);
//    }
    if(p!=NULL)
    {
        if(p->ltag!=0)
        TraversePostorderThrTree(p->lchild);
        if(p->rtag!=0)
        TraversePostorderThrTree(p->rchild);
        cout<<p->data<<" ";
    }
    cout<<endl;
}
int main()
{
    node *T;
    cout<<"按先序输入建立二叉树："<<endl;
    T=CreatTree();
//    cout<<"中序线索化……"<<endl;
//    Inordering(T);
//    cout<<"中序线索化完毕！"<<endl;
//    cout<<"中序遍历线索化二叉树："<<endl;
//    TraverseInorderThrTree(T);
//     cout<<endl;
//    cout<<"前序线索化……"<<endl;
//    PreOrderThreading(T);
//    cout<<"前序线索化完毕！"<<endl;
//    TraversePreorderThrTree(T);
cout<<"后序线索化……"<<endl;
PostOrderThreading(T);
cout<<"后序线索化完毕！"<<endl;
TraversePostorderThrTree(T);//后序遍历未完成

  return 0;
}
//
