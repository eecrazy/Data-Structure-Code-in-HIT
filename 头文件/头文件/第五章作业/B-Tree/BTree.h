#ifndef BTREE_H
#define BTREE_H
#define m 3
typedef int value;
class BTree
{
public:
    struct BTreeNode {
        unsigned    _sum;           // sum of keys
        BTreeNode*  _parent;        // parent of the node
        value       _keys[m+1];     // key array
        BTreeNode*  _children[m+1]; // children pointer
    };
    struct SearchRes {
        BTreeNode* _ptr;            // found node
        int        _pos;            // position where target value should be
        bool       _found;          // whether found
    };
    enum DIRECTION {
        NO_DIRECTION,               // no direction
        RIGHT,                      // right
        LEFT                       // left
    };
    bool insertValue(value v);      // insert value into the tree
    BTree();                        // constructor
    virtual ~BTree();               // destructor
    SearchRes Search(value v);      // search value
    void printTree() const;         // print the tree
    bool deleteValue(value v);      // delete value from the tree
protected:
    BTreeNode*  _root;      // root of BTree
    unsigned    _upper;     // upper limit for key numver
    unsigned    _lower;     // lower limit for key number
    BTreeNode* getLeaf(BTreeNode* parent);  // create a leaf node.
    bool isLowest(BTreeNode* node);         // if node is in lowest layer
    SearchRes SearchInNode(BTreeNode* node, value v);       // search value in the node
    bool insertInNode(BTreeNode*, value, int, BTreeNode*, BTreeNode*);  // insert value in the node
    void split(BTreeNode* &, value&, int&, BTreeNode*&, BTreeNode*&);         // split the node
    void printNode(BTreeNode*) const;               // print the keys of a node
    void deleteInNode(BTreeNode*, int);        // delete value from a node
    // get a value to replace the value to be deleted in a non-lowest node
    BTreeNode* findMinimumNode(BTreeNode* node);         // find the minimum node of the sub tree
    BTreeNode* getRBrother(const BTreeNode*, int& parentPos);               // get right brother
    BTreeNode* getLBrother(const BTreeNode*, int& parentPos);               // get left brother.
    void borrow(BTreeNode*, BTreeNode*, int parentPos, DIRECTION);          // borrow from brother
    void combine(BTreeNode*, BTreeNode*, int parentPos);                    // combine with brother
    void LegalizeNonLowestNode(BTreeNode*);                                 // make non-lowest legal
    void destroy(BTreeNode*);                                               // destory a tree.
};

#endif // BTREE_H
