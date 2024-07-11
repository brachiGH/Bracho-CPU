import { ref } from 'vue';
import {praseDisplayOUT} from './display.js';
import "./utilites.js";

export const registers = ref({
    "acc": 0,
    "PC": 0,
    "IR": 0,
    "A": 0,
    "B": 0,
    "C": 0,
    "LR": 0,
    "flags": {
        "overflow": 0,
        "negative": 0,
        "zero": 0
    }
})

export const display = ref(Array.from({ length: 64 }, () => Array(64).fill(0)));

export const PCregister = ref(0);



class brachocpu {
    constructor(RAM) {
        this.RAM = RAM;
        this.acc = 0;
        this.PC = 0;
        this.IR = 0;
        this.A = 0;
        this.B = 0;
        this.C = 0;
        this.LR = 0;
        this.flags = {
            "overflow": 0,
            "negative": 0,
            "zero": 0
        }
    }

    reset() {
        this.RAM = Array(0XFFF).fill("0000");
        this.acc = 0;
        this.PC = 0;
        this.IR = 0;
        this.A = 0;
        this.B = 0;
        this.C = 0;
        this.LR = 0;
        this.flags = {
            "overflow": 0,
            "negative": 0,
            "zero": 0
        }
    }

    load(RAM) {
        this.RAM = RAM;
    }

    incremmentProgramCounter() {
        this.PC++;
        PCregister.value = this.PC;

        if (this.PC > 0xFFE) {
            this.PC = 0;
        }
    }

    getInstruction() {
        this.IR = this.RAM[this.PC];
        return this.IR;
    }

    getValueInAddress(addr) {
        let val = parseInt(this.RAM[addr], 16);
        console.log("LD("+addr+") = ", val, this.RAM[addr]);
        return val;
    }

    updatedRAMcontent(addr, value) {
        console.log("STA("+addr+") => RAM[",addr,"] = ", value, numberToHex2Bytes(value))
        document.getElementById('memCell' + addr).innerText = numberToHex2Bytes(value) + " ";
    }

    restflag() {
        this.flags["negative"] = 0;
        this.flags["overflow"] = 0;
        this.flags["zero"] = 0;
    }

    ADD() {
        this.restflag();
        this.A = this.B + this.C;

        if (this.A > 0xFFFF) {
            this.A = 0xFFFF;
            this.flags["overflow"] = 1;
        }

        if (this.A == 0) {
            this.flags["zero"] = 1;
        }
    }

    SUB() {
        this.restflag();
        this.A = this.B - this.C;

        if (this.A < 0) {
            this.flags["negative"] = 1;
        }

        if (this.A == 0) {
            this.flags["zero"] = 1;
        }
    }

    MULT() {
        this.restflag();
        this.A = this.B * this.C;

        if (this.A > 0xFFFF) {
            this.A = 0xFFFF;
            this.flags["overflow"] = 1;
        }

        if (this.A == 0) {
            this.flags["zero"] = 1;
        }
    }

    DIV() {
        this.restflag();
        if (this.C === 0) {
            throw new Error("Division by zero");
        }
        this.A = Math.floor(this.B / this.C);

        if (this.A == 0) {
            this.flags["zero"] = 1;
        }
    }

    NOT() {
        this.restflag();
        this.A = ~this.A & 0xFFFF; // Assuming A is a 16-bit register

        if (this.A == 0) {
            this.flags["zero"] = 1;
        }
    }

    AND() {
        this.restflag();
        this.A = this.B & this.C;

        if (this.A == 0) {
            this.flags["zero"] = 1;
        }
    }

    OR() {
        this.restflag();
        this.A = this.B | this.C;

        if (this.A == 0) {
            this.flags["zero"] = 1;
        }
    }

    XOR() {
        this.restflag();
        this.A = this.B ^ this.C;

        if (this.A == 0) {
            this.flags["zero"] = 1;
        }
    }

    SHL(value) {
        this.restflag();
        this.A = (this.B << value) & 0xFFFF; // Assuming A and B are 16-bit registers

        if (this.A == 0) {
            this.flags["zero"] = 1;
        }
    }

    SHR(value) {
        this.restflag();
        this.A = this.B >>> value; // Logical right shift

        if (this.A == 0) {
            this.flags["zero"] = 1;
        }
    }



    /* NOTE: that we are calling restflags on evry none arithmatique and none logicale opration 
    even though the bracho cpu does not rest the flags (on none arithmatique and none logicale opration)
    it outs semi-random flags (the flags values depend on the operand first nibble not the opcode, 
        and ofc the values of the B and C registers) */
    LR(address) {
        this.restflag();
        if (address < 0 || address >= 4096) {
            throw new Error("Address out of bounds");
        }
        this.A = this.getValueInAddress(this.getValueInAddress(address) & 0xFFF);
    }

    OUT() {
        this.restflag();
        let a = praseDisplayOUT(this.A);
        console.log(a, this.A)
        display.value[a['y']][a['x']] = a['color'];
    }

    NOP() {
        this.restflag();
        // Do nothing
    }

    HALT() {
        this.restflag();
        // throw new Error("CPU Halted");
    }


    LDA(address) {
        this.restflag();
        if (address < 0 || address >= 4096) {
            throw new Error("Address out of bounds");
        }
        this.A = this.getValueInAddress(address);
    }

    LDB(address) {
        if (address < 0 || address >= 4096) {
            throw new Error("Address out of bounds");
        }
        this.B = this.getValueInAddress(address);
        this.restflag();
    }

    LDC(address) {
        if (address < 0 || address >= 4096) {
            throw new Error("Address out of bounds");
        }
        this.C = this.getValueInAddress(address);
        this.restflag();
    }

    BIN(value) {
        if (value < 0 || value >= 4096) {
            throw new Error("Immediate value out of bounds");
        }
        this.B = value;
        this.restflag();
    }

    CIN(value) {
        this.restflag();
        if (value < 0 || value >= 4096) {
            throw new Error("Immediate value out of bounds");
        }
        this.C = value;
    }

    STA(address) {
        this.restflag();
        if (address < 0 || address >= 4096) {
            throw new Error("Address out of bounds");
        }
        this.RAM[address] =  numberToHex2Bytes(this.A);
        this.updatedRAMcontent(address, this.A);
    }

    BR(address) {
        if (address < 0 || address >= 4096) {
            throw new Error("Address out of bounds");
        }
        this.PC = address;
        this.restflag();
    }

    BRN(address) {
        if (address < 0 || address >= 4096) {
            throw new Error("Address out of bounds");
        }
        if (this.flags["negative"] == 1) {
            this.PC = address;
        }
        this.restflag();
    }

    BRZ(address) {
        if (address < 0 || address >= 4096) {
            throw new Error("Address out of bounds");
        }
        if (this.flags["zero"] == 1) {
            this.PC = address;
        }
        this.restflag();
    }

    BRV(address) {
        if (address < 0 || address >= 4096) {
            throw new Error("Address out of bounds");
        }
        if (this.flags["overflow"] == 1) {
            this.PC = address;
        }
        this.restflag();
    }

    SPC() {
        this.restflag();
        this.LR = this.PC;
    }

    getRAM() {
        return this.RAM;
    }
}


export class controlUnite {
    constructor(clock) {
        this.clock = clock;
        this.instruction = "0000";

        this.cpu = new brachocpu(Array(4096).fill("0000"));
        this.printRegisterState();

        this.SetClock(clock);
        this.isPaused = true;
        this.shouldStop = true;
    }

    load(RAM) {
        this.cpu.load(RAM);
        this.isPaused = true;
        this.shouldStop = true;
    }

    reset() {
        this.cpu.reset();
        display.value = Array.from({ length: 64 }, () => Array(64).fill(0));
    }

    /* clock logique */
    async start() {

        if (this.isPaused) {
            await this.waitForResume();
        }

        this.executeAnInstruction();
        await this.sleep(this.delay);
    }

    async sleep(ms) {
        await new Promise(resolve => setTimeout(resolve, ms));
        if (!this.shouldStop) {
            this.start();
        } else {
            console.log('clock stopped');
        }
    }

    pause() {
        this.isPaused = true;
    }

    resume() {
        this.isPaused = false;
        if (this.resumeCallback) {
            this.resumeCallback();
        }
    }

    stop() {
        this.shouldStop = true;
    }

    SetClock(clk) {
        this.delay = (clk == 0)? 0 : (1 / clk) * 1000;
    }

    waitForResume() {
        return new Promise(resolve => {
            this.resumeCallback = resolve;
        });
    }
    /* clock ends here*/


    executeAnInstruction() { // this function executes only 1 instruction
        let opcode = this.cpu.getInstruction();
        this.cpu.incremmentProgramCounter();

        let operand1 = parseInt(opcode.slice(3,4), 16);
        let operand3 = parseInt(opcode.slice(1,4), 16);      

        if (opcode === "E000") {
            this.cpu.ADD();
        } else if (opcode === "E100") {
            this.cpu.SUB();
        } else if (opcode === "E200") {
            this.cpu.MULT();
        } else if (opcode === "E300") {
            this.cpu.DIV();
        } else if (opcode === "E400") {
            this.cpu.NOT();
        } else if (opcode === "E500") {
            this.cpu.AND();
        } else if (opcode === "E600") {
            this.cpu.OR();
        } else if (opcode === "E700") {
            this.cpuV.XOR();
        } else if (opcode.slice(0, 3) === "E80") {
            this.cpu.SHL(operand1);
        } else if (opcode.slice(0, 3) === "E90") {
            this.cpu.SHR(operand1);
        } else if (opcode.slice(0) === "A") {
            this.cpu.LR(operand3);
        } else if (opcode === "D000") {
            this.cpu.OUT();
        } else if (opcode === "F000") {
            this.stop()
        } else if (opcode.slice(0, 1) === "C") {
            this.cpu.LDA(operand3);
        } else if (opcode.slice(0, 1) === "1") {
            this.cpu.LDB(operand3);
        } else if (opcode.slice(0, 1) === "2") {
            this.cpu.LDC(operand3);
        } else if (opcode.slice(0, 1) === "3") {
            this.cpu.BIN(operand3);
        } else if (opcode.slice(0, 1) === "4") {
            this.cpu.CIN(operand3);
        } else if (opcode.slice(0, 1) === "5") {
            this.cpu.STA(operand3);
        } else if (opcode.slice(0, 1) === "6") {
            this.cpu.BR(operand3);
        } else if (opcode.slice(0, 1) === "7") {
            this.cpu.BRN(operand3);
        } else if (opcode.slice(0, 1) === "8") {
            this.cpu.BRZ(operand3);
        } else if (opcode.slice(0, 1) === "9") {
            this.cpu.BRV(operand3);
        } else if (opcode === "F100") {
            this.cpu.SPC();
        }

        // this.printRegisterState();
        this.updateRegisters();
    }

    next() {
        this.executeAnInstruction();
    }

    previous() { // only last 10

    }

    savesate() {
        /*
         ADD OPTION TO DISABLE THIS BEACUSE IT IS VERY SLOW!
         */
        // constructor(this.RAM, this.acc, this.PC, this.IR, this.A, this.B, this.C, this.LR, this.flags)
    }

    getOpcodeName(opcode) {

        let operand1 = parseInt(opcode.slice(3,4), 16);
        let operand3 = parseInt(opcode.slice(1,4), 16);     
        if (opcode === "E000") {
            return "ADD";
        } else if (opcode === "E100") {
            return "SUB";
        } else if (opcode === "E200") {
            return "MULT";
        } else if (opcode === "E300") {
            return "DIV";
        } else if (opcode === "E400") {
            return "NOT";
        } else if (opcode === "E500") {
            return "AND";
        } else if (opcode === "E600") {
            return "OR";
        } else if (opcode === "E700") {
            return "XOR";
        } else if (opcode.slice(0, 3) === "E80") {
            return `SHL(${operand1})`;
        } else if (opcode.slice(0, 3) === "E90") {
            return `SHR(${operand1})`;
        } else if (opcode.slice(0, 1) === "A") {
            return `LR(${operand3})`;
        } else if (opcode === "D000") {
            return "OUT";
        } else if (opcode === "F000") {
            return "HALT"
        } else if (opcode.slice(0, 1) === "C") {
            return `LDA(${operand3})`;
        } else if (opcode.slice(0, 1) === "1") {
            return `LDB(${operand3})`;
        } else if (opcode.slice(0, 1) === "2") {
            return `LDC(${operand3})`;
        } else if (opcode.slice(0, 1) === "3") {
            return `BIN(${operand3})`;
        } else if (opcode.slice(0, 1) === "4") {
            return `CIN(${operand3})`;
        } else if (opcode.slice(0, 1) === "5") {
            return `STA(${operand3})`;
        } else if (opcode.slice(0, 1) === "6") {
            return `BR(${operand3})`;
        } else if (opcode.slice(0, 1) === "7") {
            return `BRN(${operand3})`;
        } else if (opcode.slice(0, 1) === "8") {
            return `BRZ(${operand3})`;
        } else if (opcode.slice(0, 1) === "9") {
            return `BRV(${operand3})`;
        } else if (opcode === "F100") {
            return "SPC";
        } else if (opcode === "0000") {
            return "NOP";
        }

    }

    updateRegisters() {
        registers.value = {
            "acc":  '0x' + numberToHex2Bytes(this.cpu.acc) + ' | ' +  this.cpu.acc,
            "PC": '0x' + numberToHex2Bytes(this.cpu.PC) + ' | ' +  this.cpu.PC,
            "IR": '0x' + numberToHex2Bytes(this.cpu.IR) + ' | ' +  this.getOpcodeName(this.cpu.IR),
            "A": '0x' + numberToHex2Bytes(this.cpu.A) + ' | ' +  this.cpu.A,
            "B": '0x' + numberToHex2Bytes(this.cpu.B) + ' | ' +  this.cpu.B,
            "C": '0x' + numberToHex2Bytes(this.cpu.C) + ' | ' +  this.cpu.C,
            "LR": '0x' + numberToHex2Bytes(this.cpu.LR) + ' | ' +  this.cpu.LR,
            "flags": {
                "overflow": this.cpu.flags["overflow"],
                "negative": this.cpu.flags["negative"],
                "zero": this.cpu.flags["zero"]
            }
        }
    }

    printRegisterState() {
        console.log("Register State:");
        console.log(`ACC: ${this.cpu.acc}`);
        console.log(`PC: ${this.cpu.PC}`);
        console.log(`IR: ${this.cpu.IR}`);
        console.log(`A: ${this.cpu.A}`);
        console.log(`B: ${this.cpu.B}`);
        console.log(`C: ${this.cpu.C}`);
        console.log(`LR: ${this.cpu.LR}`);
        console.log(`Flags: ${JSON.stringify(this.cpu.flags)}`);
    }
}