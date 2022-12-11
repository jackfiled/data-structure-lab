//
// Created by ricardo on 22-12-11.
//

#ifndef ZIP_UNZIP_SEARCH_LOGGING_H
#define ZIP_UNZIP_SEARCH_LOGGING_H
#include "string"

class Logging
{
public:
    /**
     * 输出信息
     * @param info
     */
    static void LoggingInfo(const std::string& info);

    /**
     * 输出警告
     * @param warning
     */
    static void LoggingWarning(const std::string& warning);

    /**
     * 输出错误
     * @param error
     */
    static void LoggingError(const std::string& error);
};

#endif //ZIP_UNZIP_SEARCH_LOGGING_H
