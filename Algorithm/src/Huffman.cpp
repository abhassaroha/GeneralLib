#include "Huffman.h"

using namespace std;

void swap(int* source, int a, int b) {
	int temp = source[a];
	source[a] = source[b];
	source[b] = temp;
}

void Huffman::threeWayQuickSort(int* inArray, int left, int right) {
	if (left >= right) return;
	int i = left, j = left, k = right;
	int pivot = inArray[left + rand()%(right - left + 1)];
	while (i <= k) {
		if (inArray[i] < pivot) 
			swap(inArray, i++, j++);
		else if (inArray[i] > pivot)
			swap(inArray, i, k--);
		else i++;
	}
	threeWayQuickSort(inArray, left, j - 1);
	threeWayQuickSort(inArray, k + 1, right);
}

void Huffman::buildFrequencyTable() {
	ifstream inStream(mInFile, ios::in|ios::binary);    
	if(inStream.eof()) {
		cout<<"EOF reached"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (inStream.bad()) {
		cout<<"Bad bit set"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (inStream.fail()) {
		cout<<"Fail bit set"<<endl;
		exit(EXIT_FAILURE);
	}

	char current;
	freqTable = new int[NUMCHARS]; 
	for (int i = 0; i < NUMCHARS; i++) {
		freqTable[i] = 0;
	} 
	while (inStream.good()) {
		inStream.get(current);
		freqTable[current]++;
	}
	for (int i = 0; i < NUMCHARS; i++) {
		if (freqTable[i] != 0)
			cout<<(char)i<<"\t"<<freqTable[i]<<endl;
	}
	inStream.close();
}

void Huffman::buildPrefixFreeTree() {
	threeWayQuickSort(freqTable, 0, NUMCHARS - 1);
}

void Huffman::writePrefixFreeTree() {
}

void Huffman::writeCompressedText() {
}

void Huffman::binaryToPrefixFreeTree() {
}

void Huffman::decodeCompressedText() {
}

void Huffman::writeUncompressedText() {
}

void Huffman::encode() {
	buildFrequencyTable();
	buildPrefixFreeTree();
	writePrefixFreeTree();
	writeCompressedText();
}

void Huffman::decode() {
}

int main(int argc, char** argv) {
	Huffman* instance;
	if (argc < 4) {
		cout<<"Insufficient arguments"<<endl;
		cout<<"\tUsage: huffman -/+ inFile outFile"<<endl;
		cout<<"\t-\tEncode file"<<endl;
		cout<<"\t+\tDecode file"<<endl;
		exit(EXIT_FAILURE);
	}
	instance = new Huffman(argv[2], argv[3]);

	if (argv[1][0] == '-') {
		instance->encode();
	}
	else if (argv[1][0] == '+') {
		instance->decode();
	}
	else {
		cout<<"Incorrect argument: "<<argv[1][0]<<endl;
		cout<<"\tUsage: huffman -/+ inFile outFile"<<endl;
		cout<<"\t-\tEncode file"<<endl;
		cout<<"\t+\tDecode file"<<endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}
