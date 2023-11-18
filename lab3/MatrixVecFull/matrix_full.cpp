#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int returnSize(char* fname)
{
	FILE* f = fopen(fname, "r");
	int dim = 0;
	double tmp;
	while(fscanf(f, "%lf" , &tmp) != EOF)
		dim++;
	fclose(f);
	return dim;	
}

double* loadVec(char* fname, int n)
{
	FILE* f = fopen(fname, "r");
	double* res = new double[n];
	double* it = res;
	while(fscanf(f,"%lf",it++) != EOF);
	fclose(f);
	return res;
}

double* loadMat(char* fname,int n, int m)
{
	FILE* f = fopen(fname, "r");
	double* res = new double[n*m];
	double* it = res;
	while(fscanf(f,"%lf",it++) != EOF);
	if(m > n)
	{
		for(int i = n*n ; i < n*m  ; i++)
		{
			res[i] = 0;
		}
	}
	fclose(f);
	return res;
}

void logRes(const char* fname, double* res, int n)
{
	FILE* f = fopen(fname,"w");
	for(int i = 0 ; i != n; i++)
		fprintf(f,"%lf ",res[i]);
	fclose(f);	
}

int main(int argc,char* argv[])
{
	int csize;
	int prank;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &csize);
	MPI_Comm_rank(MPI_COMM_WORLD, &prank);
	
	char* vfname = argv[1];
	char* mfname = argv[2];
	int dim;	
	double* mat;
	double* vec;    
	double* tmat; 
	double* lres;
	double* res;
	
	if(prank == 0)
		dim = returnSize(vfname);
		
	MPI_Bcast(&dim,1,MPI_INT,0,MPI_COMM_WORLD); // Broadcasted the dimension to all procceses
	
	if(prank == 0)
		vec = loadVec(vfname,dim);
	else 
		vec = new double[dim];
	
	MPI_Bcast(vec,dim,MPI_DOUBLE,0,MPI_COMM_WORLD);	// Broadcasted the vector that is to be multiplied with matrix
	
	
	//if(prank == 0)
	//	tmat = loadMat(mfname,dim,m);
					
	int limit = (int)ceil((double)dim/csize);
	int m = limit * csize;
	int msize = limit*dim;		
	if(prank == 0)
	{	
		// Should i do this inside the loadMat function? Seg fault possibly appeares here!
		tmat = loadMat(mfname,dim,m);
		//for(int i = dim*dim ; i <= dim*m  ; i++)
		//{
		//	tmat[i] = 0;
		//}
	}
		

	mat = new double[msize];
	MPI_Scatter(tmat,msize,MPI_DOUBLE,mat,msize,MPI_DOUBLE,0,MPI_COMM_WORLD);
		
	int to = (int)ceil((float)dim / csize);
	lres = new double[to];	 		
	/////////////////////////////////////
	for(int i = 0; i != to ; ++i)
	{
		double s = 0;
		for(int j = 0; j != dim; ++j)
			s += mat[i*dim+j] * vec[j];
			
		lres[i] = s;
	}
	
	if(prank == 0)
		res = new double[dim];
		
	MPI_Gather(lres,to,MPI_DOUBLE,res,to,MPI_DOUBLE,0,MPI_COMM_WORLD);
	
	if(prank == 0)
	{	
		logRes("res.txt",res,dim);
	}	
	
	if(prank == 0)
	{
		delete [] tmat;
		delete [] res;
	}
	
	delete [] vec;
	delete [] mat;
	delete [] lres;
	
	MPI_Finalize();
	
	return 0;
	
}





