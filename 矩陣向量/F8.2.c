#include <stdio.h>
#include <time.h>
#define m 4
#define n 5
int main()
{
	int i,j;
	int a[m][n]={{2,1,3,4,0},{5,-1,2,-2,4},
	{0,3,4,1,2},{2,3,1,-3,0}},
	b[n]={3,1,4,0,3},c[m];
	for(i=0;i<m;i++)
	{
		c[i]=0;
		for(j=0;j<n;j++)
		{
			c[i]=c[i]+a[i][j]*b[j];
		}
	}
	for(i=0;i<m;i++)
	{
		printf("%d ",c[i]);
	}
	printf("\ntime: %lf\n",(double)clock() / CLOCKS_PER_SEC);
} 
