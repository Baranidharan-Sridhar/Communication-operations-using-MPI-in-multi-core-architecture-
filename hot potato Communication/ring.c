
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


int main(int argc, char** argv) {
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  
  struct timeval stop, start;
  float sum=0.0;
  int size = 512;
  int token[size];
  int i,j,k,l;
  // Receive from the lower process and send to the higher process. Take care
  // of the special case when you are the first process to prevent deadlock.
  for (j=0;j<100;j++){
  while (world_rank != 0) {
    MPI_Recv(&token, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    //printf("Process %d received from process %d\n", world_rank,
           //world_rank - 1);
	MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0,
           MPI_COMM_WORLD);	   
  } if(world_rank==0) {
    // Set the token's value if you are process 0
    //token = -1;
	
	//	printf("Process\n");
		for(i=0;i<size;i++){
			token[i]= i+100;
		}
	gettimeofday(&start, NULL);	
	for(k=0;k<size;k++)
		MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0,
           MPI_COMM_WORLD);
	//printf("Process %d time is ", start.tv_usec);
  }
 
  // Now process 0 can receive from the last process. This makes sure that at
  // least one MPI_Send is initialized before all MPI_Recvs (again, to prevent
  // deadlock)
  while (world_rank == 0 && l< size) {
	  l++;
    MPI_Recv(&token, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
			 if(l==size-1){
				 printf("timefffffffffffffffffffff ");
				gettimeofday(&stop, NULL);
				sum= (float) sum + (float)(stop.tv_usec - start.tv_usec);
			 }
    //printf("Process %d received from process %d\n", world_rank,
      //    world_size - 1);
	// sum= (float) sum + (float)(stop.tv_usec - start.tv_usec);
	//printf("time taken is %lu and time %f \n", (stop.tv_usec - start.tv_usec), sum
          // );
  }
  //sum= (float) sum + (float)(stop.tv_usec - start.tv_usec);
}

if((float)sum > 0.0)
	printf("time taken for hot potato test for %d processors is %f using 100 iterations \n", world_size, ((float)sum) /(100.0));
MPI_Finalize();
}