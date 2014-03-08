#include "FloatEquality.h"

union Float {
	Float(float val):f(val) {};
	int i;
	float f;
	bool negative() { return i >> 31;}
};

bool compareFloats(float A, float B, float maxAbsolute /* = FLT_EPSILON */, int maxUlps /* = MAX_ULPS */) {
	bool result = false;
	if (abs(A - B) < maxAbsolute) { 
		result = true;
	}
	else {
		Float fltA(A);
		Float fltB(B);
		if (fltA.negative() == fltB.negative() 
			&& abs(fltA.i - fltB.i) < maxUlps) 
			result = true;		
	}
	return result;
}
