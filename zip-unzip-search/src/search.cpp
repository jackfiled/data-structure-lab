//
// Created by ricardo on 22-12-16.
//
#include "search.h"
#include "cstdio"
#include "cstring"
#include "logging.h"
#include "file_io.h"
#include "huffman.h"

BMSearch::BMSearch(std::vector<char> &sample)
{
    int length = (int )sample.size();

    badCharArray = new int[2];
    goodSuffixArray = new int[length];
    this->sample = new std::vector<char>(sample);

    generateBrokenCharArray(sample);
    generateGoodSuffixArray(sample);
}


BMSearch::~BMSearch()
{
    delete badCharArray;
    delete goodSuffixArray;
}

void BMSearch::generateBrokenCharArray(std::vector<char> &s)
{
    int length = (int )s.size();

    // 输入字符串为01串
    for (int i = 0; i < 2; i++)
    {
        badCharArray[i] = length;
    }

    for (int i = 0; i < length - 1; i++)
    {
        badCharArray[s[i]] = length - i - 1;
    }
}

void BMSearch::generateGoodSuffixArray(std::vector<char> &s)
{
    int length = (int )s.size();

    int suffix[length];

    suffix[length - 1] = length;

    for (int i = length - 2; i >= 0; i--)
    {
        int pos = i;
        while (pos >= 0 and s[pos] == s[length - 1 - i + pos])
        {
            pos--;
        }
        suffix[i] = i - pos;
    }

    for (int i = 0; i < length; i++)
    {
        goodSuffixArray[i] = length;
    }

    int j = 0;
    for (int i = length - 1; i >= 0 ; i--)
    {
        if (suffix[i] == i + 1)
        {
            for (; j < length - 1 - i; j++)
            {
                if (goodSuffixArray[j] == length)
                {
                    goodSuffixArray[j] = length - 1 - i;
                }
            }
        }
    }

    for (int i = 0; i < length - 1; i++)
    {
        goodSuffixArray[length - 1 - suffix[i]] = length - 1 - i;
    }
}

void BMSearch::matchFile(std::string &fileName)
{
    auto buffer = new BinaryBuffer(fileName);

    std::vector<char> inputArray;

    while (true)
    {
        if (inputArray.size() != sample->size())
        {
            // bm算法要求后缀匹配
            // 所以开始之间需要读取一个长度和模式字符串长度相同的缓冲区
            char temp = buffer->read();
            if (temp == -1)
            {
                break;
            }
            else
            {
                inputArray.push_back(temp);
                continue;
            }
        }
        else
        {
            // 正式开始匹配
            int pos = (int )sample->size() - 1;
            for(; pos >= 0 and (*sample)[pos] == inputArray[pos]; pos--);
            if (pos < 0)
            {
                // 完成一次匹配
                Logging::LoggingInfo("Found at " + std::to_string(buffer->position));
                auto begin = inputArray.begin();
                auto end = begin + goodSuffixArray[0];
                inputArray.erase(begin, end);
            }
            else
            {
                // 匹配失败
                auto begin = inputArray.begin();
                int teleport = max(goodSuffixArray[pos],
                                   badCharArray[inputArray[pos]] - (int )sample->size() + 1 + pos);
                auto end = begin + teleport;
                inputArray.erase(begin, end);
            }
        }
    }
    delete buffer;
}

int BMSearch::max(int a, int b)
{
    return a >= b ? a : b;
}

void SearchInFile(char* fileName, char* sample)
{
    FILE* file = fopen(fileName, "rb");

    if (file == nullptr)
    {
        Logging::LoggingError(std::string(fileName) + " is not a valid file name.");
        exit(0);
    }

    // 读取元信息
    MetaData metaData{};
    fread(&metaData, sizeof(MetaData), 1, file);

    // 读取哈夫曼节点数组
    auto nodes = new HuffmanNode[metaData.HuffmanNodeLength];
    fread(nodes, sizeof(HuffmanNode), metaData.HuffmanNodeLength, file);
    fclose(file);
    // 从哈夫曼节点数组创建哈夫曼编码
    auto huffmanCode = new HuffmanCode(nodes, metaData.HuffmanNodeLength);
    huffmanCode->root = metaData.HuffmanRoot;
    auto dictionary = huffmanCode->getHuffmanCode();

    // 获得模板字符串的哈夫曼编码
    std::vector<char> sampleCode;
    int sampleLength = (int )strlen(sample);

    Logging::LoggingInfo("The binary representation of " + std::string(sample) + " is ");
    for (int i = 0; i < sampleLength; i++)
    {
        auto code = (*dictionary)[sample[i]];
        for (auto iter = code.begin(); iter < code.end(); iter++)
        {
            sampleCode.push_back(*iter);
            putc(*iter + 48, stdout);
        }
    }
    putc('\n', stdout);

    // 开始查找
    auto bm = new BMSearch(sampleCode);

    std::string str = std::string(fileName);
    bm->matchFile(str);

    delete bm;
    delete[] nodes;
    delete huffmanCode;
    delete dictionary;
}
