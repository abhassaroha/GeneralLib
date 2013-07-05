#include "FileBufferWriter.h"

void FileBufferWriter::open() {
	mStream.open(mFileName, ios::binary|ios::out);	
}

void FileBufferWriter::close() {
	flushBuffer();
	mStream.close();	
}

void FileBufferWriter::flushBuffer() {
	if (mBufferIndex != 0) {
		mStream.write(mBuffer, CURRENT_BYTE(mBufferIndex) + 1);
		mBufferIndex = 0;
	}
}

// keep appending to buffer till we have enough
// to flush it 
void FileBufferWriter::writeBit(bool bit) {
	char byte = mBuffer[CURRENT_BYTE(mBufferIndex)];
	if (CURRENT_BIT(mBufferIndex) == 0) byte = 0;
	// not casting as left shift of signed and unsigned 
	// are equivalent
	byte = byte|bit<<CURRENT_BIT(mBufferIndex);
	if (++mBufferIndex == BUFFER_SIZE*BYTE_SIZE) {
		flushBuffer();
	}
}

// output the code point 
void FileBufferWriter::writeByte(unsigned char codePoint) {
	char byte;
	int currentBit = CURRENT_BIT(mBufferIndex);
	if (currentBit == 0) {
		mBuffer[CURRENT_BYTE(mBufferIndex)] = codePoint;	
		mBufferIndex += BYTE_SIZE;
		if (mBufferIndex == BUFFER_SIZE*BYTE_SIZE) {
			flushBuffer();
		}
	}
	else { // incoming byte has to be split across two buffer bytes
		byte = mBuffer[CURRENT_BYTE(mBufferIndex)];
		byte = byte|codePoint<<currentBit;
		mBufferIndex += BYTE_SIZE - currentBit;
		if (mBufferIndex == BUFFER_SIZE*BYTE_SIZE) {
			flushBuffer();
		}
		mBuffer[CURRENT_BYTE(mBufferIndex)] = codePoint>>(BYTE_SIZE - currentBit);
		mBufferIndex += currentBit;
	}
}

void FileBufferWriter::writeInt(int value) {
	writeByte((unsigned char) value);
	value = value>>BYTE_SIZE;
	writeByte((unsigned char) value);
	value = value>>BYTE_SIZE;
	writeByte((unsigned char) value);
	value = value>>BYTE_SIZE;
	writeByte((unsigned char) value);
}
