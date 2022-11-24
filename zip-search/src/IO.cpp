//
// Created by ricardo on 2022/11/21.
//

#include "IO.h"
#include "const.h"
#include "logging.h"
#include "metadata.h"
#include "tree_in_file.h"

void ReadFileFrequency(const std::string& filename, int frequencyArray[])
{
    FILE *file = fopen(filename.c_str(), "r");

    while (true)
    {
        int temp = fgetc(file);

        // 文件读取完毕
        if (temp == EOF)
        {
            break;
        }

        // 判断文件中是否全部为ASCII字符
        // 避免数组访问出错
        if (temp >= ASCII_LENGTH)
        {
            LoggingWarning("读取文件中存在非ASCII字符，已自动忽略");
            continue;
        }

        frequencyArray[temp]++;
    }

    fclose(file);
}

HuffmanNodeP * GetHuffmanForests(int frequencyArray[])
{
    auto forests = (HuffmanNodeP* )malloc(ASCII_LENGTH * sizeof(HuffmanNodeP));

    for(int i = 0; i < ASCII_LENGTH; i++)
    {
        HuffmanNodeP node = CreateHuffmanNode(frequencyArray[i], (char )i);

        if (node == nullptr)
        {
            LoggingError("Can not create node!");
            return nullptr;
        }

        forests[i] = node;
    }

    return forests;
}

void WriteZipFile(const std::string &inputFileName, const std::string &outputFileName)
{
    FILE *readFile = fopen(inputFileName.c_str(), "r");
    FILE *outputFile = fopen(outputFileName.c_str(), "wb");

    // 建立压缩哈夫曼树
    int frequencyArray[ASCII_LENGTH] = {0};
    ReadFileFrequency(inputFileName, frequencyArray);

    HuffmanNodeP* forests = GetHuffmanForests(frequencyArray);

    HuffmanNodeP root = CreateHuffmanTree(forests);

    // 建立压缩字典
    HuffmanCodeT zipDict[ASCII_LENGTH];
    InitHuffmanCodeArray(zipDict, ASCII_LENGTH);

    GetHuffmanCode(root->lChild, true);
    GetHuffmanCode(root->rChild, false);

    IterHuffmanTree(root, zipDict);

    // 文件元信息
    MetaDataT metaDataT;
    // 先把元信息写入文件占位
    // 由于某些元信息需要在文件压缩完毕之后才能写入文件
    fwrite(&metaDataT, sizeof(MetaDataT), 1, outputFile);

    // 写入解压树
    TreeInFileP inFileTrees = GetInFileTrees(root);
    int treesLength = GetHuffmanTreeNotZeroNodeNumber(root);
    metaDataT.InFileZipLength = treesLength;
    fwrite(inFileTrees, sizeof(TreeInFileT) * treesLength, 1, outputFile);

    // 存储写入压缩文件中内容的缓冲区
    int buffer = 0;
    int bufferPos = 0;

    while (true)
    {
        int temp = fgetc(readFile);

        // 首先处理文件读取完毕的情况
        if (temp == EOF)
        {
            // 文件读取完毕
            // 将最后在缓冲区中的内容写入文件
            buffer = buffer << (32 - bufferPos);
            fwrite(&buffer, sizeof(int), 1, outputFile);

            // 将最后为0部分长度存储在元信息
            metaDataT.LastBufferUsedLength = bufferPos;

            break;
        }

        // 判断文件中是否全部为ASCII字符
        // 避免数组访问出错
        if (temp >= ASCII_LENGTH)
        {
            LoggingWarning("读取文件中存在非ASCII字符，已自动忽略");
            continue;
        }

        HuffmanCodeT code = zipDict[temp];

        for (int i = 0; i < code.pos; i++)
        {
            // 当缓冲区写满了
            if (bufferPos == 32)
            {
                fwrite(&buffer, sizeof(int), 1, outputFile);
                bufferPos = 0;
                buffer = 0;
            }

            buffer = (buffer << 1) + code.code[i];
            bufferPos++;
        }
    }

    // 重新写入元信息
    // 先将文件移动到开头
    fseek(outputFile, 0, SEEK_SET);
    fwrite(&metaDataT, sizeof(MetaDataT), 1, outputFile);

    // 关闭文件
    fclose(readFile);
    fclose(outputFile);

    // 释放空间
    free(forests);
    free(root);
}

void WriteUnzipFile(const std::string& inputFileName, const std::string& outputFileName)
{
    FILE* inputFile = fopen(inputFileName.c_str(), "rb");
    FILE* outputFile = fopen(outputFileName.c_str(), "w");

    // 读取元信息
    MetaDataT metaDataT;
    fread(&metaDataT, sizeof(MetaDataT), 1, inputFile);

    // 读取解压树数组
    TreeInFileT trees[metaDataT.InFileZipLength];
    fread(trees, sizeof(TreeInFileT) * metaDataT.InFileZipLength, 1, inputFile);

    // 读取文件的缓冲区
    int buffer;
    fread(&buffer, sizeof(int), 1, inputFile);
    int bufferPos;
    int nextBuffer;
    TreeInFileT tree = trees[0];

    while (true)
    {
        if (buffer == EOF)
        {
            // 当前正在读取的缓冲区为EOF
            // 退出读取
            break;
        }

        size_t readResult = fread(&nextBuffer, sizeof(int), 1, inputFile);

        if (readResult != 1)
        {
            // 读取到文件末尾
            nextBuffer = EOF;
            bufferPos = metaDataT.LastBufferUsedLength;
        }
        else
        {
            bufferPos = 32;
        }

        while (bufferPos > 0)
        {
            if (tree.data == -1)
            {
                // 非叶子节点
                int value = (buffer >> 31) & 0x1;
                buffer = buffer << 1;
                bufferPos--;

                if (value == 0)
                {
                    tree = trees[tree.lIndex];
                }
                else
                {
                    tree = trees[tree.rIndex];
                }
            }
            else
            {
                // 叶子节点
                fputc(tree.data, outputFile);
                tree = trees[0];
            }
        }

        buffer = nextBuffer;
    }

    // 关闭文件
    fclose(inputFile);
    fclose(outputFile);
}
