#include "file_io.h"
#include "logging.h"
#include "cstring"

/**
 * 输出帮助信息
 */
void PrintHelpMessage()
{
    printf("Usage: \n");
    printf("Zip File: -z [In-File-Name] [Out-File-Name]\n");
    printf("Unzip File: -u [In-File-Name] [Out-File-Name]\n");
    printf("Print Help Message: -h\n");
}


int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        std::string inputFileName = std::string(argv[2]);
        std::string outputFileName = std::string(argv[3]);

        if (strcmp(argv[1], "-z") == 0)
        {
            Logging::LoggingInfo("Start Zip File: " + inputFileName + " to zip file: " + outputFileName);

            FileIO::WriteZipFile(inputFileName, outputFileName);

            double zipRate = FileIO::CalculateZipRate(inputFileName, outputFileName) * 100.0;
            Logging::LoggingInfo("The Zip Rate is: " + std::to_string(zipRate) + "%");
            Logging::LoggingInfo("Zip Success!");
        }
        else if(strcmp(argv[1], "-u") == 0)
        {
            Logging::LoggingInfo("Start Unzip File: " + inputFileName + " to text file: " + outputFileName);

            FileIO::WriteUnzipFile(inputFileName, outputFileName);

            Logging::LoggingInfo("Unzip Success!");
        }
        else
        {
            printf("Unknown Usage!\n");
            PrintHelpMessage();
        }
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