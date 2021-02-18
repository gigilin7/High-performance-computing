//優化5 
#include <iostream>
#include <ctime>
#define BLOCKSIZE 100 
using namespace std;
const int m=1000,n=1000,p=1000;
double A[m][n], B[n][p], C[m][p], subA[n][n], subB[n][n], subC[n][n];
double f;

void block (int n, double A[][1000], double B[][1000], double C[][1000])
{
	int g=0;
	for(int kk=0;kk<n;kk+=BLOCKSIZE){
		for(int ii=0;ii<n;ii+=BLOCKSIZE){
			for(int jj=0;jj<n;jj+=BLOCKSIZE)
			{
				for(int i=ii;i<ii+BLOCKSIZE;i++){
					for(int k=kk;k<kk+BLOCKSIZE;k++){
						subA[i%BLOCKSIZE][k%BLOCKSIZE]=A[i][k];
					}
				}
				for(int k=kk;k<kk+BLOCKSIZE;k++){
					for(int j=jj;j<jj+BLOCKSIZE;j++){
						subB[k%BLOCKSIZE][j%BLOCKSIZE]=B[k][j];
					}
				}
	
				for(int i=0;i<BLOCKSIZE;i++){
					for(int k=0;k<BLOCKSIZE;k++){
						f=subA[i][k];
						for(int j=0;j<BLOCKSIZE;j++){
							subC[i][j]+=f*subB[k][j];
						}
					}
				}
				
			}
			for(int i=0;i<BLOCKSIZE;i++){
				for(int j=0;j<BLOCKSIZE;j++){
					C[i+kk][j+ii]=subC[i][j];
				}
			}
		}
	}
}

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
	
	block(1000,A,B,C);
	//cout<<C[0][0]<<' '<<C[0][1]<<' '<<C[1][0]<<' '<<C[1][1];
	
	cout << "執行時間: " << (double)clock() / CLOCKS_PER_SEC << "秒";
} 
