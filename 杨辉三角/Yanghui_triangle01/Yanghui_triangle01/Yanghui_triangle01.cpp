#include<stdio.h>

#define N 20  //限制最大行数
int main()
{
	int i,j,n,k,triangle[N][N];
	printf("请输入要打印的行数,最大不超过20行：");
	scanf("%d",&n);
	while(n>20 | n < 0)  
	{
		printf("超过最大行数，请重新输入：");
		scanf("%d",&n);
	}

	for(i=0;i<n;i++)
	{
		triangle[i][0] = triangle[i][i] = 1;   //杨辉三角每一行两端的系数都是1
	}

	for(i=2;i<n;i++)
	{
		for(j=0;j<i-1;j++)
		{
			//其他各项的系数都是左上方和右上方两个系数之和
			triangle[i][j+1] = triangle[i-1][j] + triangle[i-1][j+1];
		}
	}

	for(i=0;i<n;i++)
	{
		for(k=n-i-1;k>0;k--)
		{
			printf("  ");  //为了打印出来好看，就需要根据每一行打印不同的空格
		}
		for(j=0;j<=i;j++)
		{
			printf("%5d",triangle[i][j]);
		}
		printf("\n");
	}
	return 0;
}