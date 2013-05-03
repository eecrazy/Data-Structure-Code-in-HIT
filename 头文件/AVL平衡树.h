#ifndef H_AVL_Type
#define H_AVL_Type
#include <iostream>
using namespace std;
template<class T>
struct AVLNode
{
    T data;
    AVLNode *left,*right;
    int height;
};
template<class T>
class AVL
{
public:
    //默认构造函数
    AVL();
    //构造函数
    AVL( T *arg, int & n);
    //析构函数
    ~AVL();
    //插入
    void Insert(T &k);
    //中序遍历
    void inOrder() ;
    //前序遍历
    void preOrder() ;
    //查找
    bool Search(T &k) ;
    //删除
    bool Delete(T &k);
private:
    //根节点
    AVLNode<T> *Root;
    //实现插入
    void Insert(AVLNode<T> *&p, T &k);
    //销毁树
    void destroy(AVLNode<T> *p);
    //中序遍历
    void inOrder( AVLNode<T> *p) ;
    //前序遍历
    void preOrder( AVLNode<T> *p) ;
    //查找
    bool Search( AVLNode<T> *p, T &k) ;
    //删除节点
    bool Delete(AVLNode<T> *&p, T &k);
    //求最小节点
    T GetMin(AVLNode<T> *p) ;
    //左旋
    void leftRotate(AVLNode<T> *& p);
    //右旋
    void rightRotate(AVLNode<T> *& p);
    //求树高
    int Height( AVLNode<T> *p) ;
    //左左旋
    void Double_LeftRotate(AVLNode<T> *& p);
    //右右旋
    void Double_RightRotate(AVLNode<T> *& p);
    //删除时旋转调整
    void DeleteRotate(AVLNode<T> *& p);
};

//默认构造函数
template<class T>
AVL<T>::AVL()
{
    Root = NULL;
}
//构造函数
template<class T>
AVL<T>::AVL( T *arg, int &n)
{
    Root = NULL;
    for(int i = 0; i < n; ++i)
    {
        Insert(Root,arg[i]);
    }
}
//析构函数
template<class T>
AVL<T>::~AVL()
{
    destroy(Root);
}
//插入
template<class T>
void AVL<T>::Insert(AVLNode<T> *&p, T &k)
{
    if(p == NULL)
    {
        p = new AVLNode<T>;
        p->data = k;
        p->left = p->right = NULL;
        p->height = 0;
        return;
    }
    else if(k < p->data)
    {
        Insert(p->left,k);
        if(Height(p->left) - Height(p->right)>=2)
        {
            if(k < p->left->data)
            {
                leftRotate(p);
            }
            else
            {
                Double_LeftRotate(p);
            }
        }
    }
    else if(k > p->data)
    {
        Insert(p->right,k);
        if(Height(p->right) - Height(p->left)>=2)
        {
            if(k < p->right->data)
            {
                Double_RightRotate(p);
            }
            else
            {
                rightRotate(p);
            }
        }
    }
    int a = Height(p->left);
    int b = Height(p->right);
    p->height = max(a,b)+1;
}
//实现析构
template<class T>
void AVL<T>::destroy(AVLNode<T> *p)
{
    if(p == NULL) return;
    destroy(p->left);
    destroy(p->right);
    delete p;
}

//插入
template<class T>
void AVL<T>::Insert( T &k)
{
    Insert(Root,k);
}
//查找
template<class T>
bool AVL<T>::Search( T &k)
{
    return Search(Root,k);
}

//实现查找
template<class T>
bool AVL<T>::Search( AVLNode<T> *p, T &k)
{
    //边界条件
    if(p == NULL) return false;
    if(p->data == k)
    {
        return true;
    }
    else if(k < p->data)
    {
        return Search(p->left,k);
    }
    else
    {
        return Search(p->right,k);
    }
}

//中序遍历
template<class T>
void AVL<T>::inOrder()
{
    inOrder(Root);
}
//实现中序遍历
template<class T>
void AVL<T>::inOrder( AVLNode<T>  *p)
{
    if(p!=NULL)
    {
        inOrder(p->left);
        cout<<p->data<<" ";
        inOrder(p->right);
    }
}
//前序遍历
template<class T>
void AVL<T>::preOrder()
{
    preOrder(Root);
}
//实现前序遍历
template<class T>
void AVL<T>::preOrder( AVLNode<T> *p)
{
    if(p!=NULL)
    {
        cout<<p->data<<" ";
        preOrder(p->left);
        preOrder(p->right);
    }
}
//删除节点
template<class T>
bool AVL<T>::Delete( T &k)
{
    if(Root!=NULL)  return Delete(Root,k);
    return false;
}

//递归实现删除节点
template<class T>
bool AVL<T>::Delete(AVLNode<T> * &p, T &k)
{
    if(p == NULL) return false;
    if(p->data > k) Delete(p->left,k);
    else if(p->data < k) Delete(p->right,k);
    else if(p->left != NULL && p->right != NULL)
    {
        p->data = GetMin(p->right);
        Delete(p->right,p->data);
    }
    else
    {
        AVLNode<T> *old = p;
        p = (p->left != NULL)?p->left:p->right;
        delete old;
        return true;
    }
    //更新节点高度
    int a = Height(p->left);
    int b = Height(p->right);
    p->height=max(a,b)+1;
    //if need to be rotated
    DeleteRotate(p);
    return true;
}

//返回以p为根的最小节点
template<class T>
T AVL<T>::GetMin(AVLNode<T> *p)
{
    if(p == NULL) return 0;
    AVLNode<T> *newp = p;
    while(newp->left != NULL)
    {
        newp = newp->left;
    }
    return newp->data;
}
//求树高
template<class T>
int AVL<T>::Height( AVLNode<T> *p)
{
    return p == NULL ? -1:p->height;
}
//左旋
template<class T>
void AVL<T>::leftRotate(AVLNode<T> *&p)
{
    AVLNode<T> *leftchild = p->left;
    p->left = leftchild->right;
    leftchild->right = p;
    //the order is important!
    //the next two statement can not be switched!
    int a,b;
    a = Height(p->left);
    b = Height(p->right);
    p->height = max(a,b)+1;
    a = Height(leftchild->left);
    b = Height(leftchild->right);
    leftchild->height = max(a,b)+1;
    //the final statement is also important,it makes the p point
    //to the right node
    p = leftchild;
}

//右旋
template<class T>
void AVL<T>::rightRotate(AVLNode<T> *& p)
{
    AVLNode<T> *rightchild = p->right;
    p->right = rightchild->left;
    rightchild->left = p;
    //the order is important!
    //the next two statement can not be switched!
    int a,b;
    a = Height(p->left);
    b = Height(p->right);
    p->height = max(a,b)+1;
    a = Height(rightchild->left);
    b = Height(rightchild->right);
    rightchild->height = max(a,b)+1;
    //the final statement is also important,it makes the p point
    //to the right node
    p = rightchild;
}

//左左旋
template<class T>
void AVL<T>::Double_LeftRotate(AVLNode<T> *& p)
{
    rightRotate(p->left);
    leftRotate(p);
}
//右右旋
template<class T>
void AVL<T>::Double_RightRotate(AVLNode<T> *& p)
{
    leftRotate(p->right);
    rightRotate(p);
}
//删除旋转调整
template<class T>
void AVL<T>::DeleteRotate(AVLNode<T> *& p)
{
    if(Height(p->left)-Height(p->right)>=2)
    {
        if(p->left->left == NULL)
        {
            Double_LeftRotate(p);
        }
        else
        {
            leftRotate(p);
        }
    }
    else if (Height(p->right)-Height(p->left)>=2)
    {
        if(p->right->right==NULL)
        {
            Double_RightRotate(p);
        }
        else
        {
            rightRotate(p);
        }
    }
}
#endif
