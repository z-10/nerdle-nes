 
#include "../LIB/neslib.h"
#include "../LIB/nesdoug.h" 


#include "globals.h" 
#include "palettes.h"

#include "input.h"

#include "intro.h"
#include "game.h"

void game_end_loop()
{
	input_get_new_pad1();
	if(inputPad1 & PAD_START)
	{
		intro_exit();
		intro_setup();
	}
}


void main (void) {
	globalsRandSeed = 0;
	
	intro_setup();	
	ppu_wait_nmi(); // wait	
	while (1){
		switch(globalsGameState)
		{
			case GAME_STATE_INTRO:
				intro_main_loop();
				break;
			case GAME_STATE_INTRO_TO_GAME:
				intro_exit();
				game_setup();
				break;
			case GAME_STATE_GAME:
				game_main_loop();
				break;
			case GAME_STATE_END:
				game_end_loop();
				break;		
			
		}

		globalsRandSeed += 1;
		ppu_wait_nmi();
	}
}
	
	