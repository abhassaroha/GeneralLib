#include <cstdlib>
#include <cfloat>
#define MAX_ULPS 5

// Never thought float equality could be this complex :|
// http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
bool compareFloats(float numA, float numB, float maxAbsolute = FLT_EPSILON, int maxUlps = MAX_ULPS);