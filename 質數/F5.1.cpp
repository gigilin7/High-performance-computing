#include <iostream>
#define n 100000000 
using namespace std;
long long sum=0,a[100000000]={0};
int main()
{
	
	//cout<<"輸入n值: ";
	//cin>>n;
	for(long long i=2;i*i<=n;i++)
	{
		for(long long j=i*i;j<=n;j+=i)
		{
			if(!a[j])
				a[j]=1;//不是質數 
		}
	}
	for(long long i=2;i<=n;i++)
	{
		if(!a[i])
			sum++;
	}
	cout<<sum;
} 
