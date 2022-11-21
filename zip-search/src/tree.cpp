//
// Created by ricardo on 2022/11/21.
//
#include "tree.h"
#include "cstdlib"
#include "const.h"
#include "cstdio"

HuffmanNodeP CreateHuffmanNode(unsigned int weight, char data)
{
    HuffmanNodeP node = (HuffmanNodeP ) malloc(sizeof(HuffmanNodeT));

    if (node == nullptr)
    {
        return nullptr;
    }

    node->data = data;
    node->weight = weight;
    node->parent = nullptr;
    node->lChild = nullptr;
    node->rChild = nullptr;

    return node;
}

void DestroyHuffmanTree(HuffmanNodeP root)
{
    if (root->lChild != nullptr)
    {
        DestroyHuffmanTree(root->lChild);
    }
    if (root->rChild != nullptr)
    {
        DestroyHuffmanTree(root->rChild);
    }
    free(root);
}

HuffmanNodeP CreateHuffmanTree(HuffmanNodeP forests[])
{
    HuffmanNodeP root;
    for(int i = 0; i < ASCII_LENGTH - 1; i++)
    {
        // 对森林进行排序
        SortHuffmanForest(forests, i, ASCII_LENGTH - 1);

        root = CreateHuffmanNode(forests[i]->weight + forests[i + 1]->weight, -1);
        root->lChild = forests[i];
        root->rChild = forests[i + 1];

        forests[i + 1] = root;
    }

    return root;
}

void SortHuffmanForest(HuffmanNodeP forests[], int left, int right) {
    if (left < right)
    {
        int i = left, j = right;
        HuffmanNodeP x = forests[left];

        while (i < j)
        {
            while (i < j and forests[j]->weight >= x->weight)
            {
                j--;
            }
            if (i < j)
            {
                forests[i] = forests[j];
                i++;
            }

            while (i < j && forests[i]->weight <= x->weight)
            {
                i++;
            }
            if (i < j)
            {
                forests[j] = forests[i];
                j--;
            }
        }

        forests[i] = x;
        SortHuffmanForest(forests, left, i - 1);
        SortHuffmanForest(forests, i + 1, right);
    }
}

void GetZipDict(HuffmanNodeP root, char *zipDict, int buffer)
{
    if (root == nullptr || root->weight == 0)
    {
        // root为空指针或者权值为0
        // 停止递归
        return;
    }

    if (root->data != -1)
    {
        // 节点为叶子节点
        zipDict[root->data] = buffer;
    }

    GetZipDict(root->lChild, zipDict, (buffer << 1) + 0);
    GetZipDict(root->rChild, zipDict, (buffer << 1) + 1);
}

void IterHuffmanTree(HuffmanNodeP root)
{
    if (root == nullptr || root->weight == 0)
    {
        return;
    }

    printf("%d-%d\n", root->data, root->weight);
    IterHuffmanTree(root->lChild);
    IterHuffmanTree(root->rChild);
}

int GetHuffmanTreeNotZeroNodeNumber(HuffmanNodeP root)
{
    if (root == nullptr || root->weight == 0)
    {
        return 0;
    }

    return GetHuffmanTreeNotZeroNodeNumber(root->lChild)
    + GetHuffmanTreeNotZeroNodeNumber(root->rChild)
    + 1;
}

