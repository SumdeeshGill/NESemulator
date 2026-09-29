#include <stdio.h>

int main () {

    printf("Hello World!\n");

    return 0;
}

/*
    TODO: Implement CPU, PPU, APU, Cartridge & Mapper, Controller, Bus functions.

    Design with controller inputs over UDP in mind, may implement some P2P
    or client-server design at some point with movement prediction to account
    for latency. For now, the goal is the goal a local emulator working.
*/