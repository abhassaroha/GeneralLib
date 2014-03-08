#ifndef HUFFMAN_QUEUE_H
#define HUFFMAN_QUEUE_H

#include "FreqInfo.h"

// Queue with assumption that we will never
// overflow and underflow.
namespace algorithms {
	class Queue {
		private:
			FreqInfo** mArray;
			int mLeft;
			int mRight;
		public:
			Queue(FreqInfo** array, int left, int right = -1):
				mArray(array), mLeft(left), mRight(right) {};

			FreqInfo* pop() {
				FreqInfo* result = NULL;
				if (this->good()) {
					result = mArray[mLeft];
					mLeft++;
				}
				return result;
			};

			void push(FreqInfo* elem) {
				mArray[++mRight] = elem;
			};

			FreqInfo* peek() {
				FreqInfo* result = NULL;
				result = mArray[mLeft];
				return result;
			};

			bool good() {
				return (mLeft <= mRight);
			};

			int size() {
				int result = mRight - mLeft + 1;
				if (result < 0) result = 0;
				return result;
			}
	};
}

#endif
