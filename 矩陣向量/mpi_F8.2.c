//每個CPU只存一個值，Allgatherv將每個CPU的值放在一起 
//mpi版 (mpi1 mpi_F8.2.c) 
#include <stdio.h>
#include <mpi.h>
#define m 4
#define n 5
int main(int argc, char *argv[])
{
	int i,j,id,nproc;
	int a[m][n]={{2,1,3,4,0},{5,-1,2,-2,4},
	{0,3,4,1,2},{2,3,1,-3,0}},
	b[n]={3,1,4,0,3},c[1],allc[m];
	int index[m]={0,1,2,3},recv_cnt[m]={1,1,1,1};
	
	MPI_Init ( &argc, &argv );
	MPI_Comm_rank ( MPI_COMM_WORLD, &id );
	MPI_Comm_size ( MPI_COMM_WORLD, &nproc );
	
	for(i=id;i<m;i+=nproc)
	{
		c[0]=0;
		for(j=0;j<n;j++)
		{
			c[0]=c[0]+a[i][j]*b[j];
		}
	}
		
	MPI_Allgatherv(c,1,MPI_INT,allc,recv_cnt,index,MPI_INT,MPI_COMM_WORLD);
	
	//測試用
	/*for(i=0;i<m;i++)
	{
		printf("id:%d %d ",id,c[i]);
	} 
	printf("\n");
	*/
	
	printf("%d) ",id);
	for(i=0;i<m;i++)
	{
		printf("%d ",allc[i]);
	}
	
	MPI_Finalize();
} 
