#include "CPU.h"
#include "BUS.h"


void cpu_init(CPU *cpu, BUS *bus, Instruction *instructions) {
    *cpu = (CPU){0};

    cpu->bus = bus;
    cpu->instructions = instructions;
};

void cpu_reset (CPU *cpu) {
    cpu->a = 0;
    cpu->x = 0;
    cpu->y = 0;

    cpu->sp = 0xFD;
    cpu->status = FLAG_I | FLAG_U;

    //
};

void cpu_instructions_init(Instruction *instructions) {
    // Start with XXX (NOP) initialization to "zero out" the table
    for (int i = 0; i < CPU_OPCODE_COUNT; i++) {
        instructions[i] = (Instruction){
            .operation = XXX,
            .addressing = IMP,
            .cycles = 2
        };
    }
    // TODO next: finish populating this table.
    // TODO next: finish implementing addressing modes.
    // KEEP IN MIND^: cpu_step progresses cpu->pc by 1 byte, addressing modes progress the rest.
    // 
};

void cpu_step(CPU *cpu) {
    uint8_t opcode = bus_read(cpu->bus, cpu->pc++);

    const Instruction *instruction = &cpu->instructions[opcode];
    uint8_t extraCycles1 = instruction->addressing(cpu);
    uint8_t extraCycles2 = instruction->operation(cpu);
    // Add extra cycles using AND operator (the operations return boolean flags
    // rather than integers, based on if the page boundary was crossed.)
    cpu->cycles_remaining = instruction->cycles + (extraCycles1 & extraCycles2);
};


// Helper functions static to this file.
//-----------------------------------------------------------------------
static void cpu_set_flag(CPU *cpu, uint8_t flag, bool value) {
    if (value) {
        cpu->status |= flag;
    } else {
        cpu->status &= ~flag;
    }
};

static bool cpu_get_flag(const CPU *cpu, uint8_t flag) {
    return (cpu->status & flag) != 0;
};

static void cpu_set_zn(CPU *cpu, uint8_t value) {
    cpu_set_flag(cpu, FLAG_Z, value == 0);
    cpu_set_flag(cpu, FLAG_N, (value & 0x80) != 0);
};

//-----------------------------------------------------------------------