#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include "grid/grid.h"


void method_cuociente(Grid *grid, int number_of_threads){
	int thread_id;
	
	#pragma omp parallel shared (grid) private (thread_id)
	{
		thread_id = omp_get_thread_num();
		
		int m = grid->get_m();
		int max = m * m * m;
		int last = (thread_id + 1)*max/number_of_threads;
		
		for (int i = 0; i < 1000; i++) {
			
			int val = thread_id*max/number_of_threads;
			
			while (val < last && val < max) 
			{
				grid->next_state_cell(val / (m * m), (val % (m * m)) / m,  (val % (m * m)) % m);
				//printf("cell(%d, %d, %d) number %d was calculated by the thread %d\n", val / (m * m), (val % (m * m)) / m,  (val % (m * m)) % m, val, thread_id);
				val++;
			}
			
			#pragma omp barrier
			
			#pragma omp single
				grid->next_state();
		}
		
	}
}

void method_modulo(Grid *grid, int number_of_threads){
	int thread_id;
	
	#pragma omp parallel shared (grid) private (thread_id)
	{
		
		thread_id = omp_get_thread_num();
		int m = grid->get_m();
		
		for (int i = 0; i < 1000; i++) {
		
			int val = thread_id, max = m * m * m;
			
			while (val < max) 
			{
				grid->next_state_cell(val / (m * m), (val % (m * m)) / m,  (val % (m * m)) % m);
				//printf("cell(%d, %d, %d) number %d was calculated by the thread %d\n", val / (m * m), (val % (m * m)) / m,  (val % (m * m)) % m, val, thread_id);
				val += number_of_threads;	
			}
			
			#pragma omp barrier
			
			#pragma omp single
				grid->next_state();
		}
		
	}
}

void run_experiments()
{
	FILE *output = fopen("../results/result-time.csv", "wt");
	FILE *output2 = fopen("../results/result-wtime.csv", "wt");
	FILE *output3 = fopen("../results/result-gettimeofday.csv", "wt");
	int num_threads = 1;
	clock_t _begin;
	clock_t _end;
	
	time_t t_begin;
	time_t t_end;
	
	double d_begin;
	double d_end;
	
	struct timeval g_begin, g_end;
	
	
	fprintf(output, ",");
	fprintf(output2, ",");
	fprintf(output3, ",");
	for (int i = 5; i < 25; i++){
		fprintf(output, "%d,%d,", i, i);
		fprintf(output2, "%d,%d,", i, i);
		fprintf(output3, "%d,%d,", i, i);
	}
	fprintf(output, "\n,");
	fprintf(output2, "\n,");
	fprintf(output3, "\n,");
	for (int i = 5; i < 25; i++){
		fprintf(output, "couciente,modulo,");
		fprintf(output2, "couciente,modulo,");
		fprintf(output3, "couciente,modulo,");
	}
	fprintf(output, "\n");
	fprintf(output2, "\n");
	fprintf(output3, "\n");
	
	
	for (int k = 0; k < 5; k++){
		omp_set_num_threads(num_threads);
		fprintf(output, "%d,", num_threads);
		fprintf(output2, "%d,", num_threads);
		fprintf(output3, "%d,", num_threads);
		printf("number of threads %d\n", num_threads);
		
		for (int i = 5; i < 25; i++){
			printf("---> m = %d\n", i);
			
			Grid *grid1 = new Grid(i, 4, 10, 6, 18);
			Grid *grid2 = new Grid(i, 4, 10, 6, 18);
			
			_begin = clock();
			time(&t_begin);
			d_begin = omp_get_wtime();
			gettimeofday(&g_begin, NULL);
			
			method_cuociente(grid1, num_threads);
			
			_end = clock();
			time(&t_end);
			d_end = omp_get_wtime();
			gettimeofday(&g_end, NULL);
			//fprintf(output, "%.3f,", double(_end - _begin) / (CLOCKS_PER_SEC*num_threads));
			fprintf(output, "%.3f,", difftime(t_end, t_begin));
			fprintf(output2, "%.4f,", d_end - d_begin);
			fprintf(output3, "%.4lf,", g_end.tv_sec - g_begin.tv_sec + g_end.tv_usec/1000000.0 - g_begin.tv_usec/1000000.0);
			
			_begin = clock();
			time(&t_begin);
			d_begin = omp_get_wtime();
			gettimeofday(&g_begin, NULL);
			
			method_modulo(grid2, num_threads);
			
			_end = clock();
			time(&t_end);
			d_end = omp_get_wtime();
			gettimeofday(&g_end, NULL);
			//fprintf(output, "%.3f,", double(_end - _begin) / (CLOCKS_PER_SEC*num_threads));
			fprintf(output, "%.3f,", difftime(t_end, t_begin));
			fprintf(output2, "%.4f,", d_end - d_begin);
			fprintf(output3, "%.4lf,", g_end.tv_sec - g_begin.tv_sec + g_end.tv_usec/1000000.0 - g_begin.tv_usec/1000000.0);
			
			delete grid1;
			delete grid2;
		}
		
		fprintf(output, "\n");
		fprintf(output2, "\n");
		fprintf(output3, "\n");
		
		num_threads <<= 1;
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