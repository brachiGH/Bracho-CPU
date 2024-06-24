#ifndef OPCODES_H
#define OPCODES_H


// Instructions and their Opcodes
enum OPCODE {
    NOP = 0x0FFF,
    LDA = 0xC,
    LDB = 0x1,
    LDC = 0x2,
    BIN = 0x3,
    CIN = 0x4,
    STA = 0x5,
    BR = 0x6,
    BRN = 0x7,
    BRZ = 0x8,
    BRV = 0x9,
    LR = 0xA,
    ADD = 0xE0FF,
    SUB = 0xE1FF,
    MULT = 0xE2FF,
    DIV = 0xE3FF,
    NOT = 0xE4FF,
    AND = 0xE5FF,
    OR = 0xE6FF,
    XOR = 0xE7FF,
    SHL = 0xE8F,
    SHR = 0xE9F,
    OUT = 0xDFFF,
    HALT = 0xFFFF,
    InvalideOpcode = 0xFFFFF // a number lager than what the data bus can support
};

enum OPCODE_OPRAND_NUMBER {
    NOP_ON = 1,
    LDA_ON = 1,
    LDB_ON = 1,
    LDC_ON = 1,
    BIN_ON = 1,
    CIN_ON = 1,
    STA_ON = 1,
    BR_ON  = 1,
    BRN_ON = 1,
    BRZ_ON = 1,
    BRV_ON = 1,
    LR_ON  = 1,
    ADD_ON = 0,
    SUB_ON = 0,
    MULT_ON = 0,
    DIV_ON = 0,
    NOT_ON = 0,
    AND_ON = 0,
    OR_ON  = 0,
    XOR_ON = 0,
    SHL_ON = 1,
    SHR_ON = 1,
    OUT_ON = 0,
    HALT_ON = 0
};

// check if the Opcode is valid and return it hex code if true else return InvalideOpcode
enum OPCODE get_opcode(char* str);

// get string name of enum OPCODE
const char* get_opcode_name(enum OPCODE opcode);

// Convert opcode to hexadecimal string with bounds checking
char* OPCODE_to_hex_string(enum OPCODE opcode);


enum OPCODE_OPRAND_NUMBER opcode_number_of_required_oprand(char* str);

#endif 