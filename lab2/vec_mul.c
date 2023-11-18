#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Ovaj program prihvata od korisnika duzinu vektora, a program generise radnom vrednosti
// unutar oba. Zbog biblioteke math na kraju dodati -lm za kompajliranje

int getInput()
{
    int res;
    printf("Number : ");
    fflush(stdout);
    scanf("%d",&res);
    return (int) (res);
}

int main(int argc, char *argv[])
{
	int csize,prank,n;
	int sum;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &csize);
	MPI_Comm_rank(MPI_COMM_WORLD, &prank);
	
	srand(time(NULL) + prank);
	
	if(prank == 0)
	{
		n = getInput();
	}
		
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	int v1[n];
	int v2[n];
		
		
	if(prank == 0)
	{
		
		//srand(0);
		for(int i = 0; i < n ; i++)
		{
			v1[i] = rand()%10;
		}
		//srand(1);
		for(int i = 0; i < n ; i++)
		{
			v2[i] = rand()%10;
		}
	}
	
	MPI_Bcast(v1,n,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(v2,n,MPI_INT,0,MPI_COMM_WORLD);

	// Blokovska implemetacija
	int limit = (int)floor(n/csize);
	int loc_start = prank*limit+1;
	int loc_end = limit*(prank+1);
	int loc_value = 0;
	
	for(int i = loc_start ; i<=loc_end ; i++)
	{
		loc_value = loc_value + v1[i-1]*v2[i-1];
	}
	
	MPI_Reduce(&loc_value,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	
	if(prank == 0)
	{
		printf(" Vector 1 is : ");
		for(int p = 0 ; p < n ; p++)
		{
			printf("%d",v1[p]);
			printf(" ");
		}
		
		printf("\n Vector 2 is : ");
		for(int p = 0 ; p < n ; p++)
		{
			printf("%d",v2[p]);
			printf(" ");
		}
		
		printf("\n Scalar product of vector 1 and vector 2 is %d \n",sum);
	}
	
	MPI_Finalize();
	return 0;
}

