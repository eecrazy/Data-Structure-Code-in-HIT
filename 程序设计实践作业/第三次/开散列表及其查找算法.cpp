//外散列表：

#define N 1001
struct node
{
	int data;
	node* next;
};

node* hash[N];

int h(int k)
{
	return (k%N+51)%N;
}
node* search(int k)
{
	node* str=hash[h(k)];
	while(str!=NULL)
	{
		if(str->data==k)
			return str;
		else
			str=str->next;
	}
	return str;
}
void insert(int r)
{
	int bucket;
	node* oldherder;
	if(search(r)==NULL)
	{
		bucket=h(r);
		oldherder=hash[bucket];
		hash[bucket]=new node;
		hash[bucket]->data=r;
		hash[bucket]->next=oldherder;
	}
}
void delete(int k)
{
	int n=h(k);
	node* str;
	bool b=false;
	if(hash[n]!=NULL)
	{
		if(hash[n]->data==k)
			hash[n]=hash[n]->next;
		else
		{
			str=hash[n];
			while((str->next)&&b==false)
			{
				if(str->next->data==k)
				{
					str->next=str->next->next;
					b=true;
				}
				else
					str=str->next;
			}
		}
	}
}