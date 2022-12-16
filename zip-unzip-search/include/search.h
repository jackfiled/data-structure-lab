//
// Created by ricardo on 22-12-16.
//

#ifndef ZIP_UNZIP_SEARCH_SEARCH_H
#define ZIP_UNZIP_SEARCH_SEARCH_H
#include "vector"
#include "array"
#include "string"

/**
 * BM算法搜索实现类
 */
class BMSearch
{
public:
    explicit BMSearch(std::vector<char>& sample);

    ~BMSearch();

    /**
     * 匹配二进制文件
     * @param fileName 指向需要进行匹配的二进制文件 需要读取元信息和哈夫曼数组
     */
    void matchFile(std::string &fileName);

private:
    // 坏字符规则数组
    // 字符串为01串
    int* badCharArray;

    // 好后缀规则数组
    int* goodSuffixArray;

    std::vector<char>* sample;

    /**
     * 生成坏字符数组
     * @param s 模板字符串
     */
    void generateBrokenCharArray(std::vector<char>& s);

    /**
     * 生成好后缀数组
     * @param s 模板字符串
     */
    void generateGoodSuffixArray(std::vector<char>& s);

    static int max(int a, int b);

};

void SearchInFile(char* fileName, char* sample);

#endif //ZIP_UNZIP_SEARCH_SEARCH_H
