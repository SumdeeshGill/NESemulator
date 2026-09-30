#ifndef CPU_H
#define CPU_H

/*
*   STATUS FLAGS - Descending towards higher sig figs:
*
*   C   Carry
*   Z   Zero
*   I   Interrupt
*   D   Decimal (Unused)
*   B   Break
*   U   Unused
*   V   Overflow
*   N   Negative
*
*/

#define FLAG_C 0x01
#define FLAG_Z 0x02
#define FLAG_I 0x04
#define FLAG_D 0x08
#define FLAG_B 0x10
#define FLAG_U 0x20
#define FLAG_V 0x40
#define FLAG_N 0x80

#define CPU_OPCODE_COUNT 256

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct BUS BUS;
typedef struct Instruction Instruction;

/*
*   CPU for the NES was based off a modified MOS-6502, specifically the Ricoh 2A03/2A07 family.
*
*   CPU interacts with the bus to communicate with RAM, PPU, etc.
*   2-byte program counter.
*   1-byte accumulator, x-index, and y-index registers.
*   1-byte stack pointer.
*   1-byte status register.
*   1-byte cycle counter. CPU is main clock conductor, PPU timing based off CPU cycles.
*
*   2-byte addr holds operand address.
*   1-byte fetched holds operand.
*/

typedef struct CPU {
    BUS *bus;
    Instruction *instructions;

    uint16_t pc;
    uint16_t addr;

    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t sp;
    uint8_t status;
    uint8_t fetched;

    uint8_t cycles_remaining;
} CPU;

/*
*   Instruction type to be used by instruction and addressing table, allows the emulator to easily
*   track cycles consumed by instruction and minimizes the need to recreate each and every opcode despite
*   many performing the same operation, just on different addressing modes.
*/

typedef uint8_t (*operation_func)(CPU *cpu);
typedef uint8_t (*addressing_func)(CPU *cpu);

typedef struct Instruction {
    addressing_func addressing;
    operation_func operation;
    //
    uint8_t cycles;
} Instruction;

/*
 * Addressing modes:
 *
 * IMP  - Implied
 * IMM  - Immediate
 * ZP0  - Zero Page
 * ZPX  - Zero Page, X
 * ZPY  - Zero Page, Y
 * ABS  - Absolute
 * ABX  - Absolute, X
 * ABY  - Absolute, Y
 * REL  - Relative
 * IND  - Indirect
 * IZX  - Indexed Indirect, X
 * IZY  - Indirect Indexed, Y
 * 
 */

//--------------------------------------------
uint8_t IMP(CPU *cpu); uint8_t IMM(CPU *cpu); 
uint8_t ZP0(CPU *cpu); uint8_t ZPX(CPU *cpu); 
uint8_t ZPY(CPU *cpu); uint8_t ABS(CPU *cpu); 
uint8_t ABX(CPU *cpu); uint8_t ABY(CPU *cpu); 
uint8_t REL(CPU *cpu); uint8_t IND(CPU *cpu); 
uint8_t IZX(CPU *cpu); uint8_t IZY(CPU *cpu); 
//--------------------------------------------


/*
*   Instruction operations:
*   >
*/

//-----------------------------------------------------------------------------------------
uint8_t XXX(CPU *cpu); // catch-all NOP for illegal opcodes (no plans to implement yet).

uint8_t ADC(CPU *cpu); uint8_t CLD(CPU *cpu); uint8_t JSR(CPU *cpu); uint8_t RTS(CPU *cpu); 
uint8_t AND(CPU *cpu); uint8_t CLI(CPU *cpu); uint8_t LDA(CPU *cpu); uint8_t SBC(CPU *cpu); 
uint8_t ASL(CPU *cpu); uint8_t CLV(CPU *cpu); uint8_t LDX(CPU *cpu); uint8_t SEC(CPU *cpu); 
uint8_t BCC(CPU *cpu); uint8_t CMP(CPU *cpu); uint8_t LDY(CPU *cpu); uint8_t SED(CPU *cpu); 
uint8_t BCS(CPU *cpu); uint8_t CPX(CPU *cpu); uint8_t LSR(CPU *cpu); uint8_t SEI(CPU *cpu); 
uint8_t BEQ(CPU *cpu); uint8_t CPY(CPU *cpu); uint8_t NOP(CPU *cpu); uint8_t STA(CPU *cpu); 
uint8_t BIT(CPU *cpu); uint8_t DEC(CPU *cpu); uint8_t ORA(CPU *cpu); uint8_t STX(CPU *cpu); 
uint8_t BMI(CPU *cpu); uint8_t DEX(CPU *cpu); uint8_t PHA(CPU *cpu); uint8_t STY(CPU *cpu); 
uint8_t BNE(CPU *cpu); uint8_t DEY(CPU *cpu); uint8_t PHP(CPU *cpu); uint8_t TAX(CPU *cpu); 
uint8_t BPL(CPU *cpu); uint8_t EOR(CPU *cpu); uint8_t PLA(CPU *cpu); uint8_t TAY(CPU *cpu); 
uint8_t BRK(CPU *cpu); uint8_t INC(CPU *cpu); uint8_t PLP(CPU *cpu); uint8_t TSX(CPU *cpu); 
uint8_t BVC(CPU *cpu); uint8_t INX(CPU *cpu); uint8_t ROL(CPU *cpu); uint8_t TXA(CPU *cpu); 
uint8_t BVS(CPU *cpu); uint8_t INY(CPU *cpu); uint8_t ROR(CPU *cpu); uint8_t TXS(CPU *cpu); 
uint8_t CLC(CPU *cpu); uint8_t JMP(CPU *cpu); uint8_t RTI(CPU *cpu); uint8_t TYA(CPU *cpu); 
//-----------------------------------------------------------------------------------------


void cpu_init(CPU *cpu, BUS *bus, Instruction *instructions);
void cpu_reset(CPU *cpu);
void cpu_instructions_init(Instruction *instructions);
void cpu_step(CPU *cpu);
//void cpu_clock(CPU *cpu);

#endif