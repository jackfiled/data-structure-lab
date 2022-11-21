//
// Created by ricardo on 2022/11/21.
//

#include "IO.h"
#include "const.h"
#include "tree_in_file.h"

int main()
{
    std::string inputFile = "README.txt";
    int frequencyArray[ASCII_LENGTH] = {0};
    ReadFileFrequency(inputFile, frequencyArray);

    HuffmanNodeP* forests = GetHuffmanForests(frequencyArray);

    HuffmanNodeP root = CreateHuffmanTree(forests);
    char zipDict[ASCII_LENGTH] = {0};
    GetZipDict(root, zipDict, 0);

    //TreeInFileP trees = GetInFileTrees(root);
    IterHuffmanTree(root);

    //WriteZipFile("README.txt", "zip.bin", zipDict);

    // 释放占用的空间
    free(forests);
    //free(trees);
    DestroyHuffmanTree(root);

    return 0;
}