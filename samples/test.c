#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <time.h>
#include <omp.h>
#include "rtnice.h"

int fib(n)
{	
	if(n == 0) 
		return 0;
	else if(n == 1)
		return 1;
	else 
		return fib(n - 1) + fib(n - 2);
}

int main()
{
	int pid;
	long s_runtime;

	double start_time;
	double time;
	int i;

	printf("Time taken without soft realtime guarantees:\n");
	start_time = omp_get_wtime();
	for(i = 0; i < 4; i++)
	{
		if(fork() == 0)
		{
			int result = fib(40);
			time = omp_get_wtime() - start_time;
			printf("Processes %d: %f sec\n", i + 1, time);
			exit(0);
		}
	}
	while(i > 0)
	{
		wait(NULL);
		i--;
	}

	printf("Time taken with soft realtime guarantees:\n");
	start_time = omp_get_wtime();
	for(i = 0; i < 4; i++)
	{
		if(fork() == 0)
		{
			switch(i)
			{
				case 0:		s_runtime = 40000000000;
						break;
				case 1:		s_runtime = 30000000000;
						break;
				case 2:		s_runtime = 20000000000;
						break;
				case 3:		s_runtime = 10000000000;
						break;
				default:	s_runtime = 0;
			}
			long tmp = rtnice(getpid(), s_runtime);
			int result = fib(40);
			time = omp_get_wtime() - start_time;
			printf("Process %d: %f sec\n", i + 1, time);
			exit(0);
		}
	}
	while(i > 0)
	{
		wait(NULL);
		i--;
	}
	

	return 0;

}
