#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	#pragma omp parallel 
	{
		int trank = omp_get_thread_num();
		int tc = omp_get_num_threads();
		printf("Hello from thread %d of %d. \n",trank,tc);
	}
	
	return 0;
}
