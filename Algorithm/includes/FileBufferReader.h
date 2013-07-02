#ifndef __FILE_BUFFER_READER_H
#define __FILE_BUFFER_READER_H

class FileBufferReader {
	private:
		char* mFileName;
		ifstream mStream;
		char* mBuffer;
		int mBufferIndex;
public:
		FileBufferReader(char* fileName):mFileName(fileName) {};
		bool isGood();
		bool readBit();
		bool readByte();
};

#endif
