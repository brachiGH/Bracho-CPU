# Generates the Control Unit Logic 
ControlUnit_Logic = []

for i in range(2**5):
	ControlUnit_Logic.append("0000")


Fetch = ["PO", "RO", "II"]
Increment_PC = ["INC"]
Instructions = {"ALUoperations":["ACO", "AI"],"BIN":["IOD", "BI"],"CIN":["IOD", "CI"],"LDA":["IOA", "RO", "AI"],"LDB":["IOA", "RO", "BI"],"LDC":["IOA", "RO", "CI"],"STA":["IOA", "AO", "RI"], "BR":["IOA", "PI"],"LR":["IOA", "RO", "LI"],"LR2":["LO", "RO", "AI"],"NOP":[]}
Opcodes = {'0000': 'NOP', '1100': 'LDA', '0001': 'LDB', '0010': 'LDC', '0011': 'BIN', '0100': 'CIN', '0101': 'STA', '0110': 'BR', '1010': 'LR', '1011': 'LR2', '1110': 'ALUoperations'}
MicroInstructionBitCoefficient = {"AO":0, "BO":1, "CO":2, "ACO":3,"IOD":4, "PO":5, "LO":6, "IOA":7, "AI":8, "BI":9, "CI":10, "II":11, "PI":12, "LI":13, "PID":14, "INC":15, "RESET":16, "CinALU":17, "RI":18, "RO":19}

def Generate_Mirco_Code(ListOfMicroInstructions):
	codeInDecimal = 0
	for M in ListOfMicroInstructions:
		codeInDecimal += 2**MicroInstructionBitCoefficient[M]
	CodeInHex = f"{codeInDecimal:04x}"
	return CodeInHex

ControlUnit_Logic[0] = Generate_Mirco_Code(Fetch)
ControlUnit_Logic[1] = Generate_Mirco_Code(Increment_PC)

for address in range(2**4, 2**5):
	opcode = address - 2**4
	opcodebinary = f"{opcode:04b}"
	if opcodebinary in Opcodes:
		ControlUnit_Logic[address] = Generate_Mirco_Code(Instructions[Opcodes[opcodebinary]])

ControlUnit_Logic_string = ""
for code in ControlUnit_Logic:
	ControlUnit_Logic_string += code + " "
	
print(ControlUnit_Logic_string)