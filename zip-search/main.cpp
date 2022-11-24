//
// Created by ricardo on 2022/11/21.
//

#include "IO.h"
#include "logging.h"
#include "cstring"

int main(int argc, char * argv[])
{
    if (argc == 4)
    {
        std::string inputFileName = std::string(argv[2]);
        std::string outputFileName = std::string(argv[3]);

        if (strcmp(argv[1], "-z") == 0)
        {
            LoggingInfo("Start Zip File: " + inputFileName + " to zip file: " + outputFileName);

            WriteZipFile(inputFileName, outputFileName);

            double zipRate = CalculateZipRate(inputFileName, outputFileName) * 100.0;
            LoggingInfo("The Zip Rate is: " + std::to_string(zipRate) + "%");
            LoggingInfo("Zip Success!");
        }

        if (strcmp(argv[1], "-u") == 0)
        {
            LoggingInfo("Start Unzip File: " + inputFileName + " to text file: " + outputFileName);

            WriteUnzipFile(inputFileName, outputFileName);

            LoggingInfo("Unzip Success!");
        }

        printf("Unknown Usage!\n");
        PrintHelpMessage();
    }
    else if (argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        PrintHelpMessage();
    }
    else
    {
        printf("Unknown Usage!\n");
        PrintHelpMessage();
    }

    return 0;
}

