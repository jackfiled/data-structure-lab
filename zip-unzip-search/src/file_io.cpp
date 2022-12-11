//
// Created by ricardo on 22-12-11.
//
#include "file_io.h"
#include "logging.h"
#include "cstdio"
#include "cstdlib"
#include "const.h"

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

}

void FileIO::WriteUnzipFile(const std::string &inputFile, const std::string &outputFile)
{

}
