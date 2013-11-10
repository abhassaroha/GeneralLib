#include "LCS.h"

namespace algorithms {
	void printSyntax() {
		cout<<"Usage:"<<endl;
		cout<<"diff -d/-h file1 file2"<<endl;
	}

	void LCS::generateDiffDSH() {
	}

	void LCS::generateDiffHM() {
	}
}

int main(int argc, char** argv) {
	using namespace algorithms;
	LCS* instance;
	if (argc < 2) {
		cout<<"No argument supplied"<<endl;
		printSyntax();
		exit(EXIT_FAILURE);
	}
	else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h")) {
		printSyntax();
		exit(EXIT_SUCCESS);
	}

	if (argc < 4) {
		cout<<"Wrong usage"<<endl;
		printSyntax();
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1], "-d") == 0) {
		instance = new LCS(argv[2], argv[3]);
		instance->generateDiffDSH();
	}
	else if (strcmp(argv[1], "-m") == 0) {
		instance = new LCS(argv[2], argv[3]);
		instance->generateDiffHM();
	}
	else {
		cout<<"Wrong usage"<<endl;
		printSyntax();
		exit(EXIT_FAILURE);
	}
	return 0;
}
