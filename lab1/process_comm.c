#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
const int MAX_STRING = 100;

int main(void)
{
	char gret[MAX_STRING];
	int csize;
	int prank;
	int n;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &csize);
	MPI_Comm_rank(MPI_COMM_WORLD, &prank);
	
	int niz[csize];
	
	//srand(time(0) + prank);
	//n = 10*prank + rand()%10;
	
	// Svi procesi salju svima
	for(int i = 0 ; i<csize ; i++)
	{
		if(i != prank)
		{
			srand(time(0) + prank + i);
			n = 10*prank + rand()%10;
			MPI_Send(&n,1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}

	// Svi procesi primaju od svih
	for(int q = 0; q < csize ; q++)
	{
		if(q != prank)
		{
			MPI_Recv(&niz[q],1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}
	
	// Svi procesi salju nultom
	if(prank != 0)
	{
		sprintf(gret,"\nProcess %d recieved: ",prank);
		for(int i = 0 ; i<csize ; i++)
		{
			 if(prank != i)
			 {
				 char num_str[MAX_STRING];
		    		 sprintf(num_str, " %d", niz[i]);
		    		 strcat(gret, num_str);
			 }
		} 
		MPI_Send(gret,strlen(gret)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);
	}

	// Nulti proces ispisuje svacije poruke
	if(prank == 0)
	{	
		printf("Process 0 recieved : ");
		for(int i = 0 ; i < csize ; i++)
		{
			if(i != 0)
			{
				printf("%d ",niz[i]);
			}
		}
		for(int i = 1 ; i < csize ; i++)
		{
			MPI_Recv(gret,MAX_STRING,MPI_CHAR,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("%s \n",gret);		
		}
		
	}

	MPI_Finalize();
	return 0;
}	
