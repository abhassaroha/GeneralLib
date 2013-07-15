#ifndef LCS_H
#define LCS_H

#include <iostream>
#include <stdlib.h>

using namespace std;

class LCS {
	private:
		char* mFile1;
		char* mFile2;
	public:
		LCS(char* file1, char* file2)
			:mFile1(file1), mFile2(file2) {}
		// Simple dynamic programming solution
		void generateDiffDP();
		// James W. Hunt and M. Douglas McIlroy (June 1976). 
		// "An Algorithm for Differential File Comparison". 
		// Computing Science Technical Report, Bell Laboratories 41.
		void generateDiffHM();
};

#endif
