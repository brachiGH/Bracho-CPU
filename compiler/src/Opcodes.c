#include "Opcodes.h"
#include "utilites.h"
#include <string.h>
#include <stdlib.h>
#define OPCODE_TABLE_SIZE 32

typedef struct Opcode {
    char* opcode;
    char* opcode_in_hex;
    unsigned int number_of_required_oprand;
    unsigned int oprand_max_size;  // is Nibbles
    struct Opcode* next;
} Opcode;

typedef struct OpcodeHashMap {
    Opcode** table;
} OpcodeHashMap;


static OpcodeHashMap* map;



// hash function that converts a string key into an index for the hash table.
unsigned int hash(const char* opcode) {
    unsigned int hash = 0;
    while (*opcode) {
        hash = (hash << 5) + *opcode++;
    }
    return hash % OPCODE_TABLE_SIZE;
}

// Adds a key-value pair to the hash table. It hashes the key to find the index and inserts the pair at the beginning of the linked list at that index.
void insertOpcode(const char* key, const char* HEX_value, unsigned int number, unsigned int max) {
    unsigned int index = hash(key);
    Opcode* newOpcode = (Opcode*)malloc(sizeof(Opcode));
    newOpcode->opcode = strdup(key);
    newOpcode->opcode_in_hex = strdup(HEX_value);
    newOpcode->number_of_required_oprand = number;
    newOpcode->oprand_max_size = max;
    newOpcode->next = map->table[index];
    map->table[index] = newOpcode;
}


// Function to find an Opcode by its key
Opcode* findOpcode(const char* key) {
    if (map == NULL || key == NULL) {
        return NULL;
    }

    // Convert to upper case
    char *s = (char*)key;
    while (*s) {
        *s = toupper((unsigned char) *s);
        s++;
    }

    unsigned int index = hash(key);
    Opcode* current = map->table[index];

    while (current != NULL) {
        if (strcmp(current->opcode, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Getter functions
const char* getOpcode(const char* key) {
    Opcode* opcode = findOpcode(key);
    if (opcode != NULL) {
        return opcode->opcode;
    }
    return NULL;
}

const char* getOpcodeInHex(const char* key) {
    Opcode* opcode = findOpcode(key);
    if (opcode != NULL) {
        return opcode->opcode_in_hex;
    }
    return NULL;
}

int getNumberOfRequiredOprand(const char* key) {
    Opcode* opcode = findOpcode(key);
    if (opcode != NULL) {
        return opcode->number_of_required_oprand;
    }
    return -1; // Indicates not found or error
}

int getOprandMaxSize(const char* key) {
    Opcode* opcode = findOpcode(key);
    if (opcode != NULL) {
        return opcode->oprand_max_size;
    }
    return -1;
}

void freeOpcodeHashMap() {
    if (map == NULL) {
        return;
    }

    // Iterate through each bucket in the hash table
    for (int i = 0; i < OPCODE_TABLE_SIZE; i++) {
        Opcode* current = map->table[i];

        // Traverse the linked list in the current bucket
        while (current != NULL) {
            Opcode* temp = current;
            current = current->next;

            // Free the allocated strings
            free(temp->opcode);
            free(temp->opcode_in_hex);

            // Free the Opcode structure itself
            free(temp);
        }
    }

    // Free the table array
    free(map->table);
    // Free the OpcodeHashMap structure
    free(map);
}


OpcodeHashMap* createHashMap() {
    OpcodeHashMap* _map = (OpcodeHashMap*)malloc(sizeof(OpcodeHashMap));
    _map->table = (Opcode**)malloc(sizeof(Opcode*) * OPCODE_TABLE_SIZE);
    for (int i = 0; i < OPCODE_TABLE_SIZE; i++) {
        _map->table[i] = NULL;
    }
    return _map;
}

void generate_OpcodeHashMap() {
    map = createHashMap();


    // Insert Opcodes
    // ("OPcode", "HEX repersentation", "1:means their is an oprand", "the length of the oprand")
    insertOpcode("NOP", "0000", 0, 0);
    insertOpcode("LDA", "C", 1, 3);
    insertOpcode("LDB", "1", 1, 3);
    insertOpcode("LDC", "2", 1, 3);
    insertOpcode("BIN", "3", 1, 3);
    insertOpcode("CIN", "4", 1, 3);
    insertOpcode("STA", "5", 1, 3);
    insertOpcode("BR", "6", 1, 3);
    insertOpcode("BRN", "7", 1, 3);
    insertOpcode("BRZ", "8", 1, 3);
    insertOpcode("BRV", "9", 1, 3);
    insertOpcode("LR", "A", 1, 3);
    insertOpcode("ADD", "E000", 0, 0);
    insertOpcode("SUB", "E100", 0, 0);
    insertOpcode("MULT", "E200", 0, 0);
    insertOpcode("DIV", "E300", 0, 0);
    insertOpcode("NOT", "E400", 0, 0);
    insertOpcode("AND", "E500", 0, 0);
    insertOpcode("OR", "E600", 0, 0);
    insertOpcode("XOR", "E700", 0, 0);
    insertOpcode("SHL", "E80", 1, 1);
    insertOpcode("SHR", "E90", 1, 1);
    insertOpcode("OUT", "D000", 0, 0);
    insertOpcode("HALT", "F000", 0, 0);
    insertOpcode("SPC", "F100", 0, 0);
}