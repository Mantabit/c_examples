#include <mpi.h>
#include <stdio.h>

/*
Compilation Hints:

Load the GPI C compiler using:	module load new pgi
Load the mpi libraries using:	module load new open_mpi

Compiling the mpi application:	gpicc
Running the mpi application:	bsub -n 4 mpirun -np 4 ./mpi_test.out
								or
								mpirun

*/

int main(int argc,char** argv)
{
	int rank,size;
	int data[100];
	
	//we start the program with the shell command 'mpiexec -np 16 test.out'
	//this will create one communicator MPI_COMM_WORLD with 16 processes in it
	MPI_Init(&argc,&argv);
	//get the rank of the current process in the stated communicator
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	printf("Process with rank %d reporting...\n",rank);
	
	/*
	if(rank==0){
		//MPI_SEND(dataptr,count,datatype,sourcerank,msgtag,communicator)
		//send some data to process 1 in MPI_COMM_WORLD
		MPI_Send(data,100,MPI_INT,1,0,MPI_COMM_WORLD);
	}
	else if(rank==1){
		//MPI_SEND(dataptr,count,datatype,sourcerank,msgtag,communicator,status)
		//receive some data from process 0 in MPI_COMM_WORLD
		MPI_Recv(data,100,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	* */
	
	//terminate MPI
	MPI_Finalize();
	return 0;
}
