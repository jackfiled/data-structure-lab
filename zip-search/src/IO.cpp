//
// Created by ricardo on 2022/11/21.
//

#include "IO.h"
#include "const.h"
#include "logging.h"

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
    HuffmanNodeP* forests = (HuffmanNodeP* )malloc(ASCII_LENGTH * sizeof(HuffmanNodeP));

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

void WriteZipFile(const std::string &filename, const std::string &outputName, char ZipDict[])
{
    FILE *readFile = fopen(filename.c_str(), "r");
    FILE *outputFile = fopen(outputName.c_str(), "wb");

    // 存储写入压缩文件中的内容
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

            break;
        }

        // 判断文件中是否全部为ASCII字符
        // 避免数组访问出错
        if (temp >= ASCII_LENGTH)
        {
            LoggingWarning("读取文件中存在非ASCII字符，已自动忽略");
            continue;
        }

        char output = ZipDict[temp];
        char bitsArray[7];

        // 获得数据的位级表示
        for (int i = 0; i < 7; i++)
        {
            char pattern = 0x1 << i;
            bitsArray[i] = (output & pattern) >> i;
        }

        // 抛弃数据前面的0
        int i = 6;
        while (bitsArray[i] == 0)
        {
            i--;
        }

        while (i >= 0)
        {
            // 当缓冲区写满了
            if (bufferPos == 32)
            {
                fwrite(&buffer, sizeof(int), 1, outputFile);
                bufferPos = 0;
                buffer = 0;
            }

            buffer = (buffer << 1) + bitsArray[i];
            bufferPos++;
            i--;
        }
    }

    fclose(readFile);
    fclose(outputFile);
}
