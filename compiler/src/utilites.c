#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// check if a file exists
int file_exists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}


// Function to convert hexadecimal string to number
unsigned int hex_string_to_number(const char* hex_str) {
    unsigned int result = 0;
    size_t length = strlen(hex_str);

    for (size_t i = 0; i < length; ++i) {
        char c = hex_str[i];
        int digit_value = 0;

        if (isdigit(c)) {
            digit_value = c - '0';
        }
        else if (isxdigit(c)) {
            if (islower(c)) {
                digit_value = c - 'a' + 10;
            }
            else {
                digit_value = c - 'A' + 10;
            }
        }
        else {
            // Handle invalid characters (optional)
            fprintf(stderr, "Invalid hexadecimal character: %c\n", c);
            return 0; // Or handle error as needed
        }

        // Multiply result by 16 and add current digit value
        result = result * 16 + digit_value;
    }

    return result;
}

void remove_0x_from_hex_string(char* token) {
    size_t size = strlen(token);

    for (size_t i = 0; i < (size - 2); i++) {
        token[i] = token[i + 2];
    }

    token[size - 2] = '\0';
}


// removes the "Line Feed" and "Carriage Return" if it exist
void remove_new_line_if_it_exist_at_the_end(char* token) {
    // Get length of the token
    size_t size = strlen(token);

    // Check if the last character is a Line Feed
    if (size > 0 && token[size - 1] == '\n') {
        // Replace the newline character with a null terminator
        token[size - 1] = '\0';
    }
    else if (size > 0 && token[size - 1] == '\r') {
        // Replace the Carriage Return character with a null terminator
        token[size - 1] = '\0';
    }

    // Check if the last character is a Carriage Return
    if (size > 0 && token[size - 2] == '\r') {
        // Replace the Carriage Return character with a null terminator
        token[size - 2] = '\0';
    }
}

void remove_Tabs_if_they_exist_at_the_beginning(char* token) {
    // Get length of the token
    size_t size = strlen(token);

    //get the number of tabs in the beginning
    size_t numberoftabs = 0;  //Why Use size_t: Portability: size_t ensures that your code is portable across different platforms and architectures because it is defined to be large enough to represent the size of any object.
    while (token[numberoftabs] == '\t') {
        numberoftabs++;
    }

    // translating the token to the beginning
    size_t i;
    for (i = 0; i < size - numberoftabs; i++) {
        token[i] = token[i + numberoftabs];
    }

    token[i + 1] = '\0';
}


void printAsciiCodes(const char* arr) {
    // Iterate through each character in the array until we encounter '\0' (null terminator)
    for (int i = 0; arr[i] != '\0'; ++i) {
        printf("Character '%c' has ASCII code: %d\n", arr[i], arr[i]);
    }
}

void to_uppercase(char* str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}


void prepend_zeros(char* hex_operand, size_t target_length) {
    size_t size_hex_operand = strlen(hex_operand);
    if (size_hex_operand >= target_length) {
        // If the current length is already equal to or greater than the target length, no need to prepend zeros
        return;
    }

    // Create a new buffer to hold the final string with leading zeros
    char* result = (char*)malloc(target_length + 1);
    if (!result) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Fill the beginning of the result buffer with zeros
    size_t leading_zeros = target_length - size_hex_operand;
    memset(result, '0', leading_zeros);

    // Copy the original hex_operand to the end of the result buffer
    strcpy(result + leading_zeros, hex_operand);

    // Null-terminate the result buffer
    result[target_length] = '\0';

    // Copy the result back to the original hex_operand
    strcpy(hex_operand, result);

    // Free the temporary buffer
    free(result);
}


void  read_the_whole_file(char* filename, char* assembly_file_content, unsigned long long MAX_FILE_SIZE) {
    FILE* fd = fopen(filename, "r");
    if (fd == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t file_size = fread(assembly_file_content, 1, MAX_FILE_SIZE - 1, fd);
    assembly_file_content[file_size] = '\0';
    fclose(fd);
}

// Function to get a line from a buffer and retuen the length of the line
long int get_line_from_buffer(char** lineptr, size_t* n, const char* buffer, size_t* offset) {
    if (buffer == NULL || lineptr == NULL || n == NULL || offset == NULL) {
        return -1; // Error handling
    }

    size_t buf_len = strlen(buffer);
    if (*offset >= buf_len) {
        return -1; // No more lines to read
    }

    size_t line_len = 0;
    const char* start = buffer + *offset;
    const char* end = start;

    // Find the end of the line or buffer
    while (*end != '\0' && *end != '\n') {
        end++;
        line_len++;
    }

    // Allocate memory for the line if necessary
    if (*lineptr == NULL || *n < line_len + 1) {
        *n = line_len + 1;
        *lineptr = realloc(*lineptr, *n);
        if (*lineptr == NULL) {
            return -1; // Memory allocation failed
        }
    }

    // Copy the line to the output buffer
    strncpy(*lineptr, start, line_len);
    (*lineptr)[line_len] = '\0';

    // Update the offset
    *offset += line_len;
    if (buffer[*offset] == '\n') {
        (*offset)++;
    }

    return line_len;
}

void removeSubstring(char *str, int start, int length) {
    int strLength = strlen(str);

    // Ensure the start and length are within the bounds of the string
    if (start < 0 || start >= strLength || length <= 0 || start + length > strLength) {
        return;
    }

    // Use memmove to shift the contents of the string
    memmove(&str[start], &str[start + length], strLength - start - length + 1);
}

size_t len_of_line(char *line) {
    size_t i;
    for (i = 0; line[i] != '\n'; i++);

    return ++i;
}

// a function that removes empty lines and lines that only contain a comment
void remove_empty_lines(char* str) {
    size_t i = 0, j;

    if (str == NULL) {
        return;
    }

    while (str[i] != '\0') {
        if (str[i] == '\n') {
            i++;
            j = 0;

            if (str[i] == '\n') {
                removeSubstring(str, i, 1);
                i = 0;
            }
            else if (str[i] == '#') {
                j = len_of_line(str + i);

                removeSubstring(str, i, j);
                i = 0;
            }
        }
        i++;
    }
}

