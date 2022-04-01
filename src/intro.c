#include "intro.h"
#include "../LIB/nesdoug.h"
#include "../LIB/neslib.h"

#include "globals.h"
#include "palettes.h"
#include "input.h"


const unsigned char INTRO_SCREEN[158]={
0x01,0x00,0x01,0x89,0x2c,0x2d,0x0a,0x0b,0x44,0x45,0x08,0x09,0x28,0x29,0x0a,0x0b,
0x00,0x01,0x13,0x3c,0x3d,0x1a,0x1b,0x54,0x55,0x18,0x19,0x38,0x39,0x1a,0x1b,0x00,
0x01,0x78,0xc2,0xd9,0x00,0x01,0x36,0xd2,0xef,0xed,0xe1,0xee,0x00,0xd3,0xf4,0xe5,
0xf4,0xf3,0xf9,0xf3,0xe8,0xe9,0xee,0x00,0x01,0x6e,0xd3,0xd0,0xc5,0xc3,0xc9,0xc1,
0xcc,0x00,0xd4,0xc8,0xc1,0xce,0xcb,0xd3,0x00,0xd4,0xcf,0xba,0x00,0x01,0x2f,0xc1,
0xec,0xe5,0xf8,0xee,0xe4,0xe5,0xf2,0x00,0xd0,0xf2,0xf5,0xf3,0xf3,0x00,0x01,0x31,
0xc3,0xe1,0xec,0xec,0xe5,0x00,0xd3,0xf6,0xe5,0xee,0xf3,0xf3,0xef,0xee,0x00,0x01,
0x32,0xc4,0xef,0xf5,0xe7,0x00,0xc6,0xf2,0xe1,0xeb,0xe5,0xf2,0x00,0x01,0x94,0xd0,
0xd2,0xc5,0xd3,0xd3,0x00,0x00,0xd3,0xd4,0xc1,0xd2,0xd4,0x00,0x01,0x54,0xf6,0xb1,
0xae,0xb0,0x00,0x00,0xb2,0xb0,0xb2,0xb2,0x00,0x01,0x09,0x00,0x01,0x00
};





void intro_setup()
{
	globalsGameState = GAME_STATE_INTRO;
	ppu_off();
	oam_clear();
	pal_bg(GAME_PALETTES[0]);
	vram_adr(NAMETABLE_A);
	vram_unrle(INTRO_SCREEN);
	pal_bright(0);
	vram_adr(0x23c0);
	vram_fill(0,64);
	vram_adr(0x23ca);
	vram_put(8);
	vram_adr(0x23cb);
	vram_put(9);
	vram_adr(0x23cc);
	vram_put(9);
	vram_adr(0x23cd);
	vram_put(1);
	ppu_on_all();
	pal_fade_to(0,4);
	delay(10);
}

void intro_exit()
{
        pal_fade_to(4,0);
        delay(10);
}



void intro_main_loop()
{
	input_get_new_pad1();
	if(inputPad1 == PAD_START)
	{
		globalsGameState = GAME_STATE_INTRO_TO_GAME;
	}
}


