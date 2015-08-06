#include <stdio.h>
#include <omp.h>
#include <time.h>
#include "grid/grid.h"


void method_cuociente(Grid *grid, int number_of_threads){
	int thread_id;
	
	#pragma omp parallel shared (grid) private (thread_id)
	{
		thread_id = omp_get_thread_num();
		int m = grid->get_m();
		int max = m * m * m;
		int val = thread_id*max/number_of_threads;
		int last = (thread_id + 1)*max/number_of_threads;
		
		while (val < last && val < max) 
		{
			grid->next_state_cell(val / (m * m), (val % (m * m)) / m,  (val % (m * m)) % m);
			//printf("cell(%d, %d, %d) number %d was calculated by the thread %d\n", val / (m * m), (val % (m * m)) / m,  (val % (m * m)) % m, val, thread_id);
			val++;
		}
		
	}
}

void method_modulo(Grid *grid, int number_of_threads){
	int thread_id;
	
	#pragma omp parallel shared (grid) private (thread_id)
	{
		thread_id = omp_get_thread_num();
		int m = grid->get_m();
		int val = thread_id, max = m * m * m;
		
		while (val < max) 
		{
			grid->next_state_cell(val / (m * m), (val % (m * m)) / m,  (val % (m * m)) % m);
			//printf("cell(%d, %d, %d) number %d was calculated by the thread %d\n", val / (m * m), (val % (m * m)) / m,  (val % (m * m)) % m, val, thread_id);
			val += number_of_threads;	
		}
		
	}
}

void run_experiments()
{
	FILE *output = fopen("../results/result.csv", "wt");
	int num_threads = 16;
	clock_t _begin;
	clock_t _end;
	
	fprintf(output, ",");
	for (int i = 5; i < 25; i++){
		fprintf(output, "%d,%d,", i, i);
	}
	fprintf(output, "\n,");
	for (int i = 5; i < 25; i++){
		fprintf(output, "couciente,modulo,");
	}
	fprintf(output, "\n");
	for (int k = 0; k < 5; k++){
		omp_set_num_threads(num_threads);
		fprintf(output, "%d,", num_threads);
		printf("number of threads %d\n", num_threads);
		
		for (int i = 5; i < 25; i++){
			printf("---> m = %d\n", i);
			
			Grid *grid1 = new Grid(i, 4, 10, 6, 18);
			Grid *grid2 = new Grid(i, 4, 10, 6, 18);
			
			_begin = clock();
			for (int j = 0; j < 100; j++){
				method_cuociente(grid1, num_threads);
				
				grid1->next_state();
			}
			_end = clock();
			fprintf(output, "%.3f,", double(_end - _begin) / CLOCKS_PER_SEC);
			
			_begin = clock();
			for (int j = 0; j < 100; j++){
				method_modulo(grid2, num_threads);
				
				grid2->next_state();
			}
			_end = clock();
			fprintf(output, "%.3f,", double(_end - _begin) / CLOCKS_PER_SEC);
			
			delete grid1;
			delete grid2;
		}
		
		fprintf(output, "\n");
		
		num_threads >>= 1;
	}
}

int main()
{
	//omp_set_num_threads(16);
	//printf("threads num %d", omp_get_num_threads());
	/*#pragma omp parallel
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
	
	Grid *grid = new Grid(3, 7, 17, 13, 18);
	grid->print();
	method_modulo(grid, 16);
	grid->next_state();
	grid->print();
	grid->next_state();
	method_cuociente(grid, 16);
	grid->next_state();
	grid->print();
	
	
	omp_set_num_threads(4);
	
	method_modulo(grid, 4);
	grid->next_state();
	grid->print();
	grid->next_state();
	method_cuociente(grid, 4);
	grid->next_state();
	grid->print();
	//printf("%d\n", _OPENMP);
	*/
	
	run_experiments();
	return 0;
}