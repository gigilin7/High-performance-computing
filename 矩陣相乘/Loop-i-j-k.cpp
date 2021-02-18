//1
#include <iostream>
#include <ctime>
using namespace std;
const int m=1000,n=1000,p=1000;
double A[m][n], B[n][p], C[m][p];
double f;
int main()
{
	
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			A[i][j]=1.1;
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<p;j++)
		{
			B[i][j]=1.1;
		}
	}
	
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<p;j++)
		{
			f=0;
			for(int k=0;k<n;k++)
			{
				f+=A[i][k]*B[k][j];
			}
			C[i][j]=f;
		}
	}
	/*for(int i=0;i<m;i++)
	{
		for(int j=0;j<p;j++)
		{
			cout<<C[i][j]<<' ';
		}
		cout<<'\n';
	}*/
	//cout<<C[0][0]<<' '<<C[0][1]<<' '<<C[1][0]<<' '<<C[1][1];
	cout << "°õ¦æ®É¶¡: " << (double)clock() / CLOCKS_PER_SEC << "¬í";
} 
