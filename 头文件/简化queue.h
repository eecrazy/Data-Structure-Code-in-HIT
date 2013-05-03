//有序链表，动态分配内存。简化的优先级队列
#ifndef H_ListType
#define H_ListType
#include <iostream>
#include <cassert>
using namespace std;
template<class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};
template<class Type>
class orderedLinkedListType
{
    public:
    //默认构造函数
    orderedLinkedListType();
    //复制构造函数
    orderedLinkedListType(const orderedLinkedListType<Type> &otherList);
    //析构函数
    ~orderedLinkedListType();
    //重载赋值运算符=
    const orderedLinkedListType<Type>& operator=(const orderedLinkedListType<Type>&);
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
    //搜索元素
    bool search(const Type& searachItem);
    //在表头插入元素
    void insertNode(const Type &newItem);
    //删除节点
    void deleteNode(const Type &deleteItem);
private:
     //元素个数
    int count;
    //头指针
    nodeType<Type> *first;
    //复制函数
    void copyList(const orderedLinkedListType<Type> &otherList);
};

//插入
template<class Type>
void orderedLinkedListType<Type>::insertNode(const Type &newItem)
{
    nodeType<Type>*current;
    nodeType<Type>*trailCurrent;
    nodeType<Type>*newNode;
    bool found;
    newNode=new nodeType<Type>;
    newNode->info=newItem;
    newNode->link=NULL;
    if(first==NULL)
    {
        first=newNode;
        count++;
    }
    else
    {
        current=first;
        found=false;
        while(current!=NULL&&!found)
        {
            if(current->info>=newItem)
            {
                found=true;
            }
            else
            {
                trailCurrent=current;
                current=current->link;
            }
        }
        if(current==first)
        {
            newNode->link=first;
            first=newNode;
            count++;
        }
        else
        {
            trailCurrent->link=newNode;
            newNode->link=current;
            count++;
        }
    }
}
//判空
template<class Type>
bool orderedLinkedListType<Type>::isEmptyList()
{
    return (first==NULL);
}
//默认构造函数
template<class Type>
orderedLinkedListType<Type>::orderedLinkedListType()
{
    first=NULL;
    count=0;
}
//销毁链表
template<class Type>
void orderedLinkedListType<Type>::destroyList()
{
    nodeType<Type> *temp;
    while(first!=NULL)
    {
        temp=first;
        first=first->link;
        delete temp;
    }
    count=0;
}
//初始化
template<class Type>
void orderedLinkedListType<Type>::initializeList()
{
    destroyList();
}

//返回链表长度
template<class Type>
int orderedLinkedListType<Type>::length()
{
    return count;
}
//返回第一个元素
template<class Type>
Type orderedLinkedListType<Type>::front()
{
    assert(first!=NULL);
    return first->info;
}
//查找元素
template<class Type>
bool orderedLinkedListType<Type>::search(const Type&searchItem)
{
    nodeType<Type>*current;
    bool found;
    current=first;
    found=false;
    while(current!=NULL&&!found)
    {
        if(current->info>=searchItem)
        {
            found=true;
        }
        else
        {
            current=current->link;
        }
    }
    if(found)
    {
        found=(current->info==searchItem);
    }
    return found;
}

//删除节点
template<class Type>
void orderedLinkedListType<Type>::deleteNode(const Type&deleteItem)
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
                delete current;
            }
            else
                cout<<"Item to be deleted is not in the list!"<<endl;
        }
    }
}
//复制函数
template<class Type>
void orderedLinkedListType<Type>::copyList(const orderedLinkedListType<Type> &otherList)
{
    nodeType<Type> *newNode;
    nodeType<Type> *current;
    if(otherList.first==NULL)
    {
        first=NULL;
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
        current=current->link;
        while(current!=NULL)
        {
            newNode=new nodeType<Type>;
            assert(newNode!=NULL);
            newNode->info=current->info;
            newNode->link=NULL;
            current=current->link;
        }
    }
}
//析构函数
template<class Type>
orderedLinkedListType<Type>::~orderedLinkedListType()
{
    destroyList();
}
//默认构造函数
template<class Type>
orderedLinkedListType<Type>::orderedLinkedListType(const orderedLinkedListType<Type>& otherList)
{
    first=NULL;
    copyList(otherList);
}
//重载赋值运算符=
template<class Type>
const orderedLinkedListType<Type>& orderedLinkedListType<Type>::operator=(const orderedLinkedListType<Type>& otherList)
{
    if(this !=&otherList)
    {
        copyList(otherList);
    }
    return *this;
}
#endif
//int main()
//{
//    orderedLinkedListType<int> a;
//    a.initializeList();
//    a.insertNode(44);
//    orderedLinkedListType<int> b(a);
//    return 0;
//}
