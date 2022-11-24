//
// Created by ricardo on 2022/11/21.
//

#ifndef ZIP_SEARCH_TREE_H
#define ZIP_SEARCH_TREE_H
#include "const.h"

struct HuffmanCode
{
    /**
     * 具体的编码的内容
     */
    char code[CODE_LENGTH];
    /**
     * 已经使用的长度
     */
    char pos;
};

typedef struct HuffmanCode HuffmanCodeT;
typedef struct HuffmanCode* HuffmanCodeP;

/**
 * 初始化一个哈夫曼编码数组
 * 内存中可能不是所有的数都为0
 * @param codeArray 数组指针
 * @param length 数组长度
 */
void InitHuffmanCodeArray(HuffmanCodeP codeArray, int length);


struct HuffmanNode
{
    /**
     * 节点的权重
     */
    unsigned int weight;
    /**
     * 节点所表示的字符
     */
    char data;
    /**
     * 父节点指针
     */
    struct HuffmanNode* parent;
    /**
     * 左子节点指针
     */
    struct HuffmanNode* lChild;
    /**
     * 右子节点指针
     */
    struct HuffmanNode* rChild;

    /**
     * 哈夫曼编码
     */
    HuffmanCodeT code;
};

typedef struct HuffmanNode HuffmanNodeT;
typedef struct HuffmanNode* HuffmanNodeP;

/**
 * 创建一个哈夫曼树的节点
 * 考虑到不同节点的父子节点情况不同
 * 函数中先设置为空指针
 * @param weight 节点的权重
 * @return 创建的节点指针
 */
HuffmanNodeP CreateHuffmanNode(unsigned int weight, char data);

/**
 * 释放一颗哈夫曼树占据的内存空间
 * @param root 哈夫曼树的根节点指针
 */
void DestroyHuffmanTree(HuffmanNodeP root);

/**
 * 通过传入的哈夫曼节点数组创建哈夫曼树
 * 节点数组就是森林
 * @param forests 节点数组
 * @return 创建的哈夫曼树根节点
 */
HuffmanNodeP CreateHuffmanTree(HuffmanNodeP forests[]);

/**
 * 将哈夫曼数组进行排序
 * 排序之后的数组创建哈夫曼树更快
 * 按照从小到大的顺序
 * 快速排序实现
 * @param forests 数组指针
 */
void SortHuffmanForest(HuffmanNodeP forests[], int left, int right);

/**
 * 遍历树得到每个节点的哈夫曼编码
 * 递归实现
 * @param node 节点
 * @param isLeft 是否为左子树
 */
void GetHuffmanCode(HuffmanNodeP node, bool isLeft);

/**
 * 遍历哈夫曼树 获得压缩字典
 * @param root 哈夫曼树节点
 * @param zipDict 压缩字典
 */
void IterHuffmanTree(HuffmanNodeP root, HuffmanCodeT zipDict[]);

/**
 * 获得哈夫曼树中权值非0节点的数量
 * @param root 哈夫曼树的根节点
 * @return 非0节点的数量
 */
int GetHuffmanTreeNotZeroNodeNumber(HuffmanNodeP root);

#endif //ZIP_SEARCH_TREE_H
