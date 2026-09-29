#ifndef BUS_H
#define BUS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct CPU CPU;
typedef struct PPU PPU;
typedef struct APU APU;
typedef struct Cartridge Cartridge;
typedef struct Controller Controller;

/*
*   BUS is used by the primary system components like the CPU, PPU, RAM, etc. to interact.
*   Each component exists in isolation and uses the BUS as its interface to the "outside".
*   Address being written to determines which component is being interacted with, each
*   component has its own address range that it "owns".
*
*   RAM             : 0x0000 - 0x1FFF
*   PPU Registers   : 0x2000 - 0x3FFF
*   APU/controllers : 0x4000 - 0x4017
*   Cartridge/other : 0x4020 - 0xFFFF
*   
*/

typedef struct BUS {
    uint8_t ram[2048];

    CPU *cpu;
    PPU *ppu;
    APU *apu;
    Cartridge *cartridge;

    Controller *controller1;
    Controller *controller2;

} BUS;


uint8_t bus_read(BUS *bus, uint16_t address);
void bus_write(BUS *bus, uint16_t address, uint8_t value);

#endif