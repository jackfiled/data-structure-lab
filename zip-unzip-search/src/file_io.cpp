//
// Created by ricardo on 22-12-11.
//
#include "file_io.h"
#include "logging.h"
#include "cstdio"
#include "cstdlib"
#include "const.h"
#include "huffman.h"
#include "unistd.h"
#include "sys/stat.h"

int *FileIO::ReadCharFrequency(const std::string &fileName)
{
    FILE *file = fopen(fileName.c_str(), "r");

    if (file == nullptr)
    {
        // 文件打开失败
        Logging::LoggingInfo(fileName + "is not a valid filename");
        exit(0);
    }

    int* frequencyArray = new int[ASCII_LENGTH];

    for (int i = 0; i < ASCII_LENGTH; i++)
    {
        // 将所有频率初始化为0
        frequencyArray[i] = 0;
    }

    while (true)
    {
        int temp = fgetc(file);

        if (temp == EOF)
        {
            // 文件结束
            break;
        }

        if (temp >= ASCII_LENGTH || temp < 0)
        {
            // 读取到非法字符
            Logging::LoggingWarning(
                    "Read illegal char " + std::to_string(temp) + " in file. Ignore it");
        }

        frequencyArray[temp]++;
    }

    fclose(file);
    return frequencyArray;
}

void FileIO::WriteZipFile(const std::string &inputFile, const std::string &outputFile)
{
    int* frequencyArray = FileIO::ReadCharFrequency(inputFile);

    auto huffmanCode = new HuffmanCode(frequencyArray);
    // 创建哈夫曼树
    huffmanCode->createHuffmanTree();
    auto dictionary = huffmanCode->getHuffmanCode();

    FILE* input = fopen(inputFile.c_str(), "r");
    FILE* output = fopen(outputFile.c_str(), "wb");

    // 判断文件打开ia是否成功
    if (input == nullptr)
    {
        Logging::LoggingError(inputFile + " is not an valid file name.");
        exit(0);
    }
    if (output == nullptr)
    {
        Logging::LoggingError(outputFile + " is not an valid file name.");
        exit(0);
    }

    // 首先写入文件的元信息
    // 虽然目前元信息中部分信息还没有拿到
    // 但是先把文件中的空间占据了再说
    MetaData metaDataT{};
    fwrite(&metaDataT, sizeof(MetaData), 1, output);

    // 写入哈夫曼数组
    fwrite(huffmanCode->nodes->data(), sizeof(HuffmanNode), huffmanCode->nodes->size(), output);

    // 写入文件时的缓冲区
    int buffer = 0;
    int bufferPos = 0;

    while (true)
    {
        int temp = fgetc(input);

        // 读取到文件末尾
        if (temp == EOF)
        {

            buffer = buffer << (32 - bufferPos);
            fwrite(&buffer, sizeof(int), 1, output);

            metaDataT.LastBufferUsedLength = bufferPos;

            break;
        }

        if (temp >= ASCII_LENGTH || temp < 0)
        {
            // 读取到非法字符
            Logging::LoggingWarning(
                    "Read illegal char " + std::to_string(temp) + " in file. Ignore it");
        }

        auto code = (*dictionary)[temp];

        for (auto iter = code.begin(); iter < code.end(); iter++)
        {
            // 缓冲区已经满了
            if (bufferPos == 32)
            {
                fwrite(&buffer, sizeof(int), 1, output);
                bufferPos = 0;
                buffer = 0;
            }

            buffer = (buffer << 1) + *iter;
            bufferPos++;
        }
    }

    metaDataT.HuffmanRoot = huffmanCode->root;
    metaDataT.HuffmanNodeLength = (int )huffmanCode->nodes->size();
    // 写入元信息
    fseek(output, 0, SEEK_SET);
    fwrite(&metaDataT, sizeof(MetaData), 1, output);

    delete frequencyArray;
    delete huffmanCode;
    delete dictionary;
}

void FileIO::WriteUnzipFile(const std::string &inputFile, const std::string &outputFile)
{
    FILE* input = fopen(inputFile.c_str(), "rb");
    FILE* output = fopen(outputFile.c_str(), "w");

    // 检查文件是否正常打开
    if (input == nullptr)
    {
        Logging::LoggingError(inputFile + " is not a valid file name.");
        exit(0);
    }
    if (output == nullptr)
    {
        Logging::LoggingError(outputFile + " is not a valid file name.");
        exit(0);
    }

    // 读取元信息
    MetaData metaData{};
    fread(&metaData, sizeof(MetaData), 1, input);

    // 读取哈夫曼节点数组
    auto nodes = new HuffmanNode[metaData.HuffmanNodeLength];
    fread(nodes, sizeof(HuffmanNode), metaData.HuffmanNodeLength, input);

    // 读取文件的缓冲区
    int buffer;
    fread(&buffer, sizeof(int), 1, input);
    int bufferPos;
    int nextBuffer;

    HuffmanNode node = nodes[metaData.HuffmanRoot];

    while (true)
    {
        if (buffer == EOF)
        {
            // 读取结束
            break;
        }

        // 这里为了处理最后一个缓冲区的问题
        // 设置了双缓冲
        size_t readResult = fread(&nextBuffer, sizeof(int), 1, input);

        if (readResult != 1)
        {
            // 读取到文件末尾
            nextBuffer = EOF;
            bufferPos = metaData.LastBufferUsedLength;
        }
        else
        {
            bufferPos = 32;
        }

        while (bufferPos > 0)
        {
            if (node.data == -1)
            {
                // 非叶子节点
                int value = (buffer >> 31) & 1;
                buffer = buffer << 1;
                bufferPos--;

                if (value == 0)
                {
                    node = nodes[node.lIndex];
                }
                else
                {
                    node = nodes[node.rIndex];
                }
            }
            else
            {
                // 叶子节点
                fputc(node.data, output);
                node = nodes[metaData.HuffmanRoot];
            }
        }

        buffer = nextBuffer;
    }

    delete[] nodes;
    fclose(input);
    fclose(output);
}

double FileIO::CalculateZipRate(const std::string &inputFileName, const std::string &outputFileName)
{
    struct stat originFileStat{};
    struct stat zipFileStat{};

    stat(inputFileName.c_str(), &originFileStat);
    stat(outputFileName.c_str(), &zipFileStat);

    auto originFileSize = (double )originFileStat.st_size;
    auto zipFileSize = (double )zipFileStat.st_size;

    return zipFileSize / originFileSize;
}

BinaryBuffer::BinaryBuffer(std::string &inputFileName)
{
    file = fopen(inputFileName.c_str(), "rb");

    if (file == nullptr)
    {
        // 读取文件失败
        Logging::LoggingError(inputFileName + " is not a valid file name.");
        exit(0);
    }

    buffer = 0;
    bufferPos = 0;
    readFinishedFlag = false;

    // 读取文件开头的元信息和哈夫曼数组
    MetaData metaData{};
    fread(&metaData, sizeof(MetaData), 1, file);
    position = position + (int )sizeof(MetaData) * 8;

    // 读取哈夫曼节点数组
    HuffmanNode nodes[metaData.HuffmanNodeLength];
    fread(nodes, sizeof(HuffmanNode), metaData.HuffmanNodeLength, file);
    position = position + (int )sizeof(HuffmanNode) * metaData.HuffmanNodeLength * 8;
}

BinaryBuffer::~BinaryBuffer()
{
    fclose(file);
    file = nullptr;
}

char BinaryBuffer::read()
{
    if (readFinishedFlag)
    {
        return -1;
    }

    if (bufferPos == 0)
    {
        // 当前缓冲区读取结束
        int result = (int )fread(&buffer, sizeof(int), 1, file);

        if (result == 0)
        {
            readFinishedFlag = true;
            // 文件读取结束
            return -1;
        }

        bufferPos = 32;
    }

    int result = (buffer >> 31) & 1;
    buffer = buffer << 1;
    bufferPos--;
    position++;
    return (char )result;
}
