//F5.1的mpi完成版 
#include <stdio.h>
//#include <iostream>
#include <mpi.h>
#include <cmath>
using namespace std;
#define n 100000000
#define BLOCK_LOW(id,p,n) ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
//#define BLOCK_SIZE(id,p,n) (BLOCK_LOW((id)+1)-BLOCK_LOW(id)) /*ppt上的，但好像不能用*/ 
#define BLOCK_SIZE(id,p,n) (BLOCK_HIGH(id,p,n)-BLOCK_LOW(id,p,n))
#define BLOCK_OWNER(index,p,n) (((p)*((index)+1)-1)/(n))

bool array[n+1];

void unmark(int id,long int a,int p)
{
	long long int i, b = BLOCK_LOW(id,p,n)+2;
	i = b % a;
	if(i==0)
		i = b;
	else
		i = b+(a-i);
		
	if(id==0)
		i = i+a;
		
	for(long long int j=i;j<=BLOCK_HIGH(id,p,n);j=j+a)
	{
		array[j] = true;
	}
}

int main(int argc, char *argv[])
{
	long int i;
	long int m=2; //global minimun
	int id; //哪個cpu
	int p; //數量
	double t1,t2;
	MPI_Init(NULL,NULL);
	t1 = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	long int sum = 0;
	long int global_sum = 0;
	
	do{
		unmark(id,m,p);
		
		if(m > BLOCK_HIGH(id,p,n))
			i = n;
		else
		{
			if(m+1 < BLOCK_LOW(id,p,n))
				m = BLOCK_LOW(id,p,n);
			else
				m = m+1;
			for(i=m;i*i<=BLOCK_HIGH(id,p,n);i++)
			{
				if(array[i]==false)
					break;
			}
		}
		
		MPI_Reduce(&i,&m,1,MPI_LONG,MPI_MIN,0,MPI_COMM_WORLD);
		MPI_Bcast(&m,1,MPI_LONG,0,MPI_COMM_WORLD);
		
	}while(m*m <= n);
	
	for(i=BLOCK_LOW(id,p,n)+2;i<=BLOCK_HIGH(id,p,n);i++)
	{
		if(!array[i])
		{
			sum++;
			//printf("%d ",i);
		}
	}
	//printf("\n----------------------------");
	
	MPI_Reduce(&sum,&global_sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	//printf("\n\nsum: %d個\n",sum);
	
	if(id==0)
		printf("\ntotal: %d個\n",global_sum);
		
	t2 = MPI_Wtime();
	if(id==0)
		printf("time: %lf\n",t2-t1);
		
	MPI_Finalize();
	return 0;
}

 
