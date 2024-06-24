#include "Opcodes.h"
#include "utilites.h"



// check if the Opcode is valid and return it hex code if true else return InvalideOpcode
enum OPCODE get_opcode(char* str) {
    to_uppercase(str);
    if (strcmp(str, "NOP") == 0) {
        return NOP;
    }
    else if (strcmp(str, "LDA") == 0) {
        return LDA;
    }
    else if (strcmp(str, "LDB") == 0) {
        return LDB;
    }
    else if (strcmp(str, "LDC") == 0) {
        return LDC;
    }
    else if (strcmp(str, "BIN") == 0) {
        return BIN;
    }
    else if (strcmp(str, "CIN") == 0) {
        return CIN;
    }
    else if (strcmp(str, "STA") == 0) {
        return STA;
    }
    else if (strcmp(str, "BR") == 0) {
        return BR;
    }
    else if (strcmp(str, "BRN") == 0) {
        return BRN;
    }
    else if (strcmp(str, "BRZ") == 0) {
        return BRZ;
    }
    else if (strcmp(str, "BRV") == 0) {
        return BRV;
    }
    else if (strcmp(str, "LR") == 0) {
        return LR;
    }
    else if (strcmp(str, "ADD") == 0) {
        return ADD;
    }
    else if (strcmp(str, "SUB") == 0) {
        return SUB;
    }
    else if (strcmp(str, "MULT") == 0) {
        return MULT;
    }
    else if (strcmp(str, "DIV") == 0) {
        return DIV;
    }
    else if (strcmp(str, "NOT") == 0) {
        return NOT;
    }
    else if (strcmp(str, "AND") == 0) {
        return AND;
    }
    else if (strcmp(str, "OR") == 0) {
        return OR;
    }
    else if (strcmp(str, "XOR") == 0) {
        return XOR;
    }
    else if (strcmp(str, "SHL") == 0) {
        return SHL;
    }
    else if (strcmp(str, "SHR") == 0) {
        return SHR;
    }
    else if (strcmp(str, "OUT") == 0) {
        return OUT;
    }
    else if (strcmp(str, "HALT") == 0) {
        return HALT;
    }
    else {
        return InvalideOpcode;
    }
}

// get string name of enum OPCODE
const char* get_opcode_name(enum OPCODE opcode) {
    switch (opcode) {
        case NOP: return "NOP";
        case LDA: return "LDA";
        case LDB: return "LDB";
        case LDC: return "LDC";
        case BIN: return "BIN";
        case CIN: return "CIN";
        case STA: return "STA";
        case BR:  return "BR";
        case BRN: return "BRN";
        case BRZ: return "BRZ";
        case BRV: return "BRV";
        case LR:  return "LR";
        case ADD: return "ADD";
        case SUB: return "SUB";
        case MULT: return "MULT";
        case DIV: return "DIV";
        case NOT: return "NOT";
        case AND: return "AND";
        case OR:  return "OR";
        case XOR: return "XOR";
        case SHL: return "SHL";
        case SHR: return "SHR";
        case OUT: return "OUT";
        case HALT: return "HALT";
        default: return "UnknownOpcode";
    }
}

// Convert opcode to hexadecimal string with bounds checking
char* OPCODE_to_hex_string(enum OPCODE opcode) {
    switch (opcode) {
        case NOP: return "0FFF";
        case LDA: return "C";
        case LDB: return "1";
        case LDC: return "2";
        case BIN: return "3";
        case CIN: return "4";
        case STA: return "5";
        case BR:  return "6";
        case BRN: return "7";
        case BRZ: return "8";
        case BRV: return "9";
        case LR:  return "A";
        case ADD: return "E0FF";
        case SUB: return "E1FF";
        case MULT: return "E2FF";
        case DIV: return "E3FF";
        case NOT: return "E4FF";
        case AND: return "E5FF";
        case OR:  return "E6FF";
        case XOR: return "E7FF";
        case SHL: return "E8FF";
        case SHR: return "E9FF";
        case OUT: return "DFFF";
        case HALT: return "FFFF";
        default: return "NULL";
    }
}

// opcode_number_of_required_oprand
enum OPCODE_OPRAND_NUMBER opcode_number_of_required_oprand(char* str) {
    
    to_uppercase(str);
    if (strcmp(str, "NOP") == 0) {
        return NOP_ON;
    }
    else if (strcmp(str, "LDA") == 0) {
        return LDA_ON;
    }
    else if (strcmp(str, "LDB") == 0) {
        return LDB_ON;
    }
    else if (strcmp(str, "LDC") == 0) {
        return LDC_ON;
    }
    else if (strcmp(str, "BIN") == 0) {
        return BIN_ON;
    }
    else if (strcmp(str, "CIN") == 0) {
        return CIN_ON;
    }
    else if (strcmp(str, "STA") == 0) {
        return STA_ON;
    }
    else if (strcmp(str, "BR") == 0) {
        return BR_ON;
    }
    else if (strcmp(str, "BRN") == 0) {
        return BRN_ON;
    }
    else if (strcmp(str, "BRZ") == 0) {
        return BRZ_ON;
    }
    else if (strcmp(str, "BRV") == 0) {
        return BRV_ON;
    }
    else if (strcmp(str, "LR") == 0) {
        return LR_ON;
    }
    else if (strcmp(str, "ADD") == 0) {
        return ADD_ON;
    }
    else if (strcmp(str, "SUB") == 0) {
        return SUB_ON;
    }
    else if (strcmp(str, "MULT") == 0) {
        return MULT_ON;
    }
    else if (strcmp(str, "DIV") == 0) {
        return DIV_ON;
    }
    else if (strcmp(str, "NOT") == 0) {
        return NOT_ON;
    }
    else if (strcmp(str, "AND") == 0) {
        return AND_ON;
    }
    else if (strcmp(str, "OR") == 0) {
        return OR_ON;
    }
    else if (strcmp(str, "XOR") == 0) {
        return XOR_ON;
    }
    else if (strcmp(str, "SHL") == 0) {
        return SHL_ON;
    }
    else if (strcmp(str, "SHR") == 0) {
        return SHR_ON;
    }
    else if (strcmp(str, "OUT") == 0) {
        return OUT_ON;
    }
    else if (strcmp(str, "HALT") == 0) {
        return HALT_ON;
    }
}