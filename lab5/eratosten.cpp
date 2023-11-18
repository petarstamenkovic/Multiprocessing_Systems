#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
	int n,strategy;
	std::vector<int> res;
	printf("Upper limit for prime calculator is : ");
	scanf("%d",&n);
	printf("\nInsert a number of strategy to continute.");
	printf("\n1 - Static");
	printf("\n2 - Dynamic");
	printf("\n3 - Guided");
	printf("\n4 - Auto\n");
	scanf("%d",&strategy);
	
	bool prime[n + 1];
        memset(prime, true, sizeof(prime));
        double s = omp_get_wtime();
        int temp = (int)ceil(sqrt(n));

	switch (strategy)
	{
	case 1 :
		#pragma omp parallel for schedule(static,1)
	    	for (int p = 2; p <= temp; p++) 
	    	{

			if (prime[p] == true) 
			{
			    for (int i = p * p; i <= n; i += p)
				prime[i] = false;
			}
		}
		for (int p = 2; p <= n; p++)
		if (prime[p] == true)
		{
		    //cout << p << " ";
		    res.push_back(p);
		} 
		break;
	case 2 :
		#pragma omp parallel for schedule(dynamic,1)
	    	for (int p = 2; p <= temp; p++) 
	    	{

			if (prime[p] == true) 
			{
			    for (int i = p * p; i <= n; i += p)
				prime[i] = false;
			}
		}
		for (int p = 2; p <= n; p++)
		if (prime[p] == true)
		{
		    //cout << p << " ";
		    res.push_back(p);
		} 
		break;
		
	case 3 :
		#pragma omp parallel for schedule(guided,1)
	    	for (int p = 2; p <= temp; p++) 
	    	{

			if (prime[p] == true) 
			{
			    for (int i = p * p; i <= n; i += p)
				prime[i] = false;
			}
		}
		for (int p = 2; p <= n; p++)
		if (prime[p] == true)
		{
		    //cout << p << " ";
		    res.push_back(p);
		} 
		break;
	
	case 4 :
		#pragma omp parallel for schedule(auto)
	    	for (int p = 2; p <= temp; p++) 
	    	{

			if (prime[p] == true) 
			{
			    for (int i = p * p; i <= n; i += p)
				prime[i] = false;
			}
		}
		for (int p = 2; p <= n; p++)
		if (prime[p] == true)
		{
		    //cout << p << " ";
		    res.push_back(p);
		} 
		break;
	
	default : 
		printf("\nInavlid strategy pick. ");
		
	}	
	s = omp_get_wtime() - s;
	
	cout << "\nTime elapsed is : " << s << "s" << endl;
	
	FILE *fp = fopen("res.txt","w");
	if(fp == NULL)
	{
		cout << "Failed to open a file" << endl;
		return 1;
	}
	
	for(int i = 0; i < (int)res.size() ; i++)
	{
		fprintf(fp,"%d ",res[i]);
	}
	fclose(fp);
	cout << "Results are stored in res.txt." << endl;
	return 0;	
	
}
	
	
	
