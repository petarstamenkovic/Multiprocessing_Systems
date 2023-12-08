#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>
// C++ program for Merge Sort
#include <bits/stdc++.h>
using namespace std;

// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], int const left, int const mid,
		int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	// Create temp arrays
	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];

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
	delete[] leftArray;
	delete[] rightArray;
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

// UTILITY FUNCTIONS
// Function to print an array
void printArray(int A[], int size)
{
	for (int i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << endl;
}

// Driver code
int main(int argc, char*argv[])
{	
	time_t t;
	// Number of threads 
	int tc = strtol(argv[1],NULL,10);
	int n = strtol(argv[2],NULL,10); 
	
	int array[n];// = {9,8,10,5,4,1,8,2};
	for(int i = 0 ; i < n ; i++)
	{
		srand((unsigned) time(&t) + i);
		array[i] = rand()%50; 
	}
	

	
	cout << "Given array is \n";
	printArray(array, n);
/*
	#pragma omp parallel num_threads(tc) 
	{
	
	    int trank = omp_get_thread_num();	
	    double i = (double) trank;
	    double ds =(double) tc;
	    int limit = (int)floor(n/ds);
	    int loc_start = i*limit;
	    int loc_end = limit*i+(limit-1);
	    mergeSort(array,loc_start,loc_end);
	    
	}

	mergeSort(array, 0, n - 1);
*/	

	#pragma omp parallel num_threads(tc) 
	{
	
	    int trank = omp_get_thread_num();	
	    double i = (double) trank;
	    double ds =(double) tc;
	    int loc_start  = n*i/ds;
	    int loc_end = n*(i + 1)/ds-1;
	    printf("Start = %d, end = %d\n", loc_start, loc_end);
	    mergeSort(array,loc_start,loc_end);
	    
	}

	mergeSort(array, 0, n - 1);


	// Loop that tests if elementes are sorted!
	for(int i = 0 ; i!=n ; i++)
	{
		if(array[i] > array[i+1])
			printf("\nNot good!\n");
		
	}



	cout << "\nSorted array is \n";
	printArray(array, n);
	return 0;
}

// This code is contributed by Petar Stamenkovic
// This code was revised by Joshua Estes
