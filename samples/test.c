#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <time.h>
#include <omp.h>
#include "rtnice.h"

int fib(n){
	
	if (n == 0) 
		return 0;
	else if (n == 1)
		return 1;
	else 
		return fib(n-1) + fib(n-2);
}

int main(){
	int pid;
	long s_runtime;

	double start_time;
	double time;

	printf("Time taken without soft realtime guarantees:\n");
	start_time = omp_get_wtime();

	if (fork == 0){
		int result = fib(40);
		time = omp_get_wtime() - start_time;
		printf("Child process: %f sec\n",time );
		exit(0);
	}
	else{
		int result = fib(40);
		time = omp_get_wtime() - start_time;
		printf("Parent process: %f sec\n",time );
		wait(NULL);

	}

	printf("Time taken with soft realtime guarantees:\n");
	start_time = omp_get_wtime();

	if (fork == 0){
		s_runtime = 1000000000;
		long tmp = rtnice(getpid(), s_runtime);
		int result = fib(40);
		time = omp_get_wtime() - start_time;
		printf("Child process: %f sec\n",time );
		exit(0);
	}
	else{
		s_runtime = 2000000000;
		long tmp = rtnice(getpid(), s_runtime);
		int result = fib(40);
		time = omp_get_wtime() - start_time;
		printf("Parent process: %f sec\n",time );
		wait(NULL);

	}

	return 0;

}