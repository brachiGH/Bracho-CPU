/*
The assembler translates assembly code into binary instructions by following these steps:

    1.Clean the assembly code: Only keep the following characters: digits (0-9), lowercase letters (a-z), uppercase letters (A-Z), '#', ' ', '@', ':', or '\n'.
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
#define MAX_FILE_SIZE 10240


// returns True if the charater is a digits (0-9), lowercase letters (a-z), uppercase letters (A-Z), '#', ' ', '@', ':' or '\n'.
bool check_if_the_charater_is_valid(char c) {
    if ((47 < c && c < 59) || (63 < c && c < 91) || (96 < c && c < 123) || c == 10 || c == 32 || c == 35) { // don't change the values to to chars
        return true;
    }

    return false;
}


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


// void generate_symbol_table();

// cut the first oprand from line (note: if line does not contain an oprand the input oprand become null)
void get_oprand(char** line, char** oprand) {
    if (*line == '\0' || *line == NULL) {
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


void ParseCode(char* filename) {
    char AssemblyCode[MAX_RAM_SIZE + 1] = "0 "; // The first instruction should be always a NOP instruction

    unsigned int linenumber = 0;
    char hex_instruction[5] = ""; // is the instruction in hex
    char hex_oprand[6] = "";
    char* oprand;


    // Read the entire file into a buffer
    char assembly_file_content[MAX_FILE_SIZE];
    read_the_whole_file(filename, assembly_file_content, MAX_FILE_SIZE);

    // cleaning
    clean_assmebly_code(assembly_file_content);
    // generate_symbol_table();

    char* line = NULL;
    size_t len = 0;
    size_t offset = 0;
    long int linelen = 0;

    while ((linelen = get_line_from_buffer(&line, &len, assembly_file_content, &offset)) != -1) {
        linenumber++;
        char* linecpy_for_logging = _strdup(line);
        get_oprand(&line, &oprand);

        // checking if the first oprand is an opcode
        char* Opcode = getOpcode(oprand);

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
                    size_t size_hex_oprand = strlen(hex_oprand);
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
                    // symbol
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

            if (Opcode == "LR") { // executing LR2 if the instruction is LR
                strcat(AssemblyCode, "BFFF ");
            }

            // for checking if their an extra oprand
            get_oprand(&line, &oprand);
        }
        else
        {
            while (is_number(oprand) == true || oprand[0] == '@')
            {
                if (oprand[1] >= '0' && oprand[1] <= '9') {
                    // Convert number to hexadecimal string with bounds checking
                    snprintf(hex_oprand, sizeof(hex_oprand), "%x", atoi(oprand));
                }
                else if (oprand[1] == 'x' || oprand[1] == 'X') {
                    remove_0x_from_hex_string(oprand);
                    strncpy(hex_oprand, oprand, sizeof(hex_oprand) - 1); // only copy (sizeof(hex_oprand) - 1) chars from the oprand char array
                    hex_oprand[sizeof(hex_oprand)-1] = '\0'; // making sure hex_oprand is zero-terminated
                }
                else if (oprand[0] == '@') {
                    // oprand is a symbol
                }

                if (strlen(hex_oprand) == 5) {
                    fprintf(stderr, "[ERROR][LINE %d: %s] the value (0x)%s is large and can't represented by 16 bits (e.i. the value shouldènt be larger then 0xFFFF) \n", linenumber, linecpy_for_logging, oprand);
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
        ParseCode(filename);
    }
    else {
        printf("The file '%s' does not exist.\n", filename);
    }

    return 0;
}
