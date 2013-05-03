//链表实现的堆栈，动态增加存储空间，采用模板技术，可以使用多种数据类型。
#ifndef H_LinkedStack
#define H_LinkedStack
#include <iostream>
using namespace std;
#include <cassert>
template<class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};
template<class Type>
class linkedStackType
{
public:
    //重载赋值运算符
    const linkedStackType<Type>&operator = (const linkedStackType<Type>&);
    void initializeStack();//初始化
    bool isEmptyStack();//判空
    bool isFullStack();//判满
    void destroyStack();//销毁栈
    void push(const Type&newItem);//压栈
    Type top();//返回栈顶元素
    void pop();//出栈
    linkedStackType();//默认构造函数
    linkedStackType(const linkedStackType<Type>& otherStack);//复制构造函数
    ~linkedStackType();//析构函数
private:
    nodeType<Type> *stackTop;
    void copyStack(const linkedStackType<Type>& otherStack);
};
//默认构造函数
template <class Type>
linkedStackType<Type>::linkedStackType()
{
    stackTop=NULL;
}
//销毁堆栈
template <class Type>
void linkedStackType<Type>::destroyStack()
{
    nodeType<Type> *temp;
    while(stackTop!=NULL)
    {
        temp=stackTop;
        stackTop=stackTop->link;
        delete temp;
    }
}
//初始化
template <class Type>
void linkedStackType<Type>::initializeStack()
{
    destroyStack();
}
//判空
template <class Type>
bool linkedStackType<Type>::isEmptyStack()
{
    return (stackTop==NULL);
}
//判满
template <class Type>
bool linkedStackType<Type>::isFullStack()
{
    return false;
}
//压栈
template <class Type>
void linkedStackType<Type>::push(const Type&newItem)
{
    nodeType<Type> *newNode;
    newNode =new nodeType<Type>;
    assert(newNode!=NULL);
    newNode->info=newItem;
    newNode->link=stackTop;
    stackTop=newNode;
}
//返回栈顶元素
template <class Type>
Type linkedStackType<Type>::top()
{
    assert(stackTop!=NULL);
    return stackTop->info;
}
//出栈
template <class Type>
void linkedStackType<Type>::pop()
{
    nodeType<Type> *newItem;
    if(stackTop!=NULL)
    {
        newItem=stackTop;
        stackTop=stackTop->link;
        delete newItem;
    }
    else
    {
        cout<<"Cannot remove from an empty stack!"<<endl;
    }
}
//复制函数,有问题
template <class Type>
void linkedStackType<Type>::copyStack(const linkedStackType<Type>& otherStack)
{

    nodeType<Type> *newNode;
    nodeType<Type> *current;
    if(stackTop!=NULL)
        destroyStack();

    if(otherStack.stackTop==NULL)
    {
        return ;
    }
    else
    {
        current=otherStack.stackTop;
        stackTop=new nodeType<Type>;
        assert(stackTop!=NULL);
        stackTop->info=current->info;
        stackTop->link=NULL;
        nodeType<Type> *ptr=stackTop;
        current=current->link;
        while(current!=NULL)
        {
            newNode=new nodeType<Type>;
            assert(newNode!=NULL);
            newNode->info=current->info;
            newNode->link=NULL;
            ptr->link=newNode;
            ptr=newNode;
            current=current->link;
        }
    }
}
//复制构造函数
template <class Type>
linkedStackType<Type>::linkedStackType(const linkedStackType<Type>& otherStack)
{
    stackTop=NULL;
    copyStack(otherStack);
}
//析构函数
template <class Type>
linkedStackType<Type>::~linkedStackType()
{
    destroyStack();
}
//重载赋值运算符
template <class Type>
const linkedStackType<Type>& linkedStackType<Type>::operator = (const linkedStackType<Type>&otherStack)
{
    if(this!=&otherStack)
        copyStack(otherStack);
    return *this;
}
int main()
{
    linkedStackType<int> myLinkedStack;
    myLinkedStack.push(1);
    cout<<myLinkedStack.top()<<endl;
    linkedStackType<int> otherStack;
    otherStack=myLinkedStack;
    cout<<otherStack.top()<<endl;
    otherStack.pop();
    otherStack.pop();
    return 0;
}
#endif

