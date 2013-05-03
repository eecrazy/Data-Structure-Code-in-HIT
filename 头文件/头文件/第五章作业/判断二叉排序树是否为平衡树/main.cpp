//根据平衡二叉树的定义，如果任意节点的左右子树的深度相差不超过1，那这棵树就是平衡二叉树。
//首先编写一个计算二叉树深度的函数，利用递归实现。
template<typename T>
static int Depth(BSTreeNode<T>* pbs)
{
	if (pbs==NULL)
		return 0;
	else
	{
		int ld = Depth(pbs->left);
		int rd = Depth(pbs->right);
		return 1 + (ld >rd ? ld : rd);
	}
}
//下面是利用递归判断左右子树的深度是否相差1来判断是否是平衡二叉树的函数：
template<typename T>
static bool isBalance(BSTreeNode<T>* pbs)
{
	if (pbs==NULL)
		return true;
	int dis = Depth(pbs->left) - Depth(pbs->right);
	if (dis>1 || dis<-1 )
		return false;
	else
		return isBalance(pbs->left) && isBalance(pbs->right);
}
