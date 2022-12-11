#include "file_io.h"
#include "huffman.h"

int main()
{
    int* frequencyArray = FileIO::ReadCharFrequency("README");

    auto huffmanCode = new HuffmanCode(frequencyArray);
    // 创建哈夫曼树
    huffmanCode->createHuffmanTree();
    auto dictionary = huffmanCode->getHuffmanCode();

    for (int i = 0; i < ASCII_LENGTH; i++)
    {
        auto code = (*dictionary)[i];

        printf("%d: ", i);
        for (auto iter = code.begin(); iter < code.end(); iter++)
        {
            putc(*iter + 48, stdout);
        }
        putc('\n', stdout);
    }

    delete huffmanCode;
    delete dictionary;
    delete frequencyArray;

    return 0;
}