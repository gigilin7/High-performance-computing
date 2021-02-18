//mpi版是(a_mpi a.cpp) 
#include <iostream>  
#include <cstdlib>
#include <time.h>
#define n 100000000 
using namespace std;
//long long a[100000000]={0};
bool *a;

void unmark(long long i)
{
	for(long long j=i*i;j<=n;j+=i)
	{
		a[j]=true;//不是質數 
	}
}
int main()
{
	long long sum=0;
	a=(bool*)malloc(n*sizeof(bool));
	//cout<<"輸入n值: ";
	//cin>>n;
	for(long long i=2;i*i<=n;i++)
	{
		if(!a[i])
			unmark(i);
	}
	for(long long i=2;i<=n;i++)
	{
		if(!a[i])
			sum++;//質數有幾個 
	}
	cout<<sum;
	printf("\ntime: %lf\n",(double)clock() / CLOCKS_PER_SEC);
} 
