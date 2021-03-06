#include "../LIB/nesdoug.h"
#include "../LIB/neslib.h"

#include "globals.h"
#include "palettes.h"
#include "input.h"

#include "../words_db/support_words.h"
#include "../words_db/win_words.h"


#pragma bss-name(push, "ZEROPAGE")
unsigned char innerVar1, innerVar2, innerVar3, innerVar4;
unsigned char outVar1;
unsigned char param1, param2, param3;
unsigned char loopVar1, loopVar2;
long longVar1, longVar2, longVar3;

unsigned char cursor_position_x;
unsigned char cursor_position_y;
unsigned char current_action = 0;
unsigned char previous_action = 0;
unsigned char current_letter = 0;
unsigned char current_guess = 0;
unsigned char guess_word_array[5]="\0\0\0\0\0";
unsigned char picked_word_array[5]="\0\0\0\0\0";
int address;
unsigned char attr_table_copy[64];


unsigned char* start_offset = WIN_WORDS_A;
unsigned long current_word = 0;
unsigned int current_word_index = 0;

#pragma bss-name (pop)


const unsigned char LETTERS_LAYOUT_X[27] = {
176,192,208,224,240,
176,192,208,224,240,
176,192,208,224,240,
176,192,208,224,240,
176,192,208,224,240,
240,176
};

const unsigned char LETTERS_LAYOUT_Y[27] = {
32,32,32,32,32,
64,64,64,64,64,
96,96,96,96,96,
128,128,128,128,128,
160,160,160,160,160,
192,192
};

const unsigned char LETTER_LAYOUT_PALETTE_BYTE[27] = {
0x0D, 0x0E, 0x0E, 0x0F, 0x0F,
0x15, 0x16, 0x16, 0x17, 0x17,
0x1D, 0x1E, 0x1E, 0x1F, 0x1F,
0x25, 0x26, 0x26, 0x27, 0x27,
0x2D, 0x2E, 0x2E, 0x2F, 0x2F,
0x36, 0x35
};

const unsigned char LETTER_LAYOUT_PALETTE_INDEX[27] = {
1, 0, 1, 0, 1, 
1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 
1, 0, 1, 0, 1,
1, 0, 1, 0, 1, 
1, 1
};

const unsigned char WORDS_LAYPOUT_PALETTE_BYTE[6][5] = {
{0x08, 0x09, 0x0A, 0x0B, 0x0C},
{0x10, 0x11, 0x12, 0x13, 0x14},
{0x18, 0x19, 0x1A, 0x1B, 0x1C},
{0x20, 0x21, 0x22, 0x23, 0x24},
{0x28, 0x29, 0x2A, 0x2B, 0x2C},
{0x30, 0x31, 0x32, 0x33, 0x34},
};


const unsigned char WORDS_LAYOUT_X[6] = {
2, 6, 10, 14, 18, 22
};

const unsigned char WORDS_LAYOUT_Y[7] = {
4, 8, 12, 16, 20, 24, 24
};

const unsigned char LETTER_GFX[28] = {
0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,
0x20,0x22,0x24,0x26,0x28,0x2A,0x2C,0x2E,
0x40,0x42,0x44,0x46,0x48,0x4A,0x4C,0x4E,
0x60,0x62,0x64,0x6A,0
};


const unsigned char CLEAR_MASK[4] = {0xFC, 0xF3, 0xCF, 0x3F};
const unsigned char PAL_MASK[4][5] =
{
 {0, 0, 0, 0, 0},
 {1, 4, 0x10, 0x40, 0x55},
 {2, 8, 0x20, 0x80, 0xAA},
 {3, 0x0C, 0x30, 0xC0,0xFF}
};




const unsigned char GAME_SCREEN[747]={
0x01,0x00,0x01,0x28,0xc7,0xd5,0xc5,0xd3,0xd3,0x00,0xd4,0xc8,0xc5,0x00,0xd7,0xcf,
0xd2,0xc4,0x00,0x01,0x29,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x79,0x67,0x67,
0x78,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x00,0x01,0x0b,0x77,0x00,0x00,0x76,
0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,
0x00,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x00,0x77,0x00,0x00,0x76,
0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,
0x00,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x00,0x69,0x66,0x66,0x68,
0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,
0x00,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,0x00,0x79,0x67,0x67,0x78,
0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,
0x00,0x01,0x0b,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,
0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x00,0x0c,0x0d,0x0e,0x0f,0x20,0x21,0x22,0x23,
0x24,0x25,0x00,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,
0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x00,0x1c,0x1d,0x1e,0x1f,0x30,0x31,0x32,0x33,
0x34,0x35,0x00,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x69,
0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x00,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,
0x6e,0x6f,0x00,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x79,
0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x00,0x01,0x0b,0x77,0x00,0x00,0x76,0x77,0x00,
0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x00,0x26,
0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x00,0x77,0x00,0x00,0x76,0x77,0x00,
0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x00,0x36,
0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x00,0x69,0x66,0x66,0x68,0x69,0x66,
0x66,0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x00,0x6e,
0x6f,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,0x00,0x79,0x67,0x67,0x78,0x79,0x67,
0x67,0x78,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x00,0x01,
0x0b,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,
0x76,0x77,0x00,0x00,0x76,0x00,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,
0x00,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,
0x76,0x77,0x00,0x00,0x76,0x00,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,
0x00,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,
0x68,0x69,0x66,0x66,0x68,0x00,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,
0x00,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x79,0x67,0x67,
0x78,0x79,0x67,0x67,0x78,0x00,0x01,0x0b,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,
0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x00,0x4a,0x4b,0x4c,
0x4d,0x4e,0x4f,0x60,0x61,0x62,0x63,0x00,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,
0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x00,0x5a,0x5b,0x5c,
0x5d,0x5e,0x5f,0x70,0x71,0x72,0x73,0x00,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,
0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x00,0x6e,0x6f,0x6e,
0x6f,0x6e,0x6f,0x6e,0x6f,0x6e,0x6f,0x00,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,
0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x79,0x67,0x67,0x78,0x00,0x01,0x0b,0x77,
0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,
0x00,0x00,0x76,0x00,0x82,0x84,0x01,0x04,0x83,0x00,0x64,0x65,0x00,0x77,0x00,0x00,
0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,0x76,0x77,0x00,0x00,
0x76,0x00,0x94,0x86,0x96,0x01,0x02,0x97,0x95,0x00,0x74,0x75,0x00,0x69,0x66,0x66,
0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,0x68,0x69,0x66,0x66,
0x68,0x00,0x92,0x85,0x01,0x04,0x93,0x00,0x6e,0x6f,0x00,0x00,0xc1,0xd4,0xd4,0xc5,
0xcd,0xd0,0xd4,0xba,0xb1,0x00,0x01,0x53,0x00,0x01,0x00
};



const unsigned char PRESS_START[12]={
	0xd0,0xd2,0xc5,0xd3,0xd3,0x00,0x00,0xd3,0xd4,0xc1,0xd2,0xd4
};

const unsigned char YOU_WON[10]={
	0xd9,0xcf,0xd5,0x00,0xd7,0xcf,0xce,0xa1,0xa1,0xa1
};

const unsigned char YOU_LOST[10]={
	0xd9,0xcf,0xd5,0x00,0xcc,0xcf,0xd3,0xd4,0x00,0x00
};





const unsigned char CURSOR[]={
	  0,  0,0x80,0,
	  8,  0,0x81,0,
	  0,  8,0x90,0,
	  8,  8,0x91,0,
	128
};

const unsigned char CURSOR_BIG[]={
	  0,  0,0x80,0,
	  48,  0,0x81,0,
	  0,  16,0x90,0,
	  48, 16,0x91,0,
	128
};



void game_setup()
{
	globalsGameState = GAME_STATE_GAME;
	ppu_off();
	set_rand(globalsRandSeed);
	memfill(attr_table_copy, 0, 64);
	pal_bg(GAME_PALETTES[0]);
	pal_spr(GAME_PALETTES[0]);
	vram_adr(NAMETABLE_A);
	vram_unrle(GAME_SCREEN);
	vram_adr(0x23c0);
	vram_fill(0,64);
	current_action = rand8() % 26;
	current_word = 0;
	current_word_index = 0;
	start_offset = WIN_WORDS_A;

	cursor_position_x = LETTERS_LAYOUT_X[current_action];
	cursor_position_y = LETTERS_LAYOUT_Y[current_action];
	pal_bright(0);
	ppu_on_all();
	pal_fade_to(0,4);
	delay(10);

}

void set_palette_for_letter()
{
	innerVar1 = attr_table_copy[LETTER_LAYOUT_PALETTE_BYTE[param1]];
	innerVar1 = innerVar1 & CLEAR_MASK[LETTER_LAYOUT_PALETTE_INDEX[param1]];
	innerVar1 = innerVar1 | PAL_MASK[param2][LETTER_LAYOUT_PALETTE_INDEX[param1]];
	address = (0x23C0 + LETTER_LAYOUT_PALETTE_BYTE[param1]);
	one_vram_buffer(innerVar1, address);
	attr_table_copy[LETTER_LAYOUT_PALETTE_BYTE[param1]] = innerVar1;
}

void set_palette_for_guess()
{
	innerVar2 = WORDS_LAYPOUT_PALETTE_BYTE[param1][param2];
	innerVar1 = attr_table_copy[innerVar2];
	innerVar1 = innerVar1 & CLEAR_MASK[1];
	innerVar1 = innerVar1 | PAL_MASK[param3][1];
	address = (0x23C0 + innerVar2);
	one_vram_buffer(innerVar1, address);
	attr_table_copy[innerVar2] = innerVar1;
}
void set_palette_for_enter()
{
	one_vram_buffer(PAL_MASK[param2][4], 0x23F5);
	one_vram_buffer(PAL_MASK[param2][4], 0x23F6);
	innerVar1 = attr_table_copy[0x37];
	innerVar1 = innerVar1 & CLEAR_MASK[0];
	innerVar1 = innerVar1 & CLEAR_MASK[2];
	innerVar1 = innerVar1 | PAL_MASK[param2][0];
	innerVar1 = innerVar1 | PAL_MASK[param2][2];
	one_vram_buffer(innerVar1, 0x23F7);
	attr_table_copy[innerVar2] = innerVar1;
}



void read_next_word()
{
	innerVar3 = 0;
	do
	{
		innerVar1 = *start_offset;
		longVar2 = innerVar1 & 0x7F;
		innerVar2 = innerVar1 & 0x80;
		longVar1 = longVar2 << (innerVar3 * 7);
		current_word += longVar1;	
		start_offset +=1;
		innerVar3 +=1;
        } while (innerVar2 > 0);
}

void decode_current_word() {

	for(loopVar1 = 0; loopVar1 < 5; ++loopVar1)
	{	
		picked_word_array[loopVar1] = 0;
	}

	longVar1 = current_word;
	innerVar1 = 0;
	while(longVar1 > 0) 
	{
		innerVar2 = longVar1 % 26;
		picked_word_array[4 - innerVar1] = innerVar2;
		longVar1 /= 26;
		innerVar1++;
	}
}

void validate_guessed_word()
{	
	longVar3 = 0;
	for(loopVar1 = 1; loopVar1 < 5; ++loopVar1)
	{
		longVar2 = guess_word_array[5 - loopVar1];
		for(loopVar2 = 0; loopVar2 < loopVar1 - 1; ++loopVar2)
		{
			longVar2 *= 26;
		}
		longVar3 += longVar2;	
	}
	outVar1 = 0;

	current_word = 0;
	start_offset = WIN_WORDS_START[guess_word_array[0]];
	current_word_index = 0;
	while(current_word_index < WIN_WORDS_SIZE[guess_word_array[0]] && current_word < longVar3)
	{
		read_next_word();
		if(current_word == longVar3)
		{
			outVar1 = 1;
			return;
		}
		current_word_index +=1;
	}

	current_word = 0;
	start_offset = SUPPORT_WORDS_START[guess_word_array[0]];
	current_word_index = 0;
	while(current_word_index < SUPPORT_WORDS_SIZE[guess_word_array[0]] && current_word < longVar3)
	{
		read_next_word();
		if(current_word == longVar3)
		{
			outVar1 = 1;
			return;
		}
		current_word_index +=1;
	}
}

void mark_letters_in_guess()
{
	for(loopVar1 = 0; loopVar1 < 5; ++loopVar1)
	{
		param1 = current_guess;
		param2 = loopVar1;
		param3 = 1;
		for(loopVar2 = 0; loopVar2 < 5; ++loopVar2)
		{
			if(guess_word_array[loopVar1] == picked_word_array[loopVar2])
			{
				if(loopVar1 == loopVar2)
				{
					param3 = 2;
					break;
				}
				else
				{
					param3 = 3;
				}	
			}
		}
		set_palette_for_guess();
		param1 = guess_word_array[loopVar1];
		param2 = param3;
                set_palette_for_letter();
		one_vram_buffer(guess_word_array[loopVar1],NTADR_A(loopVar1,0));
	}
}

void pick_random_word()
{
	set_rand(globalsRandSeed);
	do
	{
		innerVar4 = rand8() % 26;

	} 
	while(WIN_WORDS_SIZE[innerVar4] < 1);

	param2 = rand8() % WIN_WORDS_SIZE[innerVar4];
	param1 = 1;
	current_word = 0;
	start_offset = WIN_WORDS_START[innerVar4];
	read_next_word();
	for(loopVar2 = 0; loopVar2 < param2; loopVar2++)
	{
		read_next_word();
	}
	decode_current_word();
	picked_word_array[0] = innerVar4;
}

/*
void debug_picked_word()
{
	for(loopVar1 = 0;loopVar1 < 5; ++loopVar1)
	{	
		one_vram_buffer(picked_word_array[loopVar1] + 0xC1, NTADR_A(loopVar1, 28));
	}
}
*/

void update_letter_gfx()
{
	address = NTADR_A(WORDS_LAYOUT_X[param1], WORDS_LAYOUT_Y[param2]);
	one_vram_buffer(LETTER_GFX[param3],address);

	address = NTADR_A(WORDS_LAYOUT_X[param1]+1, WORDS_LAYOUT_Y[param2]);
	one_vram_buffer(LETTER_GFX[param3]+1,address);

	address = NTADR_A(WORDS_LAYOUT_X[param1], WORDS_LAYOUT_Y[param2]+1);
	one_vram_buffer(LETTER_GFX[param3]+0x10,address);

	address = NTADR_A(WORDS_LAYOUT_X[param1]+1, WORDS_LAYOUT_Y[param2]+1);
	one_vram_buffer(LETTER_GFX[param3]+0x11,address);

}

void print_win_message()
{
	multi_vram_buffer_horz(YOU_WON, 10, NTADR_A(2,27));
	multi_vram_buffer_horz(PRESS_START, 12, NTADR_A(13,27));
}

void print_lose_message()
{
	multi_vram_buffer_horz(YOU_LOST, 10, NTADR_A(2,27));
	multi_vram_buffer_horz(PRESS_START, 12, NTADR_A(13,27));
}



void calc_current_action()
{
	input_get_new_pad1();
/*
	if(inputPad1 & PAD_SELECT)
	{
		debug_picked_word();
	}
*/
	if(inputPad1 & PAD_B)
	{
		if(current_letter > 0)
		{
			current_letter -= 1;
			guess_word_array[current_letter]=0;				
			param1 = current_letter;
			param2 = current_guess;
			param3 = 27;
			update_letter_gfx();
			if(current_letter == 4)
			{
				param2 = 0;
				set_palette_for_enter();		
			}
		}
	}

	if(inputPad1 & PAD_A)
	{
		if(picked_word_array[0] == 0)
		{
			pick_random_word();
		}
	
		if(current_action < 26)
		{
			if(current_letter < 5)
			{
				guess_word_array[current_letter]=current_action;

				param1 = current_letter;
				param2 = current_guess;
				param3 = current_action;
				update_letter_gfx();
				current_letter+=1;
			}
			
		}

		if(current_action == 26)
		{
			if(current_letter == 5 && current_guess < 6)
			{
				validate_guessed_word();
				if(outVar1 == 1)
				{
					mark_letters_in_guess();
					innerVar1 = 1;
					for(loopVar1 = 0; loopVar1 < 5; ++loopVar1)
					{
						if(picked_word_array[loopVar1] != guess_word_array[loopVar1])
						{
							innerVar1 = 0;
							break;
						}
					}
					if(innerVar1 == 1)
					{
						print_win_message();
						globalsGameState = GAME_STATE_END;
						return;
					}

					current_guess += 1;
					current_letter = 0;
					param2 = 0;
					set_palette_for_enter();		
					if(current_guess > 5)
					{
						print_lose_message();
						globalsGameState = GAME_STATE_END;
						return;
					}
					one_vram_buffer(0xB0+current_guess+1, NTADR_A(10,27));
				}
				else
				{
					param2 = 1;
					set_palette_for_enter();		
				}
			
			}
		}

		cursor_position_x = LETTERS_LAYOUT_X[current_action];
		cursor_position_y = LETTERS_LAYOUT_Y[current_action];
		return;	
	}

	innerVar1 = current_action / 5;
	innerVar2 = current_action % 5;
	innerVar3 = innerVar1;
	innerVar4 = innerVar2;
	if(inputPad1 & PAD_RIGHT)
	{
		previous_action = current_action;
		globalsRandSeed +=1;
		if(innerVar1 < 5)
		{		
			innerVar4 = innerVar2 == 4 ? 0 : innerVar2+1;
		}
		else
		{
			if(innerVar2 == 0)
			{
				previous_action = 20;				
				innerVar4 = 1;
			}
			if(innerVar2 == 1) innerVar4 = 0;
		}
	}
	if(inputPad1 & PAD_LEFT)
	{
		globalsRandSeed +=1;
		if(innerVar1 < 5)
		{		
			innerVar4 = innerVar2 == 0 ? 4 : innerVar4-1;
		}                                                                                      
		else
		{
			if(innerVar2 == 0) 
			{
				previous_action = 23;
				innerVar4 = 1;
			}
			if(innerVar2 == 1) innerVar4 = 0;
		}
	}
	if(inputPad1 & PAD_UP)
	{
		globalsRandSeed +=1;
		if(innerVar1 > 0)
		{		
			innerVar3 = innerVar1-1;

			if(innerVar1 == 5)
			{
				if (innerVar2 == 0) {innerVar4 = 4;}
				if (innerVar2 == 1) 
				{
					innerVar4 = previous_action == 25 ? 3 : previous_action % 5;
				}
			}
		}
		else
		{
			innerVar3 = 5;
			innerVar4 = innerVar2 == 4 ? 0 : 1;
 			previous_action = current_action;
		}
	}
	if(inputPad1 & PAD_DOWN)
	{
		globalsRandSeed +=1;
		if(innerVar1 < 4)
		{		
			innerVar3 = innerVar1+1;
		}
		else
		{
			if(innerVar1 == 4)
			{
				innerVar3 = 5;
				innerVar4 = innerVar2 == 4 ? 0 : 1;
				previous_action = current_action;
			}
			if(innerVar1 == 5)
			{
				if (innerVar2 == 0) {innerVar3 = 0; innerVar4 = 4;}
				if (innerVar2 == 1) {innerVar3 = 0; innerVar4 = previous_action == 25 ? 3 : previous_action % 5;}
			}
		}
	}
	
	current_action = innerVar3 * 5 + innerVar4;
	cursor_position_x = LETTERS_LAYOUT_X[current_action];
	cursor_position_y = LETTERS_LAYOUT_Y[current_action];
}

void game_main_loop()
{
	set_vram_buffer(); 
	calc_current_action();

        oam_clear();
	if(globalsGameState == GAME_STATE_GAME)
		oam_meta_spr(cursor_position_x, cursor_position_y, current_action == 26 ? CURSOR_BIG : CURSOR);
}





