#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(int argc, char* argv[])
{
	int tc = strtol(argv[1],NULL,10);
	double n;
	double sum = 0;
	double sum_array[tc];
	
	printf("Number: ");
	scanf("%lf",&n);
	
	double s = omp_get_wtime();
	int loc_sum = 0;
 	#pragma omp parallel private (loc_sum) //num_threads(tc) //reduction(+: sum)
	{
		int trank = omp_get_thread_num();
		//int limit = (int)floor(n/tc);
		//int loc_start = trank*limit + 1;
		//int loc_end = limit*(trank + 1);
		
		int i = (double)trank;
		//printf("Total amount of threads is %d \n",tc);
		while (i <= n)
		{
			loc_sum = loc_sum + i;
			i = i + tc;
		}
		//for(int p = loc_start; p <= loc_end; p++)
		//{
		//	loc_sum = loc_sum + p;
		//}
		
		
		sum_array[trank] = loc_sum;
	}
	
	for(int i = 0 ; i < tc ; i++)
	{
		sum = sum + sum_array[i];
	}
	
	s = omp_get_wtime() - s;
	printf("\n Sum is %lf.",sum);
	printf("\n Elapsed time is : %lfs. \n",s);
	
	return 0;
}
