#include "BTree.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
using namespace std;
// constructor
BTree::BTree():_root(NULL)
{
    // calculate upper and lower limits
    _upper = m - 1;
    _lower = ceill((float)m/2) - 1;
}
// destructor
BTree::~BTree()
{
    if(_root) {
        destroy(_root);
    }
}
// destroy the a tree
void BTree::destroy(BTreeNode* node) {
    // delete leaf node
    if(node->_sum == 0) {
        delete node;
        return;
    }
    for(int i = 0; i <= node->_sum; i++) {
        destroy(node->_children[i]);
    }
    delete node;
}
BTree::SearchRes BTree::Search(value v) {
    // If the tree is empty, return NULL.
    if(!_root) {
        return {NULL, 0, false};
    }
    return SearchInNode(_root, v);
}
BTree::SearchRes BTree::SearchInNode(BTreeNode* node, value v) {
    int i;
    for(i = 1; i <= node->_sum; i++) {
        // if equal, return true;
        if(node->_keys[i]==v) {
            return {node, i, true};
        } else if(node->_keys[i] > v) // else find position where v should be
            break;
    }
    if(isLowest(node)) return {node, i, false}; // if lowest layer then return;
    else return SearchInNode(node->_children[i-1], v); // recurse
}
// Judge the current is  the lowest node who is no a leaf node.
bool BTree::isLowest(BTreeNode* node) {
    BTreeNode* pseudo = node->_children[0];
    if(pseudo->_sum == 0) return true;
    else return false;
}
// v @param: value to be inserted
// Summary:
//  if insert successfully, return true, else return false.
bool BTree::insertValue(value v) {
    if(!_root) {                 // if the tree is empty
        _root = new BTreeNode;
        _root->_sum = 1;
        _root->_keys[1] = v;
        _root->_parent = NULL;
        _root->_children[0] = getLeaf(_root);
        _root->_children[1] = getLeaf(_root);
        return true;
    }
    SearchRes res = Search(v);
    if(res._found) return false;          // if v exists, then return.

    // insert v into the lowest non-leaf node.
    insertInNode(res._ptr, v, res._pos, getLeaf(res._ptr), getLeaf(res._ptr));
    return true;
}
BTree::BTreeNode* BTree::getLeaf(BTreeNode* parent) {
    BTreeNode* temp = new BTreeNode;
    temp->_sum = 0;
    temp->_parent = parent;
    return temp;
}
/*
 * node     @param: node where v is inserted.
 * v        @param: value to be inserted.
 * pos      @param: position where v is inserted in the node
 * lChild   @param: left child of v
 * rChild   @param: right child of v
 * return:
 *      False if the sum of keys are greater than _upper, else true.
 * Summary:
 *      insert v inito the node.
 */
bool BTree::insertInNode(BTreeNode* node, value v, int pos, BTreeNode* lChild, BTreeNode* rChild) {
    // Move the keys that are greater than v
    for(int i = node->_sum; i >= pos; i--) {
        node->_keys[i+1] = node->_keys[i];
        node->_children[i+1] = node->_children[i];
    }
    node->_keys[pos] = v;               // insert v
    node->_children[pos] = rChild;      // insert right child
    node->_children[pos-1] = lChild;    // insert left child
    node->_sum++;                       // increase sum
    if(node->_sum > _upper) {
        split(node, v, pos, lChild, rChild);
        return insertInNode(node, v, pos, lChild, rChild);
    }
    return true;
}
/*
 * node     @param: node to be split.
 * v        @param: value to be inserted.
 * pos      @param: position where v is inserted in the node
 * lChild   @param: left child of v
 * rChild   @param: right child of v
 * return:
 *      False if the sum of keys are greater than _upper, else true.
 * Summary:
 *      insert v inito the node.
 */
void BTree::split(BTreeNode* &node, value &v, int &pos, BTreeNode* &lChild, BTreeNode* &rChild) {
    //BTreeNode* parent = node->_parent;
    lChild = new BTreeNode;         // create a node for left child
    rChild = new BTreeNode;         // create a node for right child
    unsigned splitPos = ceil((float)m/2);  // position where node is split into two node
    v = node->_keys[splitPos];      // target value to be inserted into parent.

    // assignment for left child
    lChild->_sum = splitPos - 1;
    for(int i = 0; i < splitPos; i++) {
        lChild->_keys[i] = node->_keys[i];
        lChild->_children[i] = node->_children[i];
        lChild->_children[i]->_parent=lChild;
    }
    // assignment for right child
    rChild->_sum = node->_sum - splitPos;
    for(int i = 0; i < rChild->_sum + 1; i++) {
        rChild->_keys[i] = node->_keys[splitPos+i];
        rChild->_children[i] = node->_children[splitPos+i];
        rChild->_children[i]->_parent = rChild;
    }

    // find position where insert
    BTreeNode* parent = node->_parent;
    if(parent) {
        for(int i = 0; i < parent->_sum + 1; i++) {
            if(parent->_children[i] == node) {
                pos = i + 1;
                break;
            }
        }
    } else {   // else the node is root, so it has no parent
        _root = new BTreeNode;
        _root->_sum = 0;
        _root->_parent = NULL;
        pos = 1;
        parent = _root;
    }
    // delete the node which is split
    delete node;
    // and deal with parent
    node = parent;
    // specify parent for two children.
    lChild->_parent = rChild->_parent = node;
}
/*
 * node     @param: node to print
 * Summary
 *      print all keys of the specified node
 */
void BTree::printNode(BTreeNode* node) const {
    // if leaf node, then return.
    if(node->_sum == 0) return;
    // print all keys of this node
    cout<<"Keys : ";
    for(int i = 1; i <= node->_sum; i++) {
        cout<<node->_keys[i]<<", ";
    }
    if(node->_parent) {
        cout<<"\t\t------ parent[0] : "<<node->_parent->_keys[1];
    }
    cout<<endl;
    // print each child node
    for(int i = 0; i <= node->_sum; i++) {
        printNode(node->_children[i]);
    }
}
// print all the tree
void BTree::printTree() const {
    if(_root) printNode(_root);
    else
        cout<<"B- Tree is empty!!!!"<<endl;
}
// delete value v form the tree
bool BTree::deleteValue(value v) {
    if(!_root) return false;            // if empty tree
    SearchRes res = Search(v);
    if(!res._found) return false;       // if v is not found
    deleteInNode(res._ptr, res._pos);
    return true;
}
/*
 * node     @param: target node where v is deleted
 * pos      @param: position where v is delete in the node
 * Summary:
 *      delete value from the node at the specified position.
 */
void BTree::deleteInNode(BTreeNode* node, int pos) {
    // if node is non-lowest node, replace target value with minimum value of minimum node.
    if(!isLowest(node)) {
        BTreeNode* miniNode;
        miniNode = findMinimumNode(node->_children[pos]);
        node->_keys[pos] = miniNode->_keys[1];
        deleteInNode(miniNode, 1);
        return;
    }
    //printNode(_root);
    //return;
    delete node->_children[pos];        // delete value at pos position.

    // move forward items after v at pos position.
    for(int i = pos; i < node->_sum; i++) {
        node->_keys[pos] = node->_keys[pos+1];
        node->_children[pos] = node->_children[pos+1];
    }
    node->_sum--;
    // if _root is lowest node, just remove the value,
    // cause sum of _root keys is allowed to be any value.
    if(node == _root) {
        if(_root->_sum == 0) {
            delete _root->_children[0];
            delete _root;
            _root = NULL;
        }
        return;
    }
    // after deletion, if the sum of keys is legal, then return.
    if(node->_sum >= _lower) return;
    // else the sum is less than _lower.
    // LPos : node as left node, and its position in parent;
    // RPos : node as right node, and its position in parent;
    int LPos, RPos;
    BTreeNode* rBrother = getRBrother(node, LPos);
    // brow value from right brother
    if(rBrother && rBrother->_sum > _lower) {
        borrow(node, rBrother, LPos, RIGHT);
        return;
    }
    BTreeNode* lBrother = getLBrother(node, RPos);
    //borrow value from left brother
    if(lBrother && lBrother->_sum > _lower) {
        borrow(node, lBrother, RPos, LEFT);
        return;
    }
    // combine node with right or left brother
    BTreeNode* parent = node->_parent;
    BTreeNode *L, *R;
    int positionInParent;
    if(rBrother) {
        L = node;
        R = rBrother;
        positionInParent = LPos + 1;    // where value is removed from parent

    } else if(lBrother) {
        L = lBrother;
        R = node;
        positionInParent = RPos;        // where value is removed from parent
    } else {
        assert(0 && "Error occurs when deleting value!");
    }
    combine(L, R, positionInParent);
//    // get value from parent
//    L->_keys[L->_sum+1] = parent->_keys[positionInParent];
//    L->_children[L->_sum+1] = R->_children[0];
//    L->_sum++;
//    // delete value from parent
//    for(int i = positionInParent; i < parent->_sum; i++) {
//        parent->_keys[i] = parent->_keys[i+1];
//        parent->_children[i] = parent->_children[i+1];
//    }
//    parent->_sum--;
//    // combine the right brother
//    for(int i = 1; i <= R->_sum; i++) {
//        L->_keys[node->_sum+i] = R->_keys[i];;
//        L->_children[node->_sum+i] = R->_children[i];
//    }
//    L->_sum += R->_sum;
//    delete R;
    LegalizeNonLowestNode(parent);
}
// find minimum node of the sub tree
BTree::BTreeNode* BTree::findMinimumNode(BTreeNode* node) {
    if(isLowest(node)) {
        return  node;
    } else {
        node = node->_children[0];
        return findMinimumNode(node);
    }
}
// get right brother node, if no right brother ,then return NULL
// and return postion where node in parent's _children by reference
BTree::BTreeNode* BTree::getRBrother(const BTreeNode* node, int& parentPos) {
    parentPos = -1;
    if(node == _root) return NULL;              // root has no brother
    BTreeNode* parent = node->_parent;
    // if node is maximum child of parent, then return NULL
    if(parent->_children[parent->_sum] == node) return NULL;
    int i;
    // find the position of node
    for(i = 0; i < parent->_sum; i++) {
        if(parent->_children[i] == node) break;
    }
    parentPos = i;
    return parent->_children[i+1];
}
// get left brother node, if no left brother ,then return NULL
// and return postion where node in parent's _children  by reference
BTree::BTreeNode* BTree::getLBrother(const BTreeNode* node, int& parentPos) {
    parentPos = -1;
    if(node == _root) return NULL;              // root has no brother
    BTreeNode* parent = node->_parent;
    // if node is minimum child of parent, then return NULL
    if(parent->_children[0] == node) return NULL;
    int i;
    // find the position of node
    for(i = parent->_sum; i > 0; i--) {
        if(parent->_children[i] == node) break;
    }
    parentPos = i;
    return parent->_children[i-1];
}
/* ori          @param: node who borrows value from tar
 * tar          @param: node from who ori borrows value
 * parentPos    @param: pos where ori is located in parent
 * dir          @param: direction where ori borrows value
 * Summary:
 *      ori borrows value from brother
 */
void BTree::borrow(BTreeNode* ori, BTreeNode* tar, int parentPos, DIRECTION dir) {
    BTreeNode* parent = ori->_parent;
    if(dir == RIGHT) {
        // move value from parent.
        ori->_keys[ori->_sum+1] = parent->_keys[parentPos+1];
        // move the minimum child tar as the maximum child of ori
        ori->_children[ori->_sum+1] = tar->_children[0];
        ori->_sum++;
        // move minimum value of tar upon to parent node
        parent->_keys[parentPos+1] = tar->_keys[1];
        // delete borrowed value from tar.
        for(int i = 0; i < tar->_sum; i++) {
            tar->_keys[i] = tar->_keys[i+1];
            tar->_children[i] = tar->_children[i+1];
        }
        tar->_sum--;
        return;

    }
    if(dir == LEFT) {
        // leave space for borrowed value
        for(int i = ori->_sum + 1; i > 0; i--) {
            ori->_keys[i] = ori->_keys[i-1];
            ori->_children[i] = ori->_children[i-1];
        }
        ori->_sum++;
        // move value from parent to ori
        ori->_keys[1] = parent->_keys[parentPos];
        // move the maximum child of tar as the minimum child of ori
        ori->_children[0] = tar->_children[tar->_sum];
        // move the maximum value of tar upon to the parent
        parent->_keys[parentPos] = tar->_keys[tar->_sum];
        tar->_sum--;
        return;
    }
    assert(0 && "Error occurs when borrowing value!");
}
/* lNode        @param: left node who combines its right brother
 * rNode        @param: right node  who combines its left brother
 * parentPos    @param: pos where lNode is pointed by its parent
 * Summary:
 *      combine ori and tar.
 */
void BTree::combine(BTreeNode* lNode, BTreeNode* rNode, int parentPos){
    BTreeNode* parent = lNode->_parent;
    // move key from parent to rightmost in left children array.
    lNode->_keys[lNode->_sum+1] = parent->_keys[parentPos];
    lNode->_children[lNode->_sum+1] = rNode->_children[0];
    lNode->_sum++;
    // move the after keys forwards
    for(int i = parentPos; i < parent->_sum; i++) {
        parent->_keys[i] = parent->_keys[i+1];
        parent->_children[i] = parent->_children[i+1];
    }
    parent->_sum--;
    // move right brother keys and childre into left brother.
    for(int i = 1; i <= rNode->_sum; i++) {
        lNode->_keys[lNode->_sum+i] = rNode->_keys[i];
        lNode->_children[lNode->_sum+i] = rNode->_children[i];
    }
    lNode->_sum += rNode->_sum;
    // delete right brother
    delete rNode;

}
// after value is borrowed by children, if sum is illegal, then do some thing.
void BTree::LegalizeNonLowestNode(BTreeNode* node) {
    // if node is root, it is legal if the sum is less than _lower unless sum equals to zero
    if(node == _root) {
        if(node->_sum == 0) {   // if root has no key, let first child as root.
            _root = node->_children[0];
            _root->_parent = NULL;
            delete node;
        }
        return;
    }
    // if node is legal, just return;
    if(node->_sum >= _lower) return;
    // else the sum is less than _lower.
    // LPos : node as left node, and its position in parent;
    // RPos : node as right node, and its position in parent;
    int LPos, RPos;
    BTreeNode* parent = node->_parent;
    BTreeNode* rBrother = getRBrother(node, LPos);
    // if right brother has redundant keys, then borrow from it.
    if(rBrother && rBrother->_sum > _lower) {
        borrow(node, rBrother, LPos, RIGHT);
        LegalizeNonLowestNode(parent);
        return;
    }
    BTreeNode* lBrother = getLBrother(node, RPos);
    // if left brother has redundant keys, then borrow from it.
    if(lBrother && lBrother->_sum > _lower) {
        borrow(node, lBrother, RPos, LEFT);
        LegalizeNonLowestNode(parent);
        return;
    }
    BTreeNode *L, *R;
    int positionInParent;   // where the key combined into children is removed
    if(rBrother) {
        L = node;
        R = rBrother;
        positionInParent = LPos + 1;
    } else if(lBrother) {
        L = lBrother;
        R = node;
        positionInParent = RPos;
    } else {
        assert(0 && "Error occurs when deleting value!");
    }
    combine(L, R, positionInParent);
    LegalizeNonLowestNode(parent);
}
