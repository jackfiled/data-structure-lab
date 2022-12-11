//
// Created by ricardo on 22-12-11.
//
#include "huffman.h"
#include "const.h"
#include "cstdio"

HuffmanCode::HuffmanCode(int *frequencyArray)
{
    for (int i = 0; i < ASCII_LENGTH; i++)
    {
        HuffmanNode node{};
        node.data = (char )i;
        node.frequency = frequencyArray[i];
        node.id = i;
        node.lIndex = -1;
        node.rIndex = -1;

        nodes->push_back(node);
    }
}

HuffmanCode::~HuffmanCode()
{
    delete nodes;
}

void HuffmanCode::sortForests(std::vector<HuffmanNode> &forests)
{
    std::size_t length = forests.size();
    bool sorted = false;

    for (std::size_t i = 1; i < length and !sorted; i++)
    {
        sorted = true;

        for (std::size_t j = 0; j < length - i; j++)
        {
            if (forests[j].frequency > forests[j + 1].frequency)
            {
                HuffmanNode node = forests[j];
                forests[j] = forests[j + 1];
                forests[j + 1] = node;
                sorted = false;
            }
        }
    }
}

void HuffmanCode::createHuffmanTree()
{
    auto forests = new std::vector<HuffmanNode>(*nodes);
    // 节点数组里的编号
    int pos = (*nodes).rbegin()->id + 1;

    while (forests->size() != 1)
    {
        // 反复执行建树的过程
        sortForests(*forests);

        HuffmanNode node{};
        node.frequency = (*forests)[0].frequency + (*forests)[1].frequency;
        node.data = -1;
        // 权值大的节点为左子结点
        // 权值小的节点为右子结点
        node.rIndex = (*forests)[0].id;
        node.lIndex = (*forests)[1].id;
        node.id = pos;
        pos++;
        nodes->push_back(node);

        // 在森里中删除已经合并的两棵树
        // 新建一颗树
        forests->erase(forests->begin(), forests->begin() + 2);
        forests->push_back(node);
    }

    root = forests->begin()->id;
    delete forests;
}

void HuffmanCode::printHuffmanTree()
{
    if (root == -1)
    {
        return;
    }

    printHuffmanTreeR(root);
}

void HuffmanCode::printHuffmanTreeR(int nodeId)
{
    HuffmanNode node = (*nodes)[nodeId];

    // 不打印权值为0的节点
    if (node.lIndex != -1 and node.frequency != 0)
    {
        printf("%d %d\n", node.id, node.lIndex);
        printHuffmanTreeR(node.lIndex);
    }

    if (node.rIndex != -1 and node.frequency != 0)
    {
        printf("%d %d\n", node.id, node.rIndex);
        printHuffmanTreeR(node.rIndex);
    }
}

std::array<std::vector<char>, 128> * HuffmanCode::getHuffmanCode()
{
    if (root == -1)
    {
        return nullptr;
    }

    auto dictionary = new std::array<std::vector<char>, ASCII_LENGTH>();

    std::vector<char> code;

    getHuffmanCodeR(*dictionary, root, code);

    return dictionary;
}

void HuffmanCode::getHuffmanCodeR(std::array<std::vector<char>, ASCII_LENGTH> &dictionary, int nodeId,
                                  std::vector<char> &code)
{
    HuffmanNode node = (*nodes)[nodeId];

    if (node.data != -1)
    {
        for (auto iterator = code.begin(); iterator < code.end(); iterator++)
        {
            dictionary[node.data].push_back(*iterator);
        }
    }

    if (node.lIndex != -1)
    {
        // 遍历左子树
        code.push_back(0);
        getHuffmanCodeR(dictionary, node.lIndex, code);
        code.pop_back();
    }

    if (node.rIndex != -1)
    {
        // 遍历右子树
        code.push_back(1);
        getHuffmanCodeR(dictionary, node.rIndex, code);
        code.pop_back();
    }
}

void HuffmanCode::printHuffmanCode(const std::array<std::vector<char>, ASCII_LENGTH>& dictionary)
{
    for (int i = 0; i < ASCII_LENGTH; i++)
    {
        auto code = dictionary[i];

        printf("%d: ", i);
        for (auto iter = code.begin(); iter < code.end(); iter++)
        {
            putc(*iter + 48, stdout);
        }
        putc('\n', stdout);
    }
}
