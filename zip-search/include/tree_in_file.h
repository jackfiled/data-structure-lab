//
// Created by ricardo on 2022/11/22.
//

#ifndef ZIP_SEARCH_TREE_IN_FILE_H
#define ZIP_SEARCH_TREE_IN_FILE_H
#include "tree.h"

/**
 * 存储在压缩文件中的树节点
 */
struct TreeInFile
{
    // 存储的字符
    char data;
    // 左右子节点在数组中的索引
    // 采用char类型节省空间
    char lIndex;
    char rIndex;
};

typedef struct TreeInFile TreeInFileT;
typedef struct TreeInFile* TreeInFileP;

/**
 * 获得存储在文件中的哈夫曼列表
 * 删除了权值为0的节点和不必要的数据
 * @param root 原有哈夫曼树的根节点
 * @return 新节点列表
 */
TreeInFileP GetInFileTrees(HuffmanNodeP root);

int CreateInFileTreeNode(HuffmanNodeP node, TreeInFileT trees[], int pos);

#endif //ZIP_SEARCH_TREE_IN_FILE_H