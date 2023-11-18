#include <stdio.h>
#include <mpi.h>

double getInput()
{
    double res;
    printf("Number : ");
    fflush(stdout);
    scanf("%lf",&res);
    return (double) (res);
}

int main(int argc, char* argv[])
{
    double n;
    double sum = 0;
    int csize, prank;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &csize);
    MPI_Comm_rank(MPI_COMM_WORLD, &prank);

    if(prank == 0)
    {
        n = getInput();
    }

    MPI_Bcast(&n,1,MPI_DOUBLE,0,MPI_COMM_WORLD);    // Proces 0 salje unos svima u COMM_WORLD

    double s = MPI_Wtime();
    double i = (double) prank;
    double ds =(double) csize;
	
    // Segment koda za cirkularnu raspodelu	
    while (i <= n)
    {
        sum = sum + i;
        i = i + ds;
    }

    double tsum;    // Total sum, promenljiva u kojoj se smesta suma svih procesa pojedinacno (sum)
    MPI_Reduce(&sum, &tsum, 1, MPI_DOUBLE, MPI_SUM, 0 , MPI_COMM_WORLD);

    double e = MPI_Wtime();
    double d = e - s;
    double mind;    // Maksimalno vreme, promenljiva u kojoj ce se smestiti maximalno vreme od svih procesa pojedinacno (d)
    MPI_Reduce(&d, &mind, 1, MPI_DOUBLE, MPI_MAX, 0 , MPI_COMM_WORLD);
    if(prank == 0)
    {
        printf("Sum of first %f integers is %f : \n", n,tsum);
        printf("Elapsed time : %f \n", mind);
    }
    MPI_Finalize();
    return 0;
        

}
