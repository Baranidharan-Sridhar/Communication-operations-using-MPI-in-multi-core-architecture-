#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#endif

int main( int argc, char *argv[] )
{
    int my_rank, pr_size;
    int chunk_size = 128;
    int i;
    int *sndbuff;
    int *recbuff;
	struct timeval stop, start;
    int status, gstatus;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&pr_size);
    for ( i=1 ; i < argc ; ++i ) {
        if ( argv[i][0] != '-' )
            continue;
        switch(argv[i][1]) {
            case 'm':
                chunk_size = atoi(argv[++i]);
                break;
            default:
                fprintf(stderr, "Unrecognized argument %s\n", argv[i]);fflush(stderr);
                MPI_Abort(MPI_COMM_WORLD,EXIT_FAILURE);
        }
    }
    sndbuff = (int *)malloc(pr_size*chunk_size*sizeof(int));
    recbuff = (int *)malloc(pr_size*chunk_size*sizeof(int));
    
    for ( i=0 ; i < pr_size*chunk_size ; i++ ) {
        sndbuff[i] = my_rank + 1;
        recbuff[i] = 0;
    }
	float sum=0.0;
	for(i=0; i<100; i++){
		gettimeofday(&start, NULL);	
		MPI_Alltoall(sndbuff, chunk_size, MPI_INT, recbuff, chunk_size, MPI_INT, MPI_COMM_WORLD);
		gettimeofday(&stop, NULL);
		sum= (float) sum + (float)(stop.tv_usec - start.tv_usec);
		//printf("sum is %f", (float)sum);
	}
	
    free(sndbuff);
    free(sndbuff);
	if(my_rank==0)
		printf("time is %f \n", ((float)(sum))/100.0);
    MPI_Finalize();
    return(EXIT_SUCCESS);
}
