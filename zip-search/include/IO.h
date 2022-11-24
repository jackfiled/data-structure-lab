//
// Created by ricardo on 2022/11/21.
//

#ifndef ZIP_SEARCH_IO_H
#define ZIP_SEARCH_IO_H
#include "cstdio"
#include "string"
#include "tree.h"

void ReadFileFrequency(const std::string& filename, int frequencyArray[]);

void WriteZipFile(const std::string &inputFileName, const std::string &outputFileName);

void WriteUnzipFile(const std::string& inputFileName, const std::string& outputFileName);

HuffmanNodeP * GetHuffmanForests(int frequencyArray[]);

#endif //ZIP_SEARCH_IO_H
