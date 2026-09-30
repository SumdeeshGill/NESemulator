#include "CPU.h"
#include "BUS.h"

void cpu_init(CPU *cpu, BUS *bus) {
    *cpu = (CPU){0};

    cpu->bus = bus;
};

void cpu_reset (CPU *cpu) {
    cpu->a = 0;
    cpu->x = 0;
    cpu->y = 0;

    cpu->sp = 0xFD;
    cpu->status = FLAG_I | FLAG_U;

    //
};

static void cpu_set_flag(CPU* cpu, uint8_t flag, bool value) {
    if (value) {
        cpu->status |= flag;
    } else {
        cpu->status &= ~flag;
    }
};

static bool cpu_get_flag(const CPU* cpu, uint8_t flag) {
    return (cpu->status & flag) != 0;
};

static void cpu_set_zn(CPU *cpu, uint8_t value) {
    cpu_set_flag(cpu, FLAG_Z, value == 0);
    cpu_set_flag(cpu, FLAG_N, (value & 0x80) != 0);
};