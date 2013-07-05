#include "FileBufferReader.h"

void FileBufferReader::open() {
	mStream.open(mFileName, ios::binary|ios::in);
}

void FileBufferReader::close() {
	mStream.close();	
}

bool FileBufferReader::good() {
	return mStream.good() || mBufferIndex < mReadBytes*BYTE_SIZE;
}

bool FileBufferReader::fail() {
	return mStream.fail();
}

bool FileBufferReader::bad() {
	return mStream.bad();
}

bool FileBufferReader::eof() {
	return mStream.eof();
}

void FileBufferReader::readBit(bool& bit) {
	char byte;
	if (mBufferIndex == mReadBytes*BYTE_SIZE) {
		if (mStream.good()) {
			mStream.read(mBuffer, BUFFER_SIZE);
			mReadBytes = mStream.gcount();
			mBufferIndex = 0;
		}
		else  {
			mReadBytes = 0;
			mBufferIndex = 0;
			return;
		}
	}
	int mask = 1<<CURRENT_BIT(mBufferIndex);
	byte = mBuffer[CURRENT_BYTE(mBufferIndex)];
	mBufferIndex++;
	bit = byte&mask;
}

void FileBufferReader::readByte(char& byte) {
	byte = 0;
	int currentBit;
	// buffer reached end, read more from file
	if (mBufferIndex == mReadBytes*BYTE_SIZE) {
		if (mStream.good()) {
			mStream.read(mBuffer, BUFFER_SIZE);
			mBufferIndex = 0;
			mReadBytes = mStream.gcount();
			if (mReadBytes != 0) {
				byte = mBuffer[0];
				mBufferIndex += BYTE_SIZE;
			}
		}
		else {
			mReadBytes = 0;
			mBufferIndex = 0;
		}
	} 
	else { // buffer has not reached end 
		byte = (unsigned char) mBuffer[CURRENT_BYTE(mBufferIndex)];
		currentBit = CURRENT_BIT(mBufferIndex);
		byte = ((unsigned char)byte)>>currentBit;
		mBufferIndex += BYTE_SIZE - currentBit;
		if (mBufferIndex == mReadBytes*BYTE_SIZE) {
			if (mStream.good()) {
				mStream.read(mBuffer, BUFFER_SIZE);
				mBufferIndex = 0;
				mReadBytes = mStream.gcount();
				// not casting as left shift of signed and unsigned 
				// are equivalent
				byte = byte|mBuffer[0]<<(BYTE_SIZE - currentBit);
			}
			else {
				mReadBytes = 0;
				mBufferIndex = 0;
			}
		}
		else {
			// not casting as left shift of signed and unsigned 
			// are equivalent
			byte = byte|mBuffer[CURRENT_BYTE(mBufferIndex)]<<(BYTE_SIZE - currentBit);
		}
	}
}

void FileBufferReader::readInt(int& result) {
	char byte; 
	readByte(byte);
	result = byte;
	readByte(byte);
	result = byte<<BYTE_SIZE|result;
	readByte(byte);
	result = byte<<2*BYTE_SIZE|result;
	readByte(byte);
	result = byte<<3*BYTE_SIZE|result;
}
