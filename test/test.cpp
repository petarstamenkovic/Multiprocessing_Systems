#include <iostream>
#include <vector>
using namespace std;

vector<int> divide(int size,int num_arrays)
{
    vector<int> result;
    int help = num_arrays;
    int left_size,right_size;
    
    while(help > 1)
    {
	    left_size = size/2;
	    right_size = size - left_size;
	    result.push_back(left_size);
	    result.push_back(right_size);
	    help = help / 2;
	    
	    cout << "\nHelp variable is : " << help << endl;
	    cout << "\nLeft size is : " << help << endl;
	    cout << "\nRight size is : " << help << endl;
	    
	    divide(left_size,help);
	    divide(right_size,help);
    }
    return result;
}

int main() {
  
    const int size = 15;
    cout << "\nLine before reccurent call" << endl;
    vector<int> subarraySizes = divide(15,4);

    cout << "Subarray Sizes: ";
    for (int size : subarraySizes) {
    	cout << size << " ";
    }
    	cout << endl;

    return 0;
}

