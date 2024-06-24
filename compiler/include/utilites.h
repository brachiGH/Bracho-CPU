#ifndef UTILITES_H
#define UTILITES_H
#include <stddef.h>

// check if a file exists
int file_exists(const char* filename);

// Function to convert hexadecimal string to number
unsigned int hex_string_to_number(const char *hex_str);


void remove_0x_from_hex_string(char *token);


void remove_new_line_if_it_exist_at_the_end(char *token);


void remove_Tabs_if_they_exist_at_the_beginning(char *token);


void printAsciiCodes(const char *arr);

void to_uppercase(char *str);

void  read_the_whole_file(char *filename, char *assembly_file_content, unsigned long long MAX_FILE_SIZE);

// Function to get a line from a buffer and retuen the length of the line
long int get_line_from_buffer(char** lineptr, size_t* n, const char* buffer, size_t* offset);

#endif