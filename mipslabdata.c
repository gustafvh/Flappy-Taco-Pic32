/* mipslabdata.c
   This file compiled 2015 by F Lundevall
   from original code written by Axel Isaksson

This file modified 2017-02-28 by Mattias Stahre and Gustaf Halvardsson

   For copyright and licensing, see file COPYING */



#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

char textbuffer[4][16];
char s[4][20];
extern uint8_t tubes[5*60];
//extern int objectPosLevel1[64*2];
//extern int objectPosLevel1Reset[64*2];

int gameState = 2;
int score = 0;
int gameScore0  = 0;
int gameScore1  = 0;
int gameScore2  = 0;
int gameScore3  = 0;

extern int countStart = 0;

const uint8_t const font[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 94, 0, 0, 0, 0,
	0, 0, 4, 3, 4, 3, 0, 0,
	0, 36, 126, 36, 36, 126, 36, 0,
	0, 36, 74, 255, 82, 36, 0, 0,
	0, 70, 38, 16, 8, 100, 98, 0,
	0, 52, 74, 74, 52, 32, 80, 0,
	0, 0, 0, 4, 3, 0, 0, 0,
	0, 0, 0, 126, 129, 0, 0, 0,
	0, 0, 0, 129, 126, 0, 0, 0,
	0, 42, 28, 62, 28, 42, 0, 0,
	0, 8, 8, 62, 8, 8, 0, 0,
	0, 0, 0, 128, 96, 0, 0, 0,
	0, 8, 8, 8, 8, 8, 0, 0,
	0, 0, 0, 0, 96, 0, 0, 0,
	0, 64, 32, 16, 8, 4, 2, 0,
	0, 62, 65, 73, 65, 62, 0, 0,
	0, 0, 66, 127, 64, 0, 0, 0,
	0, 0, 98, 81, 73, 70, 0, 0,
	0, 0, 34, 73, 73, 54, 0, 0,
	0, 0, 14, 8, 127, 8, 0, 0,
	0, 0, 35, 69, 69, 57, 0, 0,
	0, 0, 62, 73, 73, 50, 0, 0,
	0, 0, 1, 97, 25, 7, 0, 0,
	0, 0, 54, 73, 73, 54, 0, 0,
	0, 0, 6, 9, 9, 126, 0, 0,
	0, 0, 0, 102, 0, 0, 0, 0,
	0, 0, 128, 102, 0, 0, 0, 0,
	0, 0, 8, 20, 34, 65, 0, 0,
	0, 0, 20, 20, 20, 20, 0, 0,
	0, 0, 65, 34, 20, 8, 0, 0,
	0, 2, 1, 81, 9, 6, 0, 0,
	0, 28, 34, 89, 89, 82, 12, 0,
	0, 0, 126, 9, 9, 126, 0, 0,
	0, 0, 127, 73, 73, 54, 0, 0,
	0, 0, 62, 65, 65, 34, 0, 0,
	0, 0, 127, 65, 65, 62, 0, 0,
	0, 0, 127, 73, 73, 65, 0, 0,
	0, 0, 127, 9, 9, 1, 0, 0,
	0, 0, 62, 65, 81, 50, 0, 0,
	0, 0, 127, 8, 8, 127, 0, 0,
	0, 0, 65, 127, 65, 0, 0, 0,
	0, 0, 32, 64, 64, 63, 0, 0,
	0, 0, 127, 8, 20, 99, 0, 0,
	0, 0, 127, 64, 64, 64, 0, 0,
	0, 127, 2, 4, 2, 127, 0, 0,
	0, 127, 6, 8, 48, 127, 0, 0,
	0, 0, 62, 65, 65, 62, 0, 0,
	0, 0, 127, 9, 9, 6, 0, 0,
	0, 0, 62, 65, 97, 126, 64, 0,
	0, 0, 127, 9, 9, 118, 0, 0,
	0, 0, 38, 73, 73, 50, 0, 0,
	0, 1, 1, 127, 1, 1, 0, 0,
	0, 0, 63, 64, 64, 63, 0, 0,
	0, 31, 32, 64, 32, 31, 0, 0,
	0, 63, 64, 48, 64, 63, 0, 0,
	0, 0, 119, 8, 8, 119, 0, 0,
	0, 3, 4, 120, 4, 3, 0, 0,
	0, 0, 113, 73, 73, 71, 0, 0,
	0, 0, 127, 65, 65, 0, 0, 0,
	0, 2, 4, 8, 16, 32, 64, 0,
	0, 0, 0, 65, 65, 127, 0, 0,
	0, 4, 2, 1, 2, 4, 0, 0,
	0, 64, 64, 64, 64, 64, 64, 0,
	0, 0, 1, 2, 4, 0, 0, 0,
	0, 0, 48, 72, 40, 120, 0, 0,
	0, 0, 127, 72, 72, 48, 0, 0,
	0, 0, 48, 72, 72, 0, 0, 0,
	0, 0, 48, 72, 72, 127, 0, 0,
	0, 0, 48, 88, 88, 16, 0, 0,
	0, 0, 126, 9, 1, 2, 0, 0,
	0, 0, 80, 152, 152, 112, 0, 0,
	0, 0, 127, 8, 8, 112, 0, 0,
	0, 0, 0, 122, 0, 0, 0, 0,
	0, 0, 64, 128, 128, 122, 0, 0,
	0, 0, 127, 16, 40, 72, 0, 0,
	0, 0, 0, 127, 0, 0, 0, 0,
	0, 120, 8, 16, 8, 112, 0, 0,
	0, 0, 120, 8, 8, 112, 0, 0,
	0, 0, 48, 72, 72, 48, 0, 0,
	0, 0, 248, 40, 40, 16, 0, 0,
	0, 0, 16, 40, 40, 248, 0, 0,
	0, 0, 112, 8, 8, 16, 0, 0,
	0, 0, 72, 84, 84, 36, 0, 0,
	0, 0, 8, 60, 72, 32, 0, 0,
	0, 0, 56, 64, 32, 120, 0, 0,
	0, 0, 56, 64, 56, 0, 0, 0,
	0, 56, 64, 32, 64, 56, 0, 0,
	0, 0, 72, 48, 48, 72, 0, 0,
	0, 0, 24, 160, 160, 120, 0, 0,
	0, 0, 100, 84, 84, 76, 0, 0,
	0, 0, 8, 28, 34, 65, 0, 0,
	0, 0, 0, 126, 0, 0, 0, 0,
	0, 0, 65, 34, 28, 8, 0, 0,
	0, 0, 4, 2, 4, 2, 0, 0,
	0, 120, 68, 66, 68, 120, 0, 0,
};

int objectPosLevel1Reset[] = {
	80, -15,
	120, -16,
	160, -25,
	200, -5,
	230, -10,
	270, -19,
	330, -23,
	350, -27,
	390, -9,
	420, -20,
	460, -22,
	510, -13,
	525, -16,
	540, -19,
	565, -23,
	600, -27,
	680, -15,
	720, -16,
	760, -25,
	800, -5,
	830, -10,
	870, -19,
	930, -23,
	1050, -27,
	1090, -9,
	1120, -20,
	1160, -22,
	1210, -13,
	1225, -16,
	1240, -19,
	1265, -23,
	1300, -27,
	80, -15,
	120, -16,
	160, -25,
	200, -5,
	230, -10,
	270, -19,
	330, -23,
	350, -27,
	390, -9,
	420, -20,
	460, -22,
	510, -13,
	525, -16,
	540, -19,
	565, -23,
	600, -27,
	680, -15,
	720, -16,
	760, -25,
	800, -5,
	830, -10,
	870, -19,
	930, -23,
	1050, -27,
	1090, -9,
	1120, -20,
	1160, -22,
	1210, -13,
	1225, -16,
	1240, -19,
	1265, -23,
	1300, -27
};

int objectPosLevel1[] = {
	80, -15,
	120, -16,
	160, -25,
	200, -5,
	230, -10,
	270, -19,
	330, -23,
	350, -27,
	390, -9,
	420, -20,
	460, -22,
	510, -13,
	525, -16,
	540, -19,
	565, -23,
	600, -27,
	680, -15,
	720, -16,
	760, -25,
	800, -5,
	830, -10,
	870, -19,
	930, -23,
	1050, -27,
	1090, -9,
	1120, -20,
	1160, -22,
	1210, -13,
	1225, -16,
	1240, -19,
	1265, -23,
	1300, -27,
	78, -15,
	120, -16,
	160, -25,
	200, -5,
	230, -10,
	270, -19,
	330, -23,
	350, -27,
	390, -9,
	420, -20,
	460, -22,
	510, -13,
	525, -16,
	540, -19,
	565, -23,
	600, -27,
	680, -15,
	720, -16,
	760, -25,
	800, -5,
	830, -10,
	870, -19,
	930, -23,
	1050, -27,
	1090, -9,
	1120, -20,
	1160, -22,
	1210, -13,
	1225, -16,
	1240, -19,
	1265, -23,
	1300, -27

};


uint8_t tubes[] = {
	1, 1, 1, 1, 1,
	1, 1, 1, 1, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
  1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
  1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
  1, 255, 255, 255, 1,
		1, 1, 1, 1, 1,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
  255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
  255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
  255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
  255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
  255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	255, 255, 255, 255, 255,
	1, 1, 1, 1, 1,
	1, 255, 255, 255, 1,
  1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
  1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 255, 255, 255, 1,
	1, 1, 1, 1, 1,
	1, 1, 1, 1, 1,



};

 uint8_t icon[] = {
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,

};
