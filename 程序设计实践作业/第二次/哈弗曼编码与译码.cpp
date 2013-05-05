#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>/*包含CHAR_BIT宏常量，进行按位存储时使用*/


#define CODE_SIZE 255            /*共有255个字符*/
#define ZIP_HEAD_FLAG 0xaaaaaaaa /* 文件头,写压缩文件时用 */

/*对多个无符号量进行别名命名,方便引用*/
typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;

/*定义宏常量。用于申请内存*/
#define UINT_SIZE sizeof(UINT)
#define UCHAR_SIZE sizeof(UCHAR)
#define USHORT_SIZE sizeof(USHORT)

/*哈弗曼树节点*/
typedef struct treenode
{
    UINT  freq; /* 频度 */
    UCHAR data;
    struct treenode *leftChild;
    struct treenode *rightChild;
} HuffmanTreeNode;

/*用于编码*/
typedef struct datacode
{
    USHORT len;
    UCHAR  *pCode;
} DataCode;

/*将编码转化为数据*/
typedef struct zhuanhua
{
    USHORT len;
    UCHAR *pCode;
    UCHAR data;
} Code2Data;


/*这两个函数编译报错，嵌套使用需先声明*/
UCHAR ConvertToCodeData(const UCHAR codeStr[CHAR_BIT]);
void ConvertToCodeStr(UCHAR codeData, UCHAR codeStr[CHAR_BIT]);


/*子函数*/
void GetDataFreq(FILE *fp, UINT freqArr[CODE_SIZE])
{
    UCHAR buffer;

    fseek(fp, 0L, SEEK_SET); /* 将文件指针重新定位到起始位置 */
    memset(freqArr, 0, UINT_SIZE * CODE_SIZE);
    while(!feof(fp))
    {
        fread(&buffer, UCHAR_SIZE, 1, fp);
        freqArr[buffer]++;
    }
}

/*交换传入两个指针所指向的内存，定义void为了可将任何指针存入，但Linux不行。*/
void Swapper(void **vpnt1, void **vpnt2)/*定义指针，并将待交换的地址存入。这么用居然在windows下可以，Linux下报错。*/
{
    void *tempPnt = *vpnt1;
    *vpnt1 = *vpnt2;
    *vpnt2 = tempPnt;
}

void BuildHuffmanTree(HuffmanTreeNode **pTreeHead, const UINT freqArr[CODE_SIZE])
{
    HuffmanTreeNode **dataFreqArr;
    HuffmanTreeNode *tempInsertTreeNode;
    UINT freqLen = CODE_SIZE;
    int i;

    dataFreqArr = (HuffmanTreeNode **)malloc(sizeof(HuffmanTreeNode*) * freqLen);
    for(i = 0; i < CODE_SIZE; i++)
    {
        dataFreqArr[i] = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        dataFreqArr[i]->data = (UCHAR)i;
        dataFreqArr[i]->freq = freqArr[i];
        dataFreqArr[i]->leftChild = NULL;
        dataFreqArr[i]->rightChild = NULL;
    }

    while(freqLen != 1)
    {
        /*实现方法：每次遍历找到最小的两个结构体，将其移至末尾，相连接。*/
        /* 最后的小于最后第二个 */
        if(dataFreqArr[freqLen-1]->freq > dataFreqArr[freqLen-2]->freq)
            Swapper(dataFreqArr + freqLen-1, dataFreqArr + freqLen-2);
        for(i = freqLen-2-1; i >= 0; i--)
        {
            if(dataFreqArr[freqLen-1]->freq > dataFreqArr[i]->freq)
            {
                Swapper(dataFreqArr + freqLen-2, dataFreqArr + i);
                Swapper(dataFreqArr + freqLen-1, dataFreqArr + freqLen-2);
            }
            else if(dataFreqArr[freqLen-2]->freq > dataFreqArr[i]->freq)
            {
                Swapper(dataFreqArr + freqLen-2, dataFreqArr + i);
            }
        }
        /* 合并最后两个 */
        tempInsertTreeNode = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        tempInsertTreeNode->freq = dataFreqArr[freqLen-1]->freq + dataFreqArr[freqLen-2]->freq;
        tempInsertTreeNode->leftChild = dataFreqArr[freqLen-1];
        tempInsertTreeNode->rightChild = dataFreqArr[freqLen-2];
        dataFreqArr[freqLen-2] = tempInsertTreeNode;
        freqLen--;
    }

    *pTreeHead = dataFreqArr[0];
    free(dataFreqArr); /* 只是存放节点用的 离开之前应释放 */
}

int ZipCode2Data(const void *op1, const void *op2)
{
    UINT minLen = ((DataCode*)op1)->len < ((DataCode*)op2)->len ? ((DataCode*)op1)->len : ((DataCode*)op2)->len;
    UINT i;

    for(i = 0; i < minLen; ++i)
    {
        if(((DataCode*)op1)->pCode[i] != ((DataCode*)op2)->pCode[i])
            return ((DataCode*)op1)->pCode[i] - ((DataCode*)op2)->pCode[i];
    }
    if(((DataCode*)op1)->len == ((DataCode*)op2)->len)
        return 0;
    if(((DataCode*)op1)->len < ((DataCode*)op2)->len)
        return -((DataCode*)op2)->pCode[i];
    return ((DataCode*)op1)->pCode[i];
}

void RebuildHuffmanTreeOrder(HuffmanTreeNode **pTreeHead, UINT start, UINT end,UINT depth, const Code2Data code2DataArr[CODE_SIZE])
{
    UINT mid, i;
    HuffmanTreeNode *insertChild = NULL;
    /*判断当前开始与结束，深度的正确性，不正确则退出*/
    assert(start < end);
    assert(depth < CODE_SIZE);

    /* 根据当前层是0还是1 把数组分成两部分 */
    mid = end;
    for(i = start; i < end; ++i)
    {
        assert(code2DataArr[i].len > depth);
        if(code2DataArr[i].pCode[depth] != 0)
        {
            mid = i;
            break;
        }
    }

    if(*pTreeHead == NULL)
    {
        *pTreeHead = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        //assert(*pTreeHead);
        (*pTreeHead)->leftChild = NULL;
        (*pTreeHead)->rightChild = NULL;
    }

    /* 当前层是0的部分 */
    if(mid-1 == start)
    {
        insertChild = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        insertChild->leftChild = NULL;
        insertChild->rightChild = NULL;
        insertChild->data = code2DataArr[mid - 1].data;
        (*pTreeHead)->leftChild = insertChild;
    }
    else
        RebuildHuffmanTreeOrder(&(*pTreeHead)->leftChild, start, mid, depth+1, code2DataArr);

    /* 当前层是1的部分 */
    if(mid == end-1)
    {
        insertChild = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode));
        insertChild->leftChild = NULL;
        insertChild->rightChild = NULL;
        insertChild->data = code2DataArr[mid].data;
        (*pTreeHead)->rightChild = insertChild;
    }
    else
        RebuildHuffmanTreeOrder(&(*pTreeHead)->rightChild, mid, end, depth+1, code2DataArr);
}

void RebuildHuffmanTree(HuffmanTreeNode **pTreeHead, const DataCode dataCodeArr[CODE_SIZE])
{
    Code2Data code2DataArr[CODE_SIZE];
    UINT i;

    for(i = 0; i < CODE_SIZE; ++i)
    {
        code2DataArr[i].data = i;
        code2DataArr[i].len = dataCodeArr[i].len;
        code2DataArr[i].pCode = dataCodeArr[i].pCode;
    }
    qsort(code2DataArr, CODE_SIZE, sizeof(Code2Data), ZipCode2Data);
    RebuildHuffmanTreeOrder(pTreeHead, 0, CODE_SIZE, 0, code2DataArr);
    /* 不对code2DataArr中的指针进行释放 code2DataArr还要再用 */
}

void FreeTree(HuffmanTreeNode **pTreeHead)
{
    if(*pTreeHead != NULL)
    {
        if((*pTreeHead)->leftChild != NULL)
            FreeTree(&((*pTreeHead)->leftChild));
        if((*pTreeHead)->rightChild != NULL)
            FreeTree(&((*pTreeHead)->rightChild));
        free(*pTreeHead);
        *pTreeHead = NULL;
    }
}

void GetHuffmanCode(const HuffmanTreeNode *pTreeHead, UCHAR code[CODE_SIZE],USHORT codeLen, DataCode dataCodeArr[CODE_SIZE])
{
    if(pTreeHead != NULL)
    {
        if(pTreeHead->leftChild != NULL)/*非叶子节点*/
        {
            code[codeLen] = 0;
            GetHuffmanCode(pTreeHead->leftChild, code, codeLen+1, dataCodeArr);
            assert(pTreeHead->rightChild != NULL); /* 不可能出现一边有孩子节点 一边又没有的情况 */
            code[codeLen] = 1;
            GetHuffmanCode(pTreeHead->rightChild, code, codeLen+1, dataCodeArr);
        }
        else     /* 叶子节点 */
        {
            dataCodeArr[pTreeHead->data].pCode = (UCHAR *)malloc(UCHAR_SIZE * codeLen);
            memcpy(dataCodeArr[pTreeHead->data].pCode, code, UCHAR_SIZE * codeLen);
            dataCodeArr[pTreeHead->data].len  = codeLen;
        }
    }
}

void GetFileHuffmanCode(FILE *fp, DataCode dataCodeArr[CODE_SIZE])
{
    HuffmanTreeNode *pTreeHead = NULL;
    UINT freqArr[CODE_SIZE];
    UCHAR code[CODE_SIZE];

    GetDataFreq(fp, freqArr);
    BuildHuffmanTree(&pTreeHead, freqArr);
    memset(dataCodeArr, 0, sizeof(DataCode) * CODE_SIZE);
    memset(code, 0, UCHAR_SIZE * CODE_SIZE);
    GetHuffmanCode(pTreeHead, code, 0, dataCodeArr);
    FreeTree(&pTreeHead);
}


/* 从压缩文件头中读取编码 */
int ReadHead(FILE *fp, DataCode dataCodeArr[CODE_SIZE])
{
    UINT zipHeadFlag;
    USHORT codeLen, i, j;
    UCHAR codeBuffer, data;
    UCHAR codeStr[CHAR_BIT];

    fseek(fp, 0L, SEEK_SET);
    fread(&zipHeadFlag, UINT_SIZE, 1, fp);
    if(zipHeadFlag != ZIP_HEAD_FLAG)
        return 1;

    memset(dataCodeArr, 0, sizeof(DataCode) * CODE_SIZE);
    for(i = 0; i < CODE_SIZE; ++i)
    {
        fread(&data, UCHAR_SIZE, 1, fp);
        assert(data == i);
        fread(&codeLen, USHORT_SIZE, 1, fp);
        dataCodeArr[data].len  = codeLen;
        /* 把编码还原成字符串 */
        assert(dataCodeArr[data].pCode == NULL);
        dataCodeArr[data].pCode = (UCHAR *)malloc(UCHAR_SIZE * codeLen);
        for(j = 0; j < codeLen - codeLen % CHAR_BIT; j += CHAR_BIT)
        {
            fread(&codeBuffer, UCHAR_SIZE, 1, fp);
            ConvertToCodeStr(codeBuffer, codeStr);
            memcpy(dataCodeArr[data].pCode + j, codeStr, UCHAR_SIZE * CHAR_BIT);
        }
        if(codeLen % CHAR_BIT != 0)
        {
            fread(&codeBuffer, UCHAR_SIZE, 1, fp);
            ConvertToCodeStr(codeBuffer, codeStr);
            memcpy(dataCodeArr[data].pCode + j, codeStr, UCHAR_SIZE * (codeLen % CHAR_BIT));
        }
    }
    return 0;
}
/*进行按位压缩与解压的代码是在网上找的，自己没想出来*/
void WriteHead(FILE *fp, const DataCode dataCodeArr[CODE_SIZE])
{
    USHORT i, j;
    UCHAR codeBuffer, codeStr[CHAR_BIT];
    UINT zipHeadFlag = ZIP_HEAD_FLAG;

    fseek(fp, 0L, SEEK_SET);
    fwrite(&zipHeadFlag, UINT_SIZE, 1, fp);
    for(i = 0; i < CODE_SIZE; i++)
    {
        fwrite(&i, UCHAR_SIZE, 1, fp);
        fwrite(&dataCodeArr[i].len, USHORT_SIZE, 1, fp);
        /* 进行位运算，将字符串改成二进制码存入文件头，便于解码调用*/
        for(j = 0; j < dataCodeArr[i].len - dataCodeArr[i].len % CHAR_BIT; j += CHAR_BIT)
        {
            memcpy(codeStr, dataCodeArr[i].pCode + j, UCHAR_SIZE * CHAR_BIT);
            codeBuffer = ConvertToCodeData(codeStr);
            fwrite(&codeBuffer, UCHAR_SIZE, 1, fp);
        }
        if(dataCodeArr[i].len % CHAR_BIT != 0)
        {
            memcpy(codeStr, dataCodeArr[i].pCode + j, UCHAR_SIZE * (dataCodeArr[i].len % CHAR_BIT));
            codeBuffer = ConvertToCodeData(codeStr);
            fwrite(&codeBuffer, UCHAR_SIZE, 1, fp);
        }
    }
}

UCHAR ConvertToCodeData(const UCHAR codeStr[CHAR_BIT])
{
    UCHAR retCode = 0;
    int i;

    for(i = CHAR_BIT-1; i >= 0; --i)
    {
        retCode <<= 1;
        if(codeStr[i] != 0)
            retCode |= 1;
    }
    return retCode;
}

void ConvertToCodeStr(UCHAR codeData, UCHAR codeStr[CHAR_BIT])
{
    UINT i;

    for(i = 0; i < CHAR_BIT; ++i)
    {
        codeStr[i] = ((codeData & 1) != 0);
        codeData >>= 1;
    }
}

/*压缩函数，可实现将字符的哈弗曼编码存入压缩后的文件头，内容压缩后继续存进文档。*/
int ZipFile(const char *sourceFileName, const char *targetFileName)
{
    FILE *sourceFp = NULL, *targetFp = NULL;
    DataCode dataCodeArr[CODE_SIZE];
    USHORT writeCodeLen, i;
    UCHAR writeCode[CHAR_BIT], readData, writeData, lastBtyeLen;
    fpos_t lastBtyePos;

    if((sourceFp = fopen(sourceFileName, "rb")) == NULL)
    {
        printf("打开%s文件错误！ ", sourceFileName);
        return 1;
    }
    if((targetFp = fopen(targetFileName, "w+b")) == NULL)
    {
        printf("打开%s文件错误！ ", targetFileName);
        fclose(sourceFp);
        return 1;
    }
    GetFileHuffmanCode(sourceFp, dataCodeArr);
    WriteHead(targetFp, dataCodeArr);
    lastBtyeLen = 0;
    fgetpos(targetFp, &lastBtyePos); /* 记录位子 后面得到长度信息后 再在这里写 */
    fwrite(&lastBtyeLen, UCHAR_SIZE, 1, targetFp);

    /* 对源数据进行编码转换 并写入目标文件中 */
    memset(writeCode, 0, CHAR_BIT);
    writeCodeLen = 0;
    fseek(sourceFp, 0L, SEEK_SET);
    while(!feof(sourceFp))
    {
        /*读入字节，遍历找到编码转存。*/
        fread(&readData, UCHAR_SIZE, 1, sourceFp);
        for(i = 0; i < dataCodeArr[readData].len; i++)
        {
            writeCode[writeCodeLen++] = dataCodeArr[readData].pCode[i];
            /*每攒够一个字节长度的编码即转存*/
            if(writeCodeLen >= CHAR_BIT)
            {
                writeData = ConvertToCodeData(writeCode);
                fwrite(&writeData, UCHAR_SIZE, 1, targetFp);
                memset(writeCode, 0, UCHAR_SIZE * CHAR_BIT);
                writeCodeLen = 0;
            }
        }
    }
    /* 把剩余的不足一字节写入文件 */
    if(writeCodeLen != 0)
    {
        writeData = ConvertToCodeData(writeCode);
        fwrite(&writeData, UCHAR_SIZE, 1, targetFp);
    }
    lastBtyeLen = writeCodeLen;
    fsetpos(targetFp, &lastBtyePos);
    fwrite(&lastBtyeLen, UCHAR_SIZE, 1, targetFp);

    /* 清理 */
    for(i = 0; i < CODE_SIZE; ++i)
    {
        if(dataCodeArr[i].pCode != NULL)
        {
            free(dataCodeArr[i].pCode);
            dataCodeArr[i].pCode = NULL;
        }
    }
    fclose(sourceFp);
    fclose(targetFp);
    return 0;
}

int UnzipFile(const char *sourceFileName, const char *targetFileName)
{
    FILE *sourceFp = NULL, *targetFp = NULL;
    DataCode dataCodeArr[CODE_SIZE];
    HuffmanTreeNode *pTreeHead = NULL, *pTreeNode = NULL;
    UCHAR codeStream[CODE_SIZE], codeStr[CHAR_BIT], readData, writeData, lastBtyeLen;
    int codeStreamLen, i;

    if((sourceFp = fopen(sourceFileName, "rb")) == NULL)
    {
        printf("Error！ ");
        return 1;
    }
    if((targetFp = fopen(targetFileName, "w+b")) == NULL)
    {
        printf("Error ！ ");
        fclose(sourceFp);
        return 1;
    }

    ReadHead(sourceFp, dataCodeArr);
    fread(&lastBtyeLen,UCHAR_SIZE, 1, sourceFp);
    RebuildHuffmanTree(&pTreeHead, dataCodeArr);
    codeStreamLen = 0;
    while(!feof(sourceFp) || codeStreamLen > 0)
    {
        while(!feof(sourceFp) && codeStreamLen < CODE_SIZE - CHAR_BIT)
        {
            fread(&readData, UCHAR_SIZE, 1, sourceFp);
            ConvertToCodeStr(readData, codeStr);
            memcpy(codeStream+codeStreamLen, codeStr, CHAR_BIT);
            codeStreamLen += CHAR_BIT;
            if(feof(sourceFp))
                codeStreamLen -= lastBtyeLen + CHAR_BIT;
        }

        /* 通过编码查找原数据 */
        pTreeNode = pTreeHead;
        for(i = 0; i < codeStreamLen; i++)
        {
            if(codeStream[i] == 0)
            {
                pTreeNode = pTreeNode->leftChild;
                if(pTreeNode->leftChild == NULL)
                    break;
            }
            else
            {
                pTreeNode = pTreeNode->rightChild;
                if(pTreeNode->leftChild == NULL)
                    break;
            }
        }

        if(pTreeNode->rightChild != NULL) return 1;/* 对当前节点进行判断，若其左右孩子不为空，则为非节点，有错 */
        writeData = pTreeNode->data;
        fwrite(&writeData, UCHAR_SIZE, 1, targetFp);

        /* 读取之后要删除 */
        codeStreamLen -= i + 1;
        memcpy(codeStream, codeStream+i+1, codeStreamLen);
    }

    /* 清理 */
    FreeTree(&pTreeHead);
    for(i = 0; i < CODE_SIZE; ++i)
    {
        if(dataCodeArr[i].pCode != NULL)
        {
            free(dataCodeArr[i].pCode);
            dataCodeArr[i].pCode = NULL;
        }
    }
    fclose(sourceFp);
    fclose(targetFp);
    return 0;
}

int main()
{
    char *fileName = "book.txt";
    char *zipFileName = "encoded.txt";
    char *unzipFileName = "decoded.txt";
    char mode;
SELECT:
    puts("Please enter 1 or 2 to select mode, 1 for code,2 for decode,3 to exit now~>_<:");
    mode=getchar();
    if (mode == '1')
    {

        ZipFile(fileName, zipFileName);
        printf("Ziped file was saved.\n");
        getchar();
        goto SELECT;
    }
    else if (mode =='2')
    {
        UnzipFile(zipFileName, unzipFileName);
        getchar();/*读走缓存区的回车*/
    }
    else if (mode=='3')
    {
        exit(0);
    }
    return 0;
}


