//
// Created by ricardo on 22-12-11.
//
#include "logging.h"
#include "cstdio"

void Logging::LoggingInfo(const std::string &info)
{
    printf("[Info] %s\n", info.c_str());
}

void Logging::LoggingWarning(const std::string &warning)
{
    printf("[warning] %s\n", warning.c_str());
}

void Logging::LoggingError(const std::string &error)
{
    printf("[error] %s\n", error.c_str());
}
