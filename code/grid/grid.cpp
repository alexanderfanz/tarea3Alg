#include "grid.h"
#include <stdio.h>

Grid::Grid(int mm, int p1, int p2, int p3, int p4){
	
	m = mm;
	n1 = p1;
	n2 = p2;
	n3 = p3;
	n4 = p4;
	
	srand (time(NULL));
	
	grid = new int***[2];
	
	grid[0] = new int**[m];
	grid[1] = new int**[m];
	
	for (int i = 0; i < m; i++){
		grid[0][i] = new int*[m];
		grid[1][i] = new int*[m];
	}
	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++){
			grid[0][i][j] = new int[m];
			grid[1][i][j] = new int[m];
		}
	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < m; k++)
				grid[0][i][j][k] = rand() % 2;
				
	current = 0;
			
}

Grid::~Grid(){
	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++){
			delete [] grid[0][i][j];
			delete [] grid[1][i][j];
		}
	
	for (int i = 0; i < m; i++){
		delete [] grid[0][i];
		delete [] grid[1][i];
	}
		
	delete [] grid[0];
	delete [] grid[1];
	
	delete [] grid;
			
}

void Grid::next_state_cell(int x, int y, int z){
	
	int tot = 0;
	int arr[3];
	arr[0] = m - 1; arr[1] = 0; arr[2] = 1;
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				tot += grid[current][(x + arr[i]) % m][(y + arr[j]) % m][(z + arr[k]) % m];
	tot -= grid[current][x][y][z];
	
	grid[(current + 1) % 2][x][y][z] = (!grid[current][x][y][z] && tot >= n1 && tot < n2) || 
										(grid[current][x][y][z] && tot >= n3 && tot < n4) ? 1 : 0;
}

void Grid::next_state(){
	current = (current + 1) % 2;
}

int Grid::get_m(){
	return m;
}

void Grid::print()
{
	printf("hi\n");
	for (int i = 0; i < m; i++){
		
		for (int j = 0; j < m; j++) {
			
			for (int k = 0; k < m; k++)
				printf("%d ", grid[current][i][j][k]);
			printf("\n");
		}
		
		printf("\n");
	}
}