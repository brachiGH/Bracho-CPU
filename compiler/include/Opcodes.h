#ifndef OPCODES_H
#define OPCODES_H

void generate_OpcodeHashMap();

const char* getOpcode(const char* key);

const char* getOpcodeInHex(const char* key);

unsigned int getNumberOfRequiredOprand(const char* key);

unsigned int getOprandMaxSize(const char* key);

void freeOpcodeHashMap();
#endif 