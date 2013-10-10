#include "VectorN.h"
namespace datastructures {
	/*********************/
	/** Private methods **/
	/*********************/
	VectorN::VectorN(int size) {
		mCoords = new float[size];
		mSize = size;
		mDirty = false;
		mNorm = 0.0f;
	}
	// VectorN::VectorN(float *coords, float norm, int size) {
	// 	VectorN result(coords, size, true);
	// 	result.mNorm = norm;
	// }
	
	/********************/
	/** Public methods **/
	/********************/
	VectorN::VectorN(float* coords, int size) {
		mCoords = new float[size];
		mSize = size;
		mDirty = true;
		for (int i = 0; i < size; i++)
			mCoords[i] = coords[i];		
	}
	
	VectorN::VectorN(const VectorN& that) {
		mNorm = that.mNorm;
		mSize = that.mSize;
		mCoords = new float[mSize];
		mDirty = that.mDirty;
		for (int i = 0; i < mSize; i++)
			mCoords[i] = that.mCoords[i];
	}
	
	VectorN& VectorN::operator=(VectorN that) {
		std::swap(mSize, that.mSize);
		std::swap(mNorm, that.mNorm);
		std::swap(mDirty, that.mDirty);
		std::swap(mCoords, that.mCoords);
		return *this;
	}
	
	float VectorN::norm() {
		if (mDirty) {
			mNorm = 0.0f;
			for (int i = 0; i < mSize; i++)
				mNorm += mCoords[i]*mCoords[i];
			mNorm = sqrt(mNorm);
			mDirty = false;
		}
		return mNorm;
	}
	
	float VectorN::dotProduct(const VectorN& that) {
		float result = 0.0f;
		for (int i = 0; i < mSize; i++)
			result += mCoords[i]*that.mCoords[i];
		return result;
	}
	
	VectorN* VectorN::crossProduct(const VectorN& that) {
		return NULL;
	}
}

int main(int argc, char** argv) {
	return 0;
}
