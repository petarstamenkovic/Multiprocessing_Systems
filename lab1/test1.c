#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void)
{
	char gret[MAX_STRING];
	int csize;
	int prank;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &csize);
	MPI_Comm_rank(MPI_COMM_WORLD, &prank);
	
	if(prank != 0)
	{
		sprintf(gret, "Grets from process %d of %d and %d!", prank,csize);
		MPI_Send(gret, strlen(gret)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}
	else 
	{	
		printf("Greets from process %d of %d! \n",prank,csize);
		
		for(int q = 1 ; q<csize;q++)
		{
			MPI_Recv(gret,MAX_STRING,MPI_CHAR,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("%s\n",gret);
			
		}
	}	

	MPI_Finalize();
	return 0;
}	
