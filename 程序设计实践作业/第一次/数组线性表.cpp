template <class elemtype>
class arrayListType
{
public:
	arrayListType(int size=100);
	~arrayListType();
	bool isEmpty();
	bool isFull();
	int listSize();
	int maxListSize();
	void print();
	void insertAt(int location,elemtype& insertItem);
	void removeAt(int location);
	void replaceAt(int location,elemtype& repItem);
	void clear();
	int search(elemtype& iten);
	void insert(elemtype& insertItem);
	void remove(elemtype& removeItem);
private:
	elemtype* list;
	int length;
	int maxSize;
};
template <class elemtype>
arrayListType<elemtype>::arrayListType(int size)
{
	if(size<0)
	{
		cout<<"The array size must be positive.Creating an array of size 100"<<endl;
		maxSize=100;		
	}
	else
		maxSize=size;

	length=0;
	list=new elemtype[maxSize];
}
template <class elemtype>
arrayListType<elemtype>::~arrayListType()
{
	delete []list;
}
template <class elemtype>
bool arrayListType<elemtype>::isEmpty()
{
	return (length==0);
}
template <class elemtype>
boool arrayListType<elemtype>::isFull()
{
	return (length==maxSize);
}

template <class elemtype>
int arrayListType<elemtype>::listSize()
{
	return length;
}

template <class elemtype>
int arrayListType<elemtype>::maxListSize()
{
	return maxSize;
}
template <class elemtype>
void arrayListType<elemtype>::print()
{
	for(int i=0;i<length;i++)
	{
		cout<<list[i]<<" ";
	}
	cout<<endl;
}

template <class elemtype>
void arrayListType<elemtype>::insertAt(int location,elemtype& insertItem)
{
	if(location<0||location>=maxSize)
	{
		cout<<"The position is out of range"<<endl;
	}
	else if(length>=maxSize)
	{
		cout<<"The list is full"<<endl;
	}
	else
	{
		for(int i=length;i>location;i--)
		{
			list[i]=list[i-1];
		}
		list[location]=insertItem;
		length++;
	}

}

template <class elemtype>
void arrayListType<elemtype>::removeAt(int location)
{
	if(location<0||location>=length)
	{
		cout<<"The location is out of range"<<endl;
	}
	else
	{
		for(int i=location;i<length;i++)
		{
			list[i]=list[i+1];
		}
		length--;
	}
}

template <class elemtype>
void arrayListType<elemtype>::replaceAt(int location,elemtype& repItem)
{
	if(location<0||location>=length)
	{
		cout<<"The location is out of range"<<endl;
	}
	else
	{
		list[location]=repItem;
	}
}

template <class elemtype>
void arrayListType<elemtype>::clear()
{
	length=0;
}

template <class elemtype>
int arrayListType<elemtype>::search(elemtype& item)
{
	int loc;
	bool found=false;
	for(loc=0;loc<length;loc++)
	{
		if(list[loc]==item)
		{
			found=true;
			break;
		}
	}
	if(found)return loc;
	else return -1;
}

template <class elemtype>
void arrayListType<elemtype>::insert(elemtype &insertItem)
{
	int loc;
	if(length==0)
		list[length++]=insertItem;
	else if(length==maxSize)
	{
		cout<<"The list is full"<<endl;
	}
	else
	{
		loc=search(insertItem);
		if(loc==-1)
		{
			list[length++]=insertItem;
		}
		else
		{
			cout<<" The insertItem is already in the list!"<<endl;
		}
	}

}

template <class elemtype>
void arrayListType<elemtype>::remove(elemtype& removeItem)
{
	int loc;
	if(length==0)
	{
		cout<<"The list is empty!"<<endl;
	}
	else
	{
		loc=search(removeItem);
		if(loc!=-1)
		{
			removeAt(loc);
		}
		else
		{
			cout<<"The item to be deleted is not in the list"<<endl;
		}
	}

}