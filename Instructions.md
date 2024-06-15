NOP                     : No Operation (can be used as compare opration because the ALU does the compare opration every clock cycle. So any operation will also update the compare flags)
AND                     : REG_A <= REG_B AND REG_C
OR                      : REG_A <= REG_B OR REG_C
XOR                     : REG_A <= REG_B XOR REG_C
NOT                     : REG_A <= NOT(REG_B)
ADD                     : REG_A <= REG_B + REG_C [overflow]
SUB                     : REG_A <= REG_B - REG_C [NO overflow e.g. 3-(-32768)=32765]
MULT                    : REG_A <= REG_B * REG_C
DIV                     : REG_A <= REG_B / REG_C (the resulat is 0 in the case the division by zero) [overflow]
LDA #value              : load immediate value to REG_A [value should be between -2048 and 2048]
LDB #value              : load immediate value to REG_B (we can remove this and use swap to fill them)
LDC #value              : load immediate value to REG_C (we can remove this and use swap to fill them)
AIN [REG_B]|<offset>    : Load data from the given address into register A [offset should be between 0 and 512]
BIN [REG_A]|<offset>    : 
STA [REG_B]|<offset>    :
STB [REG_A]|<offset>    :
STC [REG_A]|<offset>    :
PCR                     : Get the current program counter value and put it into register A
LDWB                    : Load value directly after counter into register B and advance program counter by 2
SHL                     : left shift the register B value by the value in resgister C store value in register A
SHR                     : left right the register B value by the value in resgister C store value in register A
SWAB                    : Swap the values of register A and B (overwrite register C)
SWAC                    : Swap the values of register A and C (overwrite register B)
SWBC                    : Swap the values of register B and C (overwrite register A)
LD                      : Load the value at the current address of Program counter register and store the value in the instruction Register and advance program counter by 2
BR                      : Branch to the addres of register A
BRN                     : Branch to the addres of register A if the negative flag is on
BRZ                     : Branch to the addres of register A if the zero flag is on
BRV                     : Branch to the addres of register A if the overflow flag is on