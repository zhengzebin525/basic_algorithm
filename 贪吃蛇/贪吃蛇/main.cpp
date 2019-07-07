#include "Gluttonous_Snake.h"
int sleep_time = 200;

int main()
{
	Game_Init();  //游戏界面初始化
	
	while(1)
	{
		system("title 游戏中····");
		Game_Control();      //游戏控制，判断按下的是哪一个按键
		Sleep(sleep_time);   //延时200ms
		Snake_Move();
	}
}