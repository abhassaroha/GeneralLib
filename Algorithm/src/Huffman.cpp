#include "Huffman.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void buildFrequenceTable() {
}

void buildPrefixFreeTree() {
}

void writePrefixFreeTree() {
}

void writeCompressedText() {
}

void binaryToPrefixFreeTree() {
}

void decodeCompressedText() {
}

void writeUncompressedText() {
}

Huffman::Huffman(char* inFile, char* outFile) {
	inFile = inFile;
	outFile = outFile;
}

void Huffman::encode() {
}

void Huffman::decode() {
}

int main(int argc, char** argv) {
	Huffman* instance;
	if (argc < 4) {
		cout<<"Insufficient arguments"<<endl;
		cout<<"\tUsage: huffman -/+ inFile outFile"<<endl;
		exit(EXIT_FAILURE);
	}
	instance = new Huffman(argv[1], argv[2]);

	if (argv[1][0] == '-') {
		instance->encode();
	}
	else if (argv[1][0] == '+') {
		instance->decode();
	}
	else {
		cout<<"Incorrect argument: "<<argv[1][0]<<endl;
		cout<<"\tUsage: huffman -/+ inFile outFile"<<endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}
