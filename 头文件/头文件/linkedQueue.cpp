#include <iostream>
using namespace std;
#include <cassert>

struct nodeType
{
	Type info;
	nodeType<Type>* link;
};
template <class Type>
class linkedQueueType
{
public:
	const linkedQueueType<Type>& operator=(const linkedQueueType<Type>&);
	bool isEmptyQueue();
	bool isFullQueue();
	void initializeQueue();
	void destoryQueue();
	Type front();
	Type back();
	void addQueue(const Type& queueElement);
	void deleteQueue();
	linkedQueueType();
	linkedQueueType(const linkedQueueType<Type>& otherQueue);
	~linkedQueueType();
private:
    nodeType<Type>* queueFront;
    nodeType<Type>* queueRear;
};

template<class Type>
bool linkedQueueType<Type>::isEmptyQueue()
{
	return (queueFront==NULL);
}

template<class Type>
bool linkedQueueType<Type>::isFullQueue()
{
	return false;
}

template<class Type>
void linkedQueueType<Type>::destoryQueue()
{
	nodeType<Type>* temp;
	while(queueFront!=NULL)
	{
		temp=queueFront;
		queueFront=queueFront->link;
		delete temp;
	}
	queueRear=NULL;
}

template<class Type>
void linkedQueueType<Type>::initializeQueue()
{
	destoryQueue();
}

template<class Type>
void linkedQueueType<Type>::addQueue(const Type&newElement)
{
	nodeType<Type>*newNode;
	newNode=new nodeType<Type>;
	assert(newNode!=NULL);
	newNode->info=newElement;
	newNode->link=NULL;
	if(queueFront==NULL)
	{
		queueFront=newNode;
		queueRear=newNode;
	}
	else
	{
		queueRear->link=newNode;
		queueRear=queueRear->link;
	}
}

template<class Type>
Type linkedQueueType<Type>::front()
{
	assert(queueFront!=NULL);
	return queueFront->info;
}

template<class Type>
Type linkedQueueType<type>::back()
{
	assert(queueRear!=NULL);
	return queueRear->info;
}

template<class type>
void linkedQueueType<type>::deleteQueue()
{
	nodeType<type>*temp;
	if(!isEmptyQueue())
	{
		temp=queueFront;
		queueFront=queueFront->link;
		delete temp;
		if(queueFront==NULL)
		{
			queueRear=NULL;
		}
	}
	else
	{
		ceer<<"Cannot remove from an empty queue."<<endl;
	}
}