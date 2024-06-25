#ifndef OPCODES_H
#define OPCODES_H

void generate_OpcodeHashMap();

// the key is an opcode this getter function is used to verifie if the key is a valid opcode
const char* getOpcode(const char* key);

const char* getOpcodeInHex(const char* key);

int getNumberOfRequiredOprand(const char* key);

int getOprandMaxSize(const char* key);

void freeOpcodeHashMap();
#endif 