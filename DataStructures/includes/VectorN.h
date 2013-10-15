#include <cmath>
#include <algorithm>
#include <iostream>
#include "FloatEquality.h"

using namespace std;
/**
 * Class which represents an N dimensional vector.
 */
namespace datastructures {
	class VectorN {
	private:
		float* mCoords;
		float mNorm;
		int mSize;
		bool mDirty;
		VectorN(int size);
		bool checkDimensions(const VectorN&);
		// VectorN(float*, float, int);
	public:
		VectorN(float* coords, int size);
		VectorN(const VectorN&);
		VectorN& operator=(VectorN);
		~VectorN() { delete mCoords; };
		VectorN& direction() {
			return (new VectorN(mCoords, mSize))->scalarMult(1/mNorm);
		};
		float norm();
		float dotProduct(const VectorN&);
		VectorN crossProduct(const VectorN&);
		VectorN& scalarMult(float);
		VectorN operator+(const VectorN&);
		VectorN operator-(const VectorN&);
		bool operator==(const VectorN&);
		friend ostream& operator<<(ostream&, const VectorN&);
	};
}
