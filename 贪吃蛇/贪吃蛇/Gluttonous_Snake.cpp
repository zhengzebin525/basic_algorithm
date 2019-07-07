#include "Gluttonous_Snake.h"

int snake_x,snake_y;
int food_score = 10;   //每个食物的分数
int total_score = 0;   //获得的总分数
int highest_score = 0;     //最高分
int Key_Status = Key_Right;   //蛇一开始是向右行进
int Save_Status;
snake *head;
snake *newnode;       //中间变量，放在while（1）中会内存溢出
snake *food1,*food2;	

//颜色表
int color_table[6] = {
					red,		//红			
					orange,		//橙
					green,		//绿
					blue,		//蓝
					purple		//紫
					};

//定位输出坐标
void Goto_Coord(int x,int y)        
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle,pos);
}

//设置文本颜色
void color(int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,color);
}

//游戏区域展示
void Area_Show()
{
	int num;
	for(num=0;num<70;num+=2)        //如果改成num++的话，上下 边框会出现错误
	{
		Goto_Coord(num,0);
		printf("■");
		Goto_Coord(num,26);
		printf("■");
	}
	for(num=0;num<=26;num++)
	{
		Goto_Coord(0,num);
		printf("■");
		Goto_Coord(70,num);
		printf("■");
	}
}

//侧面说明展示
void Side_Show()     
{
	Goto_Coord(80,5);	
	printf("欢迎来到贪吃蛇游戏\n");
	printf("\n");

	Goto_Coord(80,7);
	printf("↑ ↓ ← → 是上下左右移动\n");
	printf("\n");

	Goto_Coord(80,9);	
	printf("规则1：不能穿墙，不能吃自己\n");
	printf("\n");

	Goto_Coord(80,11);	
	printf("规则2：ESC退出，SPACE是暂停\n");
	printf("\n");

	Goto_Coord(80,13);	
	printf("规则2：吃的食物越多，分数越高\n");
	printf("\n");

	Goto_Coord(80,15);	
	printf("规则3：其中会出现吃到了也没分数的假食物\n");
	printf("\n");
}

void Snake_Init()
{
	snake *newnode = (snake *)malloc(sizeof(struct node));
	newnode->x = 10;    //赋予初始坐标
	newnode->y = 10;    //赋予初始坐标
	newnode->next = NULL;
	
	for(int i=1;i<snake_len_init;i++)
	{
		head = (snake*)malloc(sizeof(struct node));
		head->x = 10 + 2*i;
		head->y = 10;
		head->next = newnode;
		newnode = head;
	}
	while(newnode!= NULL)
	{
		Goto_Coord(newnode->x,newnode->y);
		printf("■");
		newnode = newnode->next;
	}
}

int Food_Show()
{
	int color_num;
	snake *temp1 = NULL,*temp2 = NULL;
	food1 = (snake *)malloc(sizeof(struct node));
	food2 = (snake *)malloc(sizeof(struct node));
	if(food1 == NULL || food2 == NULL)
	{
		return FALSE;
	}
	srand((unsigned)time(NULL));    //产生随机数必须要的种子

	//产生第一个食物
	while((food1->x%2)!= 0 || food1->x == 70)       //食物x坐标不是偶数，跟边界没有对齐
	{	
		food1->x = rand()%70 + 2;
	}
	do
	{
		food1->y = rand()%26 + 1;
	}
	while(food1->y == 26);
	temp1 = head;
	while(temp1 != NULL)
	{
		if(food1->x == temp1->x && food1->y == temp1->y)
		{
			free(food1);
			Food_Show();
		}
		temp1 = temp1->next;
	}
	Goto_Coord(food1->x,food1->y);
	color_num = rand()%6;
	food1->color = color_table[color_num];
	color(food1->color);
	printf("■");

	//Goto_Coord(80,21);
	//printf("食物1坐标 %d,%d",food1->x,food1->y);

	//产生第二个食物
	while((food2->x%2)!= 0 || food2->x == 70)       //食物x坐标不是偶数，跟边界没有对齐
	{	
		food2->x = rand()%70 + 2;
	}
	do
	{
		food2->y = rand()%26 + 1;
	}
	while(food2->y == 26);
	temp2 = head;
	while(temp2 != NULL)
	{
		if(food2->x == temp2->x && food2->y == temp2->y)
		{
			free(food2);
			Food_Show();
		}
		temp2 = temp2->next;
	}
	Goto_Coord(food2->x,food2->y);
	color_num = rand()%6;
	food2->color = color_table[color_num];
	color(food2->color);
	printf("■");

	//Goto_Coord(80,23);
	//printf("食物2坐标 %d,%d",food2->x,food2->y);
	
}


//游戏界面初始化
void Game_Init()
{
	system("title 贪吃蛇");
	Goto_Coord(40,10);
	printf("欢迎来到贪吃蛇小游戏\n");
	system("pause");
	system("cls");
	Goto_Coord(40,10);
	printf("希望能带给你良好的游戏体验\n");
	system("pause");
	system("cls");

	Area_Show();	//游戏区域初始化
	Side_Show();	//侧面说明初始化
	Snake_Init();	//蛇初始化
    Food_Show();    //产生方块食物
}

void Food_Score(int food_color)
{
	switch (food_color)
	{
		case red:
			total_score += 50;break;
		case orange:
			total_score += 40;break;
		case green:
			total_score += 30;break;
		case blue:
			total_score += 20;break;
		case purple:
			total_score += 10;break;
	}
}


//游戏控制
void Game_Control()
{
	Goto_Coord(80,18);
	color(0x07);
	printf("当前获得分数：%d\n",total_score);
	

	//判断按下了哪一个按键,并且避免上一次的按键状态与其方向相反
	if(GetAsyncKeyState(VK_UP) && Key_Status != Key_Down)   
		Key_Status = Key_Up;
	else if(GetAsyncKeyState(VK_DOWN) && Key_Status != Key_Up)
		Key_Status = Key_Down;
	else if(GetAsyncKeyState(VK_LEFT) && Key_Status != Key_Right)
		Key_Status = Key_Left;
	else if(GetAsyncKeyState(VK_RIGHT) && Key_Status != Key_Left)
		Key_Status = Key_Right;
	else if(GetAsyncKeyState(VK_SPACE))      
	{
		Save_Status = Key_Status;	 //当按下了暂停健的时候，暂停前的运动方向状态需要保存起来
		Key_Status = Key_Space;
	}
	else if(GetAsyncKeyState(VK_ESCAPE ))
		Key_Status = Key_Esc;
}

//蛇的移动
void Snake_Move()
{
	snake *nextnode = (snake *)malloc(sizeof(struct node));
	snake *temp = NULL;

	if(Key_Status == Key_Up)
	{
		nextnode->x = head->x;
		nextnode->y = (head->y) - 1;
		//Goto_Coord(80,28);
		//printf("蛇头head的坐标 %d,%d",head->x,head->y);
		if((nextnode->x == food1->x && nextnode->y == food1->y) ||
			(nextnode->x == food2->x && nextnode->y == food2->y))  //移动过程中吃到了食物
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("■");
				temp = temp->next;
			}
			Food_Score(food1->color);
			free(food1);
			Food_Show();
		}
		else     //移动过程没有遇到食物
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp->next->next != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("■");
				temp = temp->next;
			}
			Goto_Coord(temp->next->x,temp->next->y);
			printf(" ");
			free(temp->next);
			temp->next = NULL;
		}
	}

	
	if(Key_Status == Key_Down)
	{
		nextnode->x = head->x;
		nextnode->y = (head->y) + 1;
		//Goto_Coord(80,28);
		//printf("蛇头head的坐标 %d,%d",head->x,head->y);
		if((nextnode->x == food1->x && nextnode->y == food1->y) ||
			(nextnode->x == food2->x && nextnode->y == food2->y))  //移动过程中吃到了食物
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("■");
				temp = temp->next;
			}
			Food_Score(food1->color);
			free(food1);
			Food_Show();
		}
		else     //移动过程没有遇到食物
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp->next->next != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("■");
				temp = temp->next;
			}
			Goto_Coord(temp->next->x,temp->next->y);
			printf(" ");
			free(temp->next);
			temp->next = NULL;
		}
	}


	if(Key_Status == Key_Left)
	{
		nextnode->x = (head->x) - 2;
		nextnode->y = head->y;
		//Goto_Coord(80,28);
		//printf("蛇头head的坐标 %d,%d",head->x,head->y);
		if((nextnode->x == food1->x && nextnode->y == food1->y) ||
			(nextnode->x == food2->x && nextnode->y == food2->y))  //移动过程中吃到了食物
		{
			
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("■");
				temp = temp->next;
			}
			Food_Score(food1->color);
			free(food1);
			Food_Show();
		}
		else     //移动过程没有遇到食物
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp->next->next != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("■");
				temp = temp->next;
			}
			Goto_Coord(temp->next->x,temp->next->y);
			printf(" ");
			free(temp->next);
			temp->next = NULL;
		}
	}
	
	if(Key_Status == Key_Right)
	{
		nextnode->x = (head->x) + 2;
		nextnode->y = head->y;
		
		//Goto_Coord(80,28);
		//printf("蛇头head的坐标 %d,%d",head->x,head->y);
		if((nextnode->x == food1->x && nextnode->y == food1->y) ||
			(nextnode->x == food2->x && nextnode->y == food2->y))  //移动过程中吃到了食物
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("■");
				temp = temp->next;
			}
			Food_Score(food1->color);
			free(food1);
			Food_Show();
		}
		else     //移动过程没有遇到食物
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp->next->next != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("■");
				temp = temp->next;
			}
			Goto_Coord(temp->next->x,temp->next->y);
			printf(" ");
			free(temp->next);
			temp->next = NULL;
		}
	}
	while(Key_Status == Key_Space)               //按空格健暂停
	{
		Sleep(300);
		if(!(GetAsyncKeyState(VK_SPACE)))
		{
			Pause();                             //暂停函数
			break;
		}	
	}
	if(Key_Status == Key_Esc)
	{
		system("cls");
		Goto_Coord(40,10);
		printf("您已结束游戏！\n");
	}


	Through_Walls();	//判断是否撞墙
	Bit_Oneself();		//判断是否咬到了自己
}

void Pause()
{
	while(1)
	{	
		system("title 暂停中····");
		Sleep(300);
		if(GetAsyncKeyState(VK_SPACE))       //第二次按空格的时候，解除暂停状态
		{
			Sleep(200);
			Key_Status = Save_Status;
			break;
		}
	}
}

//穿墙错误函数
void Through_Walls()
{
	if(head->x == 0 || head->x == 70 ||
		head->y == 0 || head->y == 26)
	{
		system("cls");
		Goto_Coord(30,10);
		printf("抱歉，事故判断，小蛇死亡撞墙\n");

		Goto_Coord(30,12);
		color(0x07);
		printf("当前获得分数：%d\n",total_score);
		
		exit(0);
	}
}

//咬到自己错误函数
void Bit_Oneself()
{
	snake *temp;
	temp = head->next;
	while(temp!=NULL)
	{
		if(head->x == temp->x && head->y == temp->y)
		{
			system("cls");
			Goto_Coord(30,10);
			printf("抱歉，事故判断，小蛇咬死了自己\n");

			Goto_Coord(30,12);
			color(0x07);
			printf("当前获得分数：%d\n",total_score);
			exit(0);
		}
		temp = temp->next;
	}
}