#include "Gluttonous_Snake.h"
int sleep_time = 200;

int main()
{
	Game_Init();  //��Ϸ�����ʼ��
	
	while(1)
	{
		system("title ��Ϸ�С�������");
		Game_Control();      //��Ϸ���ƣ��жϰ��µ�����һ������
		Sleep(sleep_time);   //��ʱ200ms
		Snake_Move();
	}
}