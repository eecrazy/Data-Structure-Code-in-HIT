#ifndef H_BST
#def    H_BST
#include <iostream>
#include <cassert>
#include <stack>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
template <class elemType>
struct nodeType
{
    elemType info;
    nodeType<elemType> *llink;
    nodeType<elemType> *rlink;
};

template <class elemType>
class bSearchTreeType
{
public:
    //默认构造函数
    bSearchTreeType();
    //复制构造函数
    bSearchTreeType(const bSearchTreeType<elemType>& otherTree);
    //析构函数
    ~bSearchTreeType();
    //重载赋值运算符
    const bSearchTreeType<elemType>& operator=(const bSearchTreeType<elemType>&);
    //判空
    bool isEmpty();
    //查找一个元素是否在树
    bool search(const elemType& searchItem);
    //插入一个元素
    void insert(const elemType& insertItem);
    //删除一个元素
    void deleteNode(const elemType& deleteItem);
    //层序遍历，广度优先搜索
    void bfs();
    //中序遍历
    void inorderTraversal();
    //前序遍历
    void preorderTraversal();
    //后序遍历
    void postorderTraversal();
    //非递归中序遍历
    void nonRecursiveInTraversal();
    //非递归前序遍历
    void nonRecursivePreTraversal();
    //非递归后序遍历
    void nonRecursivePostTraversal();
    //返回树的高度
    int treeHeight();
    //返回节点个数
    int treeNodeCount();
    //返回叶结点个数
    int treeLeavesCount();
    //销毁树
    void destroyTree();
private:
    //根节点定义
    nodeType<elemType>* root;
    //实现复制一棵树
    void copyTree(nodeType<elemType>* &copiedTreeRoot,nodeType<elemType>* otherTreeRoot);
    //实现删除
    void deleteFromTree(nodeType<elemType>* &p);
    //销毁
    void destroy(nodeType<elemType>* &p);
    //层序遍历
    void BFS(nodeType<elemType>* p);
    //实现中序遍历
    void inorder(nodeType<elemType>* p);
    //实现前序遍历
    void preorder(nodeType<elemType>* p);
    //实现后序遍历
    void postorder(nodeType<elemType>* p);
    //求树高
    int height(nodeType<elemType>* p);
    //求节点数
    int nodeCount(nodeType<elemType>* p);
    //求叶节点数
    void leavesCount(nodeType<elemType>* p,int &Count);
};
//默认构造函数
template <class elemType>
bSearchTreeType<elemType>::bSearchTreeType()
{
    root=NULL;
}
//判空
template <class elemType>
bool bSearchTreeType<elemType>::isEmpty()
{
    return (root==NULL);
}
//查找函数
template <class elemType>
bool bSearchTreeType<elemType>::search(const elemType&searchItem)
{
    nodeType<elemType>* current;
    bool found=false;
    if(root==NULL)
    {
        cerr<<"Cannot search an empty tree"<<endl;
    }
    else
    {
        current=root;
        while(current!=NULL&&!found)
        {
            if(current->info==searchItem)
                found=true;
            else if (current->info>searchItem)
            {
                current=current->llink;
            }
            else
            {
                current=current->rlink;
            }
        }
        return found;
    }

}
//插入函数
template<class elemType>
void bSearchTreeType<elemType>::insert(const elemType&insertItem)
{
    nodeType<elemType>* current;
    nodeType<elemType>* trailCurrent;
    nodeType<elemType>* newNode;
    newNode=new nodeType<elemType>;
    assert(newNode!=NULL);
    newNode->info=insertItem;
    newNode->llink=NULL;
    newNode->rlink=NULL;
    if(root==NULL)
        root=newNode;
    else
    {
        current=root;
        while(current!=NULL)
        {
            trailCurrent=current;
            if(current->info==insertItem)
            {
                cerr<<"The insertItem is already in the tree"<<endl;
                return ;
            }
            else
            {
                if(current->info>insertItem)
                    current=current->llink;
                else
                    current=current->rlink;
            }
        }
        if(trailCurrent->info>insertItem)
            trailCurrent->llink=newNode;
        else
            trailCurrent->rlink=newNode;
    }
}
//删除节点
template<class elemType>
void bSearchTreeType<elemType>::deleteFromTree(nodeType<elemType>* &p)
{
    nodeType<elemType>* current;
    nodeType<elemType>* trailCurrent;
    nodeType<elemType>* temp;
    if(p==NULL)
        cerr<<"Error!The node to be deleted is NULL!"<<endl;
    else if(p->llink==NULL&&p->rlink==NULL)
    {
        temp=p;
        p=NULL;
        delete temp;
    }
    else if(p->llink==NULL)
    {
        temp=p;
        p=temp->rlink;
        delete temp;
    }
    else if(p->rlink==NULL)
    {
        temp=p;
        p=temp->llink;
        delete temp;
    }
    else
    {
        current=p->llink;
        trailCurrent=NULL;
        while(current->rlink!=NULL)
        {
            trailCurrent=current;
            current=current->rlink;
        }
        p->info=current->info;
        if(trailCurrent==NULL)
            p->llink=current->llink;
        else
            trailCurrent->rlink=current->llink;
        delete current;
    }
}
//删除特定元素
template<class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType& deleteItem)
{
    nodeType<elemType>* current;
    nodeType<elemType>* trailCurrent;
    bool found= false;
    if(root==NULL)
    {
        cerr<<"Cannot delete from the empty tree!"<<endl;
    }
    else
    {
        current=root;
        trailCurrent=root;
        while(current!=NULL&&!found)
        {
            if(current->info==deleteItem)
            {
                found=true;
                cout<<current->info<<endl;
            }
            else
            {
                trailCurrent=current;
                if(current->info > deleteItem)
                {
                    current=current->llink;
                }
                else
                    current=current->rlink;
            }
        }
        if(current=NULL)
            cerr<<"The deleteItem is not in the vector!"<<endl;
        else
        {
            if(found)
            {
                if(current==root)
                {
                    deleteFromTree(root);
                }
                else
                {
                    if(trailCurrent->info>deleteItem)
                        deleteFromTree(trailCurrent->llink);
                    else
                        deleteFromTree(trailCurrent->rlink);
                }
            }
        }
    }
}
//中序遍历
template <class elemType>
void bSearchTreeType<elemType>::inorderTraversal()
{
    inorder(root);
    cout<<endl;
}
//前序遍历
template <class elemType>
void bSearchTreeType<elemType>::preorderTraversal()
{
    preorder(root);
    cout<<endl;
}
//后序遍历
template <class elemType>
void bSearchTreeType<elemType>::postorderTraversal()
{
    postorder(root);
    cout<<endl;
}
//求树高
template <class elemType>
int bSearchTreeType<elemType>::treeHeight()
{
    return height(root);
}
//求节点数
template <class elemType>
int bSearchTreeType<elemType>::treeNodeCount()
{
    return nodeCount(root);
}
template <class elemType>

//求叶子节点数
int bSearchTreeType<elemType>::treeLeavesCount()
{
    int Count=0;
    leavesCount(root,Count);
    return Count;
}
//层次遍历
template <class elemType>
void bSearchTreeType<elemType>::bfs()
{
    BFS(root);
}

//层次遍历的具体实现
template <class elemType>
void bSearchTreeType<elemType>::BFS(nodeType<elemType>* p)
{
    nodeType<elemType>* a[300];
    int head=0,tail=0;
    if(p)
    {
        a[head++]=p;
        while(tail!=head)
        {
            if(a[tail]->llink!=NULL)
            {
                a[head++]=a[tail]->llink;
            }
            if(a[tail]->rlink!=NULL)
            {
                a[head++]=a[tail]->rlink;
            }
            cout<<a[tail++]->info<<" ";
        }
        cout<<endl;
    }
}
//中序遍历实现
template <class elemType>
void bSearchTreeType<elemType>::inorder(nodeType<elemType>* p)
{
    if(p!=NULL)
    {
        inorder(p->llink);
        cout<<p->info<<" ";
        inorder(p->rlink);
    }
}
//前序遍历实现
template <class elemType>
void bSearchTreeType<elemType>::preorder(nodeType<elemType>* p)
{
    if(p!=NULL)
    {
        cout<<p->info<<" ";
        preorder(p->llink);
        preorder(p->rlink);
    }
}
//后序遍历实现
template <class elemType>
void bSearchTreeType<elemType>::postorder(nodeType<elemType>* p)
{
    if(p!=NULL)
    {

        postorder(p->llink);
        postorder(p->rlink);
        cout<<p->info<<" ";
    }
}
//实现求树高
template<class elemType>
int bSearchTreeType<elemType>::height(nodeType<elemType>* p)
{
    if(p==NULL)
    {
        return 0;
    }
    else
    {
        return 1+max(height(p->llink),height(p->rlink));
    }
}
//实现非递归中序遍历
template <class elemType>
void bSearchTreeType<elemType>::nonRecursiveInTraversal()
{
    stack<nodeType<elemType>* >nodeTypeStack;
    nodeType<elemType>* current;
    current=root;
    while((current!=NULL)||!nodeTypeStack.empty())
    {
        if(current!=NULL)
        {
            nodeTypeStack.push(current);
            current=current->llink;
        }
        else
        {
            current=nodeTypeStack.top();
            nodeTypeStack.pop();
            cout<<current->info<<" ";
            current=current->rlink;
        }
    }
    cout<<endl;
}
//实现非递归前序遍历
template <class elemType>
void bSearchTreeType<elemType>::nonRecursivePreTraversal()
{
    stack<nodeType<elemType>* >nodeTypeStack;
    nodeType<elemType>* current;
    current=root;
    while((current!=NULL)||!nodeTypeStack.empty())
    {
        if(current!=NULL)
        {
            cout<<current->info<<" ";
            nodeTypeStack.push(current);
            current=current->llink;
        }
        else
        {
            current=nodeTypeStack.top();
            nodeTypeStack.pop();
            current=current->rlink;
        }
    }
    cout<<endl;
}
//实现非递归后序遍历
template <class elemType>
void bSearchTreeType<elemType>::nonRecursivePostTraversal()
{
    stack<nodeType<elemType>* >nodeTypeStack;
    stack<int> IntStack;
    nodeType<elemType>* current;
    current=root;
    int v=0;
    if(current!=NULL)
    {
        nodeTypeStack.push(current);
        IntStack.push(1);
        current=current->llink;
        while(!nodeTypeStack.empty())
        {
            if(current!=NULL && v==0)
            {
                nodeTypeStack.push(current);
                IntStack.push(1);
                current=current->llink;
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
                    current=current->rlink;
                    v=0;
                }
                else
                    cout<<current->info<<" ";
            }
        }
    }
}
//实现求节点数
template<class elemType>
int bSearchTreeType<elemType>::nodeCount(nodeType<elemType>* p)
{
    if(p==NULL)
    {
        return 0;
    }
    else
    {
        return 1+nodeCount(p->llink)+nodeCount(p->rlink);
    }
}
//实现求叶子节点数
template<class elemType>
void bSearchTreeType<elemType>::leavesCount(nodeType<elemType>* p,int &Count)
{
    if(p)
    {
        if(p->llink==NULL&&p->rlink==NULL)
            Count++;
        leavesCount(p->llink,Count);
        leavesCount(p->rlink,Count);
    }
}
//复制一棵树
template<class elemType>
void bSearchTreeType<elemType>::copyTree(nodeType<elemType>* &copiedTreeRoot,nodeType<elemType>* otherTreeRoot)
{
    if(otherTreeRoot==NULL)
        copiedTreeRoot=NULL;
    else
    {
        copiedTreeRoot=new nodeType<elemType>;
        copiedTreeRoot->info=otherTreeRoot->info;
        copyTree(copiedTreeRoot->llink,otherTreeRoot->llink);
        copyTree(copiedTreeRoot->rlink,otherTreeRoot->rlink);
    }
}
//实现销毁树
template<class elemType>
void bSearchTreeType<elemType>::destroy(nodeType<elemType>* &p)
{
    if(p!=NULL)
    {
        destroy(p->llink);
        destroy(p->rlink);
        delete p;
        p=NULL;
    }
}
//销毁树
template<class elemType>
void bSearchTreeType<elemType>::destroyTree()
{
    destroy(root);
}
//复制构造函数
template<class elemType>
bSearchTreeType<elemType>::bSearchTreeType(const bSearchTreeType<elemType>& otherTree)
{
    if(otherTree.root==NULL)
    {
        root=NULL;
    }
    else
    {
        copyTree(root,otherTree.root);
    }
}
//析构函数
template<class elemType>
bSearchTreeType<elemType>::~bSearchTreeType()
{
    destroy(root);
}
//重载赋值运算符
template<class elemType>
const bSearchTreeType<elemType>& bSearchTreeType<elemType>::operator=(const bSearchTreeType<elemType>& otherTree)
{
    if(this!=&otherTree)
    {
        if(root!=NULL)
        {
            destroy(root);
        }
        if(otherTree.root==NULL)
        {
            root=NULL;
        }
        else
        {
            copyTree(root,otherTree.root);
        }
    }
    return *this;
}
#endif
//int main()
//{
//    bSearchTreeType<int> A;
//    A.insert(10);
//    A.insert(6);
//    A.insert(14);
//    A.insert(3);
//    A.insert(8);
//    A.insert(12);
//    A.insert(16);
//    cout<<"二叉树为："<<endl;
//    cout<<"               10"<<endl;
//    cout<<"            6     14"<<endl;
//    cout<<"          3  8  12  16"<<endl<<endl;
//    bSearchTreeType<int> B(A);
//    bSearchTreeType<int> C=A;
//    cout<<"树高为：";
//    cout<<C.treeHeight()<<endl;
//    cout<<"节点数为:";
//    cout<<C.treeNodeCount()<<endl;
//    cout<<"叶子节点数为:";
//    cout<<C.treeLeavesCount()<<endl;
//    cout<<"前序遍历：";
//    C.preorderTraversal();
//    cout<<"中序遍历：";
//    C.inorderTraversal();
//    cout<<"后序遍历：";
//    C.postorderTraversal();
//    cout<<"非递归后序遍历：";
//    C.nonRecursivePreTraversal();
//    cout<<"层次遍历：";
//    C.bfs();
//    return 0;
//}



