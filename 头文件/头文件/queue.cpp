#include <iostream>
using namespace std;
template <class Type>
class queueType
{
public:
	const queueType<Type>& operator=(const queueType<Type>&);
	bool isEmptyQueue();
	bool isFullQueue();
	void initializeQueue();
	void destoryQueue();
	Type front();
	Type back();
	void addQueue(const Type& queueElement);
	void deleteQueue();
	queueType(int queueSize=100);
	queueType(const queueType<Type>& otherQueue);
	~queueType();
private:
	int maxQueueSize;
	int queueFront;
	int queueRear;
	Type* list;
};

template<class Type>
void queueType<Type>::initializeQueue()
{
	queueFront=0;
	queueRear=maxQueueSize-1;
	count=0;
}

template<class Type>
bool queueType<Type>::isEmptyQueue()
{
	return (count==0);
}

template<class Type>
bool queueType<Type>::isFullQueue()
{
	return (count==maxQueueSize);
}

template<class Type>
void queueType<Type>::destoryQueue()
{
	queueFront=0;
	queueRear=maxQueueSize-1;
	count=0;
}

template<class Type>
Type queueType<Type>::front()
{
	assert(!isEmptyQueue());
	return list[queueFront];
}
template<class Type>
Type queueType<Type>::back()
{
	assert(!isEmptyQueue());
	return list[queueRear];
}

template<class Type>
void queueType<Type>::addQueue(const Type& newElement)
{
	if(!isFullQueue())
	{
		queueRear=(queueRear+1)%maxQueueSize;
		count++;
		list[queueRear]=newElement;
	}
	else
		cerr<<"Cannot add to a full queue."<<endl;
}

template<class Type>
void queueType<Type>::deleteQueue()
{
	if(!isEmptyQueue())
	{
		count=count-1;
		queueFront=(queueFront+1)%maxQueueSize;
	}
	else
	{
		cout<<"Cannot remove from an empty queue."<<endl;
	}
}

template<class Type>
queueType<Type>::queueType(int queueSize)
{
	if(queueSize<=0)
	{
		cout<<"The size of the array to hold the queue must be positive."<<endl;
		cout<<"Creating an array of size 100."<<endl;
		maxQueueSize=100;
	}
	else
	{
		maxQueueSize=queueSize;
	}
	queueFront=0;
	queueRear=maxQueueSize-1;
	count=0;
	list=new Type[maxQueueSize];
	assert(list!=NULL);
}

template<class Type>
queueType<Type>::~queueType()
{
	delete []list;
}
int main()
{

}









