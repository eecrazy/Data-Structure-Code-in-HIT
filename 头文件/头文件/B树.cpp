//2M路B树
#include <iostream>
#include <cstdio>
using namespace std;
const int M = 2;
const int KEY_MAX = 2 * M - 1;
const int KEY_MIN = M - 1;
const int CHILD_MAX = 2 * M;
const int CHILD_MIN = M;
template <class T>
class BTree
{
    typedef struct Node
    {
        int n; //关键码的个数
        T k[KEY_MAX]; //关键码
        Node * c[CHILD_MAX]; //子节点指针
        bool leaf; //是否是叶子节点
    }* PNode;
public:
    //默认构造函数
    BTree();
    //析构
    ~BTree();
    //插入
    bool Insert(T key);
    //删除
    bool Delete(T key);
    //查找
    bool Find(T key);
    //输出
    void Display();
private:
    //根节点
    PNode Root;
    //实现查找
    bool Search(PNode pNode, T key);
    bool SplitChild(PNode pParent, int nChildIndex);
    void InsertNoneFull(PNode pNode, T key);
    void MergeChild(PNode pParent, int index);
    void DeleteNoneEmpty(PNode pNode, T key);
    T GetPredecessor(PNode pNode);
    T GetSuccessor(PNode pNode);
    void GetFromLeftBrother(PNode pParent, int index, PNode pNode, PNode pLeft);
    void GetFromRightBrother(PNode pParent, int index, PNode pNode, PNode pRight);
    //销毁树
    void DestoryTree(PNode pNode);
    //实现输出
    void Display(PNode t, int level);
};
template <class T>
BTree<T>::BTree()
{
    Root = NULL;
}
template <class T>
BTree<T>::~BTree()
{
    DestoryTree(Root);
    Root = NULL;
}
template <class T>
bool BTree<T>::Insert(T key)
{
    //已经插入了，直接返回成功
    if(Search(Root, key))
        return true;
    if(Root==NULL)
        Root->n = 0;
    Root->leaf = true;
    if(Root->n == KEY_MAX)
    {
        PNode pNew = new Node;
        pNew->n = 0;
        for(int i = 0; i < CHILD_MAX; i++)
            pNew->c[i] = NULL;
        pNew->leaf = false;
        pNew->c[0] = Root;
        SplitChild(pNew, 0);
        InsertNoneFull(pNew, key);
        Root = pNew;
    }
    else
    {
        InsertNoneFull(Root, key);
    }
    return true;
}
template <class T>
bool BTree<T>::Delete(T key)
{
    if(NULL == Root)
        return true;
    //不存在，不用删了
    if(!Search(Root, key))
        return true;
    if(Root->n == 1) //特殊情况处理
    {
        if(Root->leaf)
        {
            DestoryTree(Root);
            Root = NULL;
            return true;
        }
        else
        {
            PNode pC1 = Root->c[0];
            PNode pC2 = Root->c[1];
            if(pC1->n == KEY_MIN && pC2->n == KEY_MIN)
            {
                MergeChild(Root, 0);
                delete Root;
                Root = pC1;
            }
        }
    }
    DeleteNoneEmpty(Root, key);
    return true;
}
template <class T>
bool BTree<T>::Find(T key)
{
    return Search(Root, key);
}
template <class T>
void BTree<T>::Display()
{
    Display(Root, 2);
    printf("\n");
}
template <class T>
bool BTree<T>::Search(PNode pNode, T key)
{
    if(pNode == NULL)
        return false;
    int i = 0;
    while(i < pNode->n && key > pNode->k[i])
    {
        i++;
    }
    if(i < pNode->n && (key == pNode->k[i]))
    {
        return true;
    }
    else if(pNode->leaf)
    {
        return false;
    }
    else
    {
        return Search(pNode->c[i], key);
    }
}
//将pParent的第nChildIndex个孩子分裂
template <class T>
bool BTree<T>::SplitChild(PNode pParent, int nChildIndex)
{
    PNode pChild = pParent->c[nChildIndex];
    //为新分裂出的节点分配空间
    PNode pChild2 = new Node;
        pChild2->n = 0;
        for(int i = 0; i < CHILD_MAX; i++)
            pChild2->c[i] = NULL;
    if(NULL == pChild2)
        return false;
    //与被分裂点同级
    pChild2->leaf = pChild->leaf;
    //设置分裂节点key数
    pChild2->n = KEY_MIN;
    //复制数据
    for(int i = 0; i < KEY_MIN; i++)
    {
        pChild2->k[i] = pChild->k[i + M];
    }
    //如果不是叶节点，复制指针
    if(!pChild->leaf)
    {
        for(int i = 0; i < CHILD_MIN; i++)
        {
            pChild2->c[i] = pChild->c[i + M];
        }
    }
    pChild->n = KEY_MIN;
    //将中间数作为索引插入到双亲节点中
    //插入点后面的关键字和指针都往后移动一个位置
    for(int i = pParent->n; i > nChildIndex; i--)
    {
        pParent->k[i] = pParent->k[i - 1];
        pParent->c[i + 1] = pParent->c[i];
    }
    pParent->k[nChildIndex] = pChild->k[M - 1];
    pParent->n++;
    pParent->c[nChildIndex + 1] = pChild2;
    return true;
}
template <class T>
void BTree<T>::InsertNoneFull(PNode pNode, T key)
{
    int i = pNode->n;
    PNode pChild = NULL;
    if(pNode->leaf)
    {
        while(i > 0 && (key < pNode->k[i - 1]))
        {
            pNode->k[i] = pNode->k[i - 1];
            i--;
        }
        pNode->k[i] = key;
        pNode->n++;
    }
    else
    {
        while(i > 0 && key < pNode->k[i - 1])
        {
            i--;
        }
        pChild = pNode->c[i];
        //如果子节点key满了
        if(pChild->n == KEY_MAX)
        {
            //分裂子节点
            SplitChild(pNode, i);
            //如果大于分裂后提上来的key，插入分裂后的右边，否则左边
            if(key > pNode->k[i])
            {
                i++;
                pChild = pNode->c[i]; //分裂后的右部分
            }
        }
        InsertNoneFull(pChild, key);
    }
}
template <class T>
void BTree<T>::MergeChild(PNode pParent, int index)
{
    PNode pChild1 = pParent->c[index];
    PNode pChild2 = pParent->c[index + 1];

    //将c2数据合并到c1
    pChild1->n = KEY_MAX;
    pChild1->k[M - 1] = pParent->k[index];
    for(int i = M; i < KEY_MAX; i++)
    {
        pChild1->k[i] = pChild2->k[i - M];
    }
    if(!pChild1->leaf)
    {
        for(int i = M; i < CHILD_MAX; i++)
        {
            pChild1->c[i] = pChild2->c[i - M];
        }
    }
    //父节点删除index的key，index后的往前移动一位
    pParent->n--;
    for(int i = index; i < (pParent->n); i++)
    {
        pParent->k[i] = pParent->k[i + 1];
        pParent->c[i + 1] = pParent->c[i + 2];
    }
    //删除child2
    delete pChild2;
    pChild2=NULL;
}
template <class T>
void BTree<T>::DeleteNoneEmpty(PNode pNode, T key)
{
    int i = pNode->n;
    if(pNode->leaf)
    {
        while(i > 0 && (key < pNode->k[i - 1]))
        {
            i--;
        }
        if(key == pNode->k[i - 1]) //1
        {
            for(int j = i; j < pNode->n; j++)
            {
                pNode->k[j - 1] = pNode->k[j];
            }
            pNode->n--;
        }
    }
    else
    {
        while(i > 0 && (key < pNode->k[i - 1]))
        {
            i--;
        }
        if(i > 0 && key == pNode->k[i - 1]) //2
        {
            PNode pChild1 = pNode->c[i - 1];
            PNode pChild2 = pNode->c[i];
            //左Child多，从左Child移一个
            if(pChild1->n > KEY_MIN) //2a
            {
                T preKey = GetPredecessor(pChild1);
                DeleteNoneEmpty(pChild1, preKey);
                pNode->k[i - 1] = preKey;
            } //右Child多，从右Child移一个
            else if(pChild2->n > KEY_MIN) //2b
            {
                T sucKey = GetSuccessor(pChild2);
                DeleteNoneEmpty(pChild2, sucKey);
                pNode->k[i - 1] = sucKey;
            } //左右都是M-1，合并
            else //2c
            {
                MergeChild(pNode, i - 1);
                DeleteNoneEmpty(pChild1, key);
            }
        }
        else //3
        {
            //含有key的子树
            PNode pSub = pNode->c[i];
            if(pSub->n == KEY_MIN)
            {
                PNode pLeft = (i > 0 ? pNode->c[i - 1] : NULL);
                PNode pRight = (i < pNode->n ? pNode->c[i + 1] : NULL);
                if(pLeft && pLeft->n > KEY_MIN) //3a1
                {
                    GetFromLeftBrother(pNode, i - 1, pSub, pLeft);
                }
                else if(pRight && pRight->n > KEY_MIN) //3a2
                {
                    GetFromRightBrother(pNode, i, pSub, pRight);
                }
                else if(pLeft && pLeft->n == KEY_MIN) //3b1
                {
                    MergeChild(pNode, i - 1);
                    pSub = pLeft;
                }
                else if(pRight && pRight->n == KEY_MIN) //3b2
                {
                    MergeChild(pNode, i);
                }
            }
            DeleteNoneEmpty(pSub, key);
        }
    }
}
template <class T>
T BTree<T>::GetPredecessor(PNode pNode)
{
    while(!pNode->leaf)
    {
        pNode = pNode->c[pNode->n];
    }
    return pNode->k[pNode->n - 1];
}
template <class T>
T BTree<T>::GetSuccessor(PNode pNode)
{
    while(!pNode->leaf)
    {
        pNode = pNode->c[0];
    }
    return pNode->k[0];
}
//把left最大key给pParent(index)，把pParent(index)给pNode
template <class T>
void BTree<T>::GetFromLeftBrother(PNode pParent, int index, PNode pNode, PNode pLeft)
{
    for(int i = pNode->n; i > 0; i--)
    {
        pNode->k[i] = pNode->k[i - 1];
    }
    pNode->k[0] = pParent->k[index];
    if(!pNode->leaf)
    {
        for(int i = pNode->n; i >= 0; i--)
        {
            pNode->c[i + 1] = pNode->c[i];
        }
        pNode->c[0] = pLeft->c[pLeft->n];
    }
    pNode->n++;

    //parent
    pParent->k[index] = pLeft->k[pLeft->n - 1];

    //left
    pLeft->n--;
}
//把right最小key给pParent(index)，把pParent(index)给pNode
template <class T>
void BTree<T>::GetFromRightBrother(PNode pParent, int index, PNode pNode, PNode pRight)
{
    pNode->k[pNode->n] = pParent->k[index];
    if(!pNode->leaf)
    {
        pNode->c[pNode->n + 1] = pRight->c[0];
    }
    pNode->n++;

    //parent
    pParent->k[index] = pRight->k[0];

    //right
    for(int i = 1; i < pRight->n; i++)
    {
        pRight->k[i - 1] = pRight->k[i];
    }
    if(!pRight->leaf)
    {
        for(int i = 0; i < pRight->n; i++)
        {
            pRight->c[i] = pRight->c[i + 1];
        }
    }
    pRight->n--;
}

template <class T>
void BTree<T>::DestoryTree(PNode pNode)
{
    if(pNode)
    {
        for(int i = 0; i <= pNode->n; i++)
        {
            if(pNode->leaf)
                break;
            if(pNode->c[i])
                DestoryTree(pNode->c[i]);
        }
        delete pNode;
        pNode=NULL;
    }
}
template <class T>
void BTree<T>::Display(PNode t, int level)
{
    int i = 0;
    if(t)
    {
        while(i < level - 2)
        {
            printf(" ");
            i++;
        }
        printf("[ ");
        for(int i = 0; i < t->n; i++)
        {
            printf("%d ", t->k[i]);
        }
        printf("]\n");

        for(int i = 0; i <= t->n; i++)
        {
            Display(t->c[i], level + 3);
        }
    }
}
