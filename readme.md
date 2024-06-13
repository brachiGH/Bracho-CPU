# Discription
A personnel project aims to develop a 16-bit CPU by the end of this summer, accompanied by the creation of an emulator to run pong on it.

# Notes
[click here](https://brachigh.github.io/Bracho-CPU/)

# Design

## Bus
![alt text](https://github.com/brachiGH/Bracho-CPU/blob/main/Components/asset/images/bus-bg.svg?raw=true)

![alt text](https://github.com/brachiGH/Bracho-CPU/blob/main/Components/asset/images/RegisterBank.svg?raw=true)

## ALU
![alt text](https://github.com/brachiGH/Bracho-CPU/blob/main/Components/asset/images/ALU.svg?raw=true)

# Instruction set
```rust
NOP                     : No Operation
OUT                     : forward the value stored in A register to display 
AND                     : REG_A < = REG_B AND REG_C
OR                      : REG_A < = REG_B OR REG_C
XOR                     : REG_A < = REG_B XOR REG_C
NOT                     : REG_A < = NOT(REG_B)
ADD                     : REG_A < = REG_B + REG_C
SUB                     : REG_A < = REG_B - REG_C
MULT                    : REG_A < = REG_B * REG_C
DIV                     : REG_A < = REG_B / REG_C
SHR <value>             : Right shift the register B value by <value>
SHL <value>             : Left shift the register B value by <value>
LDB #value              : Load immediate value to REG_B [value should be between 0 and 4095]
LDC #value              : Load immediate value to REG_C 
BIN <offset>            : Load data from the given address into register B
CIN <offset>            :
STA <offset>            :
BR <address>            : Branch to <address> (Set the current program counter)
BRN                     : Branch to <address> if the negative flag is on
BRZ                     : Branch to <address> if the zero flag is on
BRV                     : Branch to <address> if the overflow flag is on
```
[The Instruction Set In More Detail](https://brachigh.github.io/Bracho-CPU/bracho-cpu/components/alu/the-instruction-set.html)