#ifndef __GLUTTONOUS_SNAKE_H
#define __GLUTTONOUS_SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define FALSE 0
#define TRUE  1

#define	snake_len_init	3		//蛇的初始化长度为3

#define	 Key_Up		1		//↑按键状态
#define	 Key_Down	2		//↓按键状态
#define  Key_Left	3		//←按键状态
#define  Key_Right	4		//→按键状态
#define  Key_Space	5
#define	 Key_Esc	6
 

#define	red		FOREGROUND_RED
#define orange	FOREGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN
#define green	FOREGROUND_GREEN
#define blue	FOREGROUND_BLUE
#define purple	FOREGROUND_RED|FOREGROUND_BLUE

typedef struct node
{
	int x;
	int y;
	int color;
	struct node *next;
}snake;


void Goto_Coord(int x,int y);
void color(int color);
void Area_Show();
void Side_Show();
void Snake_Init();
int Food_Show();
void Game_Init();
void Food_Score(int food_color);
void Game_Control();
void Snake_Move();
void Pause();
void Through_Walls();
void Bit_Oneself();


#endif