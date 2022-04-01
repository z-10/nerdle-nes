#include "globals.h"

#pragma bss-name(push, "ZEROPAGE")
unsigned char globalsGameState;
#pragma bss-name (pop)
unsigned int globalsRandSeed;