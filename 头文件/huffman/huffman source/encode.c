#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 255
#define MAX_LEN     100

struct tnode
{


    struct tnode* left;
    struct tnode* right;
    struct tnode* parent;
    struct tnode* next;
    float freq;
    int isleaf;
    char symbol;
};


/*global variables*/
//存储0-255每个ASCII码的huffman编码
char code[MAX_SYMBOLS][MAX_LEN];
struct tnode* root = NULL; /*tree of symbols*/
// queue head pointer, code head pointer
struct tnode* qhead = NULL; /*list of current symbols*/
struct tnode* chead = NULL; /*list of code*/

//新建以及初始化节点 talloc: tree node allocation
struct tnode* talloc(int symbol, float freq)
{
    struct tnode* p = (struct tnode*) malloc(sizeof (struct tnode));
    if (p != NULL)
    {
        p->left = p->right = p->parent = p->next = NULL;
        p->symbol = symbol;
        p->freq = freq;
        p->isleaf = 1;		//default is leaf node
    }
    return p;
}

//priority queue display
void pq_display(struct tnode* head)
{
    struct tnode* p = NULL;
    printf("list:");
    for (p = head; p != NULL; p = p->next)
    {
        printf("(%c,%f) ", p->symbol, p->freq);
    }
    printf("\n");
}

//priority queue intert: *p node to be inserted, *curr: working pointer
void pq_insert(struct tnode* p)
{
    struct tnode* curr = NULL;
    struct tnode* prev = NULL;
    printf("inserting:%c,%f\n", p->symbol, p->freq);

    /*TODO: write code to find correct position to insert*/
    curr = qhead;	//	pq head pointer traverse from head of pq, current pointer 初始化指向链表头

    //遍历记录插入前后节点的位置
    while(curr)  	//	traverse the pq, not end of pq 不是链表尾部
    {
        if(p -> freq <= curr -> freq)
        {
            break;
        }
        prev = curr;					//记录插入点前后结点的位置
        curr = curr -> next;			//后面位置
    }

    //插入操作：链表为空
    //insert when pq is empty
    if (qhead == NULL) /*qhead is null*/
    {
        /*TODO: write code to insert when queue is empty*/
        // curr = (struct tnode*) malloc(sizeof (struct tnode));	// memory leak ! assert(curr != NULL);
        curr = p;				//curr指针指向待插入结点p
        curr -> next = NULL;		//当前结点尾指针值为空NULL
        qhead = curr;			//全局头指针指向第一个节点
    }

    //insert at head头部插入
    else if((curr == qhead) && qhead != NULL)
    {
        /*TODO: write code to insert before the current start*/
        p -> next = qhead;
        qhead = p;

    }

    else 	/*insert between prev and next 中间插入 */
    {
        /*TODO: write code to insert in between*/
        prev -> next = p;
        p -> next = curr;
    }
}

//返回队列中频率最小的节点就可以
struct tnode* pq_pop()
{
    //需要查找频率最小的节点
    //working pointer p
    struct tnode* p = NULL;
    /*TODO: write code to remove front of the queue*/
    p = qhead;
    qhead = qhead -> next;	//modify global pq head pointer
    printf("popped:%c,%f\n", p->symbol, p->freq);
    //free(p);		//注意：坚决不能释放p执行的pq头结点，头结点作为函数返回值使用
    return p;
}

//	前序遍历这个树，保存下每个叶节点的0,1编码，注意：1、哈弗曼树的高度==编码长度；
//2、递归函数实现
void generate_code(struct tnode* root, int depth)
{
    int symbol;
    int len; /*length of code*/

    if (root->isleaf)  		//只为叶节点构建编码,从叶子节点向上一直遍历到根节点
    {

        //root是叶子节点，len 是叶节点的哈弗曼编码长度, symbol为这个字母

        symbol = root->symbol;
        len = depth;

        /* start backwards! */
        //将存储该字母哈弗曼编码数组code的最后一位赋为'\0'
        code[symbol][len] = '\0';

        /*
                TODO: follow parent pointer to the top
                to generate the code string
         */

        //通过parent指针从叶子节点一直遍历到根节点，根据自己是
        //的左儿子还是右儿子来确定字母的0,1序列，并"倒序"保存到code中

        while(root->parent)  	   //只有根节点其->parent指针才为NULL，是否到根节点
        {
            if(root == root->parent->left)  	//当前结点为左二子，编码为0
            {
                code[symbol][len-1] = '0';
                len --;
            }
            else
            {
                code[symbol][len-1] = '1';		//右儿子，编码为1
                len --;
            }
            root = root -> parent;				//从叶子节点向上遍历到其父节点
        }
        printf("built code:%c,%s\n", symbol, code[symbol]);
    }
    else  	//non leaf node
    {
        generate_code(root->left, depth + 1);	//recursive function 递归函数从depth=0开始逐层判断是否为叶节点 depth + 1
        generate_code(root->right, depth + 1);	//右儿子
    }

}

//把所有叶子节点(编码非零为有效叶子节点)的哈弗曼编码保存到code.txt中，即保存这棵树, FILE* can be used as stdout as well
void dump_code(FILE* fp)
{
    int i = 0;
    for (i = 0; i < MAX_SYMBOLS; i++)
    {
        if (code[i][0])								/* non empty */
            fprintf(fp, "%c %s\n", i, code[i]);		//Print formatted data to a stream.
    }
}

//压缩文件,直接把每个字母用哈弗曼编码的0,1字符串序列表示，这样压缩后肯定变大。建议使用实验说明中的方法达到真正压缩的目的(可选)
void encode(char* str, FILE* fout)  		//*str: ascii code 字符指针，保存相应字符的ASCII码
{

    while (*str)
    {
        fprintf(fout, "%s", code[*str]);	// 用ASCII码作索引，查找haffman编码数组code[*str] (数组随机访问快速的特点)，code数组保存了0-255个字符的huffman编码
        str++;
    }
}

/*
    @function main
 */

int main()
{
    /*test pq*/
    struct tnode* p = NULL;
    struct tnode* lc, *rc;		//pointer of left chile, right child
    //单词频度，需要自己通过文件流统计待压缩文件中所有字母的频度，频度信息只供测试使用
    float freq[] = {0.01, 0.04, 0.05, 0.11, 0.19, 0.20, 0.4};
    int NCHAR = 7; /*number of characters*/
    int i = 0;
    const char *CODE_FILE = "code.txt";		// haffman code output file	保存	huffman编码
    const char *OUT_FILE = "encoded.txt";	//output encoded code

    FILE* fout = NULL;
    /*zero out code*/
    memset(code, 0, sizeof (code));		//MSDN	<memory.h>/<string.h>
    qhead = NULL;
    for (i = 0; i < NCHAR; i++)
    {
        pq_insert(talloc('a' + i, freq[i]));
    }
    /*build tree*/
    for (i = 0; i < NCHAR - 1; i++)
    {
        lc = pq_pop();		//left child is always less than right child
        rc = pq_pop();		//right child	左二子永远小于右儿子，因此第一个弹出的为lc, 第二个为rc
        /*create parent*/
        p = talloc(0, lc->freq + rc->freq);		//parent tnode
        /*set parent link*/
        lc->parent = rc->parent = p;			//父节点
        /*set child link*/
        p->right = rc;
        p->left = lc;
        /*make it non-leaf*/
        p->isleaf = 0;							//一定是非叶节点 0
        /*add the new node to the queue*/
        pq_insert(p);		// insert at the proper position 按权frequency 大小插入队列中正确位置
    }

    /*get root */
    root = pq_pop();			//建树后，pq中只有一个节点根root
    /* build code for root node, 根节点root深度为 0 depth */
    generate_code(root, 0);		/* 根据频率生成huffman编码表 */
    /*output code*/
    puts("code:");
    fout = fopen(CODE_FILE, "w");		//char* CODE_FILE, "w" write only
    dump_code(stdout);
    dump_code(fout);
    fclose(fout);


    //压缩样例
    puts("orginal:dgdfsgsdfgdsgfgdfgdgdesgdbgdfgdfsgxgxgdfgdfbg");
    fout = fopen(OUT_FILE, "w");
    encode("dgdfsgsdfgdsgfgdfgdgdesgdbgdfgdfsgxgxgdfgdfbg", stdout);
    encode("dgdfsgsdfgdsgfgdfgdgdesgdbgdfgdfsgxgxgdfgdfbg", fout);
    fclose(fout);
    getchar();
    /*TODO: clear resources*/
    return 0;
}

