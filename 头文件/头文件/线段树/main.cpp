#include <iostream>
#include <iomanip>
using namespace std;
struct Node
{
    int   left,right,cover;  //区间左右值
    Node   *leftchild;
    Node   *rightchild;
};
Node *build(int   l ,  int r ) //建立二叉树
{
    Node   *root = new Node;
    root->left = l;
    root->right = r;     //设置结点区间
    root->leftchild = NULL;
    root->rightchild = NULL;

    if ( l +1< r )
    {
        int  mid = (r+l) >>1;
        root->leftchild = build ( l , mid ) ;
        root->rightchild = build ( mid  , r) ;
    }

    return    root;
}
void Insert(int  c, int d , Node  *root )//插入一条线段[c,d]：
{
    if(c<= root->left&&d>= root->right)
        root-> cover++;
    else
    {
        if(c < (root->left+ root->right)/2 )
        Insert (c,d, root->leftchild  );
        if(d > (root->left+ root->right)/2 )
        Insert (c,d, root->rightchild  );
    }
}
void Delete (int c , int  d , Node  *root )//删除一条线段[c,d]:
{
    if(c<= root->left&&d>= root->right)
    {
        if(root->cover>=1)
            root-> cover= root-> cover-1;
    }
    else
    {
        if(c < (root->left+ root->right)/2 ) Delete ( c,d, root->leftchild  );
        if(d > (root->left+ root->right)/2 ) Delete ( c,d, root->rightchild );
    }
}
int main()
{
    return 0;
}
