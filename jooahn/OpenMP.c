#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	/* 
	   sequential code 
	   ... 
	 */

	#pragma omp parallel
	{
		printf("I am a parallet region.");
	}

	/*
	   sequential code
	   ...
	 */

	return 0;
}