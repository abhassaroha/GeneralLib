#include "FileBufferWriter.h"

#define CURRENT_BYTE(index) \
	(index/BYTE_SIZE)
#define CURRENT_BIT(index) \
	(index%BYTE_SIZE)

void FileBufferWriter::flushBuffer() {
	if (outBufferIndex != 0) {
		mStream.write(outBuffer, CURRENT_BYTE(outBufferIndex) + 1);
		outBufferIndex = 0;
	}
}
// keep appending to buffer till we have enough
// to flush it 
void FileBufferWriter::writeBit(bool bit) {
	char byte = outBuffer[CURRENT_BYTE(outBufferIndex)];
	if (CURRENT_BIT(outBufferIndex) == 0) byte = 0;
	byte = byte|bit<<CURRENT_BIT(outBufferIndex);
	if (++outBufferIndex == BUFFER_SIZE*BYTE_SIZE) {
		flushBuffer();
	}
}

// output the code point 
void FileBufferWriter::writeByte(unsigned char codePoint) {
	char byte;
	int currentBit = CURRENT_BIT(outBufferIndex);
	// incoming byte has to be split across two buffer bytes
	if (currentBit != 0) {
		byte = outBuffer[CURRENT_BYTE(outBufferIndex)];
		byte = byte|codePoint<<currentBit;
		outBufferIndex += BYTE_SIZE - currentBit;
		if (outBufferIndex == BUFFER_SIZE*BYTE_SIZE) {
			flushBuffer();
		}
		outBuffer[CURRENT_BYTE(outBufferIndex)] = codePoint>>(BYTE_SIZE - currentBit);
		outBufferIndex += currentBit;
	}
	else {
		outBuffer[CURRENT_BYTE(outBufferIndex)] = codePoint;	
		outBufferIndex += BYTE_SIZE;
		if (outBufferIndex == BUFFER_SIZE*BYTE_SIZE) {
			flushBuffer();
		}
	}
}
