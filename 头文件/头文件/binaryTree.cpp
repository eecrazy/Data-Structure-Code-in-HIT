#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
template <class elemType>
struct nodeType
{
	elemType ifno;
	nodeType<elemType> *llink;
	nodeType<elemType> *rlink;
};

template <class elemType>
class binaryTreeType
{
public:
	binaryTreeType();
	~binaryTreeType();
	const binaryTreeType<elemType>& operator=(const binaryTreeType<elemType>&);
	bool isEmpty();
	void inorderTraversal();
	void preorderTraversal();
	void postorderTraversal();
	void nonRecursiveInTraversal();
	void nonRecursivePreTraversal();
	void nonRecursivePostTraversal();
	int treeHeight();
	int treeNodeCount();
	int treeLeavesCount();
	void destroyTree();
	binaryTreeType(const binaryTreeType<elemType>& otherTree);
private:
	nodeType<elemType>* root;
	void copyTree(nodeType<elemType>* &copiedTreeRoot,nodeType<elemType>* otherTreeRoot);
	void destroy(nodeType<elemType>* &p);
	void inorder(nodeType<elemType>* p);
	void preorder(nodeType<elemType>* p);
	void postorder(nodeType<elemType>* p);
	int height(nodeType<elemType>* p);
	int nodeCount(nodeType<elemType>* p);
	void leavesCount(nodeType<elemType>* p,int &Count);
};

template <class elemType>
binaryTreeType<elemType>::binaryTreeType()
{
	root=NULL;
}
template <class elemType>
bool binaryTreeType<elemType>::isEmpty()
{
	return (root==NULL);
}

template <class elemType>
void binaryTreeType<elemType>::inorderTraversal()
{
	inorder(root);
}
template <class elemType>
void binaryTreeType<elemType>::preorderTraversal()
{
	preorder(root);
}
template <class elemType>
void binaryTreeType<elemType>::postorderTraversal()
{
	postorder(root);
}
template <class elemType>
void binaryTreeType<elemType>::nonRecursiveInTraversal()
{
	stack<nodeType<elemType>* >nodeTypeStack;
	nodeType<elemType>* current;
	current=root;
	while((current!=NULL)||!nodeTypeStack.empty())
	{
		if(current!=NULL)
		{
			nodeTypeStack.push(current);
			current=current->llink;
		}
		else
		{
			current=nodeTypeStack.top();
			nodeTypeStack.pop();
			cout<<current->info<<" ";
			current=current->rlink;
		}
	}
	cout<<endl;
}
template <class elemType>
void binaryTreeType<elemType>::nonRecursivePreTraversal()
{
	stack<nodeType<elemType>* >nodeTypeStack;
	nodeType<elemType>* current;
	current=root;
	while((current!=NULL)||!nodeTypeStack.empty())
	{
		if(current!=NULL)
		{
			cout<<current->info<<" ";
			nodeTypeStack.push(current);
			current=current->llink;
		}
		else
		{
			current=nodeTypeStack.top();
			nodeTypeStack.pop();
			current=current->rlink;
		}
	}
	cout<<endl;
}
template <class elemType>
void binaryTreeType<elemType>::nonRecursivePostTraversal()
{
	stack<nodeType<elemType>* >nodeTypeStack;
	stack<int> IntStack;
	nodeType<elemType>* current;
	current=root;
	int v=0;
	if(current!=NULL)
	{
		nodeTypeStack.push(current);
		IntStack.push(1);
		current=current->llink;
		while(!nodeTypeStack.empty())
		{
			if(current!=NULL && v==0)
			{
				nodeTypeStack.push(current);
				IntStack.push(1);
				current=current->llink;
			}
			else
			{
				current=nodeTypeStack.top();
				nodeTypeStack.pop();
				v=IntStack.top();
				IntStack.pop();
				if(v==1)
				{
					nodeTypeStack.push(current);
					IntStack.push(2);
					current=current->rlink;
					v=0;
				}
				else
					cout<<current->info<<" ";
			}
		}
	}
}

template <class elemType>
int binaryTreeType<elemType>::treeHeight()
{
	return height(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeNodeCount()
{
    return nodeCount(root);
}
template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount()
{
    int Count=0;
    leavesCount(root,Count);
    return Count;
}
template <class elemType>
void binaryTreeType<elemType>::inorder(nodeType<elemType>* p)
{
	if(p!=NULL)
	{
		inorder(p->llink);
		cout<<p->info<<" ";
		inorder(p->rlink);
	}
}
template <class elemType>
void binaryTreeType<elemType>::preorder(nodeType<elemType>* p)
{
	if(p!=NULL)
	{
		cout<<p->info<<" ";
		preorder(p->llink);

		preorder(p->rlink);
	}
}

template <class elemType>
void binaryTreeType<elemType>::postorder(nodeType<elemType>* p)
{
	if(p!=NULL)
	{

		postorder(p->llink);
		postorder(p->rlink);
		cout<<p->info<<" ";
	}
}

template<class elemType>
int binaryTreeType<elemType>::height(nodeType<elemType>* p)
{
	if(p==NULL)
	{
		return 0;
	}
	else
	{
		return 1+max(height(p->llink),height(p->rlink));
	}
}

template<class elemType>
int binaryTreeType<elemType>::nodeCount(nodeType<elemType>* p)
{
    if(p==NULL)
    {
        return 0;
    }
    else
    {
        return 1+nodeCount(p->llink)+nodeCount(p->rlink);
    }
}
template<class elemType>
void binaryTreeType<elemType>::leavesCount(nodeType<elemType>* p,int &Count)
{
    if(p)
    {
        if(p->llink==NULL&&p->rlink==NULL)
            Count++;
        leavesCount(p->llink,Count);
        leavesCount(p->rlink,Count);
    }
}
template<class elemType>
void binaryTreeType<elemType>::copyTree(nodeType<elemType>* &copiedTreeRoot,nodeType<elemType>* otherTreeRoot)
{
	if(otherTreeRoot==NULL)
		copiedTreeRoot=NULL;
	else
	{
		copiedTreeRoot=new nodeType<elemType>;
		copiedTreeRoot->info=otherTreeRoot->info;
		copyTree(copiedTreeRoot->llink,otherTreeRoot->link);
		copyTree(copiedTreeRoot->rlink,otherTreeRoot->rink);
	}
}
template<class elemType>
void binaryTreeType<elemType>::destroy(nodeType<elemType>* &p)
{
	if(p!=NULL)
	{
		destroy(p->llink);
		destroy(p->rlink);
		delete p;
		p=NULL;
	}
}
template<class elemType>
void binaryTreeType<elemType>::destroyTree()
{
	destroy(root);
}

template<class elemType>
binaryTreeType<elemType>::binaryTreeType(const binaryTreeType<elemType>& otherTree)
{
	if(otherTree.root==NULL)
	{
		root=NULL;
	}
	else
	{
		copyTree(root,otherTree.root);
	}
}

template<class elemType>
binaryTreeType<elemType>::~binaryTreeType()
{
	destroy(root);
}

template<class elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::operator=(const binaryTreeType<elemType>& otherTree)
{
	if(this!=&otherTree)
	{
		if(root!=NULL)
		{
			destroy(root);
		}
		if(otherTree.root==NULL)
		{
			root=NULL;
		}
		else
		{
			copyTree(root,otherTree.root);
		}

	}
	return *this;
}

int main()
{
    return 0;
}


