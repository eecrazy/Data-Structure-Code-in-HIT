#include <iostream>
using namespace std;
typedef int Type;
struct Node
{
	Type element;
	Node *left;
	Node *right;
};

//访问函数
Node* access( Type X, Node* T );
//插入函数
Node* insert( Type X, Node* T );
//删除函数
Node* Delete( Type X, Node* T );

//单右旋
Node* single_right_rotate( Node* T )
{
	Node* x = T;
	Node* y = T->left;
	x->left = y->right;
	y->right = x;
	return y;
}

//单左旋
Node* single_left_rotate( Node* T )
{
	Node* x = T;
	Node* y = T->right;

	x->right = y->left;
	y->left = x;

	return y;
}
//双右旋
Node* double_right_rotate( Node* T )
{
	T->left = single_left_rotate( T->left );
	return single_right_rotate( T );
}

//双左旋
Node* double_left_rotate( Node* T )
{
	T->right = single_right_rotate( T->right );
	return single_left_rotate( T );
}

// Node* access( Element X, Node* *T )是访问函数，
// 如果X存在就做Splay操作，将包含X的节点移到树根处。并返回包含X节点的位置
// 如果不存在就返回NULL。
Node* access( Type X, Node* T )
{
	static int deepth = -1;
	Node* returnVal = NULL;
	deepth++;

	printf(" %d ", deepth);

	if (T == NULL )
	{
		deepth = -1;
		return NULL;
	}
	if ( X < T->element )
	{
		returnVal=access( X, T ->left );
		if ( returnVal == NULL )
		{
			return NULL;
		}
		if ( returnVal == T ->left )
		{
			if ( deepth == 0)
			{
				T= single_right_rotate( T );
			}
			else
			{
				deepth--;
				return returnVal;
			}
		}
		else if ( returnVal == T->left->left )
		{
			T = single_right_rotate( T );
			T = single_right_rotate( T );
		}
		else if ( returnVal == T->left->right )
		{
			T = double_right_rotate( T );
		}
		else
		{
			fprintf( stderr, "Error!/n" );
			exit(0);
		}
	}
	else if ( X > T->element )
	{
		returnVal = access( X, T->right );
		if ( returnVal == NULL )
		{
			return NULL;
		}
		if ( returnVal == T->right )
		{
			if ( deepth == 0)
			{
				T = single_left_rotate( T );
			}
			else
			{
				deepth--;
				return returnVal;
			}
		}
		else if ( returnVal == T->right->right )
		{
			T = single_left_rotate( T );
			T = single_left_rotate( T );
		}
		else if ( returnVal == T->right->left )
		{
			T = double_left_rotate( T );
		}
		else
		{
			fprintf( stderr, "Error!/n" );
			exit(0);
		}
	}
	deepth--;
	return T;
}
//插入的具体实现
static Node* _insert( Type X, Node* T )
{
	if ( T == NULL )
	{
		T = new Node;
		if ( T == NULL )
		{
			fprintf( stderr, "No Space!/n");
			exit( 1 );
		}
		T->element = X;
		T->left = NULL;
		T->right = NULL;
		return T;
	}
	if ( X < T->element )
	{
		T->left = insert( X, T->left );
	}
	else if ( X > T->element )
	{
		T->right = insert( X, T->right );
	}
	return T;
}
//插入操作,实现是先用_insert函数将X插入T中，然后访问X，将其移到树根处。
Node* insert( Type X, Node* T )
{
	T = _insert( X, T );
	return access( X, T );
}
//返回是删除后的树。如果X存在，就删除X，否则不做任何修改。
Node* Delete( Type X, Node* T )
{
	Node* child_tree = NULL;
	if ( T == NULL )
		return NULL;
	if ( X < T->element )
	{
		T->left = Delete( X, T->left );
	}
	else if ( X > T->element )
	{
		T->right = Delete( X, T->right );
	}
	else
	{
		if ( T->left == NULL )
		{
			child_tree = T->right;
			delete( T );
			T = child_tree;
		}
		else if ( T->right == NULL )
		{
			child_tree = T->left;
			delete T ;
			T = child_tree;
		}
		else
		{
			/* 寻找T右子树最小的元素min(T->right) */
			Node* Temp;
			Node* P1;
			Node* P2;
			P1 = T;
			P2 = T->right;
			while ( P2->left != NULL )
			{
				P1 = P2;
				P2 = P2->left;
			}
			/* 令parent(min(T->right))->left = NULL */
			if ( P1 != T )	// 即P2 != T->right
			{
				P1->left = NULL;
			}
			else
			{
				T->right = NULL;
			}
			Temp = T;
			/* 令T=min(T->right) */
			T = P2;
			T->left = Temp->left;
			T->right = Temp->right;
			/*释放原来的T，即要删除的元素*/
			delete Temp;
		}
	}
	return T;
}
int main()
{
return 0;
}
