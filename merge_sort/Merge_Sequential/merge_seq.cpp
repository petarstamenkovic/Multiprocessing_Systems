// C++ program for Merge Sort 
#include <iostream> 
#include<cstdlib>
#include <chrono>
#include <vector>
using namespace std::chrono;
using namespace std; 

// Merges two subarrays of array[]. 
// First subarray is arr[begin..mid] 
// Second subarray is arr[mid+1..end] 
void merge(std::vector<int>& array, int const left, 
		int const mid, int const right) 
{ 
	auto const subArrayOne = mid - left + 1; 
	auto const subArrayTwo = right - mid; 

	// Create temp vectors
	std::vector<int> leftArray(subArrayOne);
	std::vector<int> rightArray(subArrayTwo);

	// Uncomment for an array variant
	// Create temp arrays 
	//auto *leftArray = new int[subArrayOne], 
	//	*rightArray = new int[subArrayTwo]; 

	// Copy data to temp arrays leftArray[] 
	// and rightArray[] 
	for (auto i = 0; i < subArrayOne; i++) 
		leftArray[i] = array[left + i]; 
	for (auto j = 0; j < subArrayTwo; j++) 
		rightArray[j] = array[mid + 1 + j]; 

	// Initial index of first sub-array 
	// Initial index of second sub-array 
	auto indexOfSubArrayOne = 0, 
		indexOfSubArrayTwo = 0; 

	// Initial index of merged array 
	int indexOfMergedArray = left; 

	// Merge the temp arrays back into 
	// array[left..right] 
	while (indexOfSubArrayOne < subArrayOne && 
		indexOfSubArrayTwo < subArrayTwo) 
	{ 
		if (leftArray[indexOfSubArrayOne] <= 
			rightArray[indexOfSubArrayTwo]) 
		{ 
			array[indexOfMergedArray] = 
			leftArray[indexOfSubArrayOne]; 
			indexOfSubArrayOne++; 
		} 
		else
		{ 
			array[indexOfMergedArray] = 
			rightArray[indexOfSubArrayTwo]; 
			indexOfSubArrayTwo++; 
		} 
		indexOfMergedArray++; 
	} 
	
	// Copy the remaining elements of 
	// left[], if there are any 
	while (indexOfSubArrayOne < subArrayOne) 
	{ 
		array[indexOfMergedArray] = 
		leftArray[indexOfSubArrayOne]; 
		indexOfSubArrayOne++; 
		indexOfMergedArray++; 
	} 

	// Copy the remaining elements of 
	// right[], if there are any 
	while (indexOfSubArrayTwo < subArrayTwo) 
	{ 
		array[indexOfMergedArray] = 
		rightArray[indexOfSubArrayTwo]; 
		indexOfSubArrayTwo++; 
		indexOfMergedArray++; 
	} 
} 

// begin is for left index and end is 
// right index of the sub-array 
// of arr to be sorted */ 
void mergeSort(vector<int>& array, 
			int const begin, 
			int const end) 
{ 
	// Returns recursively 
	if (begin >= end) 
		return; 

	auto mid = begin + (end - begin) / 2; 
	mergeSort(array, begin, mid); 
	mergeSort(array, mid + 1, end); 
	merge(array, begin, mid, end); 
} 

// UTILITY FUNCTIONS 
// Function to print an array 
void printArray(int A[], int size) 
{ 
	for (auto i = 0; i < size; i++) 
		cout << A[i] << " "; 
	cout<<endl; 
} 

// Driver code 
int main() 
{ 
	time_t t;
   	int n,x;
   	cout << "Insert a lenght of an array: " << endl;
  	cin >> n ;
    
   	 //int inital_array[n];
    	std::vector<int> array;
    
    	auto start = high_resolution_clock::now();
    	//for(int i = 0; i<n ; i++)
   	 //{
   	 //   srand(i);
   	 //    inital_array[i] = rand()%500;
   	 //}
    
	for(int i = 0 ; i < n ; i++)
	{
		srand((unsigned) time(&t) + i);
		//array[i] = rand()%200;
		array.push_back(rand()%500); 
	}
    
	//cout << "Given array is "<<endl; 
	//printArray(inital_array, n); 

	mergeSort(array, 0, n - 1); 

	//cout << "Sorted array is "<<endl; 
	//printArray(inital_array, n); 
	
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "Elapsed time is : " << duration.count() << "ms."<< endl;

	return 0; 
} 
