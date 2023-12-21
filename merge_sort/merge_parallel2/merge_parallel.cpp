#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// Merges two subarrays of array[].
// First  subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(std::vector<int>& array, int const left, int const mid,
		int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create temp vectors
	std::vector<int> leftArray(subArrayOne);
	std::vector<int> rightArray(subArrayTwo);

	// Uncomment this for an array version
	// Create temp arrays
	//auto *leftArray = new int[subArrayOne],
	//	*rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne]
			<= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray]
				= leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	// Uncomment for an array variant
	//delete[] leftArray;
	//delete[] rightArray;
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int>& array, int const begin, int const end)
{
	if (begin >= end)
		return;
	int mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

void checkSort(const std::vector<int>& array)
{
	int flag = 0;
	int min;
	
	for(int i = 1 ; i < (int)array.size() ; i++)
	{
		min = array[i-1];
		if(array[i] < min)
		{
			flag = 1;
			break;
		}
	}
	
	if(flag == 0)
		printf("\nArray sorted well.\n");
	else 
		printf("\nArray not sorted well.\n");	
}

void printVector(const std::vector<int>& array)
{
	for(int i = 0; i < (int)array.size(); i++)
	{
		printf("%d ",array[i]);
	}
}

// MAIN CODE ------------------------------------------------------------------------------------
int main(int argc, char*argv[])
{	
	//time_t t;
	// Number of threads 
	int tc = strtol(argv[1],NULL,10);
	int n = strtol(argv[2],NULL,10); 
	
	std::vector<int> array;
	srand(time(NULL));
	for(int i = 0 ; i < n ; i++)
	{
		array.push_back(rand()%200); 
	}
	
	// Store an array in input file
	FILE *fp_in = fopen("input.txt","w");
	if(fp_in == NULL)
	{
		cout << "Failed to open a file" << endl;
		return 1;
	}
	for(int i = 0; i < n ; i++)
	{
		fprintf(fp_in,"%d ",array[i]);
	}
	fclose(fp_in);
	cout << "Input is stored in input.txt." << endl;
	
	// Start measuring time
	double s = omp_get_wtime();
	#pragma omp parallel num_threads(tc)
	{ 
	    int trank = omp_get_thread_num();	
	    double i = (double) trank;
	    double ds =(double) tc;
	    int loc_start  = n*i/ds;
	    int loc_end = n*(i + 1)/ds-1;
	    mergeSort(array,loc_start,loc_end);
	}
	
	//printVector(array);
	merge(array,0,n/2-1,n-1);

	
	// End measuring time
 	s = (omp_get_wtime() - s) * 1000.0;	
	cout << "\nTime elapsed is : " << s << "ms" << endl;
	
	
	FILE *fp_out = fopen("res.txt","w");
	if(fp_out == NULL)
	{
		cout << "Failed to open a file" << endl;
		return 1;
	}
	
	for(int i = 0; i < n ; i++)
	{
		fprintf(fp_out,"%d ",array[i]);
	}
	fclose(fp_out);
	cout << "Results are stored in res.txt." << endl;
	
	checkSort(array);
	return 0;
}


