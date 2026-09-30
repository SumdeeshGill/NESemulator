#include "BUS.h"
#include "CPU.h"


/*
*   Core BUS functions to be expanded later. Currently minimal for 6502 CPU testing.
*/

void bus_init(BUS *bus) {
    *bus = (BUS){0};
};

uint8_t bus_read(BUS *bus, uint16_t address) {
    return bus->ram[address];
};

void bus_write(BUS *bus, uint16_t address, uint8_t value) {
    bus->ram[address] = value;
};