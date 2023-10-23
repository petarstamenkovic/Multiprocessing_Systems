#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>

const int MAX_STRING = 100;

int main(void)
{
	char gret[MAX_STRING];
	int csize;
	int prank;
	int n;
	int c;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &csize);
	MPI_Comm_rank(MPI_COMM_WORLD, &prank);
	
	int niz[csize];
	
	// Svi procesi salju svima
	for(int i = 0 ; i<csize ; i++)
	{
		if(i != prank)
		{
			srand(i);
			n = prank*10 + rand()%10;
			//sprintf(gret,"Process %d sending a number %d! \n",prank,n);
			//MPI_Send(gret,strlen(gret)+1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
			MPI_Send(&n,1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		else 
		continue;
	}

	// Svi procesi primaju od svih
	for(int q = 0; q < csize ; q++)
	{
		if(q != prank)
		{
			//MPI_Recv(gret, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&n,1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			niz[q] = n;
			// Da li ovde treba jos jedan send da se posalje ceo niz nekako i onda u posednjem if delu prihvatiti niz?
		}
		else
		continue;
	}

	if(prank == 0)
	{
		for(int p = 0 ; p < csize ; p++)
		{
			//MPI_Recv(gret, MAX_STRING, MPI_CHAR, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//MPI_Recv(&n,1, MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Process %d recieved : \n",p);
			for(int z = 0 ; z < csize; z++)
			{
				printf("%d \n",niz[z]);
			}
			
		}
	}

	MPI_Finalize();
	return 0;
}	
