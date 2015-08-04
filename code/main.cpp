#include <stdio.h>
#include <omp.h>
#include "grid/grid.h"


void method_cuociente(){}

void method_modulo(){}

void run_experiments()
{
	int num_threads = 1;
	
	for (int k = 0; k < 5; k++){
		omp_set_num_threads(num_threads);
		
		for (int i = 5; i < 25; i++){
			
		}
		
		num_threads <<= 1;
	}
}

int main()
{
	omp_set_num_threads(4);
	
	#pragma omp parallel
	{
	printf("Hola mundo!!!  %d\n", omp_get_thread_num());
	printf("2Hola mundo!!!\n");
	printf("3Hola mundo!!!\n");
	}	
	
	omp_set_num_threads(16);
	
	#pragma omp parallel
	{
	printf("Hola mundo!!!  %d\n", omp_get_thread_num());
	printf("2Hola mundo!!!\n");
	printf("3Hola mundo!!!\n");
	}	
	return 0;
}