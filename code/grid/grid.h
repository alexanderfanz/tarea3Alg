#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <time.h>

class Grid {
	
	public:
		Grid(int m, int p1, int p2, int p3, int p4);
		~Grid();
		void next_state_cell(int x, int y, int z);
		void next_state();
		
	private:
		int ****grid;	
		int current;
		int m;
		int n1;
		int n2;
		int n3;
		int n4;
};

#endif