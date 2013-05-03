template <class elemType>
bool bSearchTreeType<elemType>::inorderBST_judge()
{
    elemType val;
    stack<nodeType<elemType>* >nodeTypeStack;
    nodeType<elemType>* current;
    current=root;
    int flag=1;
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
            if(flag==1)
            {
                  val=current->info;
                  flag=0;
            }
            else if(val<current->info)
            {
                val=current->info;
            }
            else
            {
                return false;
            }
            current=current->rlink;
        }
    }
    return true;
}
