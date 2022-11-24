//
// Created by ricardo on 2022/11/21.
//

#include "IO.h"
#include "logging.h"

int main()
{
    std::string inputFileName = "README.txt";
    std::string outputFileName = "test.txt";

    WriteZipFile(inputFileName, "README.bin");
    LoggingInfo("Zip Success");
    WriteUnzipFile("README.bin", outputFileName);
    LoggingInfo("Unzip Success");

    return 0;
}