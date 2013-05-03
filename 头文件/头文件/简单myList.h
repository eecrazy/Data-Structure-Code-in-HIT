//简单链表，不能在中间插入，只能在表头表尾插入。动态分配内存
#ifndef H_ListType
#define H_ListType
#include <iostream.h>
#include <cassert>
//using namespace std;
template<class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};
template<class Type>
class linkedListType
{
    //重载输出运算符<<
    friend ostream& operator<<(ostream &osObject,const linkedListType<Type>& list);
public:
    //重载赋值运算符=
    const linkedListType<Type>& operator=(const linkedListType<Type>&);
    //初始化
    void initializeList();
    //判空
    bool isEmptyList();
    //返回链表长度
    int length();
    //销毁链表
    void destroyList();
    //返回第一个元素
    Type front();
    //返回最后一个元素
    Type back();
    //搜索元素
    bool search(const Type&searachItem);
    //在表头插入元素
    void insertFirst(const Type &newItem);
    //在表尾插入元素
    void insertLast(const Type &newItem);
    //删除节点
    void deleteNode(const Type&deleteItem);
    //默认构造函数
    linkedListType();
    //复制构造函数
    linkedListType(const linkedListType<Type> &otherList);
    //析构函数
    ~linkedListType();
private:
     //元素个数
    int count;
    //头指针
    nodeType<Type> *first;
    //尾指针
    nodeType<Type> *last;
    //复制函数
    void copyList(const linkedListType<Type> &otherList);
};
//判空
template<class Type>
bool linkedListType<Type>::isEmptyList()
{
    return (first==NULL);
}
//默认构造函数
template<class Type>
linkedListType<Type>::linkedListType()
{
    first=NULL;
    last=NULL;
    count=0;
}
//销毁链表
template<class Type>
void linkedListType<Type>::destroyList()
{
    nodeType<Type> *temp;
    while(first!=NULL)
    {
        temp=first;
        first=first->link;
        delete temp;
    }
    last=NULL;
    count=0;
}
//初始化
template<class Type>
void linkedListType<Type>::initializeList()
{
    destroyList();
}
//重载输出运算符<<
template<class Type>
ostream& operator<<(ostream &osObject,const linkedListType<Type>& list)
{
    nodeType<Type>* current;
    current=list.first;
    while(current!=NULL)
    {
        osObject<<current->info<<" ";
        current=current->link;
    }
    return osObject;
}
//返回链表长度
template<class Type>
int linkedListType<Type>::length()
{
    return count;
}
//返回第一个元素
template<class Type>
Type linkedListType<Type>::front()
{
    assert(last!=NULL);
    return first->info;
}
//返回最后一个元素
template<class Type>
Type linkedListType<Type>::back()
{
    assert(last!=NULL);
    return last->info;
}
//查找元素
template<class Type>
bool linkedListType<Type>::search(const Type&searchItem)
{
    nodeType<Type>*current;
    bool found;
    current=first;
    found=false;
    while(current!=NULL&&!found)
    {
        if(current->info=searchItem)
        {
            found=true;
        }
        else
        {
            current=current->link;
        }
    }
    return found;
}
//在表头插入元素
template <class Type>
void linkedListType<Type>::insertFirst(const Type& newItem)
{
    nodeType<Type>* newNode;
    newNode=new nodeType<Type>;
    assert(newNode!=NULL);
    newNode->info=newItem;
    newNode->link=first;
    first=newNode;
    count++;
    if(last==NULL)
    {
        last=newNode;
    }
}
//在表尾插入元素
template<class Type>
void linkedListType<Type>::insertLast(const Type&newItem)
{
    nodeType<Type>*newNode;
    newNode=new nodeType<Type>;
    newNode->info=newItem;
    newNode->link=NULL;
    if(first==NULL)
    {
        first=newNode;
        last=newNode;
        count++;
    }
    else
    {
        last->link=newNode;
        last=newNode;
        count++;
    }
}
//删除节点
template<class Type>
void linkedListType<Type>::deleteNode(const Type&deleteItem)
{
    nodeType<Type> *current;
    nodeType<Type> *trailCurrent;
    bool found;
    if(first==NULL)
    {
        cout<<"Cannot delete from an empty list!\n"<<endl;
    }
    else
    {
        if(first->info==deleteItem)
        {
            current=first;
            first=first->link;
            count--;
            if(first==NULL)
            {
                last=NULL;
            }
            delete current;
        }
        else
        {
            found=false;
            trailCurrent=first;
            current=first->link;
            while(current!=NULL&&!found)
            {
                if(current->info!=deleteItem)
                {
                    trailCurrent=current;
                    current=current->link;

                }
                else
                    found=true;
            }

            if(found)
            {
                trailCurrent->link=current->link;
                count--;
                if(last==current)
                {
                    last=trailCurrent;
                }
                delete current;
            }
            else
                cout<<"Item to be deleted is not in the list!"<<endl;
        }
    }
}
//复制函数
template<class Type>
void linkedListType<Type>::copyList(const linkedListType<Type> &otherList)
{
    nodeType<Type> *newNode;
    nodeType<Type> *current;
    if(otherList.first==NULL)
    {
        first=NULL;
        last=NULL;
        count=0;
    }
    else
    {
        current=otherList.first;
        count=otherList.count;
        first=new nodeType<Type>;
        assert(first!=NULL);
        first->info=current->info;
        first->link=NULL;
        last=first;
        current=current->link;
        while(current!=NULL)
        {
            newNode=new nodeType<Type>;
            assert(newNode!=NULL);
            newNode->info=current->info;
            newNode->link=NULL;
            last->link=newNode;
            last=newNode;
            current=current->link;
        }
    }
}
//析构函数
template<class Type>
linkedListType<Type>::~linkedListType()
{
    destroyList();
}
//默认构造函数
template<class Type>
linkedListType<Type>::linkedListType(const linkedListType<Type>& otherList)
{
    first=NULL;
    copyList(otherList);
}
 //重载赋值运算符=
template<class Type>
const linkedListType<Type>& linkedListType<Type>::operator=(const linkedListType<Type>& otherList)
{
    if(this !=&otherList)
    {
        copyList(otherList);
    }
    return *this;
}
#endif
/*
int main()
{
    linkedListType<int> a;
    a.initializeList();
    a.insertFirst(44);
    a.insertLast(55);
    linkedListType<int> b(a);
    cout<<a<<endl;
    return 0;
}

*/
