#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
	#pragma omp parallel
	{
		printf("Printf 1 of %d thread \n", omp_get_thread_num());
		#pragma omp barrier
		printf("Printf 2 of %d thread \n", omp_get_thread_num());
	}
	
	return 0;
}
