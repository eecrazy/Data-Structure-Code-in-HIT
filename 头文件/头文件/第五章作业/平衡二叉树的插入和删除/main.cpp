#include <iostream>
#include <vector>
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
    AVL(const T *arg,const int & n);
    ~AVL();
    void Insert(const T &k);
    vector < T > MidOrder() const;
    vector < T > FirstOrder() const;
    bool Contains(const T &k) const;
    bool ReMove(const T &k);
private:
    //the root node
    AVLNode<T> *Root;
    //insert an element
    void Insert(AVLNode<T> *&p,const T &k);
    //Release of all nodes
    void Free(AVLNode<T> *p);
    //midorder
    void MidOrder(const AVLNode<T> *p,vector<T> &order) const;
    //firstorder
    void FirstOrder(const AVLNode<T> *p,vector<T> &order) const;
    //search the given element
    bool Contains(const AVLNode<T> *p,const T &k) const;
    //remove a node whose data is k from subtree p
    bool ReMove(AVLNode<T> *&p,const T &k);
    //return the node with the minimal data from the subtree p
    AVLNode<T> *GetMin(AVLNode<T> *p) const;
    //Left Roatate
    void RotateWithLeftChild(AVLNode<T> *& p);
    //Right Roatate
    void RotateWithRightChild(AVLNode<T> *& p);
    //Get the height of the given node
    int Height(const AVLNode<T> *p) const;
    //Double Rotate
    void DoubleRotateLeftChild(AVLNode<T> *& p);
    void DoubleRotateRightChild(AVLNode<T> *& p);
    void RemoveRotate(AVLNode<T> *& p);
};
//构造函数
template<class T>
AVL<T>::AVL(const T *arg,const int &n)
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
    Free(Root);
}
//插入
template<class T>
void AVL<T>::Insert(AVLNode<T> *&p,const T &k)
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
            //Linear
            if(k < p->left->data)
            {
                RotateWithLeftChild(p);
            }
            //Zigzag
            else
            {
                DoubleRotateLeftChild(p);
            }
        }
    }
    else if(k > p->data)
    {
        Insert(p->right,k);
        if(Height(p->right) - Height(p->left)>=2)
        {
            //Zigzag
            if(k < p->right->data)
            {
                DoubleRotateRightChild(p);
            }
            //Linear
            else
            {
                RotateWithRightChild(p);
            }
        }
    }
    int a = Height(p->left);
    int b = Height(p->right);
    p->height = max(a,b)+1;
}
//实现析构
template<class T>
void AVL<T>::Free(AVLNode<T> *p)
{
    if(p == NULL) return;
    Free(p->left);
    Free(p->right);
    delete p;
}

//插入
template<class T>
void AVL<T>::Insert(const T &k)
{
    Insert(Root,k);
}
//查找
template<class T>
bool AVL<T>::Contains(const T &k) const
{
    return Contains(Root,k);
}

//实现查找
template<class T>
bool AVL<T>::Contains(const AVLNode<T> *p,const T &k) const
{
    //边界条件
    if(p == NULL) return false;
    if(p->data == k)
    {
        return true;
    }
    else if(k < p->data)
    {
        return Contains(p->left,k);
    }
    else
    {
        return Contains(p->right,k);
    }
}

template<class T>
void AVL<T>::MidOrder(const AVLNode<T>  *p,vector<T> &order) const
{
    if(p == NULL) return;
    MidOrder(p->left,order);
    order.push_back(p->data);
    MidOrder(p->right,order);
}


template<class T>
vector<T> AVL<T>::MidOrder() const
{
    vector<T> x;
    MidOrder(Root,x);
    return x;
}


template<class T>
bool AVL<T>::ReMove(const T &k)
{
    if(Root!=NULL)  return ReMove(Root,k);
    return false;
}

template<class T>
bool AVL<T>::ReMove(AVLNode<T> * &p,const T &k)
{
    if(p == NULL) return false;
    if(p->data > k) ReMove(p->left,k);
    else if(p->data < k) ReMove(p->right,k);
    else if(p->left != NULL && p->right != NULL)
    {
        p->data = GetMin(p->right)->data;
        ReMove(p->right,p->data);
    }
    else
    {
        AVLNode<T> *old = p;
        p = (p->left != NULL)?p->left:p->right;
        delete old;
        return true;
    }
    //Update height(can not be ignored!)
    int a = Height(p->left);
    int b = Height(p->right);
    p->height=max(a,b)+1;
    //if need to be rotated
    RemoveRotate(p);
    return true;
}


template<class T>
AVLNode<T> * AVL<T>::GetMin(AVLNode<T> *p) const
{
    if(p == NULL) return NULL;
    AVLNode<T> *newp = p;
    for(; newp->left != NULL;)
    {
        newp = newp->left;
    }
    return newp;
}

template<class T>
int AVL<T>::Height(const AVLNode<T> *p) const
{
    return p == NULL ? -1:p->height;
}

template<class T>
void AVL<T>::RotateWithLeftChild(AVLNode<T> *&p)
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


template<class T>
void AVL<T>::RotateWithRightChild(AVLNode<T> *& p)
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


template<class T>
void AVL<T>::DoubleRotateLeftChild(AVLNode<T> *& p)
{
    RotateWithRightChild(p->left);
    RotateWithLeftChild(p);
}

template<class T>
void AVL<T>::DoubleRotateRightChild(AVLNode<T> *& p)
{
    RotateWithLeftChild(p->right);
    RotateWithRightChild(p);
}

template<class T>
vector<T> AVL<T>::FirstOrder() const
{
    vector<T> order;
    FirstOrder(Root,order);
    return order;
}


template<class T>
void AVL<T>::FirstOrder(const AVLNode<T> *p,vector<T> &order) const
{
    if(p == NULL) return ;
    order.push_back(p->data);
//  cout< <p->data< <":"<<p->height< <endl;
    FirstOrder(p->left,order);
    FirstOrder(p->right,order);
}


template<class T>
void AVL<T>::RemoveRotate(AVLNode<T> *& p)
{
    if(Height(p->left)-Height(p->right)>=2)
    {
        if(p->left->left == NULL)
        {
            DoubleRotateLeftChild(p);
        }
        else
        {
            RotateWithLeftChild(p);
        }
    }
    else if (Height(p->right)-Height(p->left)>=2)
    {
        if(p->right->right==NULL)
        {
            DoubleRotateRightChild(p);
        }
        else
        {
            RotateWithRightChild(p);
        }
    }
}
