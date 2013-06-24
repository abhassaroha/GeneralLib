#include "Huffman.h"

// output buffer
static char buffer;
// current buffer content size
// flush when we have one byte of data
static int bufferSize = 0;
// the bit field to represent huffman code
static bool bitField[NUMCHARS];
// length of the huffman code
static int fieldLength = 0;

// keep appending to buffer till we have enough
// to flush a byte
void appendToBuffer(ofstream &outStream, bool bit) {
	buffer = buffer<<1|bit;
	if (++bufferSize == 8) {
		outStream.put(buffer);
		bufferSize = 0;
		buffer = 0;
	}
}

// output huffman code length before the actual code
void writeFieldLength(ofstream &stream, int length) {
	cout<<"Length "<<fieldLength<<endl;
	// length can max be 8 bits (256) hence only needs bits 0-7
	if (bufferSize != 0) {
		int toFlush = 8 - bufferSize;
		// pick the top toFlush bits of the length
		int mask = (1<<toFlush - 1)<<bufferSize;
		buffer = buffer<<toFlush;
		buffer = buffer|((length&mask)>>bufferSize);
		stream.put(buffer);
		// pick up the remaining bits of length
		mask = (1<<bufferSize - 1);
		buffer = length&mask;
	}
	else stream.put((char)length);
}
 
void printFreqTable(FreqInfo** freqTable) {
	for (int i = 0; i < NUMCHARS; i++) {
			cout<<freqTable[i]->codePoint<<"\t"<<freqTable[i]->freq<<endl;
	}
}

void swap(FreqInfo** source, int a, int b) {
	FreqInfo* temp = source[a];
	source[a] = source[b];
	source[b] = temp;
}

void Huffman::threeWayQuickSort(FreqInfo** inArray, int left, int right) {
	if (left >= right) return;
	int i = left, j = left, k = right;
	int pivot = inArray[left + rand()%(right - left + 1)]->freq;
	while (i <= k) {
		if (inArray[i]->freq < pivot) 
			swap(inArray, i++, j++);
		else if (inArray[i]->freq > pivot)
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
	freqTable = new FreqInfo*[NUMCHARS]; 
	for (int i = 0; i < NUMCHARS; i++) {
		freqTable[i] = new FreqInfo;
		freqTable[i]->codePoint = (char) i;
	} 
	while (inStream.good()) {
		inStream.get(current);
		freqTable[current]->freq++;
	}
	inStream.close();
}

#define CREATE_ROOT() \
	mRoot = new FreqInfo();	\
	mRoot->left = first;		\
	mRoot->right = second;	\
	mRoot->freq = first->freq + second->freq;	\
	queueTwo->push(mRoot)

void Huffman::buildPrefixFreeTree() {
	int q1Left = 0;
	FreqInfo *first, *second;
	threeWayQuickSort(freqTable, 0, NUMCHARS - 1);
	while(freqTable[q1Left]->freq == 0) q1Left++; 
	Queue* queueOne = new Queue(freqTable, q1Left, NUMCHARS - 1);
	// we decrease number of elems by one each iteration and we stop
	// after length - 1 iterations of original array, hence second queue's
	// size is bounded as below.
	Queue* queueTwo = new Queue(new FreqInfo*[NUMCHARS - 1 - q1Left], 0);
	if (queueOne->size() == 1) {
		// handle size one queues, nothing more to do
		mRoot = queueOne->pop();
	}
	else {
		// initially queueTwo is empty
		// handle that case first
		first = queueOne->pop();
		second = queueOne->pop();
		CREATE_ROOT();
		while (queueOne->good() || queueTwo->size() > 1) {
			if (!queueOne->good()) {
				// when queuOne has nothing, choose both from queueTwo
				// while cond check guarantees two elements
				first = queueTwo->pop();
				second = queueTwo->pop();
			}
			else { // when both queues have elements
				// first comes from second queue
				if (queueTwo->peek()->freq < queueOne->peek()->freq) { 
					first = queueTwo->pop();
					if (queueTwo->good()) { //queueTwo could be empty
						if (queueTwo->peek()->freq <  queueOne->peek()->freq)
							second = queueTwo->pop();
						else second = queueOne->pop();
					}
					else {
						second = queueOne->pop();
					}
				}
				else { // first comes from first queue
					first = queueOne->pop();
					if (queueOne->good()) { // frist queue could be empty
						if (queueTwo->peek()->freq <  queueOne->peek()->freq)
							second = queueTwo->pop();
						else second = queueOne->pop();
					}
					else {
						second = queueTwo->pop();
					}
				}
			}
			CREATE_ROOT();
		}
	}
}

// Post order traversal of the prefix tree
void Huffman::writePrefixFreeTree(FreqInfo* root, ofstream& stream) {
	if (root->left == NULL) {
		// leaf node
		appendToBuffer(stream, true);
		// write length of huffman code
		cout<<"Code Point "<<(int)root->codePoint<<"\t";
		writeFieldLength(stream, fieldLength);
		root->fieldLength = fieldLength; 
		root->bitField = new bool[fieldLength];
		// write the huffman code
		for (int i = 0; i < fieldLength; i++) {
			root->bitField[i] = bitField[i];
			appendToBuffer(stream, bitField[i]);
		}
	}
	else {
		// non-leaf node
		appendToBuffer(stream, false);	
		// fieldLength++ - push stack
		bitField[fieldLength++] = false;
		writePrefixFreeTree(root->left, stream);
		// fieldLength++ - push stack
		bitField[fieldLength++] = true;
		writePrefixFreeTree(root->right, stream);
	}
	// pop stack
	fieldLength--;
}

void Huffman::writeCompressedText(ofstream& outStream) {
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
	FreqInfo* node;
	while (inStream.good()) {
		inStream.get(current);
		node = freqTable[current];
		for (int i = 0; i < node->fieldLength; i++) {
			appendToBuffer(outStream, node->bitField[i]);
		}
	}
	inStream.close();
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
	ofstream outStream(mOutFile, ios::out|ios::binary);
	writePrefixFreeTree(mRoot, outStream);
	writeCompressedText(outStream);
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
