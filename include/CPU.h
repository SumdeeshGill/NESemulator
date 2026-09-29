#ifndef CPU_H
#define CPU_H

/*
*   STATUS FLAGS - Descending towards higher sig figs:
*
*   C   Carry
*   Z   Zero
*   I   Interrupt
*   D   Decimal
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

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct BUS BUS;

/*
*   CPU for the NES was based off a modified MOS-6502, specifically the Ricoh 2A03/2A07 family.
*
*   CPU interacts with the bus to communicate with RAM, PPU, etc.
*   2-byte program counter.
*   1-byte accumulator, x-index, and y-index registers.
*   1-byte stack pointer.
*   1-byte status register.
*   1-byte cycle counter. CPU is main clock conductor, PPU timing based off CPU cycles.
*/

typedef struct CPU {
    BUS* bus;

    uint16_t pc;

    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t sp;
    uint8_t status;
    
    uint8_t cycles;

} CPU;


void cpu_init(CPU *cpu, BUS *bus);
void cpu_reset(CPU *cpu);
void cpu_clock(CPU *cpu);
void cpu_set_flag(CPU* cpu, uint8_t flag, bool value);

#endif