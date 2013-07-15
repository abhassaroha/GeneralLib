#ifndef FREQ_INFO_H
#define FREQ_INFO_H

struct FreqInfo {
	unsigned char codePoint;
	bool* bitField;
	int fieldLength;
	int freq;
	FreqInfo* left;
	FreqInfo* right;
	FreqInfo() {
		freq = 0;
		left = NULL;
		right = NULL;
		bitField = NULL;
	}
};

#endif
