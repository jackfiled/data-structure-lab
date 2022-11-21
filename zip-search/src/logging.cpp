//
// Created by ricardo on 2022/11/21.
//

#include "logging.h"

void LoggingInfo(const std::string& info)
{
    printf("[Info] %s\n", info.c_str());
}

void LoggingWarning(const std::string& warning)
{
    printf("[warning] %s\n", warning.c_str());
}

void LoggingError(const std::string& error)
{
    printf("[error] %s\n", error.c_str());
}