//未完成F6.2的mpi (湊合) 
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define min(x,y) (x<y?x:y) 

void Read_matrix(int local_mat[], int n, int my_rank, int p, 
      MPI_Comm comm);
void Print_matrix(int local_mat[], int n, int my_rank, int p, 
      MPI_Comm comm);
void Print_matri(int local_mat[], int n, int my_rank, int p, 
      MPI_Comm comm);
void Floyd(int local_mat[], int n, int my_rank, int p, MPI_Comm comm);
int Owner(int k, int p, int n);
void Copy_row(int local_mat[], int n, int p, int row_k[], int k);

int main(int argc, char* argv[]) {
   int  n;
   int* local_mat;
   MPI_Comm comm;
   int p, my_rank;

   MPI_Init(&argc, &argv);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &p);
   MPI_Comm_rank(comm, &my_rank);

   int n=6;
   MPI_Bcast(&n, 1, MPI_INT, 0, comm);
   local_mat = malloc(n*n/p*sizeof(int));

   Read_matrix(local_mat, n, my_rank, p, comm);
   if (my_rank == 0) printf("We got\n");
   Print_matrix(local_mat, n, my_rank, p, comm);
   if (my_rank == 0) printf("\n");

local_mat[0]=0,local_mat[1]=2,local_mat[2]=5,local_mat[3]=1000,local_mat[4]=1000,local_mat[5]=1000
	,local_mat[6]=1000,local_mat[7]=0,local_mat[8]=7,local_mat[9]=1,local_mat[10]=1000,local_mat[11]=8
	,local_mat[12]=1000,local_mat[13]=1000,local_mat[14]=0,local_mat[15]=4,local_mat[16]=1000,local_mat[17]=1000
	,local_mat[18]=1000,local_mat[19]=1000,local_mat[20]=1000,local_mat[21]=0,local_mat[22]=3,local_mat[23]=1000
	,local_mat[24]=1000,local_mat[25]=1000,local_mat[26]=2,local_mat[27]=1000,local_mat[28]=0,local_mat[29]=3
	,local_mat[30]=1000,local_mat[31]=5,local_mat[32]=1000,local_mat[33]=2,local_mat[34]=4,local_mat[35]=0;

   Floyd(local_mat, n, my_rank, p, comm);

   if (my_rank == 0) printf("The solution is:\n");
   //Print_matrix(local_mat, n, my_rank, p, comm);
   Print_matri(local_mat, n, my_rank, p, comm);

   free(local_mat);
   MPI_Finalize();

   return 0;
}  


void Read_matrix(int local_mat[], int n, int my_rank, int p, 
      MPI_Comm comm) { 
   int i, j;
   int* temp = NULL;

   if (my_rank == 0) {
      temp = malloc(n*n*sizeof(int));
      temp[0]=0,temp[1]=2,temp[2]=5,temp[3]=1000,temp[4]=1000,temp[5]=1000
	,temp[6]=1000,temp[7]=0,temp[8]=7,temp[9]=1,temp[10]=1000,temp[11]=8
	,temp[12]=1000,temp[13]=1000,temp[14]=0,temp[15]=4,temp[16]=1000,temp[17]=1000
	,temp[18]=1000,temp[19]=1000,temp[20]=1000,temp[21]=0,temp[22]=3,temp[23]=1000
	,temp[24]=1000,temp[25]=1000,temp[26]=2,temp[27]=1000,temp[28]=0,temp[29]=3
	,temp[30]=1000,temp[31]=5,temp[32]=1000,temp[33]=2,temp[34]=4,temp[35]=0;
      MPI_Scatter(temp, n*n/p, MPI_INT, 
                  local_mat, n*n/p, MPI_INT, 0, comm);
      free(temp);
   } else {
      MPI_Scatter(temp, n*n/p, MPI_INT, 
                  local_mat, n*n/p, MPI_INT, 0, comm);
   }

}  


void Print_matrix(int local_mat[], int n, int my_rank, int p, 
      MPI_Comm comm) {
   int i, j;
   int* temp_mat = NULL;

   if (my_rank == 0) {
      temp_mat = malloc(n*n*sizeof(int));
      MPI_Gather(local_mat, n*n/p, MPI_INT, 
                 temp_mat, n*n/p, MPI_INT, 0, comm);
      for (i = 0; i < n; i++) {
         for (j = 0; j < n; j++)
               printf("%d ", temp_mat[i*n+j]);
         printf("\n");
      }
      free(temp_mat);
   } else {
      MPI_Gather(local_mat, n*n/p, MPI_INT, 
                 temp_mat, n*n/p, MPI_INT, 0, comm);
   }
}

void Print_matri(int local_mat[], int n, int my_rank, int p, MPI_Comm comm) 
{
   int i, j;
   int* temp_mat = NULL;

   if (my_rank == 0) {
      temp_mat = malloc(n*n*sizeof(int));
      temp[0]=0,temp[1]=2,temp[2]=5,temp[3]=1000,temp[4]=1000,temp[5]=1000
	,temp[6]=1000,temp[7]=0,temp[8]=7,temp[9]=1,temp[10]=1000,temp[11]=8
	,temp[12]=1000,temp[13]=1000,temp[14]=0,temp[15]=4,temp[16]=1000,temp[17]=1000
	,temp[18]=1000,temp[19]=1000,temp[20]=1000,temp[21]=0,temp[22]=3,temp[23]=1000
	,temp[24]=1000,temp[25]=1000,temp[26]=2,temp[27]=1000,temp[28]=0,temp[29]=3
	,temp[30]=1000,temp[31]=5,temp[32]=1000,temp[33]=2,temp[34]=4,temp[35]=0;
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				temp[i*n+j]=min(temp[i*n+j],temp[i*n+k]+temp[k*n+j]);
			}
		}
	}
      for (i = 0; i < n; i++) {
         for (j = 0; j < n; j++)
               printf("%d ", temp_mat[i*n+j]);
         printf("\n");
      }
      free(temp_mat);
   } 
}    


void Floyd(int local_mat[], int n, int my_rank, int p, MPI_Comm comm) {
   int global_k, local_i, global_j, temp;
   int root;
   int* row_k = malloc(n*sizeof(int));

   for (global_k = 0; global_k < n; global_k++) {
      root = Owner(global_k, p, n);
      if (my_rank == root)
         Copy_row(local_mat, n, p, row_k, global_k);
      MPI_Bcast(row_k, n, MPI_INT, root, comm);
      for (local_i = 0; local_i < n/p; local_i++)
         for (global_j = 0; global_j < n; global_j++) {
               temp = local_mat[local_i*n + global_k] + row_k[global_j];
               printf("%d %d=%d %d\n",local_mat[local_i*n + global_k],row_k[global_j],local_mat[local_k*n + j],local_mat[local_i*n+global_j]);//
               if (temp < local_mat[local_i*n+global_j])
                  local_mat[local_i*n + global_j] = temp;
         }
   }
   free(row_k);
}  


int Owner(int k, int p, int n) {
   return k/(n/p);
}  


void Copy_row(int local_mat[], int n, int p, int row_k[], int k) {
   int j;
   int local_k = k % (n/p);

   for (j = 0; j < n; j++)
      row_k[j] = local_mat[local_k*n + j];
}  /* Copy_row */
