#ifndef __GLOBALS_H__
#define __GLOBALS_H__

extern unsigned char globalsGameState;
#pragma zpsym ("globalsGameState");
extern unsigned int globalsRandSeed;


#define GAME_STATE_INTRO 0
#define GAME_STATE_INTRO_TO_GAME 1
#define GAME_STATE_GAME 2
#define GAME_STATE_END 3


#endif
