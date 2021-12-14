#ifndef SRECORD_H
#define SRECORD_H

#define MAX 255U
#define MAX_SIZE_S5 65535U
#define MAX_SIZE_S6 1677215U

// All possible error codes the S-Record checking functions may return
enum SRecordErrors
{
   NOT_ERROR = 0,
   ERROR_S = -1,
   ERROR_TYPE = -2,
   ERROR_HEX = -3,
   ERROR_BYTE_COUNT = -4,
   ERROR_SUM = -5,
   ERROR_LINE_COUNT = -6,
   ERROR_TERMINATE = -7
};

// Read a line in srecord file
void readLine(int8_t *line, FILE *file, uint8_t *pos);

// Check start with S
enum SRecordErrors checkS(uint8_t temp);

// Check type of record
enum SRecordErrors checkType(uint8_t temp);

// Check if all characters are hex base
enum SRecordErrors checkHex(int8_t *temp);

// Check byte count
enum SRecordErrors checkByteCount(int8_t *str);

// Check checksum
enum SRecordErrors checkSum(int8_t *str);

// Check line count
enum SRecordErrors checkLineCount(int8_t *str, uint16_t count);

// Check termination
enum SRecordErrors checkTerminate(int8_t temp, uint8_t type);

// Print address, data
void printData(int8_t *str, uint8_t length, FILE *file, int8_t type);

#endif
