#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
	int tc = strtol(argv[1] , NULL , 10);
	double n;
	double sum = 0;
	
	printf("Number: ");
	scanf("%lf",&n);
	
	double s = omp_get_wtime();
	
	#pragma omp parallel for num_threads(tc) reduction(+: sum)
	for(int i = 1; i <= (int)n ; i++)
		sum += (double)i;
		
	s = omp_get_wtime() - s;
	printf("\n Sum is %lf :  \n",sum);
	printf("\n Elapsed time is %lf s. \n",s);
	
	return 0;	
		 
}
