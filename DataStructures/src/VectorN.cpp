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
	
	bool VectorN::checkDimensions(const VectorN& that) {
		bool result = true;
		if (mSize != that.mSize) {
			cout<<"Dimensions mismatch"<<endl;
			result = false;
		}
		return result;
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
		if (checkDimensions(that)) {
			std::swap(mSize, that.mSize);
			std::swap(mNorm, that.mNorm);
			std::swap(mDirty, that.mDirty);
			std::swap(mCoords, that.mCoords);			
		}
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
	
	VectorN VectorN::crossProduct(const VectorN& that) {
		VectorN result(mSize);
		return result;
	}
	
	VectorN& VectorN::scalarMult(float scale) {
		mNorm *= scale;
		for (int i = 0; i < mSize; i++)
			mCoords[i] *= scale;
		return *this;
	}
	
	VectorN VectorN::operator+(const VectorN& that) {
		VectorN result(mSize);
		for (int i = 0; i < mSize; i++)
			result.mCoords[i] = mCoords[i] + that.mCoords[i];
		result.mDirty = true;
		return result;
	}
	
	VectorN VectorN::operator-(const VectorN& that) {
		VectorN result(mSize);
		for (int i = 0; i < mSize; i++)
			result.mCoords[i] = mCoords[i] - that.mCoords[i];
		result.mDirty = true;
		return result;
	}
	
	bool VectorN::operator==(const VectorN& that) {
		bool result = true;
		for (int i = 0; i < mSize; i++) {
			if (!compareFloats(mCoords[i], that.mCoords[i])) {
				result = false;
				break;
			}
		}
		return result;	
	}
	
	ostream& operator<<(ostream& stream, const VectorN& vec) {
		for (int i = 0; i < vec.mSize; i++)
			stream<<vec.mCoords[i]<<" ";
		return stream;
	}
}

using namespace datastructures;

int main(int argc, char** argv) {
	float data[] = {1.0f, 1.0f, 1.0f};
	VectorN vec3First(data, 3);
	VectorN vec3Second(vec3First);
	vec3First.scalarMult(2.0f);
	VectorN vec3Add = vec3Second + vec3Second;
	VectorN vec3Sub = vec3First - vec3Second;
	cout<<"First "<<vec3First<<endl;
	cout<<"Second "<<vec3Second<<endl;
	cout<<"Add "<<vec3Add<<endl;
	cout<<"Sub "<<vec3Sub<<endl;
	cout<<(vec3Second == vec3Sub)<<endl;
	return 0;
}
