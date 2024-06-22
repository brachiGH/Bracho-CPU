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
    char* write_ptr = str;
    char* read_ptr = str;
    bool line_has_content = false;

    // Remove invalid characters and empty lines
    while (*read_ptr != '\0') {
        if (*read_ptr == '\n') {
            if (line_has_content) {
                *write_ptr++ = *read_ptr;
            }
            line_has_content = false;
        }
        else if (check_if_the_charater_is_valid(*read_ptr)) {
            *write_ptr++ = *read_ptr;
            if (*read_ptr != ' ' && *read_ptr != '\t') {
                line_has_content = true;
            }
        }
        read_ptr++;
    }
    *write_ptr = '\0';

    // Remove lines that start with '#' and trim leading spaces
    char* line_start = str;
    write_ptr = str;
    while (*line_start != '\0') {
        char* line_end = strchr(line_start, '\n');
        if (line_end == NULL) {
            line_end = line_start + strlen(line_start);
        }

        // Skip leading spaces
        char* line_content = line_start;
        while (*line_content == ' ' || *line_content == '\t') {
            line_content++;
        }

        // Check if the line should be copied
        if (*line_content != '#' && *line_content != '\0') {
            if (write_ptr != str) {
                *write_ptr++ = '\n';
            }
            memmove(write_ptr, line_content, line_end - line_content);
            write_ptr += line_end - line_content;
        }

        line_start = (*line_end == '\0') ? line_end : line_end + 1;
    }
    *write_ptr = '\0';
}


void ParseCode(const char* filename) {
    char AssemblyCode[MAX_RAM_SIZE + 1] = "0"; // The first instruction should be always a NOP instruction

    unsigned int linenumber = 0;
    unsigned char oprandcount = 0;
    char hex_code[5] = "";; // is the instruction in hex
    char hex_oprand[5] = "";;
    bool Assembling_error = false;



    FILE *fd = fopen(filename, "r");
    if (fd == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Read the entire file into a buffer
    char assembly_file_content[MAX_FILE_SIZE];
    size_t file_size = fread(assembly_file_content, 1, MAX_FILE_SIZE - 1, fd);
    assembly_file_content[file_size] = '\0';
    fclose(fd);

    // cleaning
    clean_assmebly_code(assembly_file_content);

    
    

    // Create a copy of the input string because strtok modifies the string
    char* assembly_file_content_copy = strdup(assembly_file_content);
    if (assembly_file_content_copy == NULL) {
        fprintf(stderr, "Error: Could not allocate memory\n");
        Assembling_error = true;
        return;
    }


    // Get the first token
    char *line = strtok(assembly_file_content_copy, "\n");


    // Read the line by line
    while (line != NULL) {
        linenumber++;
        remove_new_line_if_it_exist_at_the_end(line);

        // Create a copy of the input string because strtok modifies the string
        char* str_copy = strdup(line);
        if (str_copy == NULL) {
            fprintf(stderr, "Error: Could not allocate memory\n");
            Assembling_error = true;
            return;
        }

        // Get the first token
        char *token = strtok(str_copy, " ");

        if (str_copy[0] == '\0') {continue;} // skip empty lines


        /* checking if the first token is a valid opcode */
        enum OPCODE Opcode = get_opcode(token);
        if (Opcode != InvalideOpcode) {
            // Convert opcode to hexadecimal string with bounds checking
            strcpy(hex_code, OPCODE_to_hex_string(Opcode));
        }
        
        // Walk through other tokens
        while (token != NULL) {
            if (token[0] == '#') // skip line if it is comment
                break;

            if ('0' <= token[0] && token[0] <= '9')
            {
                oprandcount++;
                // checking the the number is in hex
                if (token[1] == 'x' || token[1] == 'X')
                {
                    remove_0x_from_hex_string(token);
                    // strcpy(hex_oprand, token);
                    // Copy up to sizeof(destination) - 1 characters to leave space for the null terminator
                    strncpy(hex_oprand, token, sizeof(hex_oprand) - 1); //only copy (sizeof(hex_oprand) - 1) chars from the token char array
                }
                else {
                    // Convert number to hexadecimal string with bounds checking
                    snprintf(hex_oprand, sizeof(hex_oprand), "%x", atoi(token));
                }
                
                // checking if the oprand is of a valid size
                size_t size_hex_code = strlen(hex_code);
                size_t size_hex_oprand = strlen(hex_oprand);
                if (size_hex_oprand > 4 - size_hex_code)
                {
                    fprintf(stderr, "[ERROR][LINE %d: %s] the value 0x%s is geater then what the instruction %s can support\n", linenumber, line, hex_oprand, get_opcode_name(Opcode));
                    Assembling_error = true;
                    break;
                } else if (size_hex_oprand < 4 - size_hex_code) {
                    // formating the hex_oprand in little-endian
                    /*
                        e.g. if hex_opreand = 0xF and then instruction can support the byte worth of information then
                        after strcat(AssemblyCode, hex_opreand)
                        the instruction is gona read 0xF0 not 0x0F
                    */

                    prepend_zeros(hex_oprand, 4 - size_hex_code);
                }

                strcat(hex_code, hex_oprand);
            } else if (token[0] == '@') {
                oprandcount++;
                //..
            } else if (strlen(hex_code) == 0) // strlen(hex_code) == 0 mean that the first token is not a opcode so hex_code is left empty
            {
                fprintf(stderr, "\n\n[ERROR][LINE %d: %s] '%s' is an invalid oprand\n\n\n", linenumber, line, token);
                Assembling_error = true;
                break; // exiting the the while loop, no need to finish prasing
            }


            if (strlen(hex_code) == 4) {
                printf("[LINE %d: %s] => %s\n", linenumber, line, hex_code);
                strcat(AssemblyCode, hex_code);
                strcat(AssemblyCode, " "); // a space between each instruction
                hex_code[0] = '\0';
            } else if (oprandcount > 1) {
                fprintf(stderr, "[ERROR][LINE %d: %s] the instruction 0x%s is invalid the length of an instruction should be 4\n", linenumber, line, hex_code);
                Assembling_error = true;
            }

            token = strtok(NULL, " ");
        }

        // Free the allocated memory
        free(str_copy);

        if (Opcode == LR) { // executing LR2 if the the instruction is LR
            strcat(AssemblyCode, "BFFF ");
        }

        if (Assembling_error) {
            exit(EXIT_FAILURE);
            break;
        }

        if (oprandcount > 1) {
            fprintf(stderr, "\n\n[ERROR][LINE %d: %s]  invalid  number of oprands\n\n\n", linenumber, line);
            break;
        }
        oprandcount = 0;

        line = strtok(NULL, "\n");
    }

    if (!feof(fd))
        fprintf(stderr, "Error: Could not finish Assembling file\n");

    
    printf("\n%s\n",AssemblyCode);
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
        ParseCode(filename);
    }
    else {
        printf("The file '%s' does not exist.\n", filename);
    }

    return 0;
}
