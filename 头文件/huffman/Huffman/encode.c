#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 255
//MAX_LEN指的是每个单词haffman编码的长度
#define MAX_LEN     100

struct tnode {
    //左右儿子节点
    struct tnode* left; /*used when in tree*/
    struct tnode*right; /*used when in tree*/
    //父亲节点，用于从叶子节点搜索到根节点
    struct tnode*parent; /*used when in tree*/
    struct tnode* next; /*used when in list*/
    //单词频率
    float freq;
    //判断是否为叶子节点
    int isleaf;
    //字母
    char symbol;
};


/*global variables*/
//存储每个字母的编码
char code[MAX_SYMBOLS][MAX_LEN];
//树的根节点
struct tnode* root = NULL; /*tree of symbols*/
//队列头结点
struct tnode* qhead = NULL; /*list of current symbols*/
struct cnode* chead = NULL; /*list of code*/

/*
    @function   talloc
    @desc       allocates new node
 */
//新建以及初始化节点

struct tnode* talloc(int symbol, float freq) {
    struct tnode* p = (struct tnode*) malloc(sizeof (struct tnode));
    if (p != NULL) {
        p->left = p->right = p->parent = p->next = NULL;
        p->symbol = symbol;
        p->freq = freq;
        p->isleaf = 1;
    }
    return p;
}

/*
    @function display_tnode_list
    @desc     displays the list of tnodes during code construction
 */
//打印队列内容

void pq_display(struct tnode* head) {
    struct tnode* p = NULL;
    printf("list:");
    for (p = head; p != NULL; p = p->next) {
        printf("(%c,%f) ", p->symbol, p->freq);
    }
    printf("\n");
}

/*
    @function pq_insert
    @desc     inserts an element into the priority queue
    NOTE:     makes use of global variable qhead
 */
//插入队列

void pq_insert(struct tnode* p) {
    struct tnode* curr = NULL;
    struct tnode* prev = NULL;
    printf("inserting:%c,%f\n", p->symbol, p->freq);
    if (qhead == NULL) /*qhead is null*/ {
        /*TODO: write code to insert when queue is empty*/
    }
    /*TODO: write code to find correct position to insert*/
    if (curr == qhead) {
        /*TODO: write code to insert before the current start*/
    } else /*insert between prev and next*/ {
        /*TODO: write code to insert in between*/
    }
}

/*
    @function pq_pop
    @desc     removes the first element
    NOTE:     makes use of global variable qhead
 */
//返回队列中频率最小的节点，并删除掉它

struct tnode* pq_pop() {
    //需要查找频率最小的节点
    struct tnode* p = NULL;
    /*TODO: write code to remove front of the queue*/
    printf("popped:%c,%f\n", p->symbol, p->freq);
    return p;
}

/*
        @function build_code
        @desc     generates the string codes given the tree
        NOTE: makes use of the global variable root
 */
//前序遍历这个树，并保存下每个叶子节点的0,1编码

void generate_code(struct tnode* root, int depth) {
    int symbol;
    int len; /*length of code*/
    if (root->isleaf) {
        //root是叶子节点，len是这个叶子节点0,1,编码的长度symbol为这个字母
        symbol = root->symbol;
        len = depth;
        /*start backwards*/
        //把这个字母代表的0,1序列的最后一位赋值为'\0'
        code[symbol][len] = 0;
        //这里需要我们写出这个字母的0,1序列。方法解释一直他的叶子几点root，
        //通过father指针遍历到他的根节点。这个过程中判断他自己是他父亲节点
        //的左儿子还是右儿子，这样就知道这个字母的0,1序列了，保存到code中即可
        /*
                TODO: follow parent pointer to the top
                to generate the code string
         */
        printf("built code:%c,%s\n", symbol, code[symbol]);
    } else {
        generate_code(root->left, depth + 1);
        generate_code(root->right, depth + 1);
    }

}

/*
        @func	dump_code
        @desc	output code file
 */
//把所有的叶子节点的0,1编码保存到code.txt中，即保存这颗树
void dump_code(FILE* fp) {
    int i = 0;
    for (i = 0; i < MAX_SYMBOLS; i++) {
        if (code[i][0]) /*non empty*/
            fprintf(fp, "%c %s\n", i, code[i]);
    }
}

/*
        @func	encode
        @desc	outputs compressed stream
 */
//压缩文件（这里他直接把每个字母用哪个0,1字符串表示了，这样压缩后肯定变大。建议使用我实验说明中的方法才能达到真正意义上的压缩）
void encode(char* str, FILE* fout) {
    while (*str) {
        fprintf(fout, "%s", code[*str]);
        str++;
    }
}

/*
    @function main
 */
int main() {
    /*test pq*/
    struct tnode* p = NULL;
    struct tnode* lc, *rc;
    //这里是他自己给出的词频数据，实际上我们需要自己透过文件流统计一遍所有字母，并计算出每个字母的频率。这里的信息只供测试使用
    float freq[] = {0.01, 0.04, 0.05, 0.11, 0.19, 0.20, 0.4};
    int NCHAR = 7; /*number of characters*/
    int i = 0;
    const char *CODE_FILE = "code.txt";
    const char *OUT_FILE = "encoded.txt";
    FILE* fout = NULL;
    /*zero out code*/
    memset(code, 0, sizeof (code));
//测试队列的正确性
    /*testing queue*/
    pq_insert(talloc('a', 0.1));
    pq_insert(talloc('b', 0.2));
    pq_insert(talloc('c', 0.15));
    /*making sure it pops in the right order*/
    puts("making sure it pops in the right order");
    while ((p = pq_pop())) {
        free(p);
    }
//测试结束
    qhead = NULL;
    /*initialize with freq*/
    //建树
    for (i = 0; i < NCHAR; i++) {
        pq_insert(talloc('a' + i, freq[i]));
    }
    /*build tree*/
    for (i = 0; i < NCHAR - 1; i++) {
        lc = pq_pop();
        rc = pq_pop();
        /*create parent*/
        p = talloc(0, lc->freq + rc->freq);
        /*set parent link*/
        lc->parent = rc->parent = p;
        /*set child link*/
        p->right = rc;
        p->left = lc;
        /*make it non-leaf*/
        p->isleaf = 0;
        /*add the new node to the queue*/
        pq_insert(p);
    }
    /*get root*/
    root = pq_pop();
    /*build code*/
    generate_code(root, 0);
    /*output code*/
    puts("code:");
    fout = fopen(CODE_FILE, "w");
    dump_code(stdout);
    dump_code(fout);
    fclose(fout);
    //压缩样例
    /*encode a sample string*/
    puts("orginal:abba cafe bad");
    fout = fopen(OUT_FILE, "w");
    encode("abba cafe bad", stdout);
    encode("abba cafe bad", fout);
    fclose(fout);
    getchar();
    /*TODO: clear resources*/
    return 0;
}
