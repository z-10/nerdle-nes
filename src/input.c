#include "input.h"

#include "../LIB/nesdoug.h"
#include "../LIB/neslib.h"

#pragma bss-name(push, "ZEROPAGE")
unsigned char inputPad1;
#pragma bss-name (pop)


void input_get_new_pad1()
{
	inputPad1 = pad_poll(0);
	inputPad1 = get_pad_new(0);
}