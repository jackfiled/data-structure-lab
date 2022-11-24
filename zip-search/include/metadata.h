//
// Created by ricardo on 2022/11/23.
//

#ifndef ZIP_SEARCH_METADATA_H
#define ZIP_SEARCH_METADATA_H

#include "cstdio"

/**
 * 文件的元信息结构体
 */
struct MetaData
{
    // 文件中字典数组的长度
    int InFileZipLength;
    // 在最后一个int字节中被使用的bit数
    int LastBufferUsedLength;
};

typedef struct MetaData MetaDataT;

#endif //ZIP_SEARCH_METADATA_H
