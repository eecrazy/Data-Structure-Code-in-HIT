#include <iostream>
#include "BTree.h"
using namespace std;

int main()
{
    BTree bt;
    //int array[] = {11,5,15,1,3,19,9,21,13,7,17, 10};
    //int array[] = {11,5,15,1,3,19,9,21,13,7,17,2};
    int array[] = {11,5,15,1,3,19,9,21,13,7,17};
    int length = sizeof(array)/sizeof(int);
    for(int i = 0; i < length; i++) {
        bt.insertValue(array[i]);
        //break;
    }
    bt.printTree();
    //bt.deleteValue(19);
    //bt.deleteValue(3);
    bt.deleteValue(11);
    bt.deleteValue(21);
    bt.deleteValue(19);
    bt.deleteValue(5);
    bt.deleteValue(13);
    bt.deleteValue(7);
    bt.deleteValue(9);
    bt.deleteValue(1);
    bt.deleteValue(3);
    bt.deleteValue(15);
    bt.deleteValue(17);
    cout<<"-------------------------------"<<endl;
    //bt.deleteValue(13);
    bt.printTree();
    return 0;
}
