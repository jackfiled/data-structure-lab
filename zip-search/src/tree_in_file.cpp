//
// Created by ricardo on 2022/11/22.
//
#include "tree_in_file.h"
#include "cstdlib"
#include "cstdio"


TreeInFileP GetInFileTrees(HuffmanNodeP root) {
    int nodeNumber = GetHuffmanTreeNotZeroNodeNumber(root);

    TreeInFileP trees = (TreeInFileP ) malloc(sizeof(TreeInFileT) * (nodeNumber + 99));

    CreateInFileTreeNode(root, trees, 0);

    for (int i = 0; i < nodeNumber + 99; i++)
    {
        printf("%d:%d-l:%d-r:%d\n",i , trees[i].data, trees[i].lIndex, trees[i].rIndex);
    }

    return trees;
}

int CreateInFileTreeNode(HuffmanNodeP node, TreeInFileT trees[], int pos)
{
    if (node == nullptr || node->weight == 0)
    {
        return pos;
    }

    trees[pos].data = node->data;

}
