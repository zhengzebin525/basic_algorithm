#include<stdio.h>

#define N 20  //�����������
int main()
{
	int i,j,n,k,triangle[N][N];
	printf("������Ҫ��ӡ������,��󲻳���20�У�");
	scanf("%d",&n);
	while(n>20 | n < 0)  
	{
		printf("����������������������룺");
		scanf("%d",&n);
	}

	for(i=0;i<n;i++)
	{
		triangle[i][0] = triangle[i][i] = 1;   //�������ÿһ�����˵�ϵ������1
	}

	for(i=2;i<n;i++)
	{
		for(j=0;j<i-1;j++)
		{
			//���������ϵ���������Ϸ������Ϸ�����ϵ��֮��
			triangle[i][j+1] = triangle[i-1][j] + triangle[i-1][j+1];
		}
	}

	for(i=0;i<n;i++)
	{
		for(k=n-i-1;k>0;k--)
		{
			printf("  ");  //Ϊ�˴�ӡ�����ÿ�������Ҫ����ÿһ�д�ӡ��ͬ�Ŀո�
		}
		for(j=0;j<=i;j++)
		{
			printf("%5d",triangle[i][j]);
		}
		printf("\n");
	}
	return 0;
}