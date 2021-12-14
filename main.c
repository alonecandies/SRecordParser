#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "srecord.h"

uint8_t main(int argc, char *argv[])
{
    uint8_t length = 0;
    uint8_t count = 0;
    uint16_t index = 0;
    uint16_t lineCount = 1;
    int8_t type = 0;
    int8_t line[MAX];
    int8_t endType = 0;

    FILE *inputFile = NULL;
    FILE *outputFile = NULL;

    if (argc < 3)
    {
        printf("Error: Missing file input or file output!");
        return (-1);
    }
    else if (argc > 3)
    {
        printf("Error: Too much arguments value!");
        return (-1);
    }

    /* Open input file in read mode and output file in write mode 
    (w+ for erase existed file or create new file if not existed) */
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w+");

    // Handle error opening file case
    if (inputFile == NULL)
    {
        printf("\nError: File input is not exist!");
    }
    else
    {
        while (!feof(inputFile))
        {
            if (fgetc(inputFile) == '\n')
            {
                lineCount++;
            }
        }
    }
    rewind(inputFile);

    // If there is not any error, check error and convert input srecord file
    printf("Num.  Address \t\t Data \t\t\t Error\n");
    fprintf(outputFile, "Num.   Address \t\t Data \t\t\t Error\n");
    for (index = 0; index < lineCount - 1; index++)
    {
        printf("\n%d\t", index + 1);
        fprintf(outputFile, "%d\t", index + 1);
        readLine(line, inputFile, &length);

        // Check S19 or S28 or S37 record style
        if (line[1] == '1' || line[1] == '2' || line[1] == '3')
        {
            if (line[1] == '1')
            {
                type = '1';
                endType = '9';
            }
            else if (line[1] == '2')
            {
                type = '2';
                endType = '8';
            }
            else if (line[1] = '3')
            {
                type = '3';
                endType = '7';
            }
            count++;
        }

        // Check start with S
        if (checkS(line[0]) == NOT_ERROR)
        {
            // Check type of record
            if (checkType(line[1]) == NOT_ERROR)
            {
                // Check if all characters are hex base
                if (checkHex(line) == NOT_ERROR)
                {
                    // Check byte count
                    if (checkByteCount(line) == NOT_ERROR)
                    {
                        // Check checksum
                        if (checkSum(line) == NOT_ERROR)
                        {
                            if (type == 5 || type == 6)
                            {
                                // Check line count
                                if (checkLineCount(line, count) != NOT_ERROR)
                                {
                                    fprintf(outputFile, "\tError: Line count invalid!");
                                    printf("\tError: Line count invalid!");
                                }
                            }
                            // Print address, error, data
                            else if (index != 0 && index != lineCount - 2 && index != lineCount - 1)
                            {
                                printData(line, length, outputFile, type);
                            }
                            else if (index == lineCount)
                            {
                                // Check termination
                                if (checkTerminate(line[1], endType) != NOT_ERROR)
                                {
                                    fprintf(outputFile, "\tError: Terminated!");
                                    printf("\tError: Terminated!");
                                }
                            }
                        }
                        else
                        {
                            printData(line, length, outputFile, type);
                            fprintf(outputFile, "\tError: Checksum!");
                            printf("\tError: Checksum!");
                        }
                    }
                    else
                    {
                        printData(line, length, outputFile, type);
                        fprintf(outputFile, "\tError: Byte count invalid!");
                        printf("\tError: Byte count invalid!");
                    }
                }
                else
                {
                    printData(line, length, outputFile, type);
                    fprintf(outputFile, "\tError: Hex base invalid!");
                    printf("\tError: Hex base invalid!");
                }
            }
            else
            {
                printData(line, length, outputFile, type);
                fprintf(outputFile, "\tError: Record type invalid!");
                printf("\tError: Record type invalid!");
            }
        }
        else
        {
            printData(line, length, outputFile, type);
            fprintf(outputFile, "\tError: Not start with S!");
            printf("\tError: Not start with S!");
        }
        fprintf(outputFile, "\n");
    }

    // Close file after modification
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
