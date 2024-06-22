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
unsigned int hex_string_to_number(const char *hex_str) {
    unsigned int result = 0;
    size_t length = strlen(hex_str);

    for (size_t i = 0; i < length; ++i) {
        char c = hex_str[i];
        int digit_value = 0;

        if (isdigit(c)) {
            digit_value = c - '0';
        } else if (isxdigit(c)) {
            if (islower(c)) {
                digit_value = c - 'a' + 10;
            } else {
                digit_value = c - 'A' + 10;
            }
        } else {
            // Handle invalid characters (optional)
            fprintf(stderr, "Invalid hexadecimal character: %c\n", c);
            return 0; // Or handle error as needed
        }

        // Multiply result by 16 and add current digit value
        result = result * 16 + digit_value;
    }

    return result;
}

void remove_0x_from_hex_string(char *token) {
    size_t size = strlen(token);

    for (size_t i = 0; i < (size - 2); i++) {
        token[i]=token[i+2];
    }

    token[size - 2] = '\0';
}


// removes the "Line Feed" and "Carriage Return" if it exist
void remove_new_line_if_it_exist_at_the_end(char *token) {
    // Get length of the token
    size_t size = strlen(token);

    // Check if the last character is a Line Feed
    if (size > 0 && token[size-1] == '\n') {
        // Replace the newline character with a null terminator
        token[size-1] = '\0';
    }

    // Check if the last character is a Carriage Return
    if (size > 0 && token[size-2] == '\r') {
        // Replace the Carriage Return character with a null terminator
        token[size-2] = '\0';
    }
}

void remove_Tabs_if_they_exist_at_the_beginning(char *token) {
    // Get length of the token
    size_t size = strlen(token);

    //get the number of tabs in the beginning
    size_t numberoftabs=0;  //Why Use size_t: Portability: size_t ensures that your code is portable across different platforms and architectures because it is defined to be large enough to represent the size of any object.
    while (token[numberoftabs] == '\t') {
        numberoftabs++;
    }

    // translating the token to the beginning
    size_t i;
    for (i = 0; i < size-numberoftabs; i++) {
        token[i] = token[i+numberoftabs];
    }

    token[i+1] = '\0';
}


void printAsciiCodes(const char *arr) {
    // Iterate through each character in the array until we encounter '\0' (null terminator)
    for (int i = 0; arr[i] != '\0'; ++i) {
        printf("Character '%c' has ASCII code: %d\n", arr[i], arr[i]);
    }
}

void to_uppercase(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}


void prepend_zeros(char *hex_operand, size_t target_length) {
    size_t size_hex_operand = strlen(hex_operand);
    if (size_hex_operand >= target_length) {
        // If the current length is already equal to or greater than the target length, no need to prepend zeros
        return;
    }

    // Create a new buffer to hold the final string with leading zeros
    char *result = (char *)malloc(target_length + 1);
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
