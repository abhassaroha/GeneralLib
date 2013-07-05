#include "Huffman.h"

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
	mFileReader->open();
	if(mFileReader->eof()) {
		cout<<"EOF reached"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (mFileReader->bad()) {
		cout<<"Bad bit set"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (mFileReader->fail()) {
		cout<<"Fail bit set"<<endl;
		exit(EXIT_FAILURE);
	}

	char current;
	freqTable = new FreqInfo*[NUMCHARS]; 
	for (int i = 0; i < NUMCHARS; i++) {
		freqTable[i] = new FreqInfo;
		freqTable[i]->codePoint = (unsigned char) i;
	} 
	mFileReader->readByte(current);
	while (mFileReader->good()) {
		freqTable[current]->freq++;
		charCount++;
		mFileReader->readByte(current);
	}
	mFileReader->close();
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
		mFileWriter->writeBit(true);
		// write length of huffman code
		mFileWriter->writeByte(root->codePoint);
		root->fieldLength = fieldLength; 
		root->bitField = new bool[fieldLength];
		// write the huffman code
		for (int i = 0; i < fieldLength; i++) {
			root->bitField[i] = bitField[i];
		}
	}
	else {
		// non-leaf node
		mFileWriter->writeBit(false);	
		// fieldLength++ - push stack
		bitField[fieldLength++] = false;
		writePrefixFreeTree(root->left);
		// fieldLength++ - push stack
		bitField[fieldLength++] = true;
		writePrefixFreeTree(root->right);
	}
	// pop stack
	fieldLength--;
}

void Huffman::writeCompressedText() {
	if(mFileReader->eof()) {
		cout<<"EOF reached"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (mFileReader->bad()) {
		cout<<"Bad bit set"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (mFileReader->fail()) {
		cout<<"Fail bit set"<<endl;
		exit(EXIT_FAILURE);
	}

	char current;
	FreqInfo* node;
	mFileReader->open();
	mFileReader->readByte(current);
	while (mFileReader->good()) {
		node = freqTable[current];
		for (int i = 0; i < node->fieldLength; i++) {
			mFileWriter->writeBit(node->bitField[i]);
		}
		mFileReader->readByte(current);
	}
	mFileWriter->close();
	mFileReader->close();
}

/***************************/
/** Decompression methods **/
/***************************/

// read in the prefix free tree from file to be decoded
void Huffman::readPrefixFreeTree() {
	if(mFileReader->eof()) {
		cout<<"EOF reached"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (mFileReader->bad()) {
		cout<<"Bad bit set"<<endl;
		exit(EXIT_FAILURE);
	}
	else if (mFileReader->fail()) {
		cout<<"Fail bit set"<<endl;
		exit(EXIT_FAILURE);
	}
	mRoot = new FreqInfo;
	parsePrefixFreeTree(mRoot);
}

// do a post order traversal and regenerate the prefix free tree
void Huffman::parsePrefixFreeTree(FreqInfo* root) {
	bool current; 
	mFileReader->readBit(current);
	// leaf node
	if (current) {
		 mFileReader->readByte((char&)root->codePoint);
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
		parsePrefixFreeTree(root->left);
		bitField[fieldLength++] = true;
		parsePrefixFreeTree(root->right);
	}
	fieldLength--;
}

// Go through the remaining file and regenerate the original
// characters.
void Huffman::decodeCompressedText(int charCount) {
	FreqInfo* current = mRoot;
	bool bit;
	while(charCount > 0) {
		if (current->left == NULL) {
			mFileWriter->writeByte(current->codePoint);
			charCount--;
			current = mRoot;
		}
		else {
			mFileReader->readBit(bit);
			if (bit) {
				current = current->right;
			}
			else {
				current = current->left;
			}
		}
	}
	mFileReader->close();
	mFileWriter->close();
}

/*******************/
/** Public methods */
/*******************/

void Huffman::encode() {
	unsigned int charCount = buildFrequencyTable();
	mFileWriter->writeInt(charCount);
	buildPrefixFreeTree();
	writePrefixFreeTree(mRoot);
	writeCompressedText();
	cout<<"Read bytes "<<inBytes<<"\tWrote bytes "<<outBytes<<endl;
}

void Huffman::decode() {
	mFileReader->open();
	int charCount; 
	mFileReader->readInt(charCount);
	readPrefixFreeTree();
	decodeCompressedText(charCount);
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
