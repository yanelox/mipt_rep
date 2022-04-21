#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

//MPI Задание 1

int main(int aggc, char**argv){
    int rank, size, n=200, i, count;
    MPI_Init(&aggc, &argv);
    double a[n], b[n], c[n], *buf;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //printf("Hello_world %d %d\n", rank, size);

    for(i=rank*(int)(n/size); i<(rank+1)*(int)(n/size); i++){
        a[i] = i;
        b[i] = i*i+1/(i+1);
        c[i] = a[i]+b[i];

        //printf("%d\n", i);
    }

    count = (int)(n/size);

    if(rank==0){
        buf = malloc(n*sizeof(double));
        
        for(i=1; i<size; i++){
            MPI_Recv((buf+count*i), count, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for(i=0; i<n; i++){
            printf("%d - %f\n", i, buf[i]);      
        } 

        free(buf);

    }
    else{
        MPI_Send(&a[rank*(int)(n/size)], count, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}