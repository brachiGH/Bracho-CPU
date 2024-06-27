/*
The assembler translates assembly code into binary instructions by following these steps:

    1.Clean the assembly code: Only keep the following characters: digits (0-9), lowercase letters (a-z), uppercase letters (A-Z), '#', ' ', '@', ':', '_', '[', ']', or '\n'.
                                And Removes leading spaces in each line.
    2.Generate the symbol table: Create a table of addresses.
    3.Read the code line by line:
        - If the first word is an opcode, check if it requires any operands and verify their validity.
        - If the first word is a number, pass it as is. Then, check if the subsequent words are also numbers (in hexadecimal or decimal). Continue adding numbers until the end of the line.
        Note: Symbols are treated like numbers.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Opcodes.h"
#include "utilites.h"

#define MAX_LINE_LENGTH 1024
#define MAX_RAM_SIZE 16384 // in bytes
#define MAX_FILE_SIZE 36384

#define MAX_SYMBOLS 1000
#define MAX_SYMBOL_LENGTH 256

#define SKIPED_WORD 1 // the first word in the ram is a NOP instruction

typedef struct {
    char symbol[MAX_SYMBOL_LENGTH];
    int lineNumber;
} SymbolMap;

void generate_symbol_table(const char* str, SymbolMap* map, int* mapSize) {
    int lineNumber = 0;
    bool atLineStart = true;

    const char* readPtr = str;
    const char* lineStart = str;

    while (*readPtr != '\0') {
        // Check if the line starts with '@'
        if (atLineStart && *readPtr == '@') {
            const char* patternEnd = readPtr;

            // Find the end of the pattern
            while (*patternEnd != '\0' && *patternEnd != '\n') {
                patternEnd++;
            }

            // Check if the pattern ends with ':'
            if (*(patternEnd - 1) == ':') {
                // Store the pattern and line number in the map
                int patternLength = patternEnd - readPtr;
                strncpy(map[*mapSize].symbol, readPtr, patternLength - 1);// -1 for removing the ':'
                map[*mapSize].symbol[patternLength] = '\0';
                map[*mapSize].lineNumber = lineNumber + SKIPED_WORD; // we don't add +1 because the first address is 0 not a 1
                (*mapSize)++;

                // Skip over the pattern and the newline character
                readPtr = patternEnd + 1;
                lineStart = readPtr;
                atLineStart = true;
                continue;
            }
        }

        // Move to the next character
        if (*readPtr == '\n') {
            lineNumber++;
            lineStart = readPtr + 1;
            atLineStart = true;
        }
        else {
            atLineStart = false;
        }
        readPtr++;
    }
}

int getSymbolLineNumber(const SymbolMap *map, int mapSize, const char *pattern) {
    for (int i = 0; i < mapSize; i++) {
        if (strcmp(map[i].symbol, pattern) == 0) {
            return map[i].lineNumber;
        }
    }
    return -1;  // Pattern not found
}

void handle_arrays(char* str) {
    int inBrackets = 0;
    int length = strlen(str);
    char* result = (char*)malloc(length * 2 * sizeof(char)); // Allocate memory for the result
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    int j = 0;

    for (int i = 0; i < length; i++) {
        if (str[i] == '[') {
            inBrackets = 1;
            continue;
        }
        else if (str[i] == ']') {
            inBrackets = 0;
            continue;
        }

        if (inBrackets) {
            if (str[i] == ' ') {
                result[j++] = '\n';
            }
            else {
                result[j++] = str[i];
            }
        }
        else {
            result[j++] = str[i];
        }
    }

    result[j] = '\0'; // Null-terminate the result

    // Copy the result back to the original string
    strcpy(str, result);

    // Free dynamically allocated memory
    free(result);
}

void remove_arrays_brackets(char* input) {
    int len = strlen(input);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] != '[' && input[i] != ']') {
            input[j++] = input[i];
        }
    }
    input[j] = '\0'; // Null-terminate the modified string
}

// returns True if the charater is a digits (0-9), lowercase letters (a-z), uppercase letters (A-Z), '#', ' ', '@', ':', '_', '[', ']' or '\n'.
bool check_if_the_charater_is_valid(char c) {
    if ((47 < c && c < 59) || (63 < c && c < 91) || (96 < c && c < 123) || c == 10 || c == 32 || c == 35 || c == '_' || c == '[' || c == ']') { // don't change the values to to chars
        return true;
    }

    return false;
}

// 
void clean_assmebly_code(char* str) {
    char* dest = str;
    char* src = str;
    bool new_line = true; // Flag to handle leading spaces at the start of a line

    while (*src) {
        // Remove leading spaces in each line
        if (new_line && *src == ' ') {
            src++;
            continue;
        }

        // Reset the new_line flag if a non-space character is encountered
        if (*src == '\n') {
            new_line = true;
        }
        else if (*src != ' ') {
            new_line = false;
        }

        // Check if the character is valid
        if (check_if_the_charater_is_valid(*src)) {
            *dest++ = *src;
        }
        src++;
    }
    *dest = '\0'; // Null-terminate the cleaned string
}


// Function to remove words that start with @ and end with :
void remove_symbols(char *str) {
    int length = strlen(str);
    int writeIndex = 0;
    int readIndex = 0;
    bool atLineStart = true;

    while (readIndex < length) {
        // Check if the line starts with '@'
        if (atLineStart && str[readIndex] == '@') {
            int patternEndIndex = readIndex;

            // Find the end of the pattern
            while (patternEndIndex < length && str[patternEndIndex] != '\n') {
                patternEndIndex++;
            }

            // Check if the pattern ends with ':'
            if (patternEndIndex < length && str[patternEndIndex - 1] == ':') {
                // Skip over the pattern and the newline character
                readIndex = patternEndIndex + 1;
                atLineStart = true;
                continue;
            }
        }

        // Copy the current character to the write position
        str[writeIndex++] = str[readIndex++];

        // Check if we've reached a newline character
        if (str[writeIndex - 1] == '\n') {
            atLineStart = true;
        } else {
            atLineStart = false;
        }
    }

    // Null-terminate the modified string
    str[writeIndex] = '\0';
}

// cut the first oprand from line (note: if line does not contain an oprand the input oprand become null)
void get_oprand(char** line, char** oprand) {
    if ((*line)[0] == '\0' || *line == NULL) {
        *oprand = NULL;
        return;
    }

    int i = 0;
    while ((*line)[i] == ' ')
    {
        i++;
    }
    *oprand = (*line) + i;
    while ((*line)[i] != '\0' && (*line)[i] != ' ' && (*line)[i] != '\n')
    {
        i++;
    }



    if ((*line)[i] != '\0') {
        (*line)[i] = '\0';
        *line = *line + 1 + i;
    }
    else {
        *line = *line + i;
    }

    return;
}


// checks if the oprand is a valid dec or hex number
bool is_number(char* oprand) {
    if (oprand == NULL || *oprand == '\0') {
        return false;
    }

    if (strlen(oprand) > 2 && (oprand[0] == '0') && (oprand[1] == 'x' || oprand[1] == 'X')) {
        // Hexadecimal number
        for (int i = 2; oprand[i] != '\0'; i++) {
            if (!(isdigit(oprand[i]) || (oprand[i] >= 'A' && oprand[i] <= 'F') || (oprand[i] >= 'a' && oprand[i] <= 'f'))) {
                return false;
            }
        }
        return true;
    }
    else {
        // Decimal number
        for (int i = 0; oprand[i] != '\0'; i++) {
            if (!isdigit(oprand[i])) {
                return false;
            }
        }
        return true;
    }
}


void ParseCode(char* assembly_file_content, SymbolMap *symbol_map, int mapSize) {
    char AssemblyCode[MAX_RAM_SIZE + 1] = "0 "; // The first instruction should be always a NOP instruction

    unsigned int linenumber = 1;
    char hex_instruction[5] = ""; // is the instruction in hex
    char hex_oprand[6] = "";
    char* oprand;

    char* line = NULL;
    size_t len = 0;
    size_t offset = 0;
    long int linelen = 0;

    while ((linelen = get_line_from_buffer(&line, &len, assembly_file_content, &offset)) != -1) {
        linenumber++;
        char* linecpy_for_logging = strdup(line);
        get_oprand(&line, &oprand);

        // checking if the first oprand is an opcode
        const char* Opcode = getOpcode(oprand);

        if (Opcode != NULL) {
            // Convert opcode to hexadecimal string
            strcpy(hex_instruction, getOpcodeInHex(Opcode));

            if (getNumberOfRequiredOprand(Opcode) == 1)
            {
                get_oprand(&line, &oprand);

                // checking if there is an oprand
                if (oprand == NULL || oprand[0] == '\0' || oprand[0] == '#') {
                    fprintf(stderr, "[ERROR][LINE %d: %s] the requires an oprand\n", linenumber, linecpy_for_logging);
                    exit(EXIT_FAILURE);
                }

                if (is_number(oprand) == true)
                {
                    // checking the number is in hex
                    if (oprand[1] == 'x' || oprand[1] == 'X') {
                        remove_0x_from_hex_string(oprand);
                        strncpy(hex_oprand, oprand, sizeof(hex_oprand) - 2); // only copy (sizeof(hex_oprand) - 2) chars from the oprand char array
                        hex_oprand[sizeof(hex_oprand) - 1] = '\0'; // making sure hex_oprand is zero-terminated because strncpy does not that
                    }
                    else {
                        // Convert number to hexadecimal string with bounds checking
                        snprintf(hex_oprand, sizeof(hex_oprand), "%x", atoi(oprand));
                    }

                    // checking if the operand is of a valid size
                    int size_hex_oprand = strlen(hex_oprand);
                    if (size_hex_oprand > getOprandMaxSize(Opcode)) {
                        fprintf(stderr, "[ERROR][LINE %d: %s] the value 0x%s is greater than what the instruction %s can support\n", linenumber, linecpy_for_logging, hex_oprand, Opcode);
                        exit(EXIT_FAILURE);
                        break;
                    }
                    else if (size_hex_oprand < getOprandMaxSize(Opcode)) {
                        // formatting the hex_oprand in little-endian
                        prepend_zeros(hex_oprand, getOprandMaxSize(Opcode));
                    }

                    strcat(hex_instruction, hex_oprand);

                }
                else if (oprand[0] == '@') {
                    int lineNumber = getSymbolLineNumber(symbol_map, mapSize, oprand);
                    if (lineNumber == -1) {
                        fprintf(stderr, "[ERROR][LINE %d: %s] the symbol %s does not exist\n", linenumber, linecpy_for_logging, oprand);
                        exit(EXIT_FAILURE);
                    }
                    snprintf(hex_oprand, sizeof(hex_oprand), "%x", lineNumber);
                    prepend_zeros(hex_oprand, 3);
                    strcat(hex_instruction, hex_oprand);
                }
                else {
                    fprintf(stderr, "[ERROR][LINE %d: %s] the oprand \"%s\" is invalid\n", linenumber, linecpy_for_logging, oprand);
                    exit(EXIT_FAILURE);
                }
            }

            if (strlen(hex_instruction) == 4) {
                printf("[LINE %d: %s] => %s\n", linenumber, linecpy_for_logging, hex_instruction);
                strcat(AssemblyCode, hex_instruction);
                strcat(AssemblyCode, " "); // a space between each instruction
            }
            else {
                fprintf(stderr, "[ERROR][LINE %d: %s] the instruction assembly '%s' is UNKONW\n", linenumber, linecpy_for_logging, hex_instruction);
                exit(EXIT_FAILURE);
            }

            if (strcmp(Opcode, "LR") == 0) { // executing LR2 if the instruction is LR
                strcat(AssemblyCode, "BFFF ");
            }

            // for checking if their an extra oprand
            get_oprand(&line, &oprand);
        }
        else if (oprand != NULL)
        {
            while ((oprand != NULL)?(is_number(oprand) == true || oprand[0] == '@'):false)
            {
                if ((strlen(oprand) > 2)?(oprand[1] == 'x' || oprand[1] == 'X'):false) {
                    remove_0x_from_hex_string(oprand);
                    strncpy(hex_oprand, oprand, sizeof(hex_oprand) - 1); // only copy (sizeof(hex_oprand) - 1) chars from the oprand char array
                    hex_oprand[sizeof(hex_oprand) - 1] = '\0'; // making sure hex_oprand is zero-terminated
                } else if (oprand[0] >= '0' && oprand[0] <= '9') {
                    // Convert number to hexadecimal string with bounds checking
                    snprintf(hex_oprand, sizeof(hex_oprand), "%x", atoi(oprand));
                }
                else if (oprand[0] == '@') {
                    int lineNumber = getSymbolLineNumber(symbol_map, mapSize, oprand);
                    if (lineNumber == -1) {
                        fprintf(stderr, "[ERROR][LINE %d: %s] the symbol %s does not exist\n", linenumber, linecpy_for_logging, oprand);
                        exit(EXIT_FAILURE);
                    }
                    snprintf(hex_oprand, sizeof(hex_oprand), "%x", lineNumber);
                }

                if (strlen(hex_oprand) == 5) {
                    fprintf(stderr, "[ERROR][LINE %d: %s] the value (0x)%s is large and can't represented by 16 bits (e.i. the value shouldènt be larger then 0xFFFF) \n", linenumber, linecpy_for_logging, hex_oprand);
                    exit(EXIT_FAILURE);
                }

                prepend_zeros(hex_oprand, 4);
                strcat(AssemblyCode, hex_oprand);
                strcat(AssemblyCode, " "); // a space between each instruction

                // get next oprand
                get_oprand(&line, &oprand);
            }
        }

        // check if there is an unused oprand, it is invalid.
        if (oprand != NULL) {
            if (oprand[0] != '\0' && oprand[0] != '#') {
                fprintf(stderr, "[ERROR][LINE %d: %s] the oprand \"%s\" is invalid\n", linenumber, linecpy_for_logging, oprand);
                exit(EXIT_FAILURE);
            }
        }

        free(linecpy_for_logging);

        line = line - (linelen - strlen(line)); // reseting the line to it initial position
    }

    printf("\n%s\n", AssemblyCode);
}

int main(int argc, char** argv) {
    // Check if the number of arguments is correct
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    

    // Check if the file exists
    if (file_exists(filename)) {
        generate_OpcodeHashMap();  //loading into memory opcodes and their information

        // Read the entire file into a buffer
        char assembly_file_content[MAX_FILE_SIZE];
        read_the_whole_file(filename, assembly_file_content, MAX_FILE_SIZE);

        // cleaning
        clean_assmebly_code(assembly_file_content);

        // generating the symbols map
        char * assembly_file_content_cpy = strdup(assembly_file_content);
        handle_arrays(assembly_file_content_cpy);
        remove_empty_lines(assembly_file_content_cpy);
        SymbolMap map[MAX_SYMBOLS];
        int mapSize = 0;
        generate_symbol_table(assembly_file_content_cpy, map, &mapSize);
        free(assembly_file_content_cpy);

        // more cleaning
        remove_arrays_brackets(assembly_file_content);
        remove_symbols(assembly_file_content);
        
        ParseCode(assembly_file_content, map, mapSize);
    }
    else {
        printf("The file '%s' does not exist.\n", filename);
    }

    return 0;
}
