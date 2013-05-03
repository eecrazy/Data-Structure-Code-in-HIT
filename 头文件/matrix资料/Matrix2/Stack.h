#if !defined(AFX_STACK_H__75314E61_4BBF_11D5_9DFE_5254AB1C303A__INCLUDED_)
#define AFX_STACK_H__75314E61_4BBF_11D5_9DFE_5254AB1C303A__INCLUDED_
#include <afxtempl.h>




template<class T>
class CStack:public CList<T,T &>
{
	public:
		CStack();
		~CStack();
		void Push(T data);
		bool Pop(T & data);
		T GetTop();
};

template<class T>
CStack<T>::CStack()
{
}

template<class T>
CStack<T>::~CStack()
{
}

template<class T>
void CStack<T>::Push(T data)
{
	AddHead(data);
}

template<class T>
bool CStack<T>::Pop(T & data)
{
	if(GetCount()==0) return false;
	POSITION pos=GetHeadPosition();
	data=GetAt(pos);
	RemoveAt(pos);
	return true;
}

template<class T>
T CStack<T>::GetTop()
{
	return GetHead();
}


#endif