#include <stdio.h>
#include <mpi.h>

int returnSize(char* fname)
{
	FILE* f = fopen(fname, "r");
	int dim = 0;
	double tmp;
	while(fscanf(f, "%lf", &tmp) != EOF)
		dim++;
	fclose(f);
	return dim;
}

double* loadVec(char* fname, int n)
{
	FILE* f = fopen(fname, "r");
	double* res = new double[n];
	double* it = res;
	while(fscanf(f, "%lf", it++) != EOF);
	fclose(f);
	return res;
}

double* loadMat(char* fname, int n)
{
	FILE* f = fopen(fname, "r");
	double* res = new double[n*n];
	double* it = res;
	while(fscanf(f, "%lf", it++) != EOF);
	fclose(f);
	return res;
}

void logRes(const char* fname, double* res, int n)
{
	FILE* f = fopen(fname, "w");
	for (int i = 0; i != n; ++i)
		fprintf(f, "%lf ", res[i]);
	fclose(f);
}

int main(int argc, char* argv[])
{
	int csize;
	int id;

	char* vfname = argv[1];
	char* mfname = argv[2];
	int dim;
	int rnum; // Row number for calculation
	double* mat = NULL;
	double* vec = NULL;
	double* tmat = NULL;
	double* lres = NULL;
	double* res = NULL;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &csize);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	if (id == 0)
		dim = returnSize(vfname);

	MPI_Bcast(&dim, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (id == 0)
		vec = loadVec(vfname, dim);
	else
		vec = new double[dim];

	MPI_Bcast(vec, dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if (id == 0)
	    tmat = loadMat(mfname, dim);

	rnum = dim / csize;
	if (id < dim % csize) rnum++;

	mat = new double[rnum * dim];
	printf("%d - %d\n", id , rnum * dim);
	MPI_Barrier(MPI_COMM_WORLD);

	int *sendcnts = NULL;
	int *displs = NULL;
	if (id == 0)
	{
	    sendcnts = new int [csize];
	    displs = new int [csize];
	    int val;
	    int acc = 0;
	    for (int i = 0; i != csize; ++i)
	    {
		val = dim / csize;
		if (i < dim % csize) val++;
		val *= dim;
		sendcnts[i] = val;
		displs[i] = acc;
		acc+= val;
	    }
	}

	MPI_Scatterv(tmat, sendcnts, displs, MPI_DOUBLE, mat, rnum * dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	lres = new double[rnum];

	for (int i = 0; i != rnum; ++i)
	{
	    double s = 0;
	    for (int j = 0; j != dim; ++j)
		s += mat[i*dim+j] * vec[j];
	    lres[i] = s;
	}

	if (id == 0)
	    res = new double[dim];

	if (id == 0)
	{
	    int val;
	    int acc = 0;
	    for (int i = 0; i != csize; ++i)
	    {
		val = dim / csize;
		if (i < dim % csize) val++;
		sendcnts[i] = val;
		displs[i] = acc;
		acc+= val;
	    }
	}

	MPI_Gatherv(lres, rnum, MPI_DOUBLE, res, sendcnts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if (id == 0)
	    logRes("res.txt", res, dim);

	if (id == 0)
	{
	    delete [] tmat;
	    delete [] res;
	    delete [] sendcnts;
	    delete [] displs;
	}

	delete [] vec;
	delete [] mat;
	delete [] lres;

	MPI_Finalize();

	return 0;
}
