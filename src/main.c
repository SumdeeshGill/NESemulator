#include "BUS.h"
#include "CPU.h"

int main () {

    Instruction instructions[CPU_OPCODE_COUNT];
    cpu_instructions_init(instructions);

    BUS bus;
    bus_init(&bus);

    CPU cpu;
    cpu_init(&cpu, &bus, instructions);

    bus.cpu = &cpu;

    return 0;
}

/*
    TODO: Implement CPU, PPU, APU, Cartridge & Mapper, Controller, Bus functions.

    Design with controller inputs over UDP in mind, may implement some P2P
    or client-server design at some point with movement prediction to account
    for latency. For now, the goal is the goal a local emulator working.
*/