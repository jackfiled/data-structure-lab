//
// Created by ricardo on 22-12-11.
//

#ifndef ZIP_UNZIP_SEARCH_FILE_IO_H
#define ZIP_UNZIP_SEARCH_FILE_IO_H
#include "string"

/**
 * 文件元信息
 */
struct MetaData
{
    /**
     * 哈夫曼树节点数组长度
     */
    int HuffmanNodeLength;
    /**
     * 哈夫曼树根节点长度
     */
    int HuffmanRoot;
    /**
     * 文件中最后一个缓冲区被使用的位数
     */
    int LastBufferUsedLength;
};

class FileIO
{
public:
    /**
     * 统计文件的字符的出现频率
     * @param fileName 文件名称
     * @return 字符频率数组 需要delete
     */
    static int* ReadCharFrequency(const std::string& fileName);

    /**
     * 写入压缩文件
     * @param inputFile 被压缩文件名称
     * @param outputFile 输出压缩文件名称
     */
    static void WriteZipFile(const std::string& inputFile, const std::string& outputFile);

    /**
     * 写入解压缩文件
     * @param inputFile 压缩文件名称
     * @param outputFile 解压文件名称
     */
    static void WriteUnzipFile(const std::string& inputFile, const std::string& outputFile);

    /**
     * 计算文件的压缩率
     * @param inputFileName
     * @param outputFileName
     * @return
     */
    static double CalculateZipRate(const std::string& inputFileName, const std::string& outputFileName);
};

class BinaryBuffer
{
public:
    explicit BinaryBuffer(std::string& inputFileName);

    ~BinaryBuffer();

    char read();

    int position = 0;

private:
    FILE* file = nullptr;

    int buffer;
    int bufferPos;
    bool readFinishedFlag;


};

#endif //ZIP_UNZIP_SEARCH_FILE_IO_H
