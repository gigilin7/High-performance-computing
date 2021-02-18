#include <iostream>
#include <algorithm>
#define n 6
using namespace std;
int main()
{
	int i,j,k;
	int a[n][n]={{0,2,5,1000,1000,1000},
					 {1000,0,7,1,1000,8},
					 {1000,1000,0,4,1000,1000},
					 {1000,1000,1000,0,3,1000},
					 {1000,1000,2,1000,0,3},
					 {1000,5,1000,2,4,0}};
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
} 
