#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 255
#define MAX_LEN     10

/**
*1.还原树时，注意已经有儿子的节点不需要再新建儿子节点
*2.在encode时，输出一个字符后必须将curr指针重新指向根节点
*/

struct tnode {
    struct tnode* left; /*used when in tree*/
    struct tnode* right; /*used when in tree*/
    int isleaf;
    char symbol;
};

struct code {
    int symbol;
    char strcode[MAX_LEN];
};

/*global variables*/
struct tnode* root = NULL; /*tree of symbols*/

/*
    @function   talloc
    @desc       allocates new node
 */

struct tnode* talloc() {
    struct tnode* p = (struct tnode*) malloc(sizeof (struct tnode));
    if (p != NULL) {
        p->left = p->right = NULL;
        p->symbol = 0;
        p->isleaf = 0;
    }
    return p;
}

/*
    @function build_tree
    @desc     builds the symbol tree given the list of symbols and code.h
        NOTE: alters the global variable root that has already been allocated in main
 */

//根据code.txt的内容还原huffman树

void build_tree(FILE* fp) {
    char symbol;
    char strcode[MAX_LEN];
    int items_read;
    int i, len;
    struct tnode* curr = NULL;

    while (!feof(fp)) {			//读入每1行，并为每个symbol建树
        items_read = fscanf(fp, "%c %s\n", &symbol, strcode);	//格式: symbol strcode
        if (items_read != 2) break;								//判断成功
        curr = root;				//from root	初始化为根节点(从根节点开始重建)
        len = strlen(strcode);		//hufman code length = depth 编码长度等于树的深度
        for (i = 0; i < len; i++) {	//rebuild the tree according to strcode[len]根据strcode中保存的huffman编码的每一个字符重建树depth
            /*TODO: create the tree as you go*/
			
            if(strcode[i] == '0') {				//strcode[i] == 0 : left 左儿子
                if(curr -> left == NULL)
                    curr -> left = talloc();
                curr = curr -> left;
            }
            else {
                if(curr -> right == NULL)		//strcode[i] != 0 :  right 右儿子
                    curr -> right = talloc();
                curr = curr -> right;
            }
        }

        /*assign code for the leaf node */
        curr->isleaf = 1;						
        curr->symbol = symbol;
        printf("inserted symbol:%c\n", symbol);
    }
}

/*
        function decode
 */
//解压缩
void decode(FILE* fin, FILE* fout) {
    char c;
    struct tnode* curr = root;			//start from root
    while ((c = getc(fin)) != EOF) {
        /*TODO:
                traverse the tree
                print the symbols only if you encounter a leaf node
		*/
        // 当遍历到叶节点，说明一个huffman编码解码结束；恢复current指针指向root，继续下一个huffman码解码
		if(c == '0') {
            curr = curr -> left;
            if(curr->isleaf) {			//when leaf traverse go on from the root
                fprintf(fout, "%c", curr -> symbol);
                curr = root;			//恢复使得current指针指向根节点root
            }
        }else {
            curr = curr -> right;
            if(curr->isleaf) {			//when leaf travrse goon from the root
                fprintf(fout, "%c", curr -> symbol);
                curr = root;			//current points to the root again
            }
        }
    }
}

/*
        @function freetree
        @desc	  cleans up resources for tree
 */

//删除这棵树 recursive function递归函数
void freetree(struct tnode* root) {
    if (root == NULL)
        return;					
								//递归到base case，释放左、右、父节点
    freetree(root->right);		//释放右儿子节点
    freetree(root->left);		//释放左儿子节点
    free(root);					//释放父节点
}

int main() {
    const char* IN_FILE = "encoded.txt";
    const char* CODE_FILE = "code.txt";
    const char* OUT_FILE = "decoded.txt";
    FILE* fout;
    FILE* fin;
    /*allocate root*/
    root = talloc();
    fin = fopen(CODE_FILE, "r");
    /*build tree*/
    build_tree(fin);
    fclose(fin);

    /*decode*/
    fin = fopen(IN_FILE, "r");
    fout = fopen(OUT_FILE, "w");
    decode(fin, fout);
    fclose(fin);
    fclose(fout);
    /*cleanup*/
    freetree(root);
    return 0;
}

