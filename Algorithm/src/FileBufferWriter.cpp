#include "FileBufferWriter.h"

void FileBufferWriter::open() {
	mBufferIndex = 0;
	mOutBytes = 0;
	mStream.open(mFileName, ios::binary|ios::out);	
}

void FileBufferWriter::close() {
	flushBuffer();
	mStream.close();	
}

void FileBufferWriter::flushBuffer() {
	int size = CURRENT_BYTE(mBufferIndex);
	if (mBufferIndex != 0) {
		if (CURRENT_BIT(mBufferIndex) != 0) size++;
		mStream.write(mBuffer, size);
		mOutBytes += size;
		mBufferIndex = 0;
	}
}

// keep appending to buffer till we have enough
// to flush it 
void FileBufferWriter::writeBit(bool bit) {
	char byte = mBuffer[CURRENT_BYTE(mBufferIndex)];
	if (CURRENT_BIT(mBufferIndex) == 0) byte = 0;
	byte = byte|bit<<CURRENT_BIT(mBufferIndex);
	mBuffer[CURRENT_BYTE(mBufferIndex)] = byte;
	if (++mBufferIndex == BUFFER_SIZE*BYTE_SIZE) {
		flushBuffer();
	}
}

// output the code point 
void FileBufferWriter::writeByte(char codePoint) {
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
		mBuffer[CURRENT_BYTE(mBufferIndex)] = byte;
		mBufferIndex += BYTE_SIZE - currentBit;
		if (mBufferIndex == BUFFER_SIZE*BYTE_SIZE) {
			flushBuffer();
		}
		// unsigned char, will be padded with 0's
		mBuffer[CURRENT_BYTE(mBufferIndex)] = 
		(unsigned char)codePoint>>(BYTE_SIZE - currentBit);
		mBufferIndex += currentBit;
	}
}

void FileBufferWriter::writeInt(unsigned int value) {
	writeByte(value&0xFF);
	value = value>>BYTE_SIZE;
	writeByte(value&0xFF);
	value = value>>BYTE_SIZE;
	writeByte(value&0xFF);
	value = value>>BYTE_SIZE;
	writeByte(value&0xFF);
}
