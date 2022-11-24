//
// Created by ricardo on 2022/11/22.
//
#include "tree_in_file.h"
#include "cstdlib"

TreeInFileP GetInFileTrees(HuffmanNodeP root) {
    int nodeNumber = GetHuffmanTreeNotZeroNodeNumber(root);

    auto trees = (TreeInFileP ) malloc(sizeof(TreeInFileT) * (nodeNumber));

    CreateInFileTreeNode(root, trees, 0);

    return trees;
}

int CreateInFileTreeNode(HuffmanNodeP node, TreeInFileT trees[], int pos)
{
    if (node->weight == 0)
    {
        // 不创建权值为0的节点
        // 这里会导致一个问题
        // 部分节点的左右子节点就可能指向数组中不存在的元素
        // 不过由于权值为0的节点
        return pos;
    }
    else
    {
        TreeInFileT& tree = trees[pos];
        tree.data = node->data;

        if (node->lChild != nullptr)
        {
            tree.lIndex = pos + 1;
            pos = CreateInFileTreeNode(node->lChild, trees, pos + 1);
        }
        else
        {
            tree.lIndex = -1;
        }
        if (node->rChild != nullptr)
        {
            tree.rIndex = pos + 1;
            pos = CreateInFileTreeNode(node->rChild, trees, pos + 1);
        }
        else
        {
            tree.rIndex = -1;
        }

        return pos;
    }
}
