#include "Gluttonous_Snake.h"

int snake_x,snake_y;
int food_score = 10;   //ÿ��ʳ��ķ���
int total_score = 0;   //��õ��ܷ���
int highest_score = 0;     //��߷�
int Key_Status = Key_Right;   //��һ��ʼ�������н�
int Save_Status;
snake *head;
snake *newnode;       //�м����������while��1���л��ڴ����
snake *food1,*food2;	

//��ɫ��
int color_table[6] = {
					red,		//��			
					orange,		//��
					green,		//��
					blue,		//��
					purple		//��
					};

//��λ�������
void Goto_Coord(int x,int y)        
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle,pos);
}

//�����ı���ɫ
void color(int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,color);
}

//��Ϸ����չʾ
void Area_Show()
{
	int num;
	for(num=0;num<70;num+=2)        //����ĳ�num++�Ļ������� �߿����ִ���
	{
		Goto_Coord(num,0);
		printf("��");
		Goto_Coord(num,26);
		printf("��");
	}
	for(num=0;num<=26;num++)
	{
		Goto_Coord(0,num);
		printf("��");
		Goto_Coord(70,num);
		printf("��");
	}
}

//����˵��չʾ
void Side_Show()     
{
	Goto_Coord(80,5);	
	printf("��ӭ����̰������Ϸ\n");
	printf("\n");

	Goto_Coord(80,7);
	printf("�� �� �� �� �����������ƶ�\n");
	printf("\n");

	Goto_Coord(80,9);	
	printf("����1�����ܴ�ǽ�����ܳ��Լ�\n");
	printf("\n");

	Goto_Coord(80,11);	
	printf("����2��ESC�˳���SPACE����ͣ\n");
	printf("\n");

	Goto_Coord(80,13);	
	printf("����2���Ե�ʳ��Խ�࣬����Խ��\n");
	printf("\n");

	Goto_Coord(80,15);	
	printf("����3�����л���ֳԵ���Ҳû�����ļ�ʳ��\n");
	printf("\n");
}

void Snake_Init()
{
	snake *newnode = (snake *)malloc(sizeof(struct node));
	newnode->x = 10;    //�����ʼ����
	newnode->y = 10;    //�����ʼ����
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
		printf("��");
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
	srand((unsigned)time(NULL));    //�������������Ҫ������

	//������һ��ʳ��
	while((food1->x%2)!= 0 || food1->x == 70)       //ʳ��x���겻��ż�������߽�û�ж���
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
	printf("��");

	//Goto_Coord(80,21);
	//printf("ʳ��1���� %d,%d",food1->x,food1->y);

	//�����ڶ���ʳ��
	while((food2->x%2)!= 0 || food2->x == 70)       //ʳ��x���겻��ż�������߽�û�ж���
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
	printf("��");

	//Goto_Coord(80,23);
	//printf("ʳ��2���� %d,%d",food2->x,food2->y);
	
}


//��Ϸ�����ʼ��
void Game_Init()
{
	system("title ̰����");
	Goto_Coord(40,10);
	printf("��ӭ����̰����С��Ϸ\n");
	system("pause");
	system("cls");
	Goto_Coord(40,10);
	printf("ϣ���ܴ��������õ���Ϸ����\n");
	system("pause");
	system("cls");

	Area_Show();	//��Ϸ�����ʼ��
	Side_Show();	//����˵����ʼ��
	Snake_Init();	//�߳�ʼ��
    Food_Show();    //��������ʳ��
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


//��Ϸ����
void Game_Control()
{
	Goto_Coord(80,18);
	color(0x07);
	printf("��ǰ��÷�����%d\n",total_score);
	

	//�жϰ�������һ������,���ұ�����һ�εİ���״̬���䷽���෴
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
		Save_Status = Key_Status;	 //����������ͣ����ʱ����ͣǰ���˶�����״̬��Ҫ��������
		Key_Status = Key_Space;
	}
	else if(GetAsyncKeyState(VK_ESCAPE ))
		Key_Status = Key_Esc;
}

//�ߵ��ƶ�
void Snake_Move()
{
	snake *nextnode = (snake *)malloc(sizeof(struct node));
	snake *temp = NULL;

	if(Key_Status == Key_Up)
	{
		nextnode->x = head->x;
		nextnode->y = (head->y) - 1;
		//Goto_Coord(80,28);
		//printf("��ͷhead������ %d,%d",head->x,head->y);
		if((nextnode->x == food1->x && nextnode->y == food1->y) ||
			(nextnode->x == food2->x && nextnode->y == food2->y))  //�ƶ������гԵ���ʳ��
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("��");
				temp = temp->next;
			}
			Food_Score(food1->color);
			free(food1);
			Food_Show();
		}
		else     //�ƶ�����û������ʳ��
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp->next->next != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("��");
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
		//printf("��ͷhead������ %d,%d",head->x,head->y);
		if((nextnode->x == food1->x && nextnode->y == food1->y) ||
			(nextnode->x == food2->x && nextnode->y == food2->y))  //�ƶ������гԵ���ʳ��
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("��");
				temp = temp->next;
			}
			Food_Score(food1->color);
			free(food1);
			Food_Show();
		}
		else     //�ƶ�����û������ʳ��
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp->next->next != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("��");
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
		//printf("��ͷhead������ %d,%d",head->x,head->y);
		if((nextnode->x == food1->x && nextnode->y == food1->y) ||
			(nextnode->x == food2->x && nextnode->y == food2->y))  //�ƶ������гԵ���ʳ��
		{
			
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("��");
				temp = temp->next;
			}
			Food_Score(food1->color);
			free(food1);
			Food_Show();
		}
		else     //�ƶ�����û������ʳ��
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp->next->next != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("��");
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
		//printf("��ͷhead������ %d,%d",head->x,head->y);
		if((nextnode->x == food1->x && nextnode->y == food1->y) ||
			(nextnode->x == food2->x && nextnode->y == food2->y))  //�ƶ������гԵ���ʳ��
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("��");
				temp = temp->next;
			}
			Food_Score(food1->color);
			free(food1);
			Food_Show();
		}
		else     //�ƶ�����û������ʳ��
		{
			nextnode->next = head;
			head = nextnode;
			temp = head;
			while(temp->next->next != NULL)
			{
				Goto_Coord(temp->x,temp->y);
				printf("��");
				temp = temp->next;
			}
			Goto_Coord(temp->next->x,temp->next->y);
			printf(" ");
			free(temp->next);
			temp->next = NULL;
		}
	}
	while(Key_Status == Key_Space)               //���ո���ͣ
	{
		Sleep(300);
		if(!(GetAsyncKeyState(VK_SPACE)))
		{
			Pause();                             //��ͣ����
			break;
		}	
	}
	if(Key_Status == Key_Esc)
	{
		system("cls");
		Goto_Coord(40,10);
		printf("���ѽ�����Ϸ��\n");
	}


	Through_Walls();	//�ж��Ƿ�ײǽ
	Bit_Oneself();		//�ж��Ƿ�ҧ�����Լ�
}

void Pause()
{
	while(1)
	{	
		system("title ��ͣ�С�������");
		Sleep(300);
		if(GetAsyncKeyState(VK_SPACE))       //�ڶ��ΰ��ո��ʱ�򣬽����ͣ״̬
		{
			Sleep(200);
			Key_Status = Save_Status;
			break;
		}
	}
}

//��ǽ������
void Through_Walls()
{
	if(head->x == 0 || head->x == 70 ||
		head->y == 0 || head->y == 26)
	{
		system("cls");
		Goto_Coord(30,10);
		printf("��Ǹ���¹��жϣ�С������ײǽ\n");

		Goto_Coord(30,12);
		color(0x07);
		printf("��ǰ��÷�����%d\n",total_score);
		
		exit(0);
	}
}

//ҧ���Լ�������
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
			printf("��Ǹ���¹��жϣ�С��ҧ�����Լ�\n");

			Goto_Coord(30,12);
			color(0x07);
			printf("��ǰ��÷�����%d\n",total_score);
			exit(0);
		}
		temp = temp->next;
	}
}