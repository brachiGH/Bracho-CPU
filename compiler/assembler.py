#!/usr/bin/python3

Opcodes = {'NOP': '0', 'LDB': '0001', 'LDC': '0010', 'BIN': '0011', 'CIN': '0100', 'STA': '0101', 'BR': '0110', 'LR': '1010', 'LR2': '1011000000000000', 'ADD': '1110000000000000', 'SUB': '1110000100000000', 'MULT': '1110001000000000', 'DIV': '1110001100000000', 'NOT': '1110010000000000', 'AND': '1110010100000000', 'OR': '1110011000000000', 'XOR': '1110011100000000', 'SHL': '111010000000', 'SHR': '111010010000', 'OUT': '1101000000000000', 'HALT': '1111000000000000', 'BRN': '0111', 'BRZ': '1000', 'BRV': '1001', 'LDA':'1100'}


def binary_to_hex(binary_num):
    decimal_num = int(binary_num, 2)
    hex_num = hex(decimal_num)
    return hex_num[2:]

def convert_to_hex(string, length):
    if (string[0:2] == "0x"):
        hex_number = string[2:]
    else:
        if not string.isdigit():
            raise ValueError(":The input ["+string+"] contains non-numeric characters.")
        
        number = int(string)
        hex_number = hex(number)[2:]  # Convert to hex and remove the '0x' prefix

    if len(hex_number) > length:
        raise ValueError(":The input ["+string+"] is Bigger then 0x"+"F"*length)
    
    # Pad with leading zeros to the specified length
    padded_hex = hex_number.zfill(length)
    
    return padded_hex

def store_addresses(code):
    addresses = {}

    lines = []
    for line in code.split('\n'):
        if line and line[0] != "#" and line[0] != " ":
            lines.append(line)
    
    for line_number, line in enumerate(lines, start=1):
        words = line.split()
        if words and words[0].startswith('@'):
            word = words.pop(0)
            if word in addresses:
                addresses[word].append(line_number)
            else:
                addresses[word] = str(line_number)
        
        # Reconstruct the line without the removed word
        lines[line_number - 1] = ' '.join(words)
    
    return addresses, "\n".join(lines)


def printInstructions(code, asm):
    i = 0
    codeInstructions = code.strip().split("\n")
    for instruction in asm.split(' ')[1:len(codeInstructions)+1]:
        print("[@"+convert_to_hex(str(i+1), 4)+"]: "+instruction+" "+codeInstructions[i])
        i += 1



def assemble(code, addresses):
    asm="0 "
    opcodehex = ""
    for line in code.strip().split("\n"):
        print("[assembling instruction]:"+line)
        for opcode in line.split():
            if (opcode[0] == '#'):
                break
            elif (opcode[0] == '@'):
                asm += convert_to_hex(addresses[opcode], 4-len(opcodehex))
                continue
            if opcode in Opcodes:
                opcodehex = binary_to_hex(Opcodes[opcode])
                asm += opcodehex
            else:
                asm += convert_to_hex(opcode, 4-len(opcodehex))
        
        print("[assembled instruction]:"+asm[-4:])
        asm += " "
        opcodehex = "" #rest the opcode
    return asm



if __name__ == '__main__':
    from sys import argv

    if len(argv) == 2:
        codePath = argv[1]

        f = open(codePath,'r')
        code = f.read()
        f.close()


        addresses, code = store_addresses(code)
        print(addresses)
        asm = assemble(code, addresses)
        printInstructions(code, asm)
        
        
        f = open(codePath+".bin",'w')
        f.write(asm)
        f.close()

        print("\n\n[Binary file]: "+ codePath+".bin")
    else:
        print("wrong number of arguments")

