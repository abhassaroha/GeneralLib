#include "Huffman.h"

// in bytes 
#define BUFFER_SIZE	8
#define BYTE_SIZE 8

void writeCharCount(ofstream &stream, unsigned int charCount) {
	stream.put((char)charCount);
	charCount>>=BYTE_SIZE;
	stream.put((char)charCount);
	charCount>>=BYTE_SIZE;
	stream.put((char)charCount);
	charCount>>=BYTE_SIZE;
	// write character count to prevent buffer byte from being decoded
	// its the first word in outputted file
	stream.put((char)charCount);
}

unsigned int readCharCount(ifstream &stream) {
	unsigned int charCount;
	char byte;
	// read character count to prevent last byte from being decoded
	// its the first word in outputted file
	stream.get(byte);
	charCount = byte;
	stream.get(byte);
	charCount|=byte<<8;
	stream.get(byte);
	charCount|=byte<<16;
	stream.get(byte);
	charCount|=byte<<24;
	return charCount;
}
 
#ifdef DEBUG
void printFreqTable(FreqInfo** freqTable) {
	for (int i = 0; i < NUMCHARS; i++) {
			cout<<freqTable[i]->codePoint<<"\t"<<freqTable[i]->freq<<endl;
	}
}
#endif

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

/*************************/
/** Compression methods **/
/*************************/

unsigned int Huffman::buildFrequencyTable() {
	unsigned int charCount = 0;
	if(stream.eof()) {
		cout<<"EOF reached"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (stream.bad()) {
		cout<<"Bad bit set"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (stream.fail()) {
		cout<<"Fail bit set"<<endl;
		exit(EXIT_FAILURE);
	}

	char current;
	freqTable = new FreqInfo*[NUMCHARS]; 
	for (int i = 0; i < NUMCHARS; i++) {
		freqTable[i] = new FreqInfo;
		freqTable[i]->codePoint = (unsigned char) i;
	} 
	stream.get(current);
	while (stream.good()) {
		freqTable[current]->freq++;
		charCount++;
		stream.get(current);
	}
	stream.close();
	return charCount;
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
	FreqInfo** copy = new FreqInfo*[NUMCHARS];
	for (int i = 0; i < NUMCHARS; i++)
		copy[i] = freqTable[i];
	threeWayQuickSort(copy, 0, NUMCHARS - 1);
	while(copy[q1Left]->freq == 0) q1Left++; 
	Queue* queueOne = new Queue(copy, q1Left, NUMCHARS - 1);
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
void Huffman::writePrefixFreeTree(FreqInfo* root) {
	if (root->left == NULL) {
		// leaf node
		writeBit(stream, true);
		// write length of huffman code
		writeByte(stream, root->codePoint);
		root->fieldLength = fieldLength; 
		root->bitField = new bool[fieldLength];
		// write the huffman code
		for (int i = 0; i < fieldLength; i++) {
			root->bitField[i] = bitField[i];
		}
	}
	else {
		// non-leaf node
		writeBit(stream, false);	
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

void Huffman::writeCompressedText() {
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
			writeBit(outStream, node->bitField[i]);
		}
	}
	inStream.close();
}

/***************************/
/** Decompression methods **/
/***************************/

// read in the prefix free tree from file to be decoded
void Huffman::readPrefixFreeTree() {
	if(stream.eof()) {
		cout<<"EOF reached"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (stream.bad()) {
		cout<<"Bad bit set"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (stream.fail()) {
		cout<<"Fail bit set"<<endl;
		exit(EXIT_FAILURE);
	}
	mRoot = new FreqInfo;
	parsePrefixFreeTree(mRoot, stream);
}

// do a post order traversal and regenerate the prefix free tree
void Huffman::parsePrefixFreeTree(FreqInfo* root) {
	bool current = readBit(stream);
	// leaf node
	if (current) {
		root->codePoint = readByte(stream);
		root->fieldLength = fieldLength; 
		root->bitField = new bool[fieldLength];
		// write the huffman code
		for (int i = 0; i < fieldLength; i++) {
			root->bitField[i] = bitField[i];
		}
	}
	else { // non leaf
		root->left = new FreqInfo;
		root->right = new FreqInfo;
		bitField[fieldLength++] = false;
		parsePrefixFreeTree(root->left, stream);
		bitField[fieldLength++] = true;
		parsePrefixFreeTree(root->right, stream);
	}
	fieldLength--;
}

// Go through the remaining file and regenerate the original
// characters.
void Huffman::decodeCompressedText(unsigned int charCount) {
	FreqInfo* current = mRoot;
	while(charCount > 0) {
		if (current->left == NULL) {
			writeByte(outStream, current->codePoint);
			charCount--;
			current = mRoot;
		}
		else {
			if (readBit(inStream)) {
				current = current->right;
			}
			else {
				current = current->left;
			}
		}
	}
	outStream.close();
}

/*******************/
/** Public methods */
/*******************/

void Huffman::encode() {
	unsigned int charCount = buildFrequencyTable();
	writeCharCount(stream, charCount);
	buildPrefixFreeTree();
	writePrefixFreeTree(mRoot, stream);
	writeCompressedText(stream);
	// align to byte
	flushBuffer(stream);
	stream.close();
	cout<<"Read bytes "<<inBytes<<"\tWrote bytes "<<outBytes<<endl;
}

void Huffman::decode() {
	unsigned int charCount = readCharCount(inStream);
	readPrefixFreeTree(inStream);
	decodeCompressedText(inStream, charCount);
	inStream.close();
	cout<<"Read bytes "<<inBytes<<"\tWrote bytes "<<outBytes<<endl;
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
