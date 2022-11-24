//
// Created by ricardo on 2022/11/21.
//
#include "tree.h"
#include "cstdlib"
#include "const.h"

void InitHuffmanCodeArray(HuffmanCodeP codeArray, int length)
{
    for (int i = 0; i < length; i++)
    {
        HuffmanCodeT code = codeArray[i];
        code.pos = 0;
        for (int j = 0; j < CODE_LENGTH; j++)
        {
            code.code[j] = 0;
        }
    }
}

HuffmanNodeP CreateHuffmanNode(unsigned int weight, char data)
{
    auto node = (HuffmanNodeP ) malloc(sizeof(HuffmanNodeT));

    if (node == nullptr)
    {
        return nullptr;
    }

    node->data = data;
    node->weight = weight;
    node->parent = nullptr;
    node->lChild = nullptr;
    node->rChild = nullptr;

    node->code.pos = 0;

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
        root->lChild->parent = root;
        root->rChild->parent = root;

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

void GetHuffmanCode(HuffmanNodeP node, bool isLeft)
{
    // 当递归到头时
    // 停止遍历
    if (node == nullptr)
    {
        return;
    }

    // 首先复制父节点的编码
    for(int i = 0; i < node->parent->code.pos; i++)
    {
        node->code.code[i] = node->parent->code.code[i];
    }
    // 然后复制父节点目前编码的位置
    node->code.pos = node->parent->code.pos;

    if(isLeft)
    {
        node->code.code[node->code.pos] = 0;
    }
    else
    {
        node->code.code[node->code.pos] = 1;
    }
    node->code.pos++;

    GetHuffmanCode(node->lChild, true);
    GetHuffmanCode(node->rChild, false);
}

void IterHuffmanTree(HuffmanNodeP root, HuffmanCodeT zipDict[])
{
    if (root == nullptr || root->weight == 0)
    {
        return;
    }

    if(root->data != -1)
    {
        zipDict[root->data].pos = root->code.pos;
        for (int i = 0; i < root->code.pos; i++)
        {
            zipDict[root->data].code[i] = root->code.code[i];
        }
    }

    IterHuffmanTree(root->lChild, zipDict);
    IterHuffmanTree(root->rChild, zipDict);
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

