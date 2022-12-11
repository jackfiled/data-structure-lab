//
// Created by ricardo on 22-12-11.
//

#ifndef ZIP_UNZIP_SEARCH_FILE_IO_H
#define ZIP_UNZIP_SEARCH_FILE_IO_H
#include "string"


class FileIO
{
public:
    static int* ReadCharFrequency(const std::string& fileName);

    static void WriteZipFile(const std::string& inputFile, const std::string& outputFile);

    static void WriteUnzipFile(const std::string& inputFile, const std::string& outputFile);
};

#endif //ZIP_UNZIP_SEARCH_FILE_IO_H
