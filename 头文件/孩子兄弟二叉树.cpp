//程序采用孩子兄弟表示法存储树，实现了树的构造、
//遍历、深度、宽度、结点个数、叶子个数 以及
//结点的层次、祖先、双亲、左兄弟、右兄弟各种功能
#include <iostream>
using namespace std;
const int MaxCSTreeSize = 20;
template<class T>
class CSNode
{
public:
    T data;
    CSNode* firstchild;
    CSNode* nextsibling;
public:
    CSNode();
    CSNode(CSNode* fchild,CSNode* nextsibling,T newdata);
    CSNode* getFirstChild();
    CSNode* getNextSibling();
    T getData();
    void setFirstChild(T newData);
    void setNextsibling(T newData);
    void showInputChild();//显示本节点并请求输入它的孩子
};

template<class T>
CSNode<T>::CSNode():firstchild(NULL),nextsibling(NULL)
{ }

template<class T>
CSNode<T>::CSNode(CSNode* fchild,CSNode* nextsibling,T newdata):firstchild(fchild),nextsibling(nextsibling),data(newdata)
{ }

template<class T>
CSNode<T>* CSNode<T>::getFirstChild()
{
    return firstchild;
}

template<class T>
CSNode<T>* CSNode<T>::getNextSibling()//模板类：凡是包含模板类名的都要加<>，无论是在返回值还是在作用域
{
    //模板类中函数：在类外实现的时候，要有个冒	template<class T>  表示这是个模板类的函数，区分与不同函数
    return nextsibling;
}

template<class T>
T CSNode<T>::getData()
{
    return data;
}

template<class T>
void CSNode<T>::setFirstChild(T newData)
{
    firstchild->data = newData;
}

template<class T>
void CSNode<T>::setNextsibling(T newData)
{
    nextsibling->data = newData;
}

template<class T>
void CSNode<T>::showInputChild()
{
    cout<<"请输入"<<data<<"的孩子:";
}

template<class T>
class CSTree
{
public:
    CSTree();
    CSTree(const CSTree<T>& csTree);
    ~CSTree();
    const CSTree<T>& operator=(const CSTree<T>& csTree);
    void  createCSTree(); //按建立树
    void  InitCSTree();   //初始化树
    void  destoryCSTree();//销毁树
    bool  isEmptyCSTree();//检查树是否为空
    void  preOrderTraverse();//先序遍历
    void  postOrderTraverse(); //后序遍历
    void  levelOrderTraverse();//层序遍历
    int   heightCSTree();//树高度
    int   widthCSTree(); //树宽度
    int   getDegreeCSTree();//树的度--树中所有结点度的最大值
    int   nodeCountCSTree();  //树结点个数
    int   LeavesCountCSTree();//树叶子个数
    int   nodeLevelCSTree(T item);//结点item在的层次
    int   getChildrenCount(const CSNode<T>* p)const;//返回结点孩子个数
    void  getAllParentCSTree(T item)const;//找item的所有祖先
    void  longPathCSNode();//输出从每个叶子结点到根结点的最长路径 ----- 未实现
    bool  findCSNode(const T item,CSNode<T>*& ret)const; //查找结点
    bool  getParentCSTree(const T item,CSNode<T>*& ret)const;//查找结点item的父亲结点
    bool  getleftChild(const CSNode<T>* p,CSNode<T>*& ret) const;   //返回最左边的兄弟
    bool  getrightSibling(const CSNode<T>* p,CSNode<T>*& ret) const;  //返回最右边的兄弟
    bool  getAllSibling(const T item) const; //输出所有兄弟
    bool  getAllChildren(T item);//输出所有的孩子
private:
    void create(CSNode<T>*& p);//以p为根创建子树
    void  copyTree(CSNode<T>*& copyTreeRoot,CSNode<T>* otherTreeRoot);
    //把以otherTreeRoot为根节点的部分拷贝到copyTreeRoot为根节点的部分
    void  destory(CSNode<T>*& p,int& num);
    //销毁以p为根节点的部分
    void  preOrder(CSNode<T>* p);
    //先序遍历以p为根节点的部分
    void  postOrder(CSNode<T>* p);
    //后序遍历以p为根节点的部分
    void  levelOrder(CSNode<T>* p);
    //层次遍历以p为根节点的部分
    int   height(CSNode<T>* p);
    //计算以p为根节点的高度
    int   width(CSNode<T>* p);
    //计算以p为根子树的宽度
    int   nodeCount(CSNode<T>* p);
    //计算以p为根节点的结点个数
    int   leavesCount(CSNode<T>* p);
    //计算以p为根节点的叶子个数
    void  nodeLevel(T item,CSNode<T>* p,int level,int& nlevel);
    //计算以p为根节点的中item所在层次，如有多个元素，则遇到第一个则返回（离根最近），如果没有出现，则返回0
    bool  find(CSNode<T>*p,const T item,bool& isFind,CSNode<T>*& cur)const;
    //在p指向的树中，返回 值为item的指针
    bool  getParent(CSNode<T>*p,const T item,bool& isFind,bool& isFirst,CSNode<T>*& ret)const;
    //在p指向子树中，找item的父亲
    bool getAllParent(T item,CSNode<T>* p,CSNode<T>* path[MaxCSTreeSize],int& seat,bool& isFind)const;
    //找item的所有祖先，seat表示最后一个父亲的下标
    void  longPath(CSNode<T>* p,int len,int& maxLen,CSNode<T>*& longNode);
    ////输出从每个叶子结点到根结点的最长路径
    int getDegree(CSNode<T>* p);
    //输出树的度（书中结点的孩子最大值）
private:
    CSNode<T>* root;
};

template<class T>
CSTree<T>::CSTree():root(NULL)//注意，这里构造函数要为root赋值为空，否则在之后和空比对的时候，可能会出错
{ }

template<class T>
CSTree<T>::~CSTree()
{
    if (root!=NULL)
    {
        int num=0;
        destory(root,num);
        InitCSTree();
    }
}

template<class T>
void CSTree<T>::createCSTree()
{
    create(root);
}

template<class T>
void CSTree<T>::create(CSNode<T>*& p)
{
    T parent;
    T child;
    //定义一个队列
    int front=0;
    int rear=0;
    CSNode<T>*pNode = p;
    CSNode<T>* queue[MaxCSTreeSize];
    cin>>parent>>child;
    while(child!='#')
    {
        CSNode<T>* node = new CSNode<T>;
        node->data = child;
        node->firstchild = NULL;
        node->nextsibling = NULL;
        if (parent=='#')
        {
            p = node;//为根
            queue[(rear++)%MaxCSTreeSize]=node;//根入队
        }
        else
        {
            pNode = queue[front];//读取队头元素
            while(pNode->data!=parent) //找自己父亲节点的指针
            {
                front=(front+1)%MaxCSTreeSize;
                pNode = queue[front];//读取队头元素---不能写成pNode = queue[front++]啊，因为在找到父亲的时候，front又执行了++，父亲就直接出队列了，当父亲后来的孩子来的时候就找不到父亲而出错了！
            }
            if (pNode->data==parent)//是儿子
            {
                if (pNode->firstchild==NULL)
                {
                    pNode->firstchild = node;
                }
                else
                {
                    pNode = pNode->firstchild;
                    while (pNode->nextsibling)
                    {
                        pNode=pNode->nextsibling;
                    }
                    pNode->nextsibling= node;
                }
            }
            if ((rear+1)%MaxCSTreeSize!=front)//队不满，则入队
            {
                queue[(rear++)%MaxCSTreeSize]=node;//把自己的儿子放到队列中
            }
        }
        cin>>parent>>child;
    }
}

template<class T>
void CSTree<T>::copyTree(CSNode<T>*& dstTreeRoot,CSNode<T>* srcTreeRoot)
{
    if (srcTreeRoot)
    {
        dstTreeRoot = new CSNode<T>;
        dstTreeRoot->data = srcTreeRoot->data;
        copyTree(dstTreeRoot->firstchild,srcTreeRoot->firstchild);
        copyTree(dstTreeRoot->nextsibling,srcTreeRoot->nextsibling);
    }
}

template<class T>
CSTree<T>::CSTree(const CSTree<T>& csTree)
{
    if (csTree.root==NULL)
    {
        root = NULL;
    }
    else
    {
        copyTree(this->root,csTree.root);
    }
}

template<class T>
const CSTree<T>& CSTree<T>::operator=(const CSTree<T>& csTree)
{
    if (this!=&csTree)//避免自己赋值
    {
        if (root!=NULL)//
        {
            int num=0;//num只是为了调试用
            destory(root,num);//自己有成员，先销毁
        }
        if (csTree.root==NULL)
        {
            root = NULL;
        }
        else
        {
            copyTree(this->root,csTree.root);
        }
    }
    return *this;
}

template<class T>
void CSTree<T>::InitCSTree()
{
    root=NULL;
}

template<class T>
void CSTree<T>::destoryCSTree()
{
    int num=0;
    destory(root,num);
    root=NULL;
    cout<<"销毁了"<<num<<"个结点"<<endl;
}
/*使用后序销毁树--可以直接把该树看成一半的二叉树，见结点销毁即可*/
template<class T>
void CSTree<T>::destory(CSNode<T>*& p,int& num)
{
    if (!p)//空节点
    {
        return;
    }
    destory(p->firstchild,num);
    destory(p->nextsibling,num);
    delete p;
    num++;
}

template<class T>
bool CSTree<T>::isEmptyCSTree()
{
    if (root==NULL)
    {
        return true;
    }
    return false;
}

template<class T>
void CSTree<T>::preOrderTraverse()
{
    preOrder(root);
    cout<<endl;
}

/*树的先序遍历和转变成二叉树后的先序遍历是一样的*/
template<class T>
void CSTree<T>::preOrder(CSNode<T>* p)
{
    if (p)
    {
        cout<<p->getData();
        preOrder(p->firstchild);
        preOrder(p->nextsibling);
    }
}

template<class T>
void CSTree<T>::postOrderTraverse()
{
    postOrder(root);
    cout<<endl;
}

/*树的后序遍历和转变成二叉树后的中序遍历是一样的*/
template<class T>
void CSTree<T>::postOrder(CSNode<T>* p)
{
    if (p)
    {
        postOrder(p->firstchild);
        cout<<p->getData();
        postOrder(p->nextsibling);
    }
}

template<class T>
void CSTree<T>::levelOrderTraverse()
{
    levelOrder(root);
    cout<<endl;
}
/*树的层次遍历和二叉树的层次遍历思路是一样的，入队的都是该结点的所有孩子*/
template<class T>
void CSTree<T>::levelOrder(CSNode<T>* p)
{
    //定义一个队列
    int front=0;
    int rear=0;
    CSNode<T>* queue[MaxCSTreeSize];
    if(!p)
    {
        return;
    }
    queue[(rear++)%MaxCSTreeSize]=p;
    while(front<rear)
    {
        CSNode<T>* t = queue[(front++)%MaxCSTreeSize];
        cout<<t->data;
        for(CSNode<T>* pNode=t->firstchild; pNode; pNode = pNode->nextsibling)
        {
            queue[(rear++)%MaxCSTreeSize]=pNode;
        }
    }
}

template<class T>
int CSTree<T>::LeavesCountCSTree()
{
    return leavesCount(root);
}

/*如果一个节点的做左子树为空，则必为叶子节点*/
template<class T>
int CSTree<T>::leavesCount(CSNode<T>* p)
{
    int count = 0;
    if (!p)//老忘 出口一
    {
        return 0;
    }
    if (!p->firstchild)
    {
        return 1;
    }
    for(CSNode<T>* pNode=p->firstchild; pNode; pNode = pNode->nextsibling)
    {
        count += leavesCount(pNode);
    }
    return count;
}
/*寻找item的结点*/
template<class T>
int CSTree<T>::nodeLevelCSTree(T item)
{
    int nlevel = 0;
    nodeLevel(item,root,1,nlevel);//首先到第一层查找
    return nlevel;
}

/*
level参数表示现在已经查找到第几层
nlevel参数表示记录结点所在的最终的层次
*/
template<class T>
void CSTree<T>::nodeLevel(T item,CSNode<T>* p,int level,int& nlevel)
{
    if (nlevel) //当层次非0时，表示已经找到 -- 出口一
    {
        return;
    }
    if (!p) //出口二
    {
        return;
    }
    if (p->data == item)//出口三
    {
        nlevel = level;
        return;
    }
    for (CSNode<T>*pNode = p->firstchild; pNode; pNode=pNode->nextsibling) //在孩子处查找 --- 入口
    {
        nodeLevel(item,pNode,level+1,nlevel);
    }
}

template<class T>
int CSTree<T>::heightCSTree()
{
    return height(root);
}

/*把根和右孩子的深度比较，取最大值*/
template<class T>
int CSTree<T>::height(CSNode<T>* p)
{
    int maxHeight = 0;
    if (!p)//因为在递归的时候不对空孩子进行判断，参数可能会有为空的情况，这时要专门对空进行处理
    {
        return 0;
    }
    if (!p->firstchild)//结点是叶子结点的情况
    {
        return 1;
    }
    for (CSNode<T>* pNode = p->firstchild; pNode; pNode=pNode->nextsibling) //结点是有多个孩子的情况
    {
        int h = height(pNode) + 1;
        if (h>maxHeight)
        {
            maxHeight = h;
        }
    }
    return maxHeight;
}


/*树的宽度*/
template<class T>
int CSTree<T>::widthCSTree()
{
    return width(root);
}

/*求宽度的函数总是想不出要引入last变量，一定要注意啊*/
template<class T>
int CSTree<T>::width(CSNode<T> *p)
{
    int w = 0;
    int maxWidth=0;
    int front=0;
    int rear = 0;
    int last=0;//last指向一层中最后那个元素
    CSNode<T>*queue[MaxCSTreeSize];
    //根先入队
    if (!p)
    {
        maxWidth = 0;
    }
    else
    {
        queue[rear++]=p;
        while (front<=last)//等号成立：最后那个元素仍然是本层的元素，要继续处理
        {
            CSNode<T>* cur = queue[front++];//出队处理
            w++;
            for (CSNode<T>* pNode=cur->firstchild; pNode; pNode=pNode->nextsibling)
            {
                queue[rear++]=pNode;
            }
            if (front>last)
            {
                last = rear-1;//因为rear总是指向本层元素的下一位
                if (w > maxWidth)
                {
                    maxWidth = w;
                }
                w=0;
            }
        }
    }
    return maxWidth;
}

template<class T>
int CSTree<T>::nodeCountCSTree()
{
    return nodeCount(root);
}
/*根据先序遍历得到*/
template<class T>
int CSTree<T>::nodeCount(CSNode<T>* p)
{
    int sum=0;
    if (!p)
    {
        return 0;
    }
    if (!p->firstchild)//左孩子为空，该结点就为叶子结点
    {
        return 1;
    }
    for (CSNode<T>*pNode = p->firstchild; pNode; pNode=pNode->nextsibling)
    {
        sum+=nodeCount(pNode);
    }
    return sum + 1;//1代表父亲本身，sum为孩子的总和
}



template<class T>
bool CSTree<T>::findCSNode(const T item,CSNode<T>*& ret)const
{
    bool isFind = false;
    find(root,item,isFind,ret);
    return isFind;
}

/*使用深度遍历进行查找*/
template<class T>
bool CSTree<T>::find(CSNode<T>*p,const T item,bool& isFind,CSNode<T>*& cur)const
{
    if (isFind)//找到直接返回
    {
        return isFind;
    }
    if (!p)//结点为空，直接返回
    {
        cur = NULL;
        return isFind;
    }
    if (p->data == item)//找到
    {
        cur = p;
        isFind = true;
        return isFind;
    }//没找到，继续递归
    for (CSNode<T>*pNode = p->firstchild; pNode; pNode=pNode->nextsibling)
    {
        find(pNode,item,isFind,cur);
        if (isFind)
        {
            return isFind;
        }
    }
    return isFind;
}

template<class T>
int CSTree<T>::getDegreeCSTree()
{
    return getDegree(root);
}

template<class T>
int CSTree<T>::getDegree(CSNode<T>* p)
{
    int num=0;
    if (!p)//递归出口一 -- 结点为空
    {
        return 0;
    }
    if (!p->firstchild)//递归出口二 -- 结点为叶子结点
    {
        return 1;
    }
    for (CSNode<T>* pNode = p->firstchild; pNode; pNode=pNode->nextsibling) //处理自身，计算自己孩子的个数 -- 结点有孩子
    {
        num++;
    }
    for (CSNode<T>* pNode = p->firstchild; pNode; pNode=pNode->nextsibling) //计算自己的孩子的度，并与自己的度相比较，返回最大度
    {
        int num1 = getDegree(pNode);
        if(num1>num)
        {
            num = num1;
        }
    }
    return num;
}
template<class T>
bool CSTree<T>::getleftChild(const CSNode<T>* p,CSNode<T>*& ret)const
{
    if (!p)
    {
        return false;
    }
    else
    {
        if(getParentCSTree(p->data,ret))//找到p结点的父亲
        {
            ret = ret->firstchild;
            return true;
        }
        else
            return false;//找不到父亲结点，表示这是个根节点
    }
}

template<class T>
bool CSTree<T>::getrightSibling(const CSNode<T>* p,CSNode<T>*& ret)const
{
    if(!p)
    {
        return false;
    }
    else
    {
        if(getParentCSTree(p->data,ret))//找到p结点的父亲
        {
            CSNode<T>* node = ret->firstchild;
            while(node->nextsibling)
            {
                node = node->nextsibling;
            }
            ret = node;
            return true;
        }
        else
            return false;//找不到父亲结点，表示这是个根节点
    }
}

template<class T>
bool CSTree<T>::getParentCSTree(const T item,CSNode<T>*& ret) const
{
    bool isFind = false;
    bool isFirst = true;
    getParent(root,item,isFind,isFirst,ret);
    return isFind;
}

/*使用层次遍历得到检查结点*/
template<class T>
bool CSTree<T>::getParent(CSNode<T>*p,const T item,bool& isFind,bool& isFirst,CSNode<T>*& ret)const
{
    if (isFind) //出口一
    {
        return isFind;
    }
    if (!p)//p为空 // 出口二
    {
        return false;
    }
    if (p->data == item )//检查自己 //出口三
    {
        if (p==root)
        {
            cout<<"要查找元素为根！"<<endl;//不存在父亲结点
            isFind = false;
            return isFind;
        }
        else
        {
            isFind = true;
            //这里ret还不能赋值，只能在递归出去后才能继续得到父亲的指针
            return isFind;
        }
    }
    for (CSNode<T>* pNode = p->firstchild; pNode; pNode=pNode->nextsibling) //出口五 + 入口
    {
        getParent(pNode,item,isFind,isFirst,ret); //入口一
        if (isFind && isFirst)//检查递归回来的结果，如果找到，就为ret赋值，因为递归在回退的时候，isFind仍也是true，不引入isFirst就还会对结点ret赋值，即一路回退一路赋值。如果要避免这种情况，则需要引入这个变量，只有第一次出现这个情况的时候才为其赋值
        {
            isFirst = false;
            ret = p;
            return isFind;
        }
    }
    return isFind;
}

template<class T>
int CSTree<T>::getChildrenCount(const CSNode<T>* p)const
{
    int count= 0;
    for (CSNode<T>* pNode = p->firstchild; pNode; pNode=pNode->nextsibling) //计算本结点的度
    {
        count++;
    }
    return count;
}

template<class T>
void CSTree<T>::getAllParentCSTree(T item)const
{
    CSNode<T>* path[MaxCSTreeSize];//存放树的结点
    //int len=0;//递归的层次
    int seat=0;//结点有多少双亲
    bool isFind = false;//是否已经找到
    getAllParent(item,root,path,seat,isFind);
    if (isFind)
    {
        for (int i=0; i<seat; i++)
        {
            cout<<path[i]->data;
        }
        cout<<endl;
    }
    else
    {
        cout<<"没有找到结点!"<<item<<endl;
    }
}
//可以直接使用转换二叉树后的先序遍历。
/*思想:
使用一个数组保存双亲结点
双亲放入数组，之后当处理检查完自己和左子树的时候，如果没找到，则这个结点就不会再是其双亲结点，直接把该结点移除数组。
*/
template<class T>
bool CSTree<T>::getAllParent(T item,CSNode<T>* p,CSNode<T>* path[MaxCSTreeSize],int& seat,bool& isFind)const //需要思考啊
{
    if (isFind)//找到直接返回
    {
        return isFind;
    }
    if (!p)//空子树不进数组
    {
        return false;
    }
    if (p->data==item)//找着的这个数也不进入数组
    {
        isFind = true;
        return isFind;
    }
    else
    {
        path[seat++]=p;
        getAllParent(item,p->firstchild,path,seat,isFind);
        if (!isFind)
        {
            seat=seat-1;//减1是因为：ath[seat++]=p;这里seat是指向下一个要存放的位置，这里当执行到这一步的时候，说明左面的兄弟没找到，因为他们两个是兄弟关系，这时要把最左边的孩子移除去，这里只需还让右孩子放到左孩子的位置直接覆盖就好
            getAllParent(item,p->nextsibling,path,seat,isFind);
        }
    }
    return isFind;
}

template<class T>
bool CSTree<T>::getAllSibling(const T item) const
{
    //先找到自己的父亲
    bool isFind = false;
    CSNode<T>* ret = NULL;
    isFind = getParentCSTree(item,ret);
    if (!isFind)
    {
        //没找到父亲
        return false;
    }
    else
    {
        isFind=false;//同时利用isFind表示是不是找到了自己的兄弟
        for (CSNode<T>*pNode = ret->firstchild; pNode; pNode=pNode->nextsibling)
        {
            if (pNode->data!=item)
            {
                isFind = true;
                cout<<pNode->data<<" ";//兄弟从左到右依次为：
            }

        }
        return isFind;
    }
}

template<class T>
bool CSTree<T>::getAllChildren(T item)
{
    bool isFind = false;
    CSNode<T> *parent = NULL;
    findCSNode(item,parent);
    for (CSNode<T>*pNode = parent->firstchild; pNode; pNode=pNode->nextsibling)
    {
        isFind = true;//有孩子
        cout<<pNode->data<<" ";//兄弟从左到右依次为：
    }
    return isFind;
}

int main()
{
    /* ----测试赋值函数
    CSTree<char> csTree;
    CSTree<char> csTree1;
    cout<<"建立树，以##表示结束:"<<endl;
    csTree1.createCSTree();
    csTree = csTree1;//调用赋值函数
    */

    //测试赋值构造函数

    CSTree<char> csTree1;
    cout<<"建立树，以##表示结束:"<<endl;
    csTree1.createCSTree();
    CSTree<char> csTree = csTree1;//调用拷贝构造函数

    //---一般操作
    cout<<"先序遍历为:";
    csTree.preOrderTraverse();
    cout<<"后序遍历为:";
    csTree.postOrderTraverse();
    cout<<"层次遍历为:";
    csTree.levelOrderTraverse();
    cout<<"树的高度为："<<csTree.heightCSTree()<<endl;
    cout<<"树的宽度为："<<csTree.widthCSTree()<<endl;
    cout<<"树的度为："<<csTree.getDegreeCSTree()<<endl;
    cout<<"树的结点个数为："<<csTree.nodeCountCSTree()<<endl;
    cout<<"树的叶子结点为："<<csTree.LeavesCountCSTree()<<endl;
    char item='f';
    CSNode<char>* cur=NULL;
    if (csTree.findCSNode(item,cur))
    {
        cout<<item<<"的层次："<<csTree.nodeLevelCSTree(item)<<endl;

        cout<<item<<"的祖先为:";
        csTree.getAllParentCSTree(item);

        CSNode<char>* ret=NULL;
        if (csTree.getParentCSTree(item,ret))
        {
            cout<<item<<"的父亲为:"<<ret->getData()<<endl;
        }
        else
        {
            cout<<item<<"没有双亲！"<<endl;
        }
        if (csTree.getleftChild(cur,ret))
        {
            if (ret->data == cur->data)
            {
                cout<<item<<"的最左的兄弟为自己！"<<endl;
            }
            else
            {
                cout<<item<<"的最左的兄弟为:"<<ret->getData()<<endl;
            }
        }
        else
        {
            cout<<item<<"没有最左的兄弟！"<<endl;
        }
        if (csTree.getrightSibling(cur,ret))
        {
            if (ret->data == cur->data)
            {
                cout<<item<<"的最右的兄弟为自己！"<<endl;
            }
            else
            {
                cout<<item<<"的最右边的兄弟为:"<<ret->getData()<<endl;
            }
        }
        else
        {
            cout<<item<<"没有最右边的兄弟"<<endl;
        }
        cout<<item<<"的所有兄弟为:";
        bool isFind = csTree.getAllSibling(item);
        cout<<endl;
        if (!isFind)
        {
            cout<<item<<"没有兄弟！"<<endl;
        }
        cout<<item<<"的所有孩子为:";
        isFind =csTree.getAllChildren(item);
        cout<<endl;
        if (!isFind)
        {
            cout<<item<<"没有孩子！"<<endl;
        }
    }
    else
    {
        cout<<"结点"<<item<<"不存在！"<<endl;
    }
    csTree.destoryCSTree();
    system("pause");
    return 1;
}
