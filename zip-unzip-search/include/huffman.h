//
// Created by ricardo on 22-12-11.
//

#ifndef ZIP_UNZIP_SEARCH_HUFFMAN_H
#define ZIP_UNZIP_SEARCH_HUFFMAN_H
#include "vector"
#include "array"
#include "const.h"

/**
 * 哈夫曼树中的节点结构体
 */
struct HuffmanNode
{
    /**
     * 节点的编号
     */
    int id;
    /**
     * 节点表示的字符
     * 如果不是叶子节点
     * 值为-1
     */
    char data;
    /**
     * 字符在文件中出现的频率
     * 也就是哈夫曼树中节点的权值
     */
    int frequency;
    /**
     * 左子结点在节点数组中的索引
     */
    int lIndex;
    /**
     * 右子结点在节点中的索引
     */
    int rIndex;
};

class HuffmanCode
{
public:
    /**
     * 树中节点列表
     */
    std::vector<HuffmanNode>* nodes = new std::vector<HuffmanNode>();

    /**
     * 哈夫曼树根节点索引
     */
    int root = -1;

    explicit HuffmanCode(int * frequencyArray);

    ~HuffmanCode();

    /**
     * 创建哈夫曼树
     */
    void createHuffmanTree();

    /**
     * 打印哈夫曼树
     */
    void printHuffmanTree();

    /**
     * 得到哈夫曼编码
     * @return 哈夫曼编码字典
     */
    std::array<std::vector<char>, ASCII_LENGTH> * getHuffmanCode();

    /**
     * 打印哈夫曼编码字典
     * @param dictionary 字典
     */
    static void printHuffmanCode(const std::array<std::vector<char>, ASCII_LENGTH>& dictionary);

private:
    /**
     * 对森林列表按权值排序
     * @param forests
     */
    static void sortForests(std::vector<HuffmanNode>& forests);

    void printHuffmanTreeR(int nodeId);

    void getHuffmanCodeR(std::array<std::vector<char>, ASCII_LENGTH> &dictionary, int nodeId, std::vector<char> &code);

};
#endif //ZIP_UNZIP_SEARCH_HUFFMAN_H
